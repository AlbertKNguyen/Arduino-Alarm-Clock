#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 1, en = 0;
LiquidCrystal lcd(en, rs, 2, 3, 4, 5); // lcd constructor setup

const int LED = 13; // led pin
const int BACKLIGHT = 8; // lcd backlight pin
const int BUZZER = 7; // buzzer pin
const int BUTTON = 9; // button pin

int hour = 5; //current hour
int minute = 37; //current minute
const int wakeUPIN = 5; // alarm will ring in x hours

void setup() {
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  pinMode (BUZZER, OUTPUT);
  pinMode (LED, OUTPUT);
  pinMode (BUTTON, INPUT);
  pinMode (BACKLIGHT, OUTPUT);
}


 void loop() {

    // wait for button press
    while(digitalRead(BUTTON) == LOW){
    delay(100);
    }

    // turn on lcd with delay
    delay(1000);
    digitalWrite(BACKLIGHT, HIGH);

    //sleep message
    lcd.setCursor(0, 1);
    lcd.print("zzzzzzzzzzzzzzzz");

    // wait...
    lcd.setCursor(5, 0);
    for(int countDown = wakeUPIN * 60; countDown > 0; countDown--)
    {
      if(hour >= 10) {
        lcd.setCursor(5, 0);
      } else {
        lcd.setCursor(6, 0);
      }
      lcd.print(hour);
      lcd.setCursor(7, 0);
      lcd.print(":");
      if(minute < 10) {
        lcd.setCursor(8, 0);
        lcd.print("0");
        lcd.setCursor(9, 0);
        lcd.print(minute);
      } else {
        lcd.setCursor(8, 0);
        lcd.print(minute);
      }
      delay(59990);
      minute++;
      if(minute == 60) {
        minute = 0;
        hour++;
        if(hour == 24) {
          hour = 0;
        }
      }
    }  

    // alarm
    while(digitalRead(BUTTON) == LOW){
      digitalWrite(BACKLIGHT, HIGH);
      lcd.setCursor(0, 1);
      lcd.print("!!!!WAKE  UP!!!!");
      digitalWrite(LED, HIGH); 
      tone(BUZZER, 50,2000);
      delay(500)
      digitalWrite(LED, LOW);
      digitalWrite(BACKLIGHT, LOW); 
    }
    
    // turn off lcd
    lcd.clear();
    digitalWrite(BACKLIGHT, LOW);
}
