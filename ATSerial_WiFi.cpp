/**
 * MIT License
 *
 * Copyright (c) 2016 Ajay Sreedhar
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "ATSerial_WiFi.h"

ATSerial_WiFi::ATSerial_WiFi(void):ATSerial() {}
ATSerial_WiFi::ATSerial_WiFi(uint16_t rx, uint16_t tx, long baud): ATSerial(rx, tx, baud) {}

/**
 * Quits access point.
 *
 * @return true if quit, else false
 */
bool ATSerial_WiFi::quitAp(void) {
  _uart->write("AT+CWQAP\r\n");
  return checkResponse("OK\r\n");
}

/**
 * Joins an access point.
 *
 * @param ssid the access point ssid
 * @param passw password for the ssid
 * @return true if connection successful, else false
 */
bool ATSerial_WiFi::joinAp(char* ssid, char* passw) {
  // Close active connections.
  quitAp();

  // Set mode to STA.
  _uart->write("AT+CWMODE=1\r\n");
  if (!checkResponse("OK\r\n")) return false;

  char* s = (char*) malloc(64);
  snprintf(s, 64, "AT+CWJAP=\"%s\",\"%s\"\r\n", ssid, passw);
  _uart->write(s);
  free(s);

  while (true) {
    s = readString();

    if (NULL != strstr(s, "FAIL")) return false;
    if (NULL != strstr(s, "WIFI CONNECTED")) return true;
  }

  return false;
}

/**
 * Creates a new access point.
 *
 * @param ssid the new SSID
 * @param passw new password
 * @param chn channel number
 * @param ecn encryption
 *return true if setup successfully, false otherwise
 */
bool ATSerial_WiFi::createAp(char* ssid, char* passw, uint16_t chn, uint16_t ecn) {
  _uart->write("AT+CWMODE=2\r\n");
  if (!checkResponse("OK\r\n")) return false;

  char s[64];
  snprintf(s, 64, "AT+CWSAP=\"%s\",\"%s\",%d,%d\r\n", ssid, passw, chn, ecn);
  _uart->write(s);
  return checkResponse("OK\r\n");
}

/**
 * Sets connection mode to single connection.
 *
 * @return true if set successfully, false otherwise
 */
bool ATSerial_WiFi::setSingleCipmux(void) {
  _uart->write("AT+CIPMUX=0\r\n");
  return checkResponse("OK\r\n");
}

/**
 * Sets connection mode to multiple connections.
 *
 * @return true if set successfully, false otherwise
 */
bool ATSerial_WiFi::setMultiCipmux(void) {
  _uart->write("AT+CIPMUX=1\r\n");
  return checkResponse("OK\r\n");
}

/**
 * Start a TCP server at a specified port.
 *
 * @param port the port number
 * @return true if started successfully, false otherwise
 */
bool ATSerial_WiFi::tcpServer(uint16_t port) {
  if (!setMultiCipmux()) return false;

  char s[64];
  snprintf(s, 64, "AT+CIPSERVER=1,%d\r\n", port);
  _uart->write(s);

  return checkResponse("OK\n");
}
