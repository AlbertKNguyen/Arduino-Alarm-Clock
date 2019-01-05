
// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 1, en = 0;
LiquidCrystal lcd(en, rs, 2, 3, 4, 5); // lcd constructor setup

const int LED = 13; // led pin
const int BACKLIGHT = 8; // lcd backlight pin
const int BUZZER = 7; // buzzer pin
const int BUTTON = 9; // button pin
const int startTime = 5; // bomb timer
int pos = 7;  // countdown number position on lcd

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

    // countdown to 1 with beeps/lcd blinks as each number counts down
    for(int countDown = startTime; countDown > 0; countDown--)
    {
      if(countDown < 10){ //centers countdown number when number becomes single digit
        pos = 8;
      }
      lcd.setCursor(1, 0);
      lcd.print("Detonation in:");
      lcd.setCursor(pos, 1);
      tone(BUZZER, 1600, 10);
      lcd.print(countDown);
      digitalWrite(LED, HIGH);
      delay(500);
      lcd.clear();
      digitalWrite(LED, LOW);
      delay(500);
    }  

    // prints 0 countdown
    lcd.setCursor(1, 0);
    lcd.print("Detonation in:");
    lcd.setCursor(pos, 1);
    lcd.print("0");

    // warning beeps
    for(int countDown = 10; countDown > 0; countDown--)
    {
      tone(BUZZER, 400, 100);
      digitalWrite(BACKLIGHT, HIGH);
      digitalWrite(LED, HIGH); 
      delay(75);
      digitalWrite(BACKLIGHT, LOW);
      digitalWrite(LED, LOW);
      delay(75);
    }

    // explosion
    digitalWrite(BACKLIGHT, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("BOOOOOOOOOOOOOOO");
    lcd.setCursor(0, 1);
    lcd.print("OOOOOOOOOOOOOOOM");
    digitalWrite(LED, HIGH); 
    tone(BUZZER, 50,2000);
    delay(2000);
    digitalWrite(LED, LOW); 

    // turn off lcd
    lcd.clear();
    digitalWrite(BACKLIGHT, LOW);
}
