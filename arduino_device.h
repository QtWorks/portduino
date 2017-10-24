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

#ifndef PORTDUINO_ARDUINO_DEVICE_H
#define PORTDUINO_ARDUINO_DEVICE_H

#include <vector>

#include <QComboBox>
#include <QDialog>
#include <QLabel>

#include "arduino_info.h"

namespace portduino {
class ArduinoDevice : public QDialog
{
    Q_OBJECT

public:
    static int scan(ArduinoInfo& arduino, bool* ok);

private slots:
    void scanPorts();

private:
    ArduinoDevice();

    QComboBox 	m_box;
    std::vector<BoardInfo> m_boards;
};
} // portduino

#endif // PORTDUINO_ARDUINO_DEVICE_H
