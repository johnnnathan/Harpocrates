#include "MyWindow.h"
#include <QVBoxLayout>
#include "EncodingHelper.h"
#include "EncodingType.h"


MyWindow::MyWindow(QWidget *parent)
    : QWidget(parent)
{

    // Main grid layout for alignment
    QGridLayout *gridLayout = new QGridLayout(this);

    // Left section controls
    encodingTypeDropdown = new QComboBox(this);
    encodingTypeDropdown->addItem("Binary");
    encodingTypeDropdown->addItem("Decimal");
    encodingTypeDropdown->addItem("Hex");
    encodingTypeDropdown->addItem("ASCII");

    textField = new QLineEdit(this);
    textField->setPlaceholderText("Input value...");

    displayLabel = new QLabel(this);

    // Add left section widgets to grid layout
    gridLayout->addWidget(encodingTypeDropdown, 0, 0);
    gridLayout->addWidget(textField, 1, 0);
    gridLayout->addWidget(displayLabel, 2, 0);

    // Right section controls
    outputEncodingDropdown = new QComboBox(this);
    outputEncodingDropdown->addItem("Binary");
    outputEncodingDropdown->addItem("Decimal");
    outputEncodingDropdown->addItem("Hex");
    outputEncodingDropdown->addItem("ASCII");

    outputField = new QLineEdit(this);
    outputField->setPlaceholderText("Output value...");
    outputField->setReadOnly(true);  // Make it read-only for copying

    // Add right section widgets to grid layout
    gridLayout->addWidget(outputEncodingDropdown, 0, 1);
    gridLayout->addWidget(outputField, 1, 1);

    setLayout(gridLayout);

    // Connect signals to slots
    connect(textField, &QLineEdit::textChanged, this, &MyWindow::handleInput);
    connect(encodingTypeDropdown, &QComboBox::currentIndexChanged, this, &MyWindow::handleDropdownChange);
}

void MyWindow::handleInput()
{

    QString inputText = textField->text().toUpper();

    EncodingType encoding = getEncodingType(encodingTypeDropdown->currentIndex());
    EncodingType outputEncoding = getEncodingType(outputEncodingDropdown->currentIndex());

    int step = isValid(encoding, inputText);


    if (step != 0) {
        textField->setStyleSheet("background-color: green;");
        outputField->setText(encode(encoding, outputEncoding, inputText,step));
    } else {
        textField->setStyleSheet("background-color: red;");
        displayLabel->setText("Invalid input for " + encodingTypeDropdown->currentText());
    }
}

void MyWindow::handleDropdownChange(int index)
{
    QString selectedItem = encodingTypeDropdown->currentText();
    displayLabel->setText("Selected: " + selectedItem);
}
