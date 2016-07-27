#include "savefileclass.h"

saveFileClass::saveFileClass()
{
    file.setFileName("hotelData.txt");
}

void saveFileClass::saveHotelData(QString &saveData)
{
    QTextStream dataOut(&file);
    if (file.open(QIODevice::ReadWrite | QIODevice::Text))
     dataOut<<saveData;
else{
    }
}

saveFileClass::~saveFileClass()
{
}
