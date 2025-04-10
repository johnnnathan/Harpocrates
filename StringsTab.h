#ifndef STRINGSTAB_H
#define STRINGSTAB_H

#include <qcombobox.h>
#include <qtextedit.h>>
#pragma once
#include <QWidget>

class QVBoxLayout;
class QTabWidget;

class StringsTab: public QWidget {
    Q_OBJECT

public:
    explicit StringsTab(QWidget *parent = nullptr);
    void addToTabWidget(QTabWidget *tabWidget);  // call this from MyWindow
    void performStringOperation();
private:
    QWidget   *stringTab;
    QComboBox *stringOperationDropdown;
    QTextEdit *stringInput;
    QTextEdit *stringOutput;
    QLineEdit *stringCharacterType;
    QLineEdit *stringCharacterCounter;
};
#endif // STRINGSTAB_H
