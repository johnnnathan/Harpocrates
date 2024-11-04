#include "EncodingHelper.h"
#include <QMessageBox>
#include <QDebug>



EncodingType getEncodingType(int dropdownSelection)
{
    switch (dropdownSelection) {
    case 0:
        return BINARY;
    case 1:
        return DECIMAL;
    case 2:
        return HEX;
    case 3:
        return ASCII;
    default:
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);                   // Set the icon to critical
        msgBox.setText("Error");                                 // Title of the message box
        msgBox.setInformativeText("Encoding/Base type invalid"); // Detailed message
        msgBox.setStandardButtons(QMessageBox::Ok);              // Button options
        msgBox.exec();                                           // Show the message box
        return NONE;
    }
}



int binaryToDecimal(QString data){
    int length = data.length();
    if (length % 8 != 0){qDebug() << "Cannot Interpret Byte, not multiple of 8\n"; return 0;}
    int totalByte[length];
    for (int bit = 0 ; bit < length; bit++){
        totalByte[bit] = data.at(bit).digitValue();
    }
    int sum = 0;
    int power = 0;
    for (int index = length - 1; index > -1 ; index --){
        if (totalByte[index]){
            sum += pow(2, power);
        }
        power += 1;
    }
    return sum;
}


int encodingToDecimal(EncodingType encoding, QString data)
{
    switch (encoding) {
        case DECIMAL:
            return data.toInt();
        case BINARY:
            return binaryToDecimal(data);


    }
    if (encoding == DECIMAL)
        return data.toInt();
    int decimalValue = 0;
    int length = data.length();

    for (int index = 0; index < length; index++) {
        qDebug() << data.at(index).toLatin1();
    }
    return 0;
}



QString decimalToEncoding(EncodingType endEncoding, int value);
