#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define BLYNK_PRINT DebugSerial


// You could use a spare Hardware Serial on boards that have it (like Mega)
#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(0, 1); // RX, TX

#include <BlynkSimpleStream.h>
WidgetTerminal terminal(V10);
char auth[] = "33GFPAf3c4HAGktB2NGqeUNbdZf0P_7o";

LiquidCrystal_I2C lcd(0x27, 16, 2); // Define the LCD connections
int led1= 11;
int led2= 12;
const int sensor1Pin = 7; // Connect first IR sensor to digital pin 7
const int sensor2Pin = 6; // Connect second IR sensor to digital pin 6

BLYNK_WRITE(V10)
{
  String paramValue = param.asStr(); // Get the value sent from the widget

  // You can use a conditional statement to handle different values if needed
  if (paramValue == "sensor1") {
    int car1Status = digitalRead(sensor1Pin); // Read the status of sensor1

    // Update the Blynk widget with the status of sensor1
    Blynk.virtualWrite(V10, car1Status);

    // Optionally, you can also update the LCD or perform other actions based on the sensor status here.
  }
}
void setup() {
  lcd.init(); 
   lcd.backlight();  // Initialize the LCD
  lcd.setCursor(0, 0);
  lcd.print("Parking Status:");
  pinMode(sensor1Pin, INPUT);
  pinMode(sensor2Pin, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  DebugSerial.begin(9600);

  // Blynk will work through Serial
  // Do not read or write this serial manually in your sketch
  Serial.begin(9600);
  Blynk.begin(Serial, auth);
  
}

void loop() {
  
  int car1Status = digitalRead(sensor1Pin); // Read the status of the first sensor
  int car2Status = digitalRead(sensor2Pin); // Read the status of the second sensor

  lcd.setCursor(0, 0); // Set the cursor to the second line
 
  if (car1Status == HIGH) {
    lcd.print("slot1: vacant");
    digitalWrite(led1, LOW);

  } else {
    lcd.print("slot1 occupied");
    digitalWrite(led1, HIGH);
  }

  lcd.setCursor(0, 1); // Set the cursor to the third line
  
  if (car2Status == HIGH) {
    lcd.print("Slot 2: vacant ");
    digitalWrite(led2, LOW);

  } else {
    lcd.print("Slot 2: occupied");
    digitalWrite(led2, HIGH);
  }
  
   Blynk.run();

 
}
