#include "savefileclass.h"
#include <QDebug>

saveFileClass::saveFileClass()
{//will create file at start of mainwindow initialization
    file.setFileName("hotelData.txt");
    file.open(QIODevice::ReadWrite | QIODevice::Text|QFile::Truncate);
}

void saveFileClass::saveHotelData(QString &saveData)
{//QtextStream declared in each function
    //because data is lost using private class member
    QTextStream txtFileOut(&file);
if(file.isOpen()&& !saveData.isEmpty()){
        if(saveData!="King" && saveData!="Full")
        {
            txtFileOut<<"Name: ";
        }
         txtFileOut<<saveData;
    }
}

void saveFileClass::changetoString(qint32 &num, bool &occupied)
{//to make sure the conversion to TextStream is readable in a txt file.
    QTextStream txtFileOut(&file);
    QString isOccupied;
    if(occupied){
        isOccupied = "Occupied";
    }//parses through roomData for readability
    else{
        isOccupied = "Vacant";
    }

    QString changedData;
    changedData = tr(" %1: %2,\n ").arg(num).arg(isOccupied);
    txtFileOut<<changedData;
    //change params to QString, then output into dataOut
}

void saveFileClass::changetoString(qint32 &checkIn, qint32 &numNights, qint32 &roomAssigned)
{//does the same as the above except with different params for guestData.
    QTextStream txtFileOut(&file);
    QString changedData = tr(" Date of Check In: %1,Number of Nights Staying: %2, Room Number Assigned: %3\n")
            .arg(checkIn).arg(numNights).arg(roomAssigned);
    qDebug()<<changedData;
    txtFileOut<<changedData;
}

saveFileClass::~saveFileClass()
{
}
