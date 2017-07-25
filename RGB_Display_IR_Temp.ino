//Trying some Arduino lines using the Arduino Uno, Grove Shield,RGB LCD and Digital IR temperature sensor

#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

#include "MLX90615.h"
#include <I2cMaster.h>

#define SDA_PIN 3   //define the SDA pin
#define SCL_PIN 2   //define the SCL pin

SoftI2cMaster i2c(SDA_PIN, SCL_PIN);
MLX90615 mlx90615(DEVICE_ADDR, &i2c);

void setup()
{
    // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  lcd.setRGB(0, 255, 0);

  lcd.print("Amb:       deg C");
  lcd.setCursor(0,1);
  lcd.print("Obj:       deg C");
   
  Serial.begin(9600);
  Serial.println("Setup...");

  //mlx90615.writeEEPROM(Default_Emissivity); //write data into EEPROM when you need to adjust emissivity.
  //mlx90615.readEEPROM(); //read EEPROM data to check whether it's a default one.
}

void loop()
{
  //Measure Temperatures
  
  float temp = (mlx90615.getTemperature(MLX90615_AMBIENT_TEMPERATURE));
  float obj = (mlx90615.getTemperature(MLX90615_OBJECT_TEMPERATURE));
  
  // Print a message to the LCD.
  lcd.setCursor(5,0);
  lcd.print(temp);
  lcd.setCursor(5,1);

  //Set background color to blue below 20 deg C and red above 28 deg C. Otherwise set to green.
  if (obj < 20.0) {lcd.setRGB(0,0,255);} else if (obj > 28.0) {lcd.setRGB(255,0,0);} else {lcd.setRGB(0,255,0);}
  
  lcd.print(obj);

  Serial.print("Object temperature: ");
  Serial.println(mlx90615.getTemperature(MLX90615_OBJECT_TEMPERATURE));
  Serial.print("Ambient temperature: ");
  Serial.println(mlx90615.getTemperature(MLX90615_AMBIENT_TEMPERATURE));
  
  delay(1000);
}
