#include "guestinfodialog.h"
#include "ui_guestinfodialog.h"

guestInfoDialog::guestInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::guestInfoDialog)
{
    ui->setupUi(this);
}

guestInfoDialog::~guestInfoDialog()
{
    delete ui;
}
