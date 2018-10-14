/****************************************************************************************************
  Bluetooth.h

  License: GNU GPLv3

  A Bluetooth library for Arduino
  Written by A BORDIN and C DJEDJEBI

  This library is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with the Bluetooth library.  If not, see <http://www.gnu.org/licenses/>.

Version Modified By Date     Comments
------- ----------- -------- --------
0001    A BORDIN      21/04/15 Bluetooth.cpp and Bluetooth.h (https://github.com/aron-bordin/PNG-Arduino-Framework/tree/master/Bluetooth)
0002    C DJEDJEBI    13/10/18 Added support for HC05
****************************************************************************************************/

#ifndef bluetooth_h
#define bluetooth_h

#include "Arduino.h"
#include <SoftwareSerial.h>

typedef enum {
	HC05,
	HC06,
} deviceType;

class Bluetooth{
private:
    int rxPin;
    int txPin;
    int autoResetPin;
    int atCommandPin;
    int reg33SwitchPin;
    deviceType type;
    char PIN[32];
    SoftwareSerial *btSerial;
    char msg[1024];
    char name[255];
    char message_end;
    unsigned long baudrate;

public:
    Bluetooth(int r, int t, deviceType type);
    ~Bluetooth();
    int getrxPin();
    int gettxPin();
    int getAtCommandPin();
    int getReg33SwitchPin();
    int getAutoResetPin();   
    deviceType getType();
    char * read();
    char * getName();
    char getMessageEnd();
    char * getPIN();
    void setMessageEnd(char end);
    void setName(char name[]);
    void setrxPin(int rx);
    void settxPin(int tx);
    void setType(deviceType type);    
    void setAtCommandPin(int atCommand);
    void setReg33SwitchPin(int reg33Switch);
    void setAutoResetPin(int autoReset);    
    void setPIN(int pin);
    void setupBluetooth();
    void send(char c[]);
    void setBaudrate(unsigned long baudrate);
    void begin();
};

#endif