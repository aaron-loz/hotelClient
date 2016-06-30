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

    //when socket is ready to be read, automatically reads the hotelInfo. Change this as different data gets set in.
    connect(tcpSocket, &QIODevice::readyRead, this, &MainWindow::readHotelInfo);
    //when socket has error, displays error
    typedef void (QAbstractSocket::*QAbstractSocketErrorSignal)(QAbstractSocket::SocketError);
    connect(tcpSocket, static_cast<QAbstractSocketErrorSignal>(&QAbstractSocket::error),
            this, &MainWindow::displayError);

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
        //so, this deals with the network session right?Then, it should call with network session
        connect(networkSession, &QNetworkSession::opened, this,&MainWindow::sessionOpened);
        qDebug()<<"networksession is connected";
        ui->statusLabel->setText("Connecting to Server...");
        networkSession->open();
    }


    ui->setupUi(this);

    ui->lineEdit->setValidator(new QIntValidator(1, 65535, this));//LineEdit can only put numbers
    QString hostName =QHostInfo::localHostName();

    if(!hostName.isEmpty()){
        ui->comboBox->addItem(hostName);
        QString domain = QHostInfo::localDomainName();
        if(!domain.isEmpty()){
            ui->comboBox->addItem(hostName +QChar('.') +domain);}
    }

    if(hostName != QLatin1String("localhost")){
        ui->comboBox->addItem(QString("localhost"));}
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    for(int i=0;i<ipAddressesList.size();i++){
        if(!ipAddressesList.at(i).isLoopback()){//if address doesn't have loopback, it is added to server namebox
            ui->comboBox->addItem(ipAddressesList.at(i).toString());}
    }

    for(int i=0;i<ipAddressesList.size();i++){
        //this is different because it allows for addresses with a loopback.
            if (ipAddressesList.at(i).isLoopback()){
                ui->comboBox->addItem(ipAddressesList.at(i).toString());}
    }
}


//!Action Slots
void MainWindow::on_action_Exit_triggered()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Exit", "Are you sure you wanna Quit?",
                                  QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes){
        QCoreApplication::exit();}
}

//!Network Slots
void MainWindow::sessionOpened(){
    qDebug()<<"sessionOpened called";
    QNetworkConfiguration config = networkSession->configuration();
    QString id;
    if (config.type() == QNetworkConfiguration::UserChoice)
        id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
    else
        id = config.identifier();

    QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
    settings.beginGroup(QLatin1String("QtNetwork"));
    settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
    settings.endGroup();
}

void MainWindow::readHotelInfo(){
    //!change this slot to the actual button press.
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);
    qDebug()<<"readHotelInfo called";

    //if blocksize does not have datasize, checks socket bytes and writes data to blocksize
    if (blocksize == 0) {//if isnt 16bit stream, stop
        if (tcpSocket->bytesAvailable() < (int)sizeof(quint16)){
            return;}
        in >> blocksize;
    }
    if (tcpSocket->bytesAvailable() < blocksize)
        return;//if socketbytes les than blocksize, stops slot cuz error.
    //inStream writes into nextFortune, which displays in qlabel
    QString hotelInfo;
    qint32 a[49];
    in >> hotelInfo;
    for(int i=0;i<49;i++){
    in>>a[i];
    }
    //if nextfortune is the same as currentFortune,sets timer to 0, which signals for requestNewFortune slot
    ui->statusLabel->setText("Hotel Server connected");
    QMessageBox::about(this, tr("hotel Info!"),hotelInfo);
}

void MainWindow::displayError(QAbstractSocket::SocketError socketError){
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The host was not found. Please check the "
                                    "host name and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The connection was refused by the peer. "
                                    "Make sure the fortune server is running, "
                                    "and check that the host name and port "
                                    "settings are correct."));
        break;
    default:
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The following error occurred: %1.")
                                 .arg(tcpSocket->errorString()));
    }
}

//!UI Slots
void MainWindow::on_pushButton_clicked()
{
    qDebug()<<"pushButton acts as sendFortune slot";
    blocksize = 0;
    tcpSocket->abort();
    int port = ui->lineEdit->text().toInt();
    tcpSocket->connectToHost(ui->comboBox->currentText(),port);

}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    ui->pushButton->setEnabled(true);
}

void MainWindow::on_lineEdit_returnPressed()
{
    on_pushButton_clicked();
}

void MainWindow::on_findRoom_clicked()
{
    roomDialog = new roomInfoDialog;
    if(roomDialog->exec()){

    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
