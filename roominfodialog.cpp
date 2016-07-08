#include "roominfodialog.h"
#include "ui_roominfodialog.h"

roomInfoDialog::roomInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::roomInfoDialog)
{
    ui->setupUi(this);
    roomModel = new QStandardItemModel();
}

void roomInfoDialog::setRoomData(qint32 &roomNum, QString &bedType, bool &occupied){
    QString isOccupied;
    if(occupied){
        isOccupied = "Occupied";
    }
    else{
        isOccupied = "Vacant";
    }
    QStandardItem *item = new QStandardItem(QString("%0 | %1 | %2").arg(roomNum).arg(bedType).arg(isOccupied));
    roomModel->appendRow(item);
    ui->listView->setModel(roomModel);
}

void roomInfoDialog::clearData(){
    roomModel->clear();
}

roomInfoDialog::~roomInfoDialog()
{
    delete ui;
}

