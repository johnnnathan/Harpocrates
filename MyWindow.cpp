#include "MyWindow.h"
#include <QRegularExpression>
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
    QRegularExpression hexRegex("^[0-9A-F]*$");
    QString inputText = textField->text().toUpper().remove(" ");
    EncodingType encoding = getEncodingType(encodingTypeDropdown->currentIndex());
    EncodingType outputEncoding = getEncodingType(outputEncodingDropdown->currentIndex());


    if (outputEncoding == ASCII){

    }
    bool isValid = false;
    switch (encoding) {
    case BINARY:
        isValid = (inputText.length() % 8 == 0)
                  && (inputText.count('0') + inputText.count('1') == inputText.length());
        break;
    case HEX:
        isValid =  inputText.contains(hexRegex); // Check for valid hex characters
        break;
    case DECIMAL:
        isValid = inputText.toInt();
        break;
    case ASCII:
        isValid = !inputText.isEmpty();
        break;
    default:
        isValid = false;
        break;
    }

    if (isValid) {
        textField->setStyleSheet("background-color: green;");
        if (encoding == BINARY || encoding == HEX) {
            // Perform conversion if valid
            long int result = encodingToDecimal(encoding, inputText);
            displayLabel->setText(inputText + " -> " + QString::number(result));
        } else {
            displayLabel->setText("Valid " + encodingTypeDropdown->currentText() + " input.");
        }
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
