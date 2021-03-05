/*
 - Nut bam:
      + nút bấm 1 chân nối chân pin2 và điện trở nối GND. Chân còn lại nối 5V
 - nhiệt độ : pin 4;
 - lcd : 
      + SCL : a5
      + SDA : a4
  - dien tro: 
      + chan giua noi V0 cua LCD
 */
#include <DHT.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
int  nutbam = 2;
int value = 0; 
#define  DHT11Pin 4
#define DHTType DHT11
DHT HT(DHT11Pin,DHTType);

byte degree[8] = {
  0B01110,
  0B01010,
  0B01110,    
  0B00000,
  0B00000,
  0B00000,
  0B00000,
  0B00000
};

void setup() {
  Serial.begin(9600);
  pinMode(nutbam,INPUT);
  lcd.init();  
  lcd.backlight();
  
  lcd.createChar(1, degree);

  HT.begin(); 
   
}

void loop() {
  int v = digitalRead(nutbam);
  Serial.println(v);
  float t = HT.readTemperature();
  if(check(v) == 1){
    value = abs(value - 1);
  }
  lcd.setCursor(0,0);

  if (isnan(t)) { // Kiểm tra xem thử việc đọc giá trị có bị thất bại hay không. Hàm isnan bạn xem tại đây http://arduino.vn/reference/isnan

  } 
  else {
    if(value == 0)
    {
    lcd.print("Do C: ");
    lcd.print(round(t));
    lcd.print(" C");
    }
    else   
    {
    lcd.print("Do F: ");
    lcd.print(round(t*1.8+32));
    lcd.print(" F"); 
    }   
  }
  delay(300);
}

int check( int v){
  if(v == 1){
    return 1;
  }
  else{
    return 0;
  }
}
