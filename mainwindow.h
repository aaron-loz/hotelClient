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
    void sessionOpened();
    //void requestHotelInfo();
    void readHotelInfo();
    //!Maybe have the connected slot in the server go to a different slot if needed
    //void requestClientInfo();
    void displayError(QAbstractSocket::SocketError socketError);

    void on_lineEdit_textChanged(const QString &arg1);
    void on_action_Exit_triggered();
    void on_pushButton_clicked();

    void on_lineEdit_returnPressed();

    void on_findRoom_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket *tcpSocket;
    QString clientData;
    quint16 blocksize;
    QNetworkSession *networkSession;
};

#endif // MAINWINDOW_H
