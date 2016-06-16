#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
class QTcpSocket;
class QNetworkSession;
QT_END_NAMESPACE

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    //void requestHotelInfo;
    //void readHotelInfo;
    //!Maybe have the connected slot in the server go to a different slot if needed
    //void requestClientInfo;

private:
    Ui::MainWindow *ui;
    QTcpSocket *tcpSocket;
    QString clientData;
    quint16 blocksize;
    QNetworkSession *networkSession;
};

#endif // MAINWINDOW_H
