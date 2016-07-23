#include "newguestdialog.h"
#include "ui_newguestdialog.h"

newGuestDialog::newGuestDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newGuestDialog)
{
    ui->setupUi(this);
//stops user from breaking the params of the set GuestData function
    ui->lineEdit_2->setValidator(new QIntValidator(1, 65535, this));
    ui->lineEdit_3->setValidator(new QIntValidator(1, 65535, this));
}

newGuestDialog::~newGuestDialog()
{
    delete ui;
}

void newGuestDialog::setnewGuestData()
{//gets handed off to the guestmodel Dialog for processing
    newGuestName=ui->lineEdit->text();
    roomNumSet=ui->lineEdit_2->text().toInt();
    newNumNights=ui->lineEdit_3->text().toInt();
}
