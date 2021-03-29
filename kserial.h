#ifndef KSERIAL_H
#define KSERIAL_H

/* To include and use this library please add QT += serialport in qmake.pro file. */

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <vector>
#include <QMainWindow>



class kserial
{
public:
    kserial();
    ~kserial();

    void getAvalilableSerialDevices();
    QString serialRead();
    QString getBuf();
    void clearBuf();
    void serialWrite(QString message);
    bool connectMe(QSerialPortInfo myComPort);
    void disconnectMe();
    QSerialPort *usbDevice;
    bool serialDeviceIsConnected;
    std::vector<QSerialPortInfo> serialComPortList; //A list of the available ports for the dropdownmenue in the GUI


private:

    qint32 baudrate;
    QString deviceDescription;
    QString serialBuffer;


};

#endif // KSERIAL_H
