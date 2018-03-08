#include <LiquidCrystal.h>
#define LDRpin A0 // pin where we connected the LDR and the resistor
#define TempSen A1


// initialize the library with the numbers of the interface pins

LiquidCrystal lcd(0, 1, 8, 9, 10, 11); /// REGISTER SELECT PIN,ENABLE PIN,D4 PIN,D5 PIN, D6 PIN, D7 PIN
int LDRValue = 0; 
int ld2=0;
//int ledPin = 13;
float temppin=0;
void setup()

{


  // set up the LCD's number of columns and rows:

lcd.begin(16, 2);
lcd.print("Light  Temp ");

}

 

void loop()

{
  temppin=analogRead(TempSen);
  temppin=temppin*0.48828125;
  LDRValue = analogRead(LDRpin)/10;
  ld2=LDRValue/1.02;
  lcd.setCursor(0,1);
lcd.print(ld2);     
lcd.print("%");
lcd.setCursor(6,1); 
lcd.print(temppin);
lcd.print(" *C");// read the value from the LDR
         
                                                         // print the value to the serial port
  delay(100);  
lcd.print("");
delay(1);
/*if(LDRValue < 15){
  digitalWrite(ledPin,HIGH); 
}else{
  digitalWrite(ledPin,LOW);
} */                           
// set the cursor to column 0, line 1

//lcd.print("   CIRCUIT DIGEST");//print name

//lcd.setCursor(0, 1); // set the cursor to column 0, line 2

//lcd.print(LDRValue);//print name

//delay(750);//delay of 0.75sec

//lcd.scrollDisplayLeft();//shifting data on LCD

//lcd.setCursor(0, 0);// set the cursor to column 0, line1

}
