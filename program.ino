#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <TEA5767Radio.h>
#include <FlashStorage.h>

// Initialize the Rotary Encoder
#define CLK 3
#define DT 1
#define SW 2

// Initialize the LCD
#define LCD_ADDR 0x27
LiquidCrystal_I2C lcd(0x27,  16, 2);
TEA5767Radio radio = TEA5767Radio();

struct saveFreq {
    bool valid;
    float freqVal;
};

FlashStorage(my_float_store, saveFreq);
saveFreq savedFreq;

int currentStateCLK;
int lastStateCLK;
String currentDir ="";
unsigned long lastButtonPress = 0;
unsigned long lastRotatedTime = 0;
const unsigned long backlightTimeout = 5000;

float current_freq = 76.0;

void setup() {
    Serial.begin(115200);

    if(!Serial) {
        Serial.print("Serial not connected.");
    }

    savedFreq = my_float_store.read();
    if(!savedFreq.valid) {
        Serial.println("No saved frequency found! Using default frequency.");
        savedFreq.freqVal = 76.0;
        savedFreq.valid = true;
        my_float_store.write(savedFreq);
        Serial.println("Default frequency saved.");
    } else {
        Serial.println("Saved frequency found: " + String(savedFreq.freqVal) + " MHz");
        current_freq = savedFreq.freqVal;
    }

    lcd.init();
    lcd.clear();
    lcd.noBacklight();
    lcd.setCursor(0,0);
    lcd.print("FM Radio");
    lcd.setCursor(0,1);
    lcd.print("Freq: " + String(current_freq));

    Wire.begin();
    radio.setFrequency(current_freq);

    pinMode(CLK,INPUT);
    pinMode(DT,INPUT);
    pinMode(SW, INPUT_PULLUP);
    lastStateCLK = digitalRead(CLK);
}

void loop() {
    currentStateCLK = digitalRead(CLK);
    if(currentStateCLK != lastStateCLK  && currentStateCLK == 1) {
        lastRotatedTime = millis();
        if(digitalRead(DT) != currentStateCLK) {
            Serial.println("RE moved clockwise");
            if(current_freq >= 108.0) {
                current_freq = 76.0;
            }
            current_freq = current_freq + 0.1;
            Serial.print("New Frequency: ");
            Serial.println(current_freq);
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("FM RADIO");
            lcd.setCursor(0,1);
            lcd.print("FM: " + String(current_freq) + "MHz");

            // Update saved frequency
            savedFreq.freqVal = current_freq;
            my_float_store.write(savedFreq);
        } else {
            Serial.println("RE moved Counter-clockwise");
            if(current_freq <= 76.0) {
                current_freq = 108.0;
            }
            current_freq = current_freq - 0.1;
            Serial.print("New Frequency: ");
            Serial.println(current_freq);
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("FM RADIO");
            lcd.setCursor(0,1);
            lcd.print("FM: " + String(current_freq) + "MHz");

            // Update saved frequency
            savedFreq.freqVal = current_freq;
            my_float_store.write(savedFreq);
        }
    }
    lastStateCLK = currentStateCLK;
    int btnState = digitalRead(SW);
    if(btnState == LOW) {
        if(millis() - lastButtonPress > 50) {
            Serial.println("RE Button pressed!");
            radio.setFrequency(current_freq);
        }
        lastButtonPress = millis();
    }

    // Check if the display backlight should be turned off
    if(millis() - lastRotatedTime >= backlightTimeout) {
        lcd.noBacklight();
    } else {
        lcd.backlight();
    }

    delay(1);
}
