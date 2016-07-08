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

void guestInfoDialog::setGuestData(qint32 &roomNum, QString &guestName, int &numNights){

    QStandardItem *item = new QStandardItem(QString("%0 | %1 | %2").arg(roomNum).arg(guestName).arg(numNights));
    guestModel->appendRow(item);
    ui->listView->setModel(guestModel);
}
