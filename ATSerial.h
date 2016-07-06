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

#include<Arduino.h>
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
    SoftwareSerial *_uart;
    bool _checkResponse(String);

  public:
    ATSerial(void);
    ATSerial(uint16_t, uint16_t, long);

    bool isOkay(void);
    bool restart(void);
    int available(void);
    int read(void);

    String readString(void);
};

#endif
