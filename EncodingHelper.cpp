#include "EncodingHelper.h"
#include <QDebug>
#include <QMessageBox>



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
        popup("Invalid Encoding type, I don't know how you did this, congratulations!!!");                   // Show the message box
        return NONE;
    }
}



void popup(QString message){
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Critical);                   // Set the icon to critical
    msgBox.setText("Error");                                 // Title of the message box
    msgBox.setInformativeText(message); // Detailed message
    msgBox.setStandardButtons(QMessageBox::Ok);              // Button options
    msgBox.exec();
}




long int hexToDecimal(QString data){
    int length = data.length();
    data = data.toUpper();

    int power = 0;
    long int sum = 0;
    int decimalValues[length];
    char tempChar;
    for (int index = length - 1; index > -1; index--){
        tempChar = data.at(index).toLatin1();
        sum += (tempChar - 65 + 10) * pow(16, power);
        power += 1;
    }

    return sum;

}



bool checkLength(int length, int modVal, int baseCase){
    if (baseCase == 0) baseCase = length;
    if (length % modVal != 0 && length != baseCase) {
        qDebug() << "Cannot Interpret Byte, not multiple of" + QString::number(modVal) + " \n";
        return false;
    }
    return true;
}


long int binaryToDecimal(QString data)
{
    int length = data.length();
    if (!checkLength(length, 8, 0)){return 0;}


    int totalByte[length];
    for (int bit = 0; bit < length; bit++) {
        totalByte[bit] = data.at(bit).digitValue();
    }
    long int sum = 0;
    int power = 0;
    for (int index = length - 1; index > -1; index--) {
        if (totalByte[index]) {
            sum += pow(2, power);
        }
        power += 1;
    }
    return sum;
}

long int encodingToDecimal(EncodingType encoding, QString data)
{
    switch (encoding) {
    case DECIMAL:
        return data.toInt();
    case BINARY:
        return binaryToDecimal(data);
    case HEX:
        return hexToDecimal(data);
    }

    return 0;
}

QString decimalToEncoding(EncodingType endEncoding, int value);
