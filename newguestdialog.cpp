#include "newguestdialog.h"
#include "ui_newguestdialog.h"

newGuestDialog::newGuestDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newGuestDialog)
{
    ui->setupUi(this);

    ui->lineEdit_2->setValidator(new QIntValidator(1, 65535, this));
    ui->lineEdit_3->setValidator(new QIntValidator(1, 65535, this));
}

newGuestDialog::~newGuestDialog()
{
    delete ui;
}

void newGuestDialog::setnewGuestData()
{
    newGuestName=ui->lineEdit->text();
    roomNumSet=ui->lineEdit_2->text();
    newNumNights=ui->lineEdit_3->text();
}
