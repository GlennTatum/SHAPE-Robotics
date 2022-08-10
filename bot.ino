/*
 * This file can be found originally authored and written at https://github.com/GlennTatum/SHAPE-Robotics
 * 
 * This program is free software:you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This arduino program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 * 
 */


// Line tracker module

// Line tracker module sensor left
#define LTL A2
// Line tracker module sensor middle
#define LTM A1
// Line tracker module sensor right
#define LTR A0

// Infared heat sensor
#define HEAT A5

// I/O Board Motor control

// Standby
#define STBY 3

// RIGHT Motor
#define PWMA 5
// RIGHT motor voltage control
#define AI 8

//LEFT Motor
#define PWMB 6
// LEFT motor voltage control
#define BI 7

#define SPEED 35

void setup() {
  Serial.begin(9600);

  // Line tracking Module
  pinMode(LTL, INPUT);
  pinMode(LTM, INPUT);
  pinMode(LTR, INPUT);

  pinMode(STBY, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(AI, OUTPUT);
  pinMode(BI, OUTPUT);
}

void loop() {
  
    if (analogRead(LTL) > 600 && analogRead(LTR) > 600) {
      left();
      stats();
    }
    
    else if (analogRead(LTM) > 400) {
      forward();
      stats();
    }

    else {
      right();
      delay(200);  
      stats();
    }
    
  // Flame Detector

   /*
   * Primary Maze loop
   * While the Fire is not detected keep searching for the flame until it is detected
   */
  
  /*
    while (analogRead(HEAT) > 1010) {
    Serial.println("    Candle not close");
    stats();
    
  }

  // If the flame is close start the encounter to the flame

  if (analogRead(HEAT) < 1010) {
    Serial.println("    Candle is close");

    // Candle is very close and over te wet towel

    if (analogRead(HEAT) < 1005) {
      Serial.println("    Candle can be extinguished");
    }
    
    stats();
  }
  */
}

// Functions must be declared outside of the main loop in an arduino sketch

// Logging stats

void stats() {

  Serial.print("    LEFT SENSOR = ");
  Serial.print(analogRead(LTL));
  
  Serial.print("    MIDDLE SENSOR = ");
  Serial.print(analogRead(LTM));

  Serial.print("    RIGHT SENSOR = ");
  Serial.print(analogRead(LTR));

  Serial.print("    HEAT SENSOR = ");
  Serial.println(analogRead(HEAT));
}

// Foward

void forward() {
  digitalWrite(STBY, HIGH);
  
  digitalWrite(AI, HIGH);
  digitalWrite(BI, HIGH);
  analogWrite(PWMA, SPEED);
  analogWrite(PWMB, SPEED);
}

void backwards() {
  digitalWrite(STBY, HIGH);
  
  digitalWrite(AI, LOW);
  digitalWrite(BI, LOW);
  analogWrite(PWMA, SPEED);
  analogWrite(PWMB, SPEED);
  
}

void left() {
  digitalWrite(STBY, HIGH);
  
  digitalWrite(AI, LOW);
  digitalWrite(BI, HIGH);
  analogWrite(PWMA, SPEED);
  analogWrite(PWMB, SPEED);
}

void right() {
  digitalWrite(STBY, HIGH);
  digitalWrite(AI, HIGH);
  digitalWrite(BI, LOW);
  analogWrite(PWMA, SPEED);
  analogWrite(PWMB, SPEED);
}

void breaks() {
  digitalWrite(STBY, HIGH);
  
  digitalWrite(AI, HIGH);
  digitalWrite(BI, HIGH);
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
}
