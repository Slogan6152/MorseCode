#include <LiquidCrystal.h>
#include <MemoryFree.h>

String mletters[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", // A-I
  ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", // J-R
  "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.." // S-Z
};
String letters[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I",
                    "J", "K", "L", "M", "N", "O", "P", "Q", "R",
                    "S", "T", "U", "V", "W", "X", "Y", "Z" , "", ""
                   };
//LCD SCREEN
LiquidCrystal lcd(12,11,10,5,4,3,2);
int backLight = 13;

//MyoWare Threshold values
int thresholdLow = 200;
int thresholdHigh = 400;
int timediff = 600;


long uptime = 0;
int isup = 0;
String phrase = "";
int phraseindex = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(backLight, OUTPUT);
  digitalWrite(backLight, HIGH);
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0,0);
}

void loop() {
  // put your main code here, to run repeatedly:
  int valin = analogRead(A0);
  if (valin > thresholdHigh && isup == 0) {
    //Serial.println("High");
    uptime = millis();
    isup = 1;
  }
  if (valin < thresholdLow && isup == 1 && uptime > 100) {
    isup = 0;
    if (millis() - uptime < timediff) {
      phrase += ".";
      //Serial.print(".");
    }
    else {
      phrase += "-";
      //Serial.print("-");
    }
  }
  if (isup == 0 && millis() - uptime > 2000) {
    findletter();
  }
  if (isup == 0 && millis() - uptime > 10000) {
    //lcd.clear();
    //lcd.setCursor(0,0);
  }
  //Serial.println(freeMemory());
  delay(1);
}


char findletter() {
  //Serial.println("");
  for (int i = 0; i < 26; i++) {
    if (phrase == mletters[i]) {
      Serial.println(letters[i]);
      lcd.print(letters[i]);
    }
  }
  uptime = millis();
//  lcd.show();
  phrase = "";
}
