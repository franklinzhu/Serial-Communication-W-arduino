//4x4 Physical Installation
//Fengyi Zhu
//fengyizhu.com/4x4
//Simply a sample of receiving data from computer and apply the data to each servo motor
//Adafruit PWM librabry was used for driving 16 servos on the PWM servo driver 


#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)

String testString;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
}

void loop() {
  digitalWrite(13, HIGH);
  //delay(1000);
  //digitalWrite(13, LOW);
  //  delay(1000);
  if (Serial.available() > 0) {
    testString = Serial.readStringUntil('\n');
    if (testString.startsWith("[") && testString.endsWith("]")) {
//      int closingBracketIndex = testString.lastIndexOf("]");
//      testString.remove(closingBracketIndex);
//      testString.remove(0);
      for (int i = 0; i < 16; i++) {
        int value;
        if (i == 0) {
          int endIndex = 1;
          while (testString.charAt(endIndex) != ',') {
            endIndex ++;
          }
          value = testString.substring(1, endIndex).toInt();
        } else {
          value = getValue(testString, ',', i).toInt();
        }

        // remap the input value
//        double perc = (double)value / 80.0;
//        perc = pow(perc, 2);
//        int newValue = perc * 80;

        // map and write the value to the respective servo
        pwm.setPWM(i, 0, map(value, 0, 3, SERVOMIN, SERVOMAX));
      }
    }
  }
}

// "1,2,234,23451,153".split(',');

String getValue(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = { 0, -1  };
  int maxIndex = data.length() - 1;
  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
