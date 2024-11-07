#ifndef ENCODINGHELPER_H
#define ENCODINGHELPER_H

#include <QString>
#include "EncodingType.h"

EncodingType getEncodingType(int dropdownSelection);
long int encodingToDecimal(EncodingType encoding, QString data);
QString decimalToEncoding(EncodingType endEncoding, int value);
long int binaryToDecimal(QString data);
long int hexToDecimal(QString data);
bool checkLength(int length, int modVal, int baseCase);
void popup(QString message);

#endif // ENCODINGHELPER_H
