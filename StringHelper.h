#ifndef STRINGHELPER_H
#define STRINGHELPER_H

#include <QString>

QString addPattern(QString value, QString pattern, int each);
QString removePattern(QString value, QString pattern, int each);
QString removeEach(QString value, int each);
QString removePosition(QString value, int position);
QString findPattern(QString input, QString pattern, int count);
QString replacePattern(QString input, QString pattern, int counter, QString replacement);




#endif // STRINGHELPER_H
