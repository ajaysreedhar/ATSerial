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

#include "ATSerial.h"

/**
 * Checks for the substring in the response received from the device.
 *
 * @param s the substring to be checked
 *
 * @return true if the provided substring is found in the response, else false
 */
bool ATSerial::_checkResponse(String s) {
  if (_uart->available()) {
    String r = _uart->readString();

    /*Serial.println("{");
    Serial.println(r);
    Serial.println("}");*/

    int rLen = r.length(), sLen = s.length();
    int max = rLen - sLen, i = 0;

    for (i=0; i<= max; i++) {
      if (s == s.substring(i, i+sLen)) return true;
    }
  }

  return false;
}

/**
 * Uses default parameters.
 */
ATSerial::ATSerial(void) {
  _uart = new SoftwareSerial(DEFAULT_RX, DEFAULT_TX);
  _uart->begin(DEFAULT_BAUD);
}

/**
 * Overrides the default parameters.
 *
 * @param uint16_t rx   the RX pin
 * @param uint16_t tx   the TX pin
 * @param long baud     BAUD rate
 */
ATSerial::ATSerial(uint16_t rx, uint16_t tx, long baud) {
  _uart = new SoftwareSerial(rx, tx);
  _uart->begin(baud);
}

/**
 * Sends the command to test AT startup.
 *
 * @return true if device responds with OK, false on error
 */
bool ATSerial::isOkay(void) {
  _uart->write("AT\r\n");
  delay(UART_DELAY);
  return _checkResponse("AT\r\nOK\n");
}

/**
 * Sends the command to restart the device.
 *
 * @return true if successfully restarted, false on error
 */
bool ATSerial::restart(void) {
  _uart->write("AT+RST\r\n");
  delay(1000);
  return _checkResponse("OK");
}

/**
 * Checks if any bytes are available from the device and
 * returns the number of bytes available.
 *
 * @return number of bytes available
 */
int ATSerial::available(void) {
  return _uart->available();
}

/**
 * Reads next character.
 *
 * @return character read, -1 if none available
 */
int ATSerial::read(void) {
  return _uart->read();
}

/**
 * Reads the characters into a string buffer.
 *
 * @return the string read
 */
String ATSerial::readString(void) {
  return _uart->readString();
}
