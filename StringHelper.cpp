#include "StringHelper.h"
#include <QDebug>
#include <QRegularExpression>


QString addPattern(QString value, QString pattern,  int each){
    QString result;

    for (int i = 0; i < value.length() ; i++){
        result.append(value[i]);
        if ( (i + 1) % each == 0){
            result.append(pattern);
        }

    }
    return result;



}
/*
int main(int argc, char *argv[])
{
    qDebug() << addChar("AAAAAAA", "BB", 2);
    qDebug() << removePattern("abc-abc-abc-abc", "abc", 2);
    qDebug() << removeEach("123456", 2);
    qDebug() << removePosition("123", 2);
    return 0;
}
*/

QString removePattern(QString value, QString pattern, int each){
    QString result;
    int count = 0;

    QRegularExpression re(QRegularExpression::escape(pattern));
    QRegularExpressionMatchIterator it = re.globalMatch(value);

    int lastIndex = 0;

    while (it.hasNext()){
        QRegularExpressionMatch match = it.next();

        count ++;

        result += value.mid(lastIndex, match.capturedStart() - lastIndex);

        if (count % each != 0){
            result += match.captured();
        }
        lastIndex = match.capturedEnd();
    }

    result += value.mid(lastIndex);
    return result;
}
QString removeEach(QString value, int each){
    QString result;
    if (each != 1){
        result.append(value[0]);
    }
    for (int i = 1; i < value.length(); i++){
        if (((i + 1) % each) == 0){
            continue;
        }
        result.append(value[i]);
    }
    return result;

}
QString removePosition(QString value, int position){
    QString result;
    for (int i = 0; i < value.length(); i++){
        if (i + 1 != position){
            result.append(value[i]);
        }
    }
    return result;
}


QString findPattern(QString input, QString pattern, int counter){
    QRegularExpression regex(pattern);
    QRegularExpressionMatchIterator match = regex.globalMatch(input);
    QString result;
    int current = 1;

    while (match.hasNext()){
        QRegularExpressionMatch instance = match.next();
        if (current % counter == 0){
            result += instance.captured(0) + "\n";
        }
        current += 1;
    }
    return result;
}


QString replacePattern(QString input, QString pattern, int counter, QString replacement){
    QRegularExpression regex(pattern);
    QRegularExpressionMatchIterator match = regex.globalMatch(input);
    QString result = input;
    int current = 1;
    int offset = 0;

    while (match.hasNext()){
        QRegularExpressionMatch instance = match.next();
        if (current % counter == 0){
            result.replace(instance.capturedStart(0) + offset, instance.capturedLength(0), replacement);
            offset += replacement.length() - instance.capturedLength(0);
        }
        current += 1;
    }
    return result;

}



