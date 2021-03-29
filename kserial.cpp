#include "kserial.h"

kserial::kserial()
{
    usbDevice = new QSerialPort();
    baudrate = QSerialPort::Baud115200;
    serialDeviceIsConnected = false;
}

kserial::~kserial()
{
    delete usbDevice;
}

QString kserial::serialRead()
{
    if(serialDeviceIsConnected == true)
    {
        serialBuffer += usbDevice->readAll(); // Read the available data
    }
    return(serialBuffer);
}

QString kserial::getBuf()
{
    return(serialBuffer);
}

void kserial::clearBuf()
{
    serialBuffer = "";
}

void kserial::serialWrite(QString message)
{
    if(serialDeviceIsConnected == true)
    {
        usbDevice->write(message.toUtf8()); // Send the message to the device
        qDebug() << "Message to device: "<<message;
    }
}

bool kserial::connectMe(QSerialPortInfo myComPort)
{
    if(serialDeviceIsConnected == false)
        {
            usbDevice->setPortName(myComPort.portName());
            deviceDescription = myComPort.description();
            qDebug() << "connecting to: "<<usbDevice->portName();

            if(usbDevice->open(QIODevice::ReadWrite))
            {
                //Now the serial port is open try to set configuration
                if(!usbDevice->setBaudRate(baudrate))        //Depends on your boud-rate on the Device
                    qDebug()<<usbDevice->errorString();

                if(!usbDevice->setDataBits(QSerialPort::Data8))
                    qDebug()<<usbDevice->errorString();

                if(!usbDevice->setParity(QSerialPort::NoParity))
                    qDebug()<<usbDevice->errorString();

                if(!usbDevice->setStopBits(QSerialPort::OneStop))
                    qDebug()<<usbDevice->errorString();

                if(!usbDevice->setFlowControl(QSerialPort::NoFlowControl))
                    qDebug()<<usbDevice->errorString();

                //If any error was returned the serial il corrctly configured

                qDebug() << "Connection to: "<< usbDevice->portName() << " " << deviceDescription << " connected";
                serialDeviceIsConnected = true;
            }
            else
            {
                qDebug() << "Connection to: "<< usbDevice->portName() << " " << deviceDescription << " not connected";
                qDebug() <<"         Error: "<<usbDevice->errorString();
                serialDeviceIsConnected = false;
            }
        }
        else
        {
            qDebug() << "Can't connect, another device is connected";

        }
    return (serialDeviceIsConnected);
}

void kserial::getAvalilableSerialDevices()
{
    qDebug() << "Number of available ports: " << QSerialPortInfo::availablePorts().length();
    serialComPortList.clear();
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    {
        QString dbgStr = "Vendor ID: ";


       if(serialPortInfo.hasVendorIdentifier())
       {
          dbgStr+= serialPortInfo.vendorIdentifier();
       }
       else
       {
          dbgStr+= " - ";
       }
       dbgStr+= "  Product ID: ";
       if(serialPortInfo.hasProductIdentifier())
       {
          dbgStr+= serialPortInfo.hasProductIdentifier();
       }
       else
       {
          dbgStr+= " - ";
       }
       dbgStr+= " Name: " + serialPortInfo.portName();
       dbgStr+= " Description: "+serialPortInfo.description();
      qDebug()<<dbgStr;
      serialComPortList.push_back(serialPortInfo);
    }
}

void kserial::disconnectMe()
{
    if(serialDeviceIsConnected)
    {
        usbDevice->close();
        serialDeviceIsConnected = false;
        qDebug() << "Connection to: "<< usbDevice->portName() << " " << deviceDescription << " closed";
    }
    else
    {
       qDebug() << "Can't disconnect, no device is connected";
    }
}
