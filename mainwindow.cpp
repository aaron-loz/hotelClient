#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    tcpSocket(new QTcpSocket(this)),
    blocksize(0),
    networkSession(Q_NULLPTR),
    ui(new Ui::MainWindow)
{
    setWindowTitle(tr("Hotel Client"));
    ui->setupUi(this);
    ui->comboBox->setEditable(true);

    QString hostName =QHostInfo::localHostName();
    if(!hostName.isEmpty()){
        ui->comboBox->addItem(hostName);
        QString domain = QHostInfo::localDomainName();
        if(!domain.isEmpty()){
            ui->comboBox->addItem(hostName +QChar('.') +domain);}
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
