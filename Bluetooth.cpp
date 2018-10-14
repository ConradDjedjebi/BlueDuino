/****************************************************************************************************
  Bluetooth.cpp

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

#include "Bluetooth.h"

/**
 * Get Bluetooth RX PIN
 * @return int - rx PIN
 */
int Bluetooth::getrxPin(){
    return rxPin;
}

/**
 * Get the Bluetooth PIN
 */
char *Bluetooth::getPIN(){
    return &PIN[0];
}

/**
 * Get Bluetooth TX PIN
 * @return int TX PIN
 */
int Bluetooth::gettxPin(){
    return txPin;
}

/**
 * Get the message end delimiter
 * @return char end of messages
 */
char Bluetooth::getMessageEnd(){
    return message_end;
}

/**
 * Get Bluetooth device type
 * @return int device type
 */
deviceType Bluetooth::getType(){
    return this->type;
}

/**
 * Get Bluetooth device name
 * @return *char device name
 */
char * Bluetooth::getName(){
    return &name[0];
}

/**
 * Get Bluetooth ATCOMMAND PIN
 * @return int atCommand PIN
 */
int Bluetooth::getAtCommandPin(){
    return atCommandPin;
}

/**
 * Get Bluetooth REG33SWITCH PIN
 * @return int reg33Switch PIN
 */
int Bluetooth::getReg33SwitchPin(){
    return reg33SwitchPin;
}

/**
 * Get Bluetooth AUTORESET PIN
 * @return int - autoReset PIN
 */
int Bluetooth::getAutoResetPin(){
    return autoResetPin;
}

/**
 * Set Bluetooth RX PIN
 * @param int RX PIN
 */
void Bluetooth::setrxPin(int rx){
    rxPin = rx;
}

/**
 * Set Bluetooth TX PIN
 * @param int TX PIN
 */
void Bluetooth::settxPin(int tx){
    txPin = tx;
}

/**
 * Set the bluetooth PIN
 * @param pin [description]
 */
void Bluetooth::setPIN(int pin){
    char _pin[32];
    strcpy(PIN, "AT+PIN");
    sprintf(_pin, "%d", pin);
    strcat(PIN, _pin);
}

/**
 * Set Bluetooth AUTORESET PIN
 * @param int autoReset PIN
 */
void Bluetooth::setAutoResetPin(int autoReset){
    autoResetPin = autoReset;
}

/**
 * Set Bluetooth ATCOMMAND PIN
 * @param int atCommand PIN
 */
void Bluetooth::setAtCommandPin(int atCommand){
    atCommandPin = atCommand;
}

/**
 * Set Bluetooth REG33SWITCH PIN
 * @param int reg33Switch PIN
 */
void Bluetooth::setReg33SwitchPin(int reg33Switch){
    reg33SwitchPin = reg33Switch;
}

/**
 * Set message char that represents the end of message. Default '\0'
 * @param char end of the message
 */
void Bluetooth::setMessageEnd(char end){
    message_end = end;
}

/**
 * Set Bluetooth device type
 * @param int type
 */
void Bluetooth::setType(deviceType type){
    this->type = type;
}

/**
 * Set Bluetooth device name
 * @param char[] name
 */
void Bluetooth::setName(char new_name[]){
    strcpy(name, "AT+NAME");
    strcat(name, new_name);
}

/**
 * Set the Serial Baudrate for the bluetooth module
 * @param baudrate value with the  baudrate
 */
void Bluetooth::setBaudrate(unsigned long baudrate){
    this->baudrate = baudrate;
}

/**
 * Setup Bluetooth settings. Must be used in Arduino setup()
 */
void Bluetooth::setupBluetooth(){

  btSerial->begin(baudrate);
  delay(1100);
  btSerial->write("AT");
  btSerial->write("AT+BAUD4");
  delay(1100);
  Serial.println("\nSetting bluetooth with 9600");
  while (btSerial->available())
      Serial.write(btSerial->read());

  btSerial->write(name);
  delay(1100);
  Serial.print("\nSetting Bluetooth name: ");
  Serial.println(name);

  while (btSerial->available()) 
      Serial.write(btSerial->read());

  btSerial->write(PIN);
  delay(1100);
  Serial.print("\nNew PIN: ");
  Serial.println(PIN);
  while (btSerial->available()) 
  Serial.write(btSerial->read());

  btSerial->write("AT+VERSION");
  delay(1100);
  Serial.print("\nBluetooth version");
  while (btSerial->available()) 
  Serial.write(btSerial->read());
}

/**
 * Create and start the Serial port of Bluetooth object with RX and TX parameters.
 */
Bluetooth::Bluetooth(int r, int t, deviceType type){
  setType(type);
  switch(this->type){
    case HC05:
      pinMode(autoResetPin, OUTPUT);
      pinMode(atCommandPin, OUTPUT);
      pinMode(reg33SwitchPin, OUTPUT);

      digitalWrite(autoResetPin, HIGH);
      digitalWrite(atCommandPin, LOW);  
      digitalWrite(reg33SwitchPin, LOW);
      break;
    case HC06:
      break;
    default:
      break;
  }
  setrxPin(r);
  settxPin(t);
  setName("PNGFramework");
  setPIN(1234);
  setMessageEnd('\0');
  setBaudrate(9600);
  btSerial = new SoftwareSerial(r, t);
}

/**
 * Destroy the SoftwareSerial object
 */
Bluetooth::~Bluetooth(void)
{
  delete btSerial;
}


void Bluetooth::begin(){
    btSerial->begin(baudrate);
}

/**
 * Read received message
 * @return
 */
char * Bluetooth::read(){
    int i = 0;
    char c;
    char ch[1024];
    if(btSerial->available())
        while(1){
            c = btSerial->read();
            ch[i++] = c;
            if(c == message_end)
              break;
        }
    ch[i] = '\0';
    strcpy(msg, ch);
    return &msg[0];
}

/**
 * Send a message to the connected device by Bluetooth
 * @param char[] message
 */
void Bluetooth::send(char c[]){
    btSerial->print(c);
}