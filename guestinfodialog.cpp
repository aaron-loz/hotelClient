#include "guestinfodialog.h"
#include "ui_guestinfodialog.h"
#include <QStandardItem>


guestInfoDialog::guestInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::guestInfoDialog)
{
    ui->setupUi(this);
    guestModel = new QStandardItemModel();
}

guestInfoDialog::~guestInfoDialog()
{
    delete ui;
}

void guestInfoDialog::clearData(){
    guestModel->clear();
}

void guestInfoDialog::setGuestData(qint32 &roomNum, QString &guestName, int &numNights, int &checkInDate){

    QStandardItem *item = new QStandardItem(QString("%0 | %1 | %2 nights | CheckIn: %3").arg(guestName).arg(roomNum).arg(numNights).arg(checkInDate));
    guestModel->appendRow(item);
    ui->listView->setModel(guestModel);
}
