#include "usb_communicator.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    USB_Communicator w;
    w.show();
    return a.exec();
}
