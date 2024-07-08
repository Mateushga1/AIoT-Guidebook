/* Copyright (c) 2014 Shigenori Inoue, MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
 * and associated documentation files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, publish, distribute, 
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is 
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or 
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "DHT11.h"

// Constructor
DHT11::DHT11(PinName pin) : io(pin, PIN_INPUT, OpenDrain, 1), io_irq(pin)
{
    io_irq.rise(this, &DHT11::pos_edge);
    io_irq.fall(this, &DHT11::neg_edge);
    io_irq.disable_irq();
    t.start();
    first_time = true;
}

// Destructor
DHT11::~DHT11(void) {}

// Constants
const int DHT11::t_tol_start = 2;
const int DHT11::t_tol_pulse = 10;

// Reading the data bits from the DHT11
int DHT11::readData(void)
{
    // Checking the measurement frequency
    if (t.read_ms() < 2000 && first_time == false) {
        t.reset();
        return READ_TOO_OFTEN;
    }
    
    // Initialize
    init();

    // Checking the data bus
    if (io == 0) {
        t.reset();
        return BUS_BUSY;
    }

    // Sending start signal, low signal for around 10 ms
    t.reset();
    io.output();
    io = 0;
    do {
    } while (t.read_ms() < 20 + t_tol_start);
    io.input();
    io = 1;
    

    // Waiting for the start of the response signal
    t.reset();
    do {
        if (t.read_us() > 100) {
            t.reset();
            return NOT_PRESENT;
        }
    } while (io == 1);

    // Wainting for the start of the ready signal
    t.reset();
    do {
        if (t.read_us() > 100) {
            t.reset();
            return NOT_READY;
        }
    } while (io == 0);

    // Wainting for the end of the ready signal
    t.reset();
    do {
        if (t.read_us() > 100) {
            t.reset();
            return WATCHDOG_ERR;
        }
    } while (io == 1);

    // Starting the pulse width sensing
    // by the use of interruptions
    io_irq.enable_irq();

    do {
        wait_us(100);
        if (wdt > 50) {
            t.reset();
            return WATCHDOG_ERR;
        }
        wdt++;
    } while (eod == false);

    // Calculating the check sum
    chksum = ((data & 0xff00000000) >> 32)
             + ((data & 0x00ff000000) >> 24)
             + ((data & 0x0000ff0000) >> 16)
             + ((data & 0x000000ff00) >> 8);

    if (chksum != (data & 0x00000000ff)) {
        t.reset();
        return CHKSUM_ERR;
    } else {
        t.reset();
        first_time = false;
        return OK;
    }
}

// Extracting humidity data from the received data
int DHT11::readHumidity(void)
{
    return (data & 0xff00000000) >> 32;
}

// Extracting temperature data from the received data
int DHT11::readTemperature(void)
{
    return (data & 0x0000ff0000) >> 16;
}

// Initialization of variables
void DHT11::init(void)
{
    t_pulse_us = 0;
    data = 0;
    chksum = 0;
    cnt = 0;
    wdt = 0;
    eod = false;
    t.reset();
}

void DHT11::pos_edge(void)
{
    // Disabling the interruptions
    io_irq.disable_irq();

    // Initializing the Timer
    t.reset();

    // Enabling the interruptions
    io_irq.enable_irq();
}

void DHT11::neg_edge(void)
{
    // Disabling the interruptions
    io_irq.disable_irq();

    // Reading the positive pulse width
    t_pulse_us = t.read_us();

    // Detecting 0 if the pulse width ranges around 25 us
    if (25 - t_tol_pulse <= t_pulse_us && t_pulse_us <= 30 + t_tol_pulse) {
        // Shifting the data buffer and not adding 1 (because this bit is zero)
        data = data << 1;

        // Counting up the bits
        cnt++;
    }

    // Detecting 1 if the pulse width ranges from 70 us
    else if (70 - t_tol_pulse <= t_pulse_us && t_pulse_us <= 70 + t_tol_pulse) {
        // Shifting the data buffer and adding 1 (because this bit is one)
        data = data << 1;
        data++;

        // Counting up the bits
        cnt++;
    }

    // Detecting the end of Data
    if (cnt < 40) {
        // Enabling the interruptions
        io_irq.enable_irq();
    } else {
        eod = true;
    }
}