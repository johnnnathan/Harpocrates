#include "MyWindow.h"
#include <QVBoxLayout>
#include "EncodingHelper.h"
#include "EncodingType.h"
#include <QPushButton>

MyWindow::MyWindow(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    tabWidget = new QTabWidget(this);
    mainLayout->addWidget(tabWidget);


    setupHomeTab();
    setupEncodingTab();
    setLayout(mainLayout);
    setupCalculatorTab();
    setupStringTab();
    this->setFixedSize(this->size());

    connect(encoderInputField, &QLineEdit::textChanged, this, &MyWindow::handleInput);
    connect(encodingTypeDropdown, &QComboBox::currentIndexChanged, this, &MyWindow::handleDropdownChange);
    connect(tabWidget, &QTabWidget::currentChanged, this, &MyWindow::onTabChanged);
}
void MyWindow::setupHomeTab(){
    homeTab = new QWidget(this);
    QVBoxLayout *homeLayout = new QVBoxLayout(homeTab);


    QSpacerItem *topSpacer = new QSpacerItem(20, 60, QSizePolicy::Minimum, QSizePolicy::Expanding);
    homeLayout->addItem(topSpacer);  // Adjust this value if needed for spacing


    QLabel *titleLabel = new QLabel("Harpocrates", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(24);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    homeLayout->addWidget(titleLabel);

    QLabel *authorLabel = new QLabel("by: Dimitrios Tsiplakis", this);
    authorLabel->setAlignment(Qt::AlignCenter);
    QFont authorFont = authorLabel->font();
    authorFont.setPointSize(14);
    authorLabel->setFont(authorFont);
    homeLayout->addWidget(authorLabel);

    QLabel *descriptionLabel = new QLabel("A Reverse Engineering multi-tool", this);
    descriptionLabel->setAlignment(Qt::AlignCenter);
    QFont descriptionFont = descriptionLabel->font();
    descriptionFont.setPointSize(12);
    descriptionLabel->setFont(descriptionFont);
    homeLayout->addWidget(descriptionLabel);


    QSpacerItem *middleSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    homeLayout->addItem(middleSpacer);  // Spacer for some space between text and image

    QPixmap pixmap(":/images/images/logo.png");
    QPixmap scaledPixmap = pixmap.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QLabel *imageLabel = new QLabel(this);
    imageLabel->setPixmap(scaledPixmap);
    imageLabel->setAlignment(Qt::AlignCenter);
    homeLayout->addWidget(imageLabel);

    tabWidget->addTab(homeTab, "Home");
}

//Constructor for the dropdowns, usually the same so a waste to repeat self.
QComboBox* MyWindow::makeDropdown(){
    QComboBox *temp = new QComboBox(this);
    temp->addItem("Binary");
    temp->addItem("Decimal");
    temp->addItem("Hex");
    temp->addItem("ASCII");
    return temp;
}

void MyWindow::setupCalculatorTab(){
    calculatorTab = new QWidget(this);
    QVBoxLayout *calculatorLayout = new QVBoxLayout(calculatorTab);

    calculatorFirstInputDropdown = makeDropdown();

    calculatorSecondInputDropdown = makeDropdown();

    calculatorOutputEncoding = makeDropdown();

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
    tabWidget->addTab(calculatorTab, "Calculator");

    connect(calculateButton, &QPushButton::clicked, this, &MyWindow::performCalculation);
    connect(calculatorFirstInputField, &QLineEdit::textChanged, this, &MyWindow::handleInput);
    connect(calculatorSecondInputField, &QLineEdit::textChanged, this, &MyWindow::handleInput);



}

void MyWindow::setupStringTab(){
    stringTab =              new QWidget(this);
    QVBoxLayout *layout =    new QVBoxLayout(stringTab);
    stringInput =            new QLineEdit(this);
    stringOutput =           new QLineEdit(this);
    stringCharacterCounter = new QLineEdit(this);
    stringCharacterType =    new QLineEdit(this);

    stringOperationDropdown = new QComboBox(this);

    QPushButton *operateButton = new QPushButton("=", this);

    stringInput->setPlaceholderText("Input...");
    stringOutput->setPlaceholderText("Output...");
    stringCharacterCounter->setPlaceholderText("Every x appearances...");
    stringCharacterType->setPlaceholderText("Character...");

    stringCharacterType->setMaxLength(1);
    stringCharacterCounter->setMaxLength(2);
    QIntValidator *intValidator = new QIntValidator(0, 99, stringInput);
    stringCharacterCounter->setValidator(intValidator);

    int lineHeight = stringInput->fontMetrics().height();
    stringInput->setMinimumHeight(2 * lineHeight + 10);
    stringOutput->setMinimumHeight(2 * lineHeight + 10);


    stringOperationDropdown->addItem("Append");
    stringOperationDropdown->addItem("Subtract");

    QHBoxLayout *operationLayout = new QHBoxLayout();
    operationLayout->addWidget(stringOperationDropdown);
    operationLayout->addWidget(stringCharacterType);
    operationLayout->addWidget(stringCharacterCounter);

    operationLayout->addWidget(operateButton);


    layout->addWidget(stringInput);
    layout->addLayout(operationLayout);
    layout->addWidget(stringOutput);

    stringTab->setLayout(layout);
    tabWidget->addTab(stringTab, "String Operations");


}
void MyWindow::setupNotesTab(){}
void MyWindow::setupCheatSheetTab(){}

void MyWindow::performCalculation() {
    // Retrieve the input value, selected input and output encodings, and operation
    QString firstInputText = calculatorFirstInputField->text();
    QString secondInputText = calculatorSecondInputField->text();

    EncodingType firstInputEncoding = getEncodingType(calculatorFirstInputDropdown->currentIndex());
    EncodingType secondInputEncoding = getEncodingType(calculatorSecondInputDropdown->currentIndex());

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
}


void MyWindow::setupEncodingTab() {
    // Create main layout for the encoding tab
    encodingTab = new QWidget(this);
    QVBoxLayout *encodingLayout = new QVBoxLayout(encodingTab); // Only one main layout for encodingTab

    // Create a grid layout for the controls within the encoding tab
    QGridLayout *gridLayout = new QGridLayout();
    encodingLayout->addLayout(gridLayout); // Add grid layout to encodingLayout

    // Left section controls
    encodingTypeDropdown = makeDropdown();

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
    tabWidget->addTab(encodingTab, "Encoding");

    connect(encodingTypeDropdown, &QComboBox::currentIndexChanged, this, &MyWindow::handleDropdownChange);
    connect(outputEncodingDropdown, &QComboBox::currentIndexChanged, this, &MyWindow::handleDropdownChange);
}

//Could not find a better way to do this, sorry :)
void MyWindow::handleInput()
{

    QString inputText = encoderInputField->text().toUpper();

    QString calculatorFirstInput = calculatorFirstInputField->text().toUpper();
    QString calculatorSecondInput = calculatorSecondInputField->text().toUpper();

    EncodingType encoding;
    EncodingType outputEncoding;
    EncodingType calcFirstEnc;
    EncodingType calcSecEnc;

    if (tabWidget->currentIndex() == 1){
        encoding = getEncodingType(encodingTypeDropdown->currentIndex());
        outputEncoding = getEncodingType(outputEncodingDropdown->currentIndex());
    }
    else if (tabWidget->currentIndex() == 2){
        calcFirstEnc = getEncodingType(calculatorFirstInputDropdown->currentIndex());
        calcSecEnc = getEncodingType(calculatorSecondInputDropdown->currentIndex());

    }

    int step = isValid(encoding, inputText);
    int stepCalcFirst = isValid(calcFirstEnc, calculatorFirstInput);
    int stepCalcSecond = isValid(calcSecEnc, calculatorSecondInput);

    //Encoding Tab Validation.
    if (tabWidget->currentIndex() == 1) {
        if (step != 0) {
            encoderInputField->setStyleSheet("background-color: green;");
            qDebug() << outputEncoding;
            encoderOutputField->setText(encode(encoding, outputEncoding, inputText, step));
        } else {
            encoderInputField->setStyleSheet("background-color: red;");
            displayLabel->setText("Invalid input for " + encodingTypeDropdown->currentText());
        }
        return;
    }

    // Calculator Tab Validation
    if (tabWidget->currentIndex() == 2) {
        // Validate first calculator input field
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
}
void MyWindow::onTabChanged(int index) {
    if (index == 0) {
        this->resize(600,450);
        this->setFixedSize(this->size());

    } else {
        this->setMinimumSize(400, 300);
        this->setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
    }
}
void MyWindow::handleDropdownChange(int index)
{
    handleInput();
}



