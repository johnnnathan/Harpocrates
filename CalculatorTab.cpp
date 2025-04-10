#include "TabHelper.h"
#include "CalculatorTab.h"
#include "EncodingType.h"
#include "EncodingHelper.h"
#include <qboxlayout.h>
#include <qcombobox.h>
#include <qlineedit.h>
#include <qpushbutton.h>



CalculatorTab::CalculatorTab(QWidget *parent) : QWidget(parent) {}

void CalculatorTab::addToTabWidget(QTabWidget* widget){

    QWidget* calculatorTab = new QWidget(this);
    QVBoxLayout *calculatorLayout = new QVBoxLayout(calculatorTab);

    calculatorFirstInputDropdown = makeDropdown();
    calculatorSecondInputDropdown = makeDropdown();

    calculatorOutputEncoding = makeDropdown();
    calculatorOutputEncoding->removeItem(4);

    calculatorFirstInputDropdown->setCurrentIndex(4);
    calculatorSecondInputDropdown->setCurrentIndex(4);

    calculatorFirstInputField = new QLineEdit(this);
    calculatorFirstInputField->setPlaceholderText("Value...");
    calculatorSecondInputField = new QLineEdit(this);
    calculatorSecondInputField->setPlaceholderText("Value...");
    calculatorOutput = new QLineEdit(this);
    calculatorOutput->setPlaceholderText("Output...");

    QPushButton *calculateButton = new QPushButton("=", this);

    operationDropdown = new QComboBox(this);

    operationDropdown->addItem("+");
    operationDropdown->addItem("-");
    operationDropdown->addItem("*");
    operationDropdown->addItem("/");
    operationDropdown->addItem("%");
    QGridLayout *gridLayout = new QGridLayout();
    calculatorSecondInputDropdown->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    calculatorSecondInputField->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // Top row: Input type dropdowns side by side
    gridLayout->addWidget(calculatorFirstInputDropdown, 0, 0);
    gridLayout->addWidget(calculatorSecondInputDropdown, 0, 2);  // Move this above the second input field

    // Second row: First input field, operation dropdown, second input field, and calculate button
    gridLayout->addWidget(calculatorFirstInputField, 1, 0);
    gridLayout->addWidget(operationDropdown, 1, 1);
    gridLayout->addWidget(calculatorSecondInputField, 1, 2);  // Ensure this is below the second dropdown
    gridLayout->addWidget(calculateButton, 1, 3);

    gridLayout->addWidget(calculatorOutput, 2,0,1,3);
    gridLayout->addWidget(calculatorOutputEncoding, 2, 3);

    calculatorLayout->addLayout(gridLayout);
    widget->addTab(calculatorTab, "Calculator");

    connect(calculateButton, &QPushButton::clicked, this, &CalculatorTab::performCalculation);
    connect(calculatorFirstInputField, &QLineEdit::textChanged, this, &CalculatorTab::handleCalcInput);
    connect(calculatorSecondInputField, &QLineEdit::textChanged, this, &CalculatorTab::handleCalcInput);



}

//Could not find a better way to do this, sorry :)
void CalculatorTab::handleCalcInput()
{
    QString calculatorFirstInput = calculatorFirstInputField->text().toUpper();
    QString calculatorSecondInput = calculatorSecondInputField->text().toUpper();

    EncodingType encoding;
    EncodingType outputEncoding;
    EncodingType calcFirstEnc;
    EncodingType calcSecEnc;

    calcFirstEnc = getEncodingType(calculatorFirstInputDropdown->currentIndex());
    calcSecEnc = getEncodingType(calculatorSecondInputDropdown->currentIndex());


    QString tempCalcFirst = calculatorFirstInput;
    QString tempCalcSecond = calculatorSecondInput;


    if (calcFirstEnc == AUTO){
        calcFirstEnc = getEncoding(calculatorFirstInput);
    }
    if (calcSecEnc == AUTO){
        calcSecEnc = getEncoding(calculatorSecondInput);
    }

    int stepCalcFirst = isValid(calcFirstEnc, tempCalcFirst.trimmed());
    int stepCalcSecond = isValid(calcSecEnc, tempCalcSecond.trimmed());

    if (stepCalcFirst != 0) {
        calculatorFirstInputField->setStyleSheet("background-color: green;");
    } else {
        calculatorFirstInputField->setStyleSheet("background-color: red;");
    }

    // Validate second calculator input field
    if (stepCalcSecond != 0) {
        calculatorSecondInputField->setStyleSheet("background-color: green;");
    } else {
        calculatorSecondInputField->setStyleSheet("background-color: red;");
    }

}
void CalculatorTab::performCalculation() {
    // Retrieve the input value, selected input and output encodings, and operation
    QString firstInputText = calculatorFirstInputField->text();
    QString secondInputText = calculatorSecondInputField->text();

    EncodingType firstInputEncoding = getEncodingType(calculatorFirstInputDropdown->currentIndex());
    EncodingType secondInputEncoding = getEncodingType(calculatorSecondInputDropdown->currentIndex());


    if (firstInputEncoding == AUTO){
        firstInputEncoding = getEncoding(firstInputText);
    }
    if (secondInputEncoding == AUTO){
        secondInputEncoding = getEncoding(secondInputText);
    }
    int operation = operationDropdown->currentIndex();

    long int first = encodingToDecimal(firstInputEncoding, firstInputText);
    long int second = encodingToDecimal(secondInputEncoding, secondInputText);
    long int result = 0;

    switch (operation) {
    case 0:
        result = first + second;
        break;
    case 1:
        result = first - second;
        break;
    case 2:
        result = first * second;
        break;
    case 3:
        result = first / second;
        break;
    case 4:
        result = first % second;
        break;
    default:
        result = 0;
        break;
    }




    // Display the result in output field
    calculatorOutput->setText(decimalToEncoding(getEncodingType(calculatorOutputEncoding->currentIndex()), result));
    calculatorFirstInputField->setText(calculatorOutput->text());
    calculatorSecondInputField->clear();
    handleCalcInput();
}
