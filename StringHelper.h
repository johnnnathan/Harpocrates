#ifndef STRINGHELPER_H
#define STRINGHELPER_H

#include <QString>

QString addChar(QString value, QString pattern, int each);
QString removePattern(QString value, QString pattern, int each);
QString removeEach(QString value, int each);
QString removePosition(QString value, int position);




#endif // STRINGHELPER_H
