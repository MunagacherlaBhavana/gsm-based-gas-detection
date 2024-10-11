#include <LiquidCrystal_I2C.h>          // include the LiquidCrystal library
#include <SoftwareSerial.h>         // include the SoftwareSerial library

#define MQ2_PIN A0                    // define the analog input pin for the MQ2 sensor
#define BUZZER_PIN 2                  // define the digital output pin for the buzzer
#define LED_R 4                 //define red LED pin  

LiquidCrystal_I2C lcd(0x27, 16, 2); // create a new LiquidCrystal object
SoftwareSerial gsm(6, 8); // set the RX & TX pin for GSM
void setup() {
  lcd.init();                           // initialize the LCD
  lcd.backlight(); 
  lcd.print("Gas Sensor Test");         // print the initial message to the LCD
  pinMode(BUZZER_PIN, OUTPUT);           // set the buzzer pin as an output
  pinMode(LED_R, OUTPUT);
  pinMode(MQ2_PIN, INPUT);
  gsm.begin(9600);                     // initialize the GSM module
  delay(5000);                        // wait for the GSM module to start up
  gsm.println("AT+CMGF=1\r");                 // set the GSM module to text mode
  delay(1000);                          // Mwait for the GSM module to respond
  lcd.clear();                                  // clear the LCD screen
}
void loop() {
  int sensorValue = analogRead(MQ2_PIN); // read the analog input value from the MQ2 sensor
  if (sensorValue > 300) {                        // if the sensor value is above the threshold (adjust as needed)
    lcd.clear();                                  // clear the LCD screen
    lcd.print("Gas Detected !");                   // print the gas detection message to the LCD
    digitalWrite(BUZZER_PIN, HIGH);                    // turn on the buzzer
    digitalWrite(LED_R, HIGH);
    gsm.println("AT+CMGS=\"+916382011008\"\r");                // set the phone number to send the SMS alert to
    delay(1000);                                          // wait for the GSM module to respond
    gsm.print("ALERT : Gas detected !");                         // send the SMS message
    gsm.println((char)26);                                      // send the CTRL+Z character to indicate the end of the SMS message
    delay(5000);                                      // wait for the GSM module to send the SMS message
    digitalWrite(BUZZER_PIN, LOW);                     // turn off the buzzer
    digitalWrite(LED_R, LOW);
  } else {
    lcd.clear();                                        // clear the LCD screen
    lcd.print("No Gas Detected");                       // print the no gas detection message to the LCD
    digitalWrite(BUZZER_PIN, LOW);              // turn off the buzzer
    digitalWrite(LED_R, LOW);
    
  }
  delay(500);                                         // wait for half a second before repeating the loop
}
