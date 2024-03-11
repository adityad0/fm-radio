# FM Radio
## Components
1. Arduino UNO (Or another equivalent. I am using the SEEED Xiao SAMD21) [Buy](https://shop.lynkrtech.com/product/seeeduino-xiao-samd21-microcontroller-arduino-compatible-cortex-m0/)
2. LCD Display 16x2 [Buy](https://shop.lynkrtech.com/product/16x2-lcd-blue-background-with-white-text-with-i2c-iic-interface/)
3. Rotary Encoder [Buy](https://shop.lynkrtech.com/product/rotary-encoder-module-360-degree/)
4. TEA5767 FM receiver module [Buy](https://shop.lynkrtech.com/?s=tea5767&post_type=product)

## Instructions
1. Connect the I2C pins (SDA & SCL) of the LCD display and TEA5767 module to the microcontroller's I2C pins.
2. Connect all devices to power (5V and GND)
3. Connect the CLK, DT and SW pins of the rotary encoder to any digital pins the the microcontroller.
4. Program the microcontroller with the Arduino IDE by uploading code.ino to the microcontroller.

## References
1. Rotary encoder: [How Rotary Encoder Works and Interface It with Arduino (Last Minute Engineers)](https://lastminuteengineers.com/rotary-encoder-arduino-tutorial/)
2. I2C LCD: [I2C Liquid Crystal Displays (arduino_uno_guy/Arduino)](https://projecthub.arduino.cc/arduino_uno_guy/i2c-liquid-crystal-displays-5eb615)
3. Interfacing an I2C LCD with Arduino: [Interface an I2C LCD with Arduino (Last Minute Engineers)](https://lastminuteengineers.com/i2c-lcd-arduino-tutorial/)
4. Arduino I2C LCD Library Reference: [LiquidCrystal I2C](https://www.arduino.cc/reference/en/libraries/liquidcrystal-i2c/)

## Libraries
1. Flash storage library: [https://github.com/cmaglie/FlashStorage](https://github.com/cmaglie/FlashStorage)
2. Liquid Crystal I2C: [https://github.com/johnrickman/LiquidCrystal_I2C](https://github.com/johnrickman/LiquidCrystal_I2C)
3. TEA5767 FM Radio Receiver: [https://github.com/simonmonk/arduino_TEA5767](https://github.com/simonmonk/arduino_TEA5767)
4. Wire: Should be pre-installed.
