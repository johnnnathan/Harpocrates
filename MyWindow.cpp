#include "MyWindow.h"
#include <QVBoxLayout>
#include "EncodingHelper.h"
#include "EncodingType.h"


MyWindow::MyWindow(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    tabWidget = new QTabWidget(this);
    mainLayout->addWidget(tabWidget);


    setupHomeTab();
    setupEncodingTab();
    setLayout(mainLayout);

    this->setFixedSize(this->size());

    connect(textField, &QLineEdit::textChanged, this, &MyWindow::handleInput);
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

    QLabel *authorLabel = new QLabel("by: name", this);
    authorLabel->setAlignment(Qt::AlignCenter);
    QFont authorFont = authorLabel->font();
    authorFont.setPointSize(14);
    authorLabel->setFont(authorFont);
    homeLayout->addWidget(authorLabel);

    QLabel *descriptionLabel = new QLabel("A RE multi-tool", this);
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

void MyWindow::setupCalculatorTab(){}
void MyWindow::setupNotesTab(){}
void MyWindow::setupCheatSheetTab(){}



void MyWindow::setupEncodingTab() {
    // Create main layout for the encoding tab
    encodingTab = new QWidget(this);
    QVBoxLayout *encodingLayout = new QVBoxLayout(encodingTab); // Only one main layout for encodingTab

    // Create a grid layout for the controls within the encoding tab
    QGridLayout *gridLayout = new QGridLayout();
    encodingLayout->addLayout(gridLayout); // Add grid layout to encodingLayout

    // Left section controls
    encodingTypeDropdown = new QComboBox(this);
    encodingTypeDropdown->addItem("Binary");
    encodingTypeDropdown->addItem("Decimal");
    encodingTypeDropdown->addItem("Hex");
    encodingTypeDropdown->addItem("ASCII");

    textField = new QLineEdit(this);
    textField->setPlaceholderText("Input value...");

    displayLabel = new QLabel(this);

    // Add left section widgets to the grid layout
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
    outputField->setReadOnly(true);  // Make output field read-only

    // Add right section widgets to the grid layout
    gridLayout->addWidget(outputEncodingDropdown, 0, 1);
    gridLayout->addWidget(outputField, 1, 1);

    // Add the encoding tab to the main tab widget
    tabWidget->addTab(encodingTab, "Encoding");

    connect(encodingTypeDropdown, &QComboBox::currentIndexChanged, this, &MyWindow::handleDropdownChange);
    connect(outputEncodingDropdown, &QComboBox::currentIndexChanged, this, &MyWindow::handleDropdownChange);
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



