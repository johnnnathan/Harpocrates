#include "MyWindow.h"
#include "EncodingType.h"
#include "EncodingHelper.h"
#include <QVBoxLayout>

MyWindow::MyWindow(QWidget *parent) : QWidget(parent) {
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

    // Connect the editingFinished signal to handleInput slot
    connect(textField, &QLineEdit::editingFinished, this, &MyWindow::handleInput);
    // Connect the Encoding Type Dropdown menu for handling
    connect(encodingTypeDropdown, &QComboBox::currentIndexChanged, this, &MyWindow::handleDropdownChange);

}

void MyWindow::handleInput() {
    QString inputText = textField->text().toUpper();
    EncodingType encoding = getEncodingType(encodingTypeDropdown->currentIndex());
    encodingToDecimal(encoding, inputText);
    displayLabel->setText("You entered: " + inputText);
}

void MyWindow::handleDropdownChange(int index) {
    QString selectedItem = encodingTypeDropdown->currentText();
    displayLabel->setText("Selected: " + selectedItem);
}

