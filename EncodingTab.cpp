#include "EncodingHelper.h"
#include "TabHelper.h"
#include <qgridlayout.h>
#include <qlabel.h>
#include "EncodingTab.h"



EncodingTab::EncodingTab(QWidget *parent) : QWidget(parent) {}

void EncodingTab::addToTabWidget(QTabWidget* widget) {
    // Create main layout for the encoding tab
    encodingTab = new QWidget(this);
    QVBoxLayout *encodingLayout = new QVBoxLayout(encodingTab); // Only one main layout for encodingTab

    // Create a grid layout for the controls within the encoding tab
    QGridLayout *gridLayout = new QGridLayout();
    encodingLayout->addLayout(gridLayout); // Add grid layout to encodingLayout

    // Left section controls
    encodingTypeDropdown = makeDropdown();
    encodingTypeDropdown->setCurrentIndex(4);

    encoderInputField = new QLineEdit(this);
    encoderInputField->setPlaceholderText("Input value...");

    displayLabel = new QLabel(this);

    // Add left section widgets to the grid layout
    gridLayout->addWidget(encodingTypeDropdown, 0, 0);
    gridLayout->addWidget(encoderInputField, 1, 0);
    gridLayout->addWidget(displayLabel, 2, 0);

    // Right section controls
    outputEncodingDropdown = makeDropdown();

    encoderOutputField = new QLineEdit(this);
    encoderOutputField->setPlaceholderText("Output value...");
    encoderOutputField->setReadOnly(true);  // Make output field read-only

    // Add right section widgets to the grid layout
    gridLayout->addWidget(outputEncodingDropdown, 0, 1);
    gridLayout->addWidget(encoderOutputField, 1, 1);

    // Add the encoding tab to the main tab widget
    widget->addTab(encodingTab, "Encoding");

    connect(encodingTypeDropdown, &QComboBox::currentIndexChanged, this, &EncodingTab::handleInput);
    connect(outputEncodingDropdown, &QComboBox::currentIndexChanged, this, &EncodingTab::handleInput);
    connect(encoderInputField, &QLineEdit::textChanged, this, &EncodingTab::handleInput);
    connect(encodingTypeDropdown, &QComboBox::currentIndexChanged, this, &EncodingTab::handleInput);
}
void EncodingTab::handleInput()
{

    QString inputText = encoderInputField->text().toUpper();

    EncodingType encoding;
    EncodingType outputEncoding;
    EncodingType calcFirstEnc;
    EncodingType calcSecEnc;

        encoding = getEncodingType(encodingTypeDropdown->currentIndex());
        outputEncoding = getEncodingType(outputEncodingDropdown->currentIndex());

    QString temp = inputText;
    temp = temp.replace(" " , "");


    if (encoding == AUTO){
        encoding = getEncoding(temp);
    }

    int step = isValid(encoding, temp.trimmed());

    //Encoding Tab Validation.
    if (step != 0) {
        encoderInputField->setStyleSheet("background-color: green;");
        qDebug() << outputEncoding;
        encoderOutputField->setText(encode(encoding, outputEncoding, inputText, step));
     } else {
        encoderInputField->setStyleSheet("background-color: red;");
        displayLabel->setText("Invalid input for " + encodingTypeDropdown->currentText());
    }


}
