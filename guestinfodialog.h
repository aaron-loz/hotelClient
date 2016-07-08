#ifndef GUESTINFODIALOG_H
#define GUESTINFODIALOG_H

#include <QDialog>
#include <QStandardItemModel>

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
    QStandardItemModel *guestModel;
public slots:
    void clearData();
    void setGuestData(qint32 &roomNum, QString &guestName, int &numNights);

};

#endif // GUESTINFODIALOG_H
