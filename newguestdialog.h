#ifndef NEWGUESTDIALOG_H
#define NEWGUESTDIALOG_H

#include <QDialog>

namespace Ui {
class newGuestDialog;
}

class newGuestDialog : public QDialog
{
    Q_OBJECT

public:
    explicit newGuestDialog(QWidget *parent = 0);
    ~newGuestDialog();
    QString newGuestName;
    int newNumNights;
    int roomNumSet;

private slots:
    void setnewGuestData();
private:
    Ui::newGuestDialog *ui;
};

#endif // NEWGUESTDIALOG_H
