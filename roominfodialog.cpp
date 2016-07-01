#include "roominfodialog.h"
#include "ui_roominfodialog.h"

roomInfoDialog::roomInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::roomInfoDialog)
{
    ui->setupUi(this);
    ui->lineEdit->setValidator(new QIntValidator(1, 65535, this));//LineEdit can only put numbers

}

void roomInfoDialog::setRoomData(qint32 &data, int i){
    QStandardItem *item = new QStandardItem(QString("%0 %1").arg(data).arg(i));
    roomModel = new QStandardItemModel();
    roomModel->appendRow(item);
    ui->listView->setModel(roomModel);
}

roomInfoDialog::~roomInfoDialog()
{
    delete ui;
}
