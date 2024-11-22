#include "EncodingHelper.h"
#include <QDebug>
#include <QMessageBox>
#include "EncodingType.h"

//Takes in the index of a dropdown menu and returns the EncodingType value.
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
        popup("Invalid Encoding type, I don't know how you did this, congratulations!!!");
        return NONE;
    }
}


// Wrapper for the Qt QMessageBox object.
void popup(QString message){
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Critical);                   // Set the icon to critical
    msgBox.setText("Error");                                 // Title of the message box
    msgBox.setInformativeText(message); // Detailed message
    msgBox.setStandardButtons(QMessageBox::Ok);              // Button options
    msgBox.exec();
}



//Take a hex string and return the decimal representation.
long int hexToDecimal(QString data){
    int length = data.length();
    //To upper to not have to handle both capital and lowercase characters
    data = data.toUpper();

    int power = 0;
    long int sum = 0;
    int decimalValues[length];
    char tempChar;
    for (int index = length - 1; index >= 0; index--) {
        char tempChar = data.at(index).toLatin1();
        int decimalValue;

        if (tempChar >= '0' && tempChar <= '9') {
            decimalValue = tempChar - '0';
        } else if (tempChar >= 'A' && tempChar <= 'F') {
            decimalValue = tempChar - 65 + 10;
        }

        sum += decimalValue * pow(16, power);
        power++;
    }

    return sum;

}


//Check if the length of a value is divisible by a certain step size. Used for value evaluation when getting input.
//Example. Binary values should be divisible by 8
bool checkLength(int length, int modVal, int baseCase){
    if (baseCase == 0) baseCase = length;
    if (length % modVal != 0 && length != baseCase) {
        qDebug() << "Cannot Interpret Byte, not multiple of" + QString::number(modVal) + " \n";
        return false;
    }
    return true;
}

//Translate the binary representation of a value to decimal.
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

//Handler for translations of a certain encoding type to decimal.Translate to decimal to not have to handle each combination of encodings manually.
//Instead of (n)*(n-1) combinations there are 2(n).
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



//Handles input evaluation. Checks encoding type and ensures that the length of the input is able to be handled by the translation function.
//Returns the step count, which works as both an int value and a boolean value for the calling functions.
int isValid(EncodingType encoding, QString data){
    bool isValid = false;
    int step = 0;
    QString temp = data;
    QRegularExpression hexRegex("^[0-9A-F]*$");

    switch (encoding) {
    case BINARY:

        isValid = (temp.length() % 8 == 0)
                  && (temp.count('0') + temp.count('1') == temp.length());
        if (isValid){
            step = 8;
        }
        break;
    case HEX:

        isValid =  temp.contains(hexRegex); // Check for valid hex characters
        if (isValid){
            step = 2;
        }
        break;
    case DECIMAL:
        //Need to use a temp variable because it alters the value stored inside the variable.
        //Should not remove the spaces in the original variable because it could affect the ascii results, where applicable
        isValid = temp.remove(" ").toInt();
        if(isValid) {
            step = 1;
        }
        break;
    case ASCII:

        isValid = !temp.isEmpty();
        if (isValid) {
            step =  1;
        }
        break;
    default:
        step = 0;

    }

    return step;
}


//Decimal to binary translation. Quite basic
QString decimalToBinary(long int value){

    QString output;
    const int base = 2;
    while (value != 0){
        int remainder = value % base;
        char character;
        if (remainder){
            character = '1';
        }else {
            character = '0';
        }
        output.prepend(character);
        value /= base;
    }
    return output;
}

//Decimal to hex translation.
QString decimalToHex(long int value){

    QString output;
    const int base = 16;
    while (value != 0){
        int remainder = value % base;
        char character;
        //If starting with the Alphabetic representation
        if (remainder > 9){
            //Moves to just before the start of the capital alphabetic characters in ascii allow for iteration over them, since F is the maximum reachable value
            character = remainder + 55;
        }else {
            character = remainder + 48;
        }
        output.prepend(character);
        value /= base;
    }
    return output;

}
long int asciiToDecimal(QString value){
    QString result;

    for (int i = 0; i < value.length(); i++){
        result.append(QString::number(value[i].toLatin1()));

    }

    return result.toLong();

}


QString decimalToEncoding(EncodingType endEncoding, long int value){
    if (endEncoding == HEX){return decimalToHex(value);}
    if (endEncoding == BINARY){return decimalToBinary(value);}
    if (endEncoding == DECIMAL){return QString::number(value);}
    return "0";
}


// Use the starting and ending representation to handle all of the translations. Only this needs to be called
QString encode(EncodingType startEncoding, EncodingType endEncoding, QString data, int step){
    if (startEncoding == BINARY || startEncoding == HEX) {
        if (endEncoding == ASCII){
            QString resultString;
            for (int byte = 0; byte < data.length(); byte += step){
                QString chunk = data.mid(byte, step); // Get subset
                qDebug() << chunk;
                long int decimalValue = encodingToDecimal(startEncoding, chunk);
                resultString.append(static_cast<char>(decimalValue)); // Convert to ASCII character
                byte++;
            }
            return(resultString);

        }
        else{
            long int result = encodingToDecimal(startEncoding, data);
            return decimalToEncoding(endEncoding, result);


        }
    }
    if (startEncoding == ASCII){
        return decimalToEncoding(endEncoding, asciiToDecimal(data));
    }
    if (startEncoding == DECIMAL && endEncoding == ASCII){

        QString resultString;
        QStringList bytes = data.split(" " , Qt::SkipEmptyParts);
        for (const QString &byte : bytes){
            int decimalValue = byte.toInt();

            resultString.append(static_cast<char>(decimalValue));
        }
        return resultString;

    }
    long int decimalData = encodingToDecimal(startEncoding, data);


    return decimalToEncoding(endEncoding, decimalData);
}


