#ifndef GUESTINFODIALOG_H
#define GUESTINFODIALOG_H

#include <QDialog>

namespace Ui {
class guestInfoDialog;
}

class guestInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit guestInfoDialog(QWidget *parent = 0);
    ~guestInfoDialog();

private:
    Ui::guestInfoDialog *ui;
};

#endif // GUESTINFODIALOG_H
