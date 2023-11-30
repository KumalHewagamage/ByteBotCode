/* This example shows how to use continuous mode to take
range measurements with the VL53L0X. It is based on
vl53l0x_ContinuousRanging_Example.c from the VL53L0X API.

The range readings are in units of mm. */

#include <Wire.h>
#include <VL53L0X.h>
const int numReadings = 10;  // Number of readings to average

int readings[numReadings];   // Array to store readings
int total = 0;  // Running total of readings
int average = 0;  // Calculated average


VL53L0X sensor;

void setup()
{
  Serial.begin(9600);
  Wire.begin();

  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }

  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
  sensor.startContinuous();
  
  
}

void loop()
{
  // Take 10 readings and calculate the average
  for (int i = 0; i < numReadings; i++) {
    readings[i] = sensor.readRangeContinuousMillimeters();
    total += readings[i];
    delay(100);  // Adjust the delay as needed between readings
  }
  
  // Calculate the average
  average = total / numReadings;
  
  // Print the average to the serial monitor
  Serial.print("Average: ");
  Serial.println(average);
  Serial.println(sensor.readRangeContinuousMillimeters());
  total=0;
}





