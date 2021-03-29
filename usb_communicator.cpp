#include "usb_communicator.h"
#include "ui_usb_communicator.h"

kserial myusb;

USB_Communicator::USB_Communicator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::USB_Communicator)
{
    ui->setupUi(this);

    connect(myusb.usbDevice,SIGNAL(readyRead()),this,SLOT(onSerialDataAvailable()));

}

USB_Communicator::~USB_Communicator()
{
    delete ui;
}

void USB_Communicator::onSerialDataAvailable()
{
    QString statement;
    if(myusb.serialDeviceIsConnected == true)
    {
        myusb.serialRead(); // Read a chunk of the Message
        //To solve that problem I send a end char ";" in My case. That helped my to know when a message is complete

        if(myusb.getBuf().indexOf(";") != -1) //Message complete
        {
            qDebug() << "Message from device: "<<myusb.getBuf();
            statement = "RX: " + myusb.getBuf();
            ui->txtLog->append(statement);

            //Do something with de message here

            myusb.clearBuf();  //Clear the buffer;
        }
    }
}


void USB_Communicator::on_btnRefresh_clicked()
{
    myusb.getAvalilableSerialDevices();
    for (auto usb = myusb.serialComPortList.begin(); usb != myusb.serialComPortList.end(); ++usb)
    {
        ui->cmbUSBDevice->addItem(usb->portName() +" "+usb->description());
    }
}

void USB_Communicator::on_btnConnectUsb_clicked()
{
    myusb.connectMe(myusb.serialComPortList[ui->cmbUSBDevice->currentIndex()]);
}

void USB_Communicator::on_btnDisconnectUsb_clicked()
{
    myusb.disconnectMe();
}

void USB_Communicator::on_btnSend_clicked()
{
    QString statement;
    myusb.serialWrite(ui->txtSendStr->toPlainText());
    statement = "TX: " + ui->txtSendStr->toPlainText();
    ui->txtLog->append(statement);
    ui->txtSendStr->clear();
}
