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

#ifndef __AT_SERIAL_H__
#define __AT_SERIAL_H__

#include <Arduino.h>
#include <SoftwareSerial.h>

#ifndef UART_DELAY
#define UART_DELAY 100
#endif

#define DEFAULT_RX 0
#define DEFAULT_TX 1

#define DEFAULT_BAUD 115200

#define DEFAULT_PORT 8468

class ATSerial {
  protected:
    /**
     * UART device.
     */
    SoftwareSerial *_uart;

    /**
     * Checks for the substring in the response received from the device.
     *
     * @param s the substring to be checked
     *
     * @return true if the provided substring is found in the response, else false
     */
    bool _checkResponse(String);

  public:
    /**
     * Uses default parameters.
     */
    ATSerial(void);

    /**
     * Overrides the default parameters.
     *
     * @param uint16_t rx   the RX pin
     * @param uint16_t tx   the TX pin
     * @param long baud     BAUD rate
     */
    ATSerial(uint16_t, uint16_t, long);

    /**
     * Sends the command to test AT startup.
     *
     * @return true if device responds with OK, false on error
     */
    bool isOkay(void);

    /**
     * Sends the command to restart the device.
     *
     * @return true if successfully restarted, false on error
     */
    bool restart(void);

    /**
     * Checks if any bytes are available from the device and
     * returns the number of bytes available.
     *
     * @return number of bytes available
     */
    int available(void);

    /**
     * Reads next character.
     *
     * @return character read, -1 if none available
     */
    int read(void);

    /**
     * Reads the characters into a string buffer.
     *
     * @return the string read
     */
    String readString(void);
};

#endif
