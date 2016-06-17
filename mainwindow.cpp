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
    if(hostName != QLatin1String("localhost")){
        ui->comboBox->addItem(QString("localhost"));}
    QList<QHostAddress> ipAddressList = QNetworkInterface::allAddresses();
    for(int i=0;i<ipAddressList.size();i++){
        if(!ipAddressList.at(i).isLoopback()){//if address doesn't have loopback, it is added to server namebox
            ui->comboBox->addItem(ipAddressList.at(i).toString());}
    }
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readHotelInfo()));
    typedef void (QAbstractSocket::*QAbstractSocketErrorSignal)(QAbstractSocket::SocketError);
    QNetworkConfigurationManager manager;
    if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) {
        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

        QNetworkConfiguration config = manager.configurationFromIdentifier(id);
        if ((config.state() & QNetworkConfiguration::Discovered) !=
            QNetworkConfiguration::Discovered) {
            config = manager.defaultConfiguration();
        }

        networkSession = new QNetworkSession(config, this);
        connect(networkSession, SIGNAL(&QNetworkSession::opened), this, SLOT(sessionOpened));
        ui->statusLabel->setText("Connecting to Server...");
        networkSession->open();
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    ui->pushButton->setEnabled(true);
}

void MainWindow::on_action_Exit_triggered()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Exit", "Are you sure you wanna Quit?",
                                  QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes){
        QCoreApplication::exit();}
}

void MainWindow::sessionOpened(){

}

void MainWindow::readHotelInfo(){

}
