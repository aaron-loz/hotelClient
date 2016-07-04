#ifndef ROOMINFODIALOG_H
#define ROOMINFODIALOG_H

#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class roomInfoDialog;
}

class roomInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit roomInfoDialog(QWidget *parent = 0);
    ~roomInfoDialog();

private:
    Ui::roomInfoDialog *ui;
    QStandardItemModel *roomModel;
public slots:
    void setRoomData(qint32 &data, QString &bedType, bool &occupied);
    void clearData();
private slots:
    void on_lineEdit_editingFinished();
};

#endif // ROOMINFODIALOG_H
