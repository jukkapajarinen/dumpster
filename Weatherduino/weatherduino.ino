#include <dht.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
dht DHT;

void setup(){
  lcd.begin(16, 2);
  lcd.print("Sensor error");
}

void loop()
{
  int val = DHT.read11(2);
  if (val == 0 || val == -1) 
  {
    lcd.clear();
    lcd.home();
    lcd.print("Tem: ");
    lcd.print(DHT.temperature);
    lcd.print(char(223));
    lcd.print("C");
    lcd.setCursor(0, 1);
    lcd.print("Hum: ");
    lcd.print(DHT.humidity);
    lcd.print("%");
  }
  delay(1000);
}

