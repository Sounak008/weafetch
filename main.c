#include "api.h"
#include <stdio.h>
#include <string.h>

void print_weather_ascii(int condition_code) {

  printf("\n");

  switch (condition_code) {
  case 1000: // Sunny / Clear
    printf("█▀ █░█ █▄░█ █▄░█ █▄█\n");
    printf("▄█ █▄█ █░▀█ █░▀█ ░█░\n");
    break;

  case 1003: // Partly cloudy
    printf("█▀█ ▄▀█ █▀█ ▀█▀ █░░ █▄█   █▀▀ █░░ █▀█ █░█ █▀▄ █▄█\n");
    printf("█▀▀ █▀█ █▀▄ ░█░ █▄▄ ░█░   █▄▄ █▄▄ █▄█ █▄█ █▄▀ ░█░\n");
    break;

  case 1006: // Cloudy
  case 1009: // Overcast
    printf("█▀▀ █░░ █▀█ █░█ █▀▄ █▄█\n");
    printf("█▄▄ █▄▄ █▄█ █▄█ █▄▀ ░█░");
    break;

  case 1183: // Light rain
  case 1189: // Moderate rain
  case 1195: // Heavy rain
    printf("█▀█ ▄▀█ █ █▄░█ █▄█\n");
    printf("█▀▄ █▀█ █ █░▀█ ░█░\n");
    break;

  case 1114: // Blowing snow
  case 1213: // Light snow
  case 1219: // Moderate snow
  case 1225: // Heavy snow
    printf("█▀ █▄░█ █▀█ █░█░█\n");
    printf("▄█ █░▀█ █▄█ ▀▄▀▄▀\n");
    break;

  case 1087: // Thundery outbreaks possible
  case 1276: // Moderate or heavy rain with thunder
    printf("▀█▀ █░█ █░█ █▄░█ █▀▄ █▀▀ █▀█\n");
    printf("░█░ █▀█ █▄█ █░▀█ █▄▀ ██▄ █▀▄\n");
    break;

  default:
    printf("█▄░█ █▀█ ▀█▀   █▀▀ █▀█ █░█ █▄░█ █▀▄\n");
    printf("█░▀█ █▄█ ░█░   █▀░ █▄█ █▄█ █░▀█ █▄▀\n");
    break;
  }
  printf("\n");
}

static void print_usage(const char *prog) {
  fprintf(stderr, "Usage: %s -t <city name>\n", prog);
  fprintf(stderr, "Example: %s -t \"New York\"\n", prog);
  fprintf(stderr, "         %s -t London\n", prog);
}

int main(int argc, char *argv[]) {
  const char *city = NULL;

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-t") == 0) {
      if (i + 1 < argc) {
        city = argv[++i];
      } else {
        fprintf(stderr, "Error: -t requires a city name.\n");
        print_usage(argv[0]);
        return 1;
      }
    } else {
      fprintf(stderr, "Error: unknown flag '%s'.\n", argv[i]);
      print_usage(argv[0]);
      return 1;
    }
  }

  if (!city) {
    fprintf(stderr, "Error: no city specified.\n");
    print_usage(argv[0]);
    return 1;
  }

  if (fetch_current_weather(city) != 0) {
    fprintf(stderr, "Could not retrieve weather data. "
                    "Check the city name and your API key.\n");
    return 1;
  }

  print_weather_ascii(code);
  printf("Temperature    : %.1f °C\n", temp_c);
  printf("Feels Like     : %.1f °C\n", feelslike_c);
  printf("Humidity       : %d%%\n", humidity);
  printf("Precipitation  : %.1f mm\n", precip_mm);
  printf("Wind Direction : %s\n", wind_dir);

  return 0;
}
