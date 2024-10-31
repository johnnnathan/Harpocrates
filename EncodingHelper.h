#ifndef ENCODINGHELPER_H
#define ENCODINGHELPER_H

#include "EncodingType.h"
#include <QString>

EncodingType getEncodingType(int dropdownSelection);
int encodingToDecimal(EncodingType encoding, QString data);
QString decimalToEncoding(EncodingType endEncoding, int value);


#endif // ENCODINGHELPER_H
