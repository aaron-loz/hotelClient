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
    void changetoString(qint32 &num, bool &occupied);
    void changetoString(qint32 &checkIn, qint32 &numNights, qint32 &roomAssigned);
};

#endif // SAVEFILECLASS_H
