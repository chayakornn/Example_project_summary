## Generated by ChatGPT. Not tested.

#include <LiquidCrystal.h>

// Pin definitions
#define HEATER_PIN 7
#define VENTILATOR_PIN 8
#define HUMIDIFIER_PIN 9
#define BUTTON_UP_PIN 2
#define BUTTON_DOWN_PIN 3
#define BUTTON_ONOFF_PIN 4
#define LCD_RS_PIN 12
#define LCD_ENABLE_PIN 11
#define LCD_D4_PIN 5
#define LCD_D5_PIN 6
#define LCD_D6_PIN A0
#define LCD_D7_PIN A1

// Temperature and humidity control parameters
#define TEMPERATURE_MIN 20
#define TEMPERATURE_MAX 40
#define HUMIDITY_MIN 25
#define HUMIDITY_MAX 75
#define TEMPERATURE_ERROR_THRESHOLD 1
#define HUMIDITY_ERROR_THRESHOLD 5

// LCD object initialization
LiquidCrystal lcd(LCD_RS_PIN, LCD_ENABLE_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);

// Variables for current temperature and humidity
float currentTemperature = 0;
float currentHumidity = 0;

void setup() {
  // Initialize LCD
  lcd.begin(16, 2);

  // Set up pins
  pinMode(HEATER_PIN, OUTPUT);
  pinMode(VENTILATOR_PIN, OUTPUT);
  pinMode(HUMIDIFIER_PIN, OUTPUT);
  pinMode(BUTTON_UP_PIN, INPUT_PULLUP);
  pinMode(BUTTON_DOWN_PIN, INPUT_PULLUP);
  pinMode(BUTTON_ONOFF_PIN, INPUT_PULLUP);
  
  // Display startup message
  lcd.print("Climate Control");
  lcd.setCursor(0, 1);
  lcd.print("Chamber v1.0");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Read button inputs
  bool isUpPressed = digitalRead(BUTTON_UP_PIN) == LOW;
  bool isDownPressed = digitalRead(BUTTON_DOWN_PIN) == LOW;
  bool isOnOffPressed = digitalRead(BUTTON_ONOFF_PIN) == LOW;

  // If on/off button pressed, toggle system state
  if (isOnOffPressed) {
    digitalWrite(HEATER_PIN, LOW);
    digitalWrite(VENTILATOR_PIN, LOW);
    digitalWrite(HUMIDIFIER_PIN, LOW);
    lcd.clear();
    lcd.print("System Off");
    delay(1000);
  } else {
    // If up button pressed, increase temperature
    if (isUpPressed && currentTemperature < TEMPERATURE_MAX) {
      currentTemperature++;
    }
    // If down button pressed, decrease temperature
    if (isDownPressed && currentTemperature > TEMPERATURE_MIN) {
      currentTemperature--;
    }
    
    // Control temperature
    if (currentTemperature < TEMPERATURE_MIN - TEMPERATURE_ERROR_THRESHOLD) {
      digitalWrite(HEATER_PIN, HIGH);
    } else if (currentTemperature > TEMPERATURE_MAX + TEMPERATURE_ERROR_THRESHOLD) {
      digitalWrite(HEATER_PIN, LOW);
    }

    // Display temperature on LCD
    lcd.clear();
    lcd.print("Temp: ");
    lcd.print(currentTemperature);
    lcd.print("C");
    lcd.setCursor(0, 1);
    lcd.print("Humidity: ");
    lcd.print(currentHumidity);
    lcd.print("%");
    delay(1000);
  }
}
