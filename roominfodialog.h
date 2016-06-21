#ifndef ROOMINFODIALOG_H
#define ROOMINFODIALOG_H

#include <QDialog>

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
};

#endif // ROOMINFODIALOG_H
