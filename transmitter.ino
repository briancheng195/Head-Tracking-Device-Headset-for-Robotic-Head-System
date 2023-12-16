#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <Adafruit_HMC5883_U.h>
#include <SPI.h>
#include <RF24.h>

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

RF24 radio(7,8); // CE, CSN
const byte address[6] = "00001";

float pitch = 0.0;
float yaw = 0.0;
float roll = 0.0;
float yawOffset = 0.0; // Yaw offset for calibration

void setup() {
  Serial.begin(19200);
  accel.begin();
  mag.begin();
  radio.begin(); 
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  // Calibration routine
  delay(1000); // Allow time for sensor to stabilize
  for (int i = 0; i < 100; i++) {       // Collect multiple readings from the magnetometer sensor to calculate an average value. 
    sensors_event_t magEvent;           
    mag.getEvent(&magEvent);            // Storing the magnetometer data in the magEvent variable
    float heading = atan2(magEvent.magnetic.y, magEvent.magnetic.x);  // Calculates the heading angle based on the magnetic field values obtained from the sensor
    if (heading < 0) {                  // If heading value is 0, it adds 2 x pi to ensure the heading angle is always positive
      heading += 2 * PI;
    }
    yawOffset += heading;               // Accumulates the heading angles obtained from each iteration. To calculate the average heading angle in the next step
    delay(10);
  }
  yawOffset /= 100;                     // Calculates the average heading angle 
}

void loop() {
  sensors_event_t event;
  accel.getEvent(&event);                                                           // Storing the accelerometer data in the event variable
  float pitchAcc = atan2(event.acceleration.y, event.acceleration.z) * RAD_TO_DEG;  // Calculates the pitch angle using the accelerometer data
  
  float roll = atan2(event.acceleration.x, event.acceleration.z) * RAD_TO_DEG;
  
  sensors_event_t magEvent;                                                 
  mag.getEvent(&magEvent);                                                          // Storing the magnetometer data in the magEvent variable

  float heading = atan2(magEvent.magnetic.y, magEvent.magnetic.x);                  // Calculates the heading angle using the magnetometer data
  if (heading < 0) {
    heading += 2 * PI;
  }
  yaw = (heading - yawOffset) * RAD_TO_DEG;   // Calculates the yaw angle by subtracting the calibrated offset (yawOffset) from the heading angle

  // Create an array to hold pitch and yaw values
  float dataToSend[3] = {pitchAcc, yaw, roll};

  // Send pitch and yaw values
  radio.write(&dataToSend, sizeof(dataToSend));

  Serial.print("Pitch: ");
  Serial.print(pitchAcc); Serial.print(" degrees, ");
  Serial.print("Yaw: ");
  Serial.print(yaw); Serial.println(" degrees");
  Serial.print("Roll: "); Serial.println(" degrees");

  delay(10);
}
