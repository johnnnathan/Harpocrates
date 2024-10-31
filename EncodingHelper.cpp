#include "EncodingHelper.h"
#include <QMessageBox>
#include <iostream>


EncodingType getEncodingType(int dropdownSelection){
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
        msgBox.setIcon(QMessageBox::Critical); // Set the icon to critical
        msgBox.setText("Error"); // Title of the message box
        msgBox.setInformativeText("Encoding/Base type invalid"); // Detailed message
        msgBox.setStandardButtons(QMessageBox::Ok); // Button options
        msgBox.exec(); // Show the message box
        return NONE;
    }
}

int encodingToDecimal(EncodingType encoding, QString data){
    if (encoding == DECIMAL) return data.toInt();
    int decimalValue = 0;
    int length = data.length();


    for (int index = 0; index < length; index++){
        qDebug() << data.at(index).toLatin1();
    }
    return 0;
}

QString decimalToEncoding(EncodingType endEncoding, int value);
