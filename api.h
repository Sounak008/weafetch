#ifndef API_H
#define API_H

extern double temp_c;
extern double feelslike_c;
extern char   text[64];
extern int    humidity;
extern double precip_mm;
extern char   wind_dir[16];
extern int    code;

int fetch_current_weather(const char *city);

#endif
