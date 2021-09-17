#include<SoftwareSerial.h>
#include<LiquidCrystal.h>
const int rs = 8, en = 9, d4 =10, d5 = 11, d6 = 12, d7 =13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

SoftwareSerial ESP_Serial(6,7); //Tx, Rx

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  lcd.print("Hi! Good Day!");
  Serial.begin(115200);
  ESP_Serial.begin(9600);
  delay(20000);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  String main;
  String temperature;
  String humidity;
  String city;
  String payload;
  int i=0, j=0, starting = 0;
  int temp_celsius = 0;
  //Serial.println(ESP_Serial.available());
  //lcd.clear();
  while(ESP_Serial.available() > 0)
  {
    starting = 0;
    i = 0;
    payload=ESP_Serial.readString();
    while(i < payload.length())
    {
      if(payload[i] == ' ')
      {
        break;
      }
      i++;
    }
    main = payload.substring(starting, i);
    i += 1;
    starting = i;
    while(i < payload.length())
    {
      if(payload[i] == ' ')
      {
        break;
      }
      i++;
    }
    temperature = payload.substring(starting,i);
    i += 1;
    starting = i;
    while(i < payload.length())
    {
      if(payload[i] == ' ')
      {
        break;
      }
      i++;
    }
    humidity = payload.substring(starting,i);
    i += 1;
    starting = i;
    while(i < payload.length())
    {
      if(payload[i] == ' ')
      {
        break;
      }
      i++;
    }
    city = payload.substring(starting,i);
    delay(10000);
    temp_celsius = (int)temperature.toFloat() - 273;
    Serial.println(main);
    Serial.println(temp_celsius);
    Serial.println(humidity);
    Serial.println(city);
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print(main);
    lcd.setCursor(0,1);
    lcd.print(temp_celsius);
    lcd.setCursor(2,1);
    lcd.print(char(223));
    lcd.print('C');
    lcd.setCursor(5,1);
    lcd.print(humidity);
    lcd.setCursor(7,1);
    lcd.print(char(37));
    lcd.setCursor(10,1);
    lcd.print(city);
  }
  delay(10000);
}
