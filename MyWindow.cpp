#include "MyWindow.h"
#include <QVBoxLayout>
#include "EncodingHelper.h"
#include "EncodingType.h"

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

    // Connect the editingFinished signal to handleInput slot
    connect(textField, &QLineEdit::editingFinished, this, &MyWindow::handleInput);
    // Connect the Encoding Type Dropdown menu for handling
    connect(encodingTypeDropdown,
            &QComboBox::currentIndexChanged,
            this,
            &MyWindow::handleDropdownChange);
}

void MyWindow::handleInput()
{
    QString inputText = textField->text().toUpper();
    EncodingType encoding = getEncodingType(encodingTypeDropdown->currentIndex());
    int result = encodingToDecimal(encoding, inputText);
    displayLabel->setText(inputText + "->" + QString::number(result));
}

void MyWindow::handleDropdownChange(int index)
{
    QString selectedItem = encodingTypeDropdown->currentText();
    displayLabel->setText("Selected: " + selectedItem);
}

