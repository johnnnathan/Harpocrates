#ifndef CALCULATORTAB_H
#define CALCULATORTAB_H

#include <qcombobox.h>
#pragma once
#include <QWidget>

class QVBoxLayout;
class QTabWidget;

class CalculatorTab: public QWidget {
    Q_OBJECT

public:
    explicit CalculatorTab(QWidget *parent = nullptr);
    void addToTabWidget(QTabWidget *tabWidget);  // call this from MyWindow
    void handleCalcInput();
    void performCalculation();

private:

    QComboBox *operationDropdown;
    QComboBox *calculatorOutputEncoding;
    QComboBox *calculatorFirstInputDropdown;
    QComboBox *calculatorSecondInputDropdown;
    QLineEdit *calculatorFirstInputField;
    QLineEdit *calculatorSecondInputField;
    QLineEdit *calculatorOutput;
};
#endif // CALCULATORTAB_H
