#include "roominfodialog.h"
#include "ui_roominfodialog.h"

roomInfoDialog::roomInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::roomInfoDialog)
{
    ui->setupUi(this);
    ui->lineEdit->setValidator(new QIntValidator(1, 65535, this));//LineEdit can only put numbers

}

roomInfoDialog::~roomInfoDialog()
{
    delete ui;
}
