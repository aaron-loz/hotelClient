#include "savefileclass.h"
#include <QDebug>

saveFileClass::saveFileClass()
{//will create file at start of mainwindow initialization
    file.setFileName("hotelData.txt");
    file.open(QIODevice::ReadWrite | QIODevice::Text);
}

void saveFileClass::saveHotelData(QString &saveData)
{//setDevice is declared multiple times because constructor does not carry over setDevice call.
    dataOut.setDevice(&file);

    if (file.isOpen()){
     dataOut<<saveData;
     }
}

void saveFileClass::changetoString(qint32 &num, bool &occupied)
{//to make sure the conversion to TextStream is readable in a txt file.
    dataOut.setDevice(&file);

    QString isOccupied;
    if(occupied){
        isOccupied = "Occupied";
    }//parses through roomData for readability
    else{
        isOccupied = "Vacant";
    }

    QString changedData;
    changedData = tr(" %1: %2,\n ").arg(num).arg(isOccupied);
    dataOut<<changedData;
    //change params to QString, then output into dataOut
}

void saveFileClass::changetoString(qint32 &checkIn, qint32 &numNights, qint32 &roomAssigned)
{//This is to do the same as the above except with different params for guestData.
    dataOut.setDevice(&file);
    QString changedData = tr("Date of Check In: %1,Number of Nights Staying: %2, Room Number Assigned: %3")
            .arg(checkIn).arg(numNights).arg(roomAssigned);
    //!Bold the chars beefore outputting to dataOut
    dataOut<<changedData;
}

saveFileClass::~saveFileClass()
{
}
