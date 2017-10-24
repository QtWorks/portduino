/* Portduino - library to work with arduino through serial port.
 * Copyright (c) 2017 Golubchikov Mihail <https://github.com/rue-ryuzaki>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PORTDUINO_ARDUINO_INFO_H
#define PORTDUINO_ARDUINO_INFO_H

#include <QSerialPort>
#include <QSerialPortInfo>

namespace portduino {
struct BoardInfo
{
    BoardInfo()
        : vendorID(0),
          productID(0),
          portName()
    { }

    quint16 vendorID;
    quint16 productID;
    QString portName;
};

struct ArduinoInfo
{
    QSerialPort*  port;
    BoardInfo     board;
    bool          available;
};
} // portduino

#endif // PORTDUINO_ARDUINO_INFO_H
