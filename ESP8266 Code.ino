#include<ESP8266WiFi.h>
#include<ESP8266HTTPClient.h>
#include<ArduinoJson.h>

const char* ssid = "Redmi";
const char* password = "pushpak02";
String payload;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(1000);
    Serial.print("Connecting");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if(WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;
    http.begin("http://api.openweathermap.org/data/2.5/weather?id=1254710&appid=78ea82b1e35e18631379fdc64f5e02bf");
    int httpCode = http.GET();
    if(httpCode > 0)
    {
      //payload = http.getString();
      //Serial.println(payload);
      const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + 2*JSON_OBJECT_SIZE(2) + 2*JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(7) + JSON_OBJECT_SIZE(11) + 410;
      DynamicJsonBuffer jsonBuffer(capacity);
      JsonObject& root = jsonBuffer.parseObject(http.getString());
      JsonObject& weather_0 = root["weather"][0];
      const char* weather_0_main = weather_0["main"];
      JsonObject& main = root["main"];
      float main_temp = main["temp"];
      int main_humidity = main["humidity"];
      const char* name = root["name"];
      Serial.print(weather_0_main);
      Serial.print(' ');
      delay(1000);
      Serial.print(main_temp);
      Serial.print(' ');
      delay(1000);
      Serial.print(main_humidity);
      Serial.print(' ');
      delay(1000);
      Serial.print(name);
      Serial.print(' ');
      delay(1000);
    }
    http.end();
  }
  delay(10000);
}
