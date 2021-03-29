#ifndef USB_COMMUNICATOR_H
#define USB_COMMUNICATOR_H

#include <QMainWindow>
#include "kserial.h"

QT_BEGIN_NAMESPACE
namespace Ui { class USB_Communicator; }
QT_END_NAMESPACE

class USB_Communicator : public QMainWindow
{
    Q_OBJECT

public:
    USB_Communicator(QWidget *parent = nullptr);
    ~USB_Communicator();

private slots:
    void onSerialDataAvailable();

    void on_btnRefresh_clicked();

    void on_btnConnectUsb_clicked();

    void on_btnDisconnectUsb_clicked();

    void on_btnSend_clicked();

private:
    Ui::USB_Communicator *ui;
};
#endif // USB_COMMUNICATOR_H
