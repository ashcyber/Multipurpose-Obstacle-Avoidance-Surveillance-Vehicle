// Include the LiquidCrystal.h
#include <LiquidCrystal.h>
#define LDRpin A0 
#define TempSen A1


// initialize the library with the numbers of the interface pins
// REGISTER SELECT PIN,ENABLE PIN,D4 PIN,D5 PIN, D6 PIN, D7 PIN

LiquidCrystal lcd(0, 1, 8, 9, 10, 11); 
int LDRValue = 0; 
int ld2=0;
//int ledPin = 13;
float temppin=0;
void setup() {

// Set up the LCD's number of columns and rows:

lcd.begin(16, 2);
lcd.print("Light  Temp ");

}

void loop() {
  temppin=analogRead(TempSen);
  temppin=temppin*0.48828125;
  LDRValue = analogRead(LDRpin)/10;
  ld2=LDRValue/1.02;
  lcd.setCursor(0,1);
  lcd.print(ld2);     
  lcd.print("%");
  lcd.setCursor(6,1); 
  lcd.print(temppin);
  lcd.print(" *C");
  delay(100);  
  lcd.print("");
  delay(1);

  if(LDRValue < 15){
      digitalWrite(ledPin,HIGH); 
  }else{
      digitalWrite(ledPin,LOW);
  }                           

// set the cursor to column 0, line 1
lcd.print("   CIRCUIT DIGEST");

// set the cursor to column 0, line 2
lcd.setCursor(0, 1); 

lcd.print(LDRValue);//print name

delay(750);
  
//shifting data on LCD
lcd.scrollDisplayLeft();

// set the cursor to column 0, line1
lcd.setCursor(0, 0);

}
