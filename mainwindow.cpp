#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    tcpSocket(new QTcpSocket(this)),
    blocksize(0),
    networkSession(Q_NULLPTR),
    roomDialog(new roomInfoDialog),
    guestDialog(new guestInfoDialog),
    newguestDialog(new newGuestDialog),
    saveFile(new saveFileClass),
    ui(new Ui::MainWindow)
{
    //when socket is ready to be read, initializzes network.
    connect(tcpSocket, &QIODevice::readyRead, this, &MainWindow::readHotelInfo);
    typedef void (QAbstractSocket::*QAbstractSocketErrorSignal)(QAbstractSocket::SocketError);
    connect(tcpSocket, static_cast<QAbstractSocketErrorSignal>(&QAbstractSocket::error),
            this, &MainWindow::displayError);
    //incase configuration changes, the manager keeps those changes
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
        //if the manager capabilities are already set, goes straight to opening the socket
        networkSession = new QNetworkSession(config, this);
        connect(networkSession, &QNetworkSession::opened, this,&MainWindow::sessionOpened);
        networkSession->open();
    }
    ui->setupUi(this);

    //stops port from being broken though letters
    ui->lineEdit->setValidator(new QIntValidator(1, 65535, this));
    QString hostName =QHostInfo::localHostName();

    //adds host address to combobox in case server and client are on same machine
    if(!hostName.isEmpty()){
        ui->comboBox->addItem(hostName);
        QString domain = QHostInfo::localDomainName();
        if(!domain.isEmpty()){
            ui->comboBox->addItem(hostName +QChar('.') +domain);}
    }

    if(hostName != QLatin1String("localhost")){
        ui->comboBox->addItem(QString("localhost"));}
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
//allows user to choose which server address to connect to, both local and not
    for(int i=0;i<ipAddressesList.size();i++){
        if(!ipAddressesList.at(i).isLoopback()){//if address doesn't have loopback, it is added to server namebox
            ui->comboBox->addItem(ipAddressesList.at(i).toString());}
    }

    for(int i=0;i<ipAddressesList.size();i++){
            if (ipAddressesList.at(i).isLoopback()){
                ui->comboBox->addItem(ipAddressesList.at(i).toString());}
    }
    setWindowTitle(tr("Hotel Client"));

}


//!Action Slots
void MainWindow::on_action_Exit_triggered()
{//standard exit action slot
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Exit", "Are you sure you wanna Quit?",
                                  QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes){
        QCoreApplication::exit();}
}

//!Network Slots
void MainWindow::sessionOpened(){
    //keeps track of network configuration
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
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);
    //if blocksize doesnt have datasize, checks socket bytes and writes data to blocksize
    if (blocksize == 0) {
        //stops anything that is not 16bit
        if (tcpSocket->bytesAvailable() < (int)sizeof(quint16)){
            return;}
        in >> blocksize;
    }
    if (tcpSocket->bytesAvailable() < blocksize)
        return;//if socketbytes les than blocksize, stops slot cuz error.
    //actual data being reccieve into datastream
    in >> hotelInfo;

    for(int i=0;i<=49;i++){
    in>>roomNum[i];
    in>>bedType[i];
    in>>occupied[i];
    saveFile->saveHotelData(bedType[i]);
    saveFile->changetoString(roomNum[i],occupied[i]);
    }//data transfered to dialog and saveFile.
    for(int i=0;i<3;i++){
     in>>fullName[i];
      in>>checkInDate[i];
     in>>numNights[i];
      in>>roomNumAssigned[i];
      saveFile->saveHotelData(fullName[i]);
      qDebug()<<checkInDate[i];
      saveFile->changetoString(checkInDate[i],numNights[i], roomNumAssigned[i]);
    }

    //Unless port is retyped or changed, pushbutton stays off to stop any data being lossed.
    ui->statusLabel->setText("Hotel Server connected");
    ui->pushButton->setEnabled(false);
    socketConnected = true;
    QMessageBox::about(this, tr("hotel Info!"),hotelInfo);

    //data gets added to dialog for user to interact with
    for(int i=0;i<=49;i++){
        bedType[49]="Full";
    roomDialog->setRoomData(roomNum[i], bedType[i], occupied[i]);
    }
    //!Use qDebug to see how the datastream sorts out where everything goes.
    for(int i=0;i<3;i++){
        fullName[0]="Aaron L.";
        guestDialog->setGuestData(roomNumAssigned[i],fullName[i],numNights[i], checkInDate[i]);
    }
}

void MainWindow::displayError(QAbstractSocket::SocketError socketError){
    //in case of error recieving from server
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
    //lets more data come from server without confusing data in dialogs
    blocksize = 0;
    tcpSocket->abort();
    socketConnected =false;
    roomDialog->clearData();
    guestDialog->clearData();
    int port = ui->lineEdit->text().toInt();
    tcpSocket->connectToHost(ui->comboBox->currentText(),port);
}

void MainWindow::on_lineEdit_textChanged()
{//stops user from tyring to connect without a port
    ui->pushButton->setEnabled(true);
}

void MainWindow::on_lineEdit_returnPressed()
{//user can press return without having to press button
    on_pushButton_clicked();
}

void MainWindow::on_findRoom_clicked()
{
    if(roomDialog->exec()){
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_findGuest_clicked()
{
    if(guestDialog->exec()){
    }
}

void MainWindow::on_actionNew_Guest_triggered()
{//Since QDate isnt the standard format for the date,
    //turns QDate into QString then into int to streamline function param implementation
    if(newguestDialog->exec()){
        QString currentDay=QString::number(today.day());
        QString currentMonth=QString::number(today.month());
        QString currentYear=QString::number(today.year());
        QString currentDate=currentMonth;
        currentDate.append(currentDay);
        currentDate.append(currentYear);
        int currentDateInt=currentDate.toInt();
        guestDialog->setGuestData(newguestDialog->roomNumSet,newguestDialog->newGuestName,
                                  newguestDialog->newNumNights,currentDateInt);
    }
}

void MainWindow::on_actionAbout_2_triggered()
{
    QMessageBox::information(this,"About hotelClient","By Aaron L.,\n Using QT,\nCreated 2016.");
}

void MainWindow::on_actionHotel_Information_triggered()
{
    QMessageBox::about(this, tr("hotel Info!"),hotelInfo);
}
