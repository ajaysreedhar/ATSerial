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

#ifndef __AT_SERIAL_WIFI_H__
#define __AT_SERIAL_WIFI_H__

#include "ATSerial.h"

class ATSerial_WiFi: public ATSerial {

  public:
    ATSerial_WiFi(void);
    ATSerial_WiFi(uint16_t, uint16_t, long);

    /**
     * Quits access point.
     *
     * @return true if quit, else false
     */
    bool quitAp(void);

    /**
     * Joins an access point.
     *
     * @param ssid the access point ssid
     * @param passw password for the ssid
     * @return true if connection successful, else false
     */
    bool joinAp(char*, char*);

    /**
     * Sets up an access point.
     *
     * @param ssid the new SSID
     * @param passw new password
     * @param chn channel number
     * @param ecn encryption
     *return true if setup successfully, false otherwise
     */
    bool setAp(char*, char*, uint16_t, uint16_t);

    /**
     * Sets connection mode to single connection.
     *
     * @return true if set successfully, false otherwise
     */
    bool singleCipmux(void);

    /**
     * Sets connection mode to multiple connections.
     *
     * @return true if set successfully, false otherwise
     */
    bool multiCipmux(void);

    /**
     * Start a TCP server at a specified port.
     *
     * @param port the port number
     * @return true if started successfully, false otherwise
     */
    bool tcpServer(uint16_t);
};

#endif
