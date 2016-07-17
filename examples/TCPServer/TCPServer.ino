#include <ATSerial_WiFi.h>

// BAUD rate may vary from device to device.
// Choose accordingly.
Serial.begin(57600);
ATSerial_WiFi wifi(6, 7, 57600);

void setup() {

  // Check whether the device is connected
  // properly and is working
  if (wifi.isOkay()) {
    Serial.println("Wifi setup okay");

  } else {
    Serial.println("Wifi setup failed!");
    return;
  }

  // Create a new access point
  if (wifi.setAp("Arduino", "arduino", 5, 4)) {
    Serial.println("Created new access point, Arduino!");

  } else {
    Serial.println("Failed to create new access point!");
    return;
  }

  // Start the TCP server and listen port 8505
  if (wifi.tcpServer(8505)) Serial.println("TCP server listening on port 8505");
  else Serial.println("Failed to start TCP server!");
}

void run() {

}
