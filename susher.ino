#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

int pirPin = 2;
int readPir;
int randNumber;
int redLed = 3;
int greenLed = 4;
int blueLed = 5;
int x;
int micPin = A0;

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

void printDetail(uint8_t type, int value);

void redOn(){
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, HIGH);
  digitalWrite(blueLed, HIGH);
}

void greenOn(){
  digitalWrite(redLed, HIGH);
  digitalWrite(greenLed, LOW);
  digitalWrite(blueLed, HIGH);
}

void blueOn(){
  digitalWrite(redLed, HIGH);
  digitalWrite(greenLed, HIGH);
  digitalWrite(blueLed, LOW);
}

void allOff(){
  digitalWrite(redLed, HIGH);
  digitalWrite(greenLed, HIGH);
  digitalWrite(blueLed, HIGH);
}
void setup()
{
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);
  pinMode(redLed, OUTPUT);
  digitalWrite(redLed, HIGH);
  pinMode(greenLed, OUTPUT);
  digitalWrite(greenLed, HIGH);
  pinMode(blueLed, OUTPUT);
  digitalWrite(blueLed, HIGH);
  pinMode(pirPin, INPUT);
  pinMode(micPin, INPUT);
  randomSeed(analogRead(0));
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
  myDFPlayer.volume(15);  //Set volume value. From 0 to 30
  
  for (x=1; x < 40; x++){
   blueOn();
   delay(500);
   allOff();
   delay(500);
  }
}

void loop()
{
  readPir = digitalRead(pirPin);
  if (readPir == HIGH) {
    redOn();
    randNumber = random(1,9);
    //Serial.println("Motion!");
    //Serial.println(randNumber);
    myDFPlayer.play(randNumber);
    delay(4000);
    allOff();
  } else {
    greenOn();
    //myDFPlayer.pause();
    //Serial.println("no motion");
    delay(1000);
    allOff();
  }
}

