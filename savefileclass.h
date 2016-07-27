#ifndef SAVEFILECLASS_H
#define SAVEFILECLASS_H

#include <QFile>
#include <QTextStream>
#include <QMessageBox>

class saveFileClass : public QFile
{
    Q_OBJECT
public:
    saveFileClass();
    ~saveFileClass();
private:
    QFile file;
public slots:
    void saveHotelData(QString &saveData);
};

#endif // SAVEFILECLASS_H
