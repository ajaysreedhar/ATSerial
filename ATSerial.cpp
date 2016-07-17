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
 * Uses default parameters.
 */
ATSerial::ATSerial(void) {
  _uart = new SoftwareSerial(DEFAULT_RX, DEFAULT_TX);
  _uart->begin(DEFAULT_BAUD);
}

/**
 * Overrides the default parameters.
 *
 * @param rx the RX pin
 * @param tx the TX pin
 * @param baud BAUD rate
 */
ATSerial::ATSerial(uint16_t rx, uint16_t tx, long baud) {
  _uart = new SoftwareSerial(rx, tx);
  _uart->begin(baud);
}

/**
 * Clears the software serial buffer.
 */
void ATSerial::flush(void) {
  while (0 < _uart->read()){}
}

/**
 * Waits until data is available to read
 * or for a period of UART_TIMEOUT milliseconds.
 *
 * @return the number of bytes available, -1 if timed out
 */
int ATSerial::available(void) {
  int bytes=-1, millis=UART_DELAY;

  while (millis < UART_TIMEOUT) {
    bytes = _uart->available();
    if (bytes > 0) break;

    millis = millis + UART_DELAY;
    delay(UART_DELAY);
  }

  return bytes;
}

/**
 * Checks for the substring in the response received from the device.
 *
 * @param s the substring to be checked
 * @return true if the provided substring is found in the response, else false
 */
bool ATSerial::checkResponse(const char* s) {
  int match=0, index=0, ssize=strlen(s), ch;

  int bytes = available();
  if (bytes <= 0) return false;

  while ((ch=_uart->read())) {
    if (ch < 0) break;

    Serial.print((char)ch);
    Serial.print("=");
    Serial.println(s[index]);

    if (ch == (int)s[index]) {
      match++;

    } else if (ch == (int)s[0]) {
      match = 1;
      index = 0;

    } else {
      match = 0;
      index = -1;
    }

    if (match == ssize) {
      flush();
      return true;
    }

    index++;
  }

  flush();
  return false;
}

/**
 * Waits until bytes are available and
 * reads the bytes into a string buffer.
 *
 * @return the string read
 */
char* ATSerial::readString(void) {
  int bytes = available();
  if (bytes <= 0) return NULL;

  int ch=-1, index=0;

  char* s = (char*) malloc(bytes + 1);

  while ((ch = _uart->read()) >= 0) {
    s[index] = (char)ch;
    Serial.println((char)ch);
    index++;

    if (index >= bytes) {
      s[index] = '\0';
      break;
    }
  }

  return s;
}

/**
 * Sends the command to test AT startup.
 *
 * @return true if device responds with OK, false on error
 */
bool ATSerial::isOkay(void) {
  _uart->write("AT\r\n");
  return checkResponse("OK\r\n");
}

/**
 * Sends the command to restart the device.
 *
 * @return true if successfully restarted, false on error
 */
bool ATSerial::restart(void) {
  _uart->write("AT+RST\r\n");
  return checkResponse("OK\r\n");
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
 * Writes a string to the device.
 *
 * @param s the string to be written
 * @return the number of bytes written
 */
int ATSerial::write(const char* s) {
  return _uart->write(s);
}
