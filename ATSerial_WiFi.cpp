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
 * Joins an access point.
 *
 * @param ssid    the access point ssid
 * @param passw   password for the ssid
 *
 * @return true if connection successful, else false
 */
bool ATSerial_WiFi::joinAP(char* ssid, char* passw) {
  _uart->write("AT+CWMODE=1\r\n");
  delay(UART_DELAY);

  if (! _checkResponse("OK\n")) return false;

  char s[64];
  snprintf(s, 64, "AT+CWJAP=\"%s\",\"%s\"\r\n", ssid, passw);
  _uart->write(s);

  while (! _uart->available()){}

  return _checkResponse("OK\n");
}


bool ATSerial_WiFi::setAP(char* ssid, char* passw, uint16_t chn, uint16_t ecn) {
  _uart->write("AT+CWMODE=2\r\n");
  delay(UART_DELAY);

  if (! _checkResponse("OK\n")) return false;

  char s[64];
  snprintf(s, 64, "AT+CWSAP=\"%s\",\"%s\",%d,%d\r\n", ssid, passw, chn, ecn);
  _uart->write(s);
  delay(1000);

  return _checkResponse("OK\n");
}

bool ATSerial_WiFi::tcpServer(uint16_t port) {
  _uart->write("AT+CIPMUX=1\r\n");
  delay(UART_DELAY);
  if ( ! _checkResponse("OK\n") ) return false;

  char s[64];
  snprintf(s, 64, "AT+CIPSERVER=1,%d\r\n", port);
  _uart->write(s);
  delay(UART_DELAY);

  return _checkResponse("OK\n");
}
