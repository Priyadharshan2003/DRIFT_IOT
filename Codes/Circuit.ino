#include <Wire.h>
#include <SoftwareSerial.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <Adafruit_MPU6050.h>
#include <NewPing.h>
#include <SPI.h>
#include <mcp_can.h>

// GPS
SoftwareSerial gpsSerial(0, 1); // RX, TX

// HC-SR04
#define TRIGGER_PIN 9
#define ECHO_PIN 8
NewPing sonar(TRIGGER_PIN, ECHO_PIN, 200); // maximum distance 200cm

// MPU6050
Adafruit_MPU6050 mpu;

// ADXL335
#define X_AXIS_PIN A0
#define Y_AXIS_PIN A1
#define Z_AXIS_PIN A2

// SIM7600
SoftwareSerial lteSerial(7, 6); // TXD, RXD

void setup() {
  // Start serial communication
  Serial.begin(115200);

  // Start GPS communication
  gpsSerial.begin(9600);

  // Start MPU6050 communication
  Wire.begin();
  mpu.begin();

  // Start SIM7600 communication
  lteSerial.begin(115200);
  delay(3000); // wait for SIM7600 to initialize

  // Initialize MCP2515
  SPI.begin();
  mcp2515_init();

  // Send "AT" command to SIM7600 to check if it's working
  lteSerial.println("AT");
  delay(1000);
  while (lteSerial.available()) {
    Serial.write(lteSerial.read());
  }
}

void loop() {
  // Read GPS data
  if (gpsSerial.available()) {
    Serial.write(gpsSerial.read());
  }

  // Read distance from HC-SR04
  int distance = sonar.ping_cm();

  // Read acceleration data from ADXL335
  int x = analogRead(X_AXIS_PIN);
  int y = analogRead(Y_AXIS_PIN);
  int z = analogRead(Z_AXIS_PIN);

  // Read orientation data from MPU6050
  int ax, ay, az;
  int gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Send sensor data to server using LTE
  lteSerial.println("Data from SBC0:");
  lteSerial.println("GPS: " + String(gpsSerial.read()));
  lteSerial.println("HC-SR04: " + String(distance) + "cm");
  lteSerial.println("ADXL335: X=" + String(x) + ", Y=" + String(y) + ", Z=" + String(z));
  lteSerial.println("MPU6050: ax=" + String(ax) + ", ay=" + String(ay) + ", az=" + String(az) + ", gx=" + String(gx) + ", gy=" + String(gy) + ", gz=" + String(gz));
delay(5000); // send data every 5 seconds
}
