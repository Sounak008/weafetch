#include "cJSON.h"
#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char response_buffer[8192];
size_t buffer_pos = 0;

size_t write_callback(void *received_data, size_t size, size_t nmemb,
                      void *userdata) {
  size_t bytes = size * nmemb;
  if (buffer_pos + bytes < sizeof(response_buffer) - 1) {
    memcpy(&response_buffer[buffer_pos], received_data, bytes);
    buffer_pos += bytes;
    response_buffer[buffer_pos] = '\0';
  }
  return bytes;
}

double temp_c = 0.0;
double feelslike_c = 0.0;
char text[64] = "N/A";
int humidity = 0;
double precip_mm = 0.0;
char wind_dir[16] = "N/A";
int code = 0;

int fetch_current_weather(const char *city) {
  CURL *curl;
  CURLcode res;

  buffer_pos = 0;
  response_buffer[0] = '\0';

  curl = curl_easy_init();
  if (curl) {
    char url[512];
    snprintf(url, sizeof(url),
             "https://api.weatherapi.com/v1/"
             "current.json?key=b6ea1a07136c4810acd50152260106&q=%s&aqi=no",
             city);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

    res = curl_easy_perform(curl);

    if (res == CURLE_OK) {
      cJSON *json = cJSON_Parse(response_buffer);

      if (json) {
        cJSON *current = cJSON_GetObjectItemCaseSensitive(json, "current");

        if (current) {
          cJSON *item;

          item = cJSON_GetObjectItemCaseSensitive(current, "temp_c");
          if (cJSON_IsNumber(item))
            temp_c = item->valuedouble;

          item = cJSON_GetObjectItemCaseSensitive(current, "feelslike_c");
          if (cJSON_IsNumber(item))
            feelslike_c = item->valuedouble;

          cJSON *condition =
              cJSON_GetObjectItemCaseSensitive(current, "condition");
          if (condition) {
            item = cJSON_GetObjectItemCaseSensitive(condition, "text");
            if (cJSON_IsString(item))
              strncpy(text, item->valuestring, sizeof(text) - 1);

            item = cJSON_GetObjectItemCaseSensitive(condition, "code");
            if (cJSON_IsNumber(item)) {
              code = item->valueint;
            }
          }

          item = cJSON_GetObjectItemCaseSensitive(current, "humidity");
          if (cJSON_IsNumber(item))
            humidity = item->valueint;

          item = cJSON_GetObjectItemCaseSensitive(current, "precip_mm");
          if (cJSON_IsNumber(item))
            precip_mm = item->valuedouble;

          item = cJSON_GetObjectItemCaseSensitive(current, "wind_dir");
          if (cJSON_IsString(item))
            strncpy(wind_dir, item->valuestring, sizeof(wind_dir) - 1);

        } else {
          printf("Error: API didn't return 'current' weather.\n");
          printf("Raw Response:\n%s\n", response_buffer);
        }
        cJSON_Delete(json);
      } else {
        printf("Error: Could not parse JSON data.\n");
      }
    } else {
      fprintf(stderr, "API Request failed: %s\n", curl_easy_strerror(res));
    }
    curl_easy_cleanup(curl);
  }
  return 0;
}
