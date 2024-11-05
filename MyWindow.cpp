#include "MyWindow.h"
#include <QVBoxLayout>
#include "EncodingHelper.h"
#include "EncodingType.h"
#include <QRegularExpression>
MyWindow::MyWindow(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    encodingTypeDropdown = new QComboBox(this);

    // Add encoding types to the menu
    encodingTypeDropdown->addItem("Binary");
    encodingTypeDropdown->addItem("Decimal");
    encodingTypeDropdown->addItem("Hex");
    encodingTypeDropdown->addItem("ASCII");

    layout->addWidget(encodingTypeDropdown);
    textField = new QLineEdit(this);
    textField->setPlaceholderText("Input value...");
    layout->addWidget(textField);

    displayLabel = new QLabel(this);
    layout->addWidget(displayLabel);

    setLayout(layout);


    connect(textField, &QLineEdit::textChanged, this, &MyWindow::handleInput);

    connect(encodingTypeDropdown, &QComboBox::currentIndexChanged, this, &MyWindow::handleDropdownChange);
}

void MyWindow::handleInput()
{
    QString inputText = textField->text().toUpper().remove(" ");
    EncodingType encoding = getEncodingType(encodingTypeDropdown->currentIndex());


    bool isValid = false;
    switch (encoding) {
    case BINARY:
        isValid = (inputText.length() % 8 == 0) && (inputText.count('0') + inputText.count('1') == inputText.length());
        break;
    case HEX:
        isValid = (inputText.length() % 2 == 0) && inputText.contains(QRegularExpression("^[0-9A-F]*$")); // Check for valid hex characters
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
            int result = encodingToDecimal(encoding, inputText);
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
