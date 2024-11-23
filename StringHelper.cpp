#include "StringHelper.h"
#include <QDebug>
#include <QRegularExpression>


QString addChar(QString value, QString pattern,  int each){
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
