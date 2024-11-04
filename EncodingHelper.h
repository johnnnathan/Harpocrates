#ifndef ENCODINGHELPER_H
#define ENCODINGHELPER_H

#include <QString>
#include "EncodingType.h"

EncodingType getEncodingType(int dropdownSelection);
int encodingToDecimal(EncodingType encoding, QString data);
QString decimalToEncoding(EncodingType endEncoding, int value);

#endif // ENCODINGHELPER_H
