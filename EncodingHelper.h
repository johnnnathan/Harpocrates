#ifndef ENCODINGHELPER_H
#define ENCODINGHELPER_H

#include <QString>
#include "EncodingType.h"
#include <QRegularExpression>



EncodingType getEncodingType(int dropdownSelection);
long int encodingToDecimal(EncodingType encoding, QString data);
QString decimalToEncoding(EncodingType endEncoding, long int value);
long int binaryToDecimal(QString data);
long int hexToDecimal(QString data);
bool checkLength(int length, int modVal, int baseCase);
void popup(QString message);
int isValid(EncodingType encoding, QString data);
QString encode(EncodingType startEncoding, EncodingType endEncoding, QString data, int step);
QString decimalToBinary(long int value);
QString decimalToHex(long int value);

#endif // ENCODINGHELPER_H
