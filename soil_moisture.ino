#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h> 

#define TEMP_SENSOR_PIN A2       
#define SOIL_SENSOR_PIN A0      
#define SERVO_PIN 9              


LiquidCrystal_I2C lcd(0x27, 16, 2); 


// Create a Servo object
Servo servo;

void setup() {
  // Initialize Serial Monitor for debugging
  Serial.begin(9600);

  // Initialize LCD
  lcd.init();
  lcd.backlight(); // Turn on the backlight

  // Display a startup message
  lcd.setCursor(0, 0);
  lcd.print("Env Monitor");
  lcd.setCursor(0, 1);
  lcd.print("Starting...");
  delay(2000); // Wait 2 seconds
  lcd.clear();

  // Initialize the servo motor
  servo.attach(SERVO_PIN);
  servo.write(0);
}

void loop() {
  // Read temperature sensor value
  int tempSensorValue = analogRead(TEMP_SENSOR_PIN);
  float voltage = tempSensorValue * (5.0 / 1023.0); 
  float temperature = voltage * 100.0;          

 
  if (temperature < 0) temperature = 0; 
  if (temperature > 100) temperature = 100;

  // Read soil moisture sensor value
  int soilSensorValue = analogRead(SOIL_SENSOR_PIN); 
  int soilMoisturePercent = map(soilSensorValue, 0, 1023, 0, 100);

  // Display readings on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature, 1); 
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Soil: ");
  lcd.print(soilMoisturePercent);
  lcd.print("%");

  // Servo control logic based on soil moisture
  if (soilMoisturePercent < 40) { 
    servo.write(90); 
    lcd.setCursor(10, 1); 
    lcd.print("Servo ON");
  } else {
    servo.write(0); 
    lcd.setCursor(10, 1); 
    lcd.print("Servo OFF");
  }

  delay(2000); 
}
