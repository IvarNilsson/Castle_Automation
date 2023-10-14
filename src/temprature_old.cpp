#include "Arduino.h"
#include "esp_adc_cal.h"
#include "HTTPClient.h"
#include "WiFi.h"
#include "time.h"

// WiFi credentials
const char* ssid = "AASUS";
const char* password = "IvarNilsson/731";
String GOOGLE_SCRIPT_ID = "AKfycbxg2BERYfP52cQ24AArzivcLRKf5uWEbjZndT5ApzRn_9yLrG9fF6dHslxhRxekzpngGQ";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;

WiFiClientSecure client;
#define LM35_Sensor1 35

int LM35_Raw_Sensor1 = 0;
float LM35_TempC_Sensor1 = 0.0;
float Voltage = 0.0;

void setup() {
  Serial.begin(115200);
  delay(1000);

  
    // connect to WiFi
    Serial.println();
    Serial.print("Connecting to wifi: ");
    Serial.println(ssid);
    Serial.flush();
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    }

    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  
  Serial.println("Ready to go");
}

void loop() {

  LM35_Raw_Sensor1 = analogRead(LM35_Sensor1);
  Voltage = readADC_Cal(LM35_Raw_Sensor1);
  LM35_TempC_Sensor1 = Voltage / 10;
  Serial.print(LM35_TempC_Sensor1);
  Serial.println(" °C , ");
    if (WiFi.status() == WL_CONNECTED) {
      static bool flag = false;
      struct tm timeinfo;
      if (!getLocalTime(&timeinfo)) {
        Serial.println("Failed to obtain time");
        return;
      }

      String date_time;
      //
      char timeStringBuff[50]; //50 chars should be enough
      strftime(timeStringBuff, sizeof(timeStringBuff), "%Y", &timeinfo);
      String asString_year(timeStringBuff);
      date_time = asString_year;

      strftime(timeStringBuff, sizeof(timeStringBuff), "%B", &timeinfo);
      String asString_month(timeStringBuff);
      date_time += (String)getMonthasInt(asString_month.c_str());

      strftime(timeStringBuff, sizeof(timeStringBuff), "%d", &timeinfo);
      String asString_day(timeStringBuff);
      date_time += asString_day;

      strftime(timeStringBuff, sizeof(timeStringBuff), "%H", &timeinfo);
      String asString_hour(timeStringBuff);
      date_time += asString_hour;

      strftime(timeStringBuff, sizeof(timeStringBuff), "%M", &timeinfo);
      String asString_min(timeStringBuff);
      date_time += asString_min;

      strftime(timeStringBuff, sizeof(timeStringBuff), "%S", &timeinfo);
      String asString_sec(timeStringBuff);
      date_time += asString_sec;


      date_time.replace("-", "");
      Serial.print("date_time ");
      Serial.println(date_time);


      String urlFinal = "https://script.google.com/macros/s/" + GOOGLE_SCRIPT_ID + "/exec?" + "date=" + (String)date_time + "&sensor=" + (String)LM35_TempC_Sensor1;
      Serial.print("POST data to spreadsheet:");
      Serial.println(urlFinal);
      HTTPClient http;
      http.begin(urlFinal.c_str());
      http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
      int httpCode = http.GET();
      Serial.print("HTTP Status Code: ");
      Serial.println(httpCode);
      //---------------------------------------------------------------------
      //getting response from google sheet
      String payload;
      if (httpCode > 0) {
        payload = http.getString();
        //Serial.println("Payload: " + payload);
      }
      //---------------------------------------------------------------------
      http.end();
    }
  //delay(300*1000);
}

int getMonthasInt(const char *monthString)
{
  switch ( *(monthString) )
  {
    case 'J':
      switch ( *(monthString + 3) )
      {
        case 'u':
          return (1);       /* JanUary */
        case 'e':
          return (6);       /* JunE */
        case 'y':
          return (7);       /* JulY */
      }
    case 'F':
      return (2);               /* February */
    case 'M':
      switch ( *(monthString + 2) )
      {
        case 'r':
          return (3);       /* MaRch */
        case 'y':
          return (5);       /* MaY */
      }
    case 'A':
      switch ( *(monthString + 1) )
      {
        case 'p':
          return (4);       /* APril */
        case 'u':
          return (8);       /* AUgust */
      }
    case 'S':
      return (9);               /* September */
    case 'O':
      return (10);               /* October */
    case 'N':
      return (11);               /* November */
    case 'D':
      return (12);               /* December */
  }
  return (-1);
}

uint32_t readADC_Cal(int ADC_Raw) {
  esp_adc_cal_characteristics_t adc_chars;

  esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 1100, &adc_chars);
  return (esp_adc_cal_raw_to_voltage(ADC_Raw, &adc_chars));
}