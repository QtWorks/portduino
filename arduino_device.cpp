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

#include "arduino_device.h"

#include <QDialogButtonBox>
#include <QGridLayout>
#include <QPushButton>

#include <QDebug>

namespace portduino {
int ArduinoDevice::scan(ArduinoInfo& arduino, bool* ok)
{
    ArduinoDevice dialog;
    int ret = dialog.exec();
    if (ret == QDialog::Accepted) {
        if (dialog.m_box.currentIndex() < 0) {
            *ok = false;
        } else {
            // all ok
            *ok = true;
            arduino.board = dialog.m_boards[dialog.m_box.currentIndex()];
        }
    } else {
        *ok = false;
    }
    return ret;
}

ArduinoDevice::ArduinoDevice()
{
    this->setWindowTitle(tr("Scan serial ports"));

    QGridLayout* gridLayout = new QGridLayout;

    scanPorts();

    gridLayout->addWidget(new QLabel(tr("Select device:")), 0, 0);
    gridLayout->addWidget(&m_box, 0, 1);
    QPushButton* refreshButton = new QPushButton(tr("Refresh"));
    gridLayout->addWidget(refreshButton, 0, 2);
    connect(refreshButton, SIGNAL(clicked()), this, SLOT(scanPorts()));

    QDialogButtonBox* box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    gridLayout->addWidget(box, 1, 1);

    connect(box, SIGNAL(accepted()), this, SLOT(accept()));
    connect(box, SIGNAL(rejected()), this, SLOT(reject()));

    this->setLayout(gridLayout);
    this->setFixedSize(371, 81);
}

void ArduinoDevice::scanPorts()
{
    m_boards.clear();
    m_box.clear();

    int availablePorts = QSerialPortInfo::availablePorts().length();
    qDebug() << "Number of available ports: " << availablePorts;
    foreach (const QSerialPortInfo& info, QSerialPortInfo::availablePorts()) {
        qDebug() << "Has vendor ID: " << info.hasVendorIdentifier();
        BoardInfo board;
        board.portName = info.portName();
        if (info.hasVendorIdentifier()) {
            board.vendorID = info.vendorIdentifier();
            qDebug() << "Vendor ID: " << board.vendorID;
        }
        qDebug() << "Has product ID: " << info.hasProductIdentifier();
        if (info.hasProductIdentifier()) {
            board.productID = info.productIdentifier();
            qDebug() << "Product ID: " << board.productID;
        }
        if (board.vendorID != 0 && board.productID != 0) {
            m_boards.push_back(board);
        }
    }

    for (BoardInfo& info : m_boards) {
        m_box.addItem(tr("VEN_%1_PROD_%2").arg(info.vendorID).arg(info.productID));
    }
}
} // portduino
