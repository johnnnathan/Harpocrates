#include "StringsTab.h"
#include "StringHelper.h"
#include <qboxlayout.h>
#include <qlineedit.h>
#include <qpushbutton.h>


StringsTab::StringsTab(QWidget *parent) : QWidget(parent) {}



void StringsTab::addToTabWidget(QTabWidget* widget){
    stringTab = new QWidget(this);
    QVBoxLayout *layout =    new QVBoxLayout(stringTab);

    stringOperationDropdown = new QComboBox(this);

    QPushButton *operateButton = new QPushButton("=", this);

    stringInput = new QTextEdit();
    stringOutput = new QTextEdit();
    stringCharacterCounter = new QLineEdit();
    stringCharacterType = new QLineEdit();

    stringInput->setPlaceholderText("Input...");
    stringOutput->setPlaceholderText("Output...");
    stringCharacterCounter->setPlaceholderText("Every x appearances...");
    stringCharacterType->setPlaceholderText("Character...");


    int lineHeight = stringInput->fontMetrics().height();
    stringInput->setMinimumHeight(2 * lineHeight + 10);
    stringOutput->setMinimumHeight(2 * lineHeight + 10);


    stringOperationDropdown->addItem("Append");
    stringOperationDropdown->addItem("Subtract");
    stringOperationDropdown->addItem("Find");

    QHBoxLayout *operationLayout = new QHBoxLayout();
    operationLayout->addWidget(stringOperationDropdown);
    operationLayout->addWidget(stringCharacterType);
    operationLayout->addWidget(stringCharacterCounter);

    operationLayout->addWidget(operateButton);


    layout->addWidget(stringInput);
    layout->addLayout(operationLayout);
    layout->addWidget(stringOutput);

    stringTab->setLayout(layout);
    widget->addTab(stringTab, "String Operations");
    connect(operateButton, &QPushButton::clicked, this, &StringsTab::performStringOperation);



}


void StringsTab::performStringOperation(){
    QString input = stringInput->toPlainText();
    QString output;
    int characterCounter = stringCharacterCounter->text().toInt();
    QString characterType = stringCharacterType->text();
    int operation = stringOperationDropdown->currentIndex();
    int length = input.length();
    switch (operation) {
    case 0:
        output = addPattern(input, characterType, characterCounter);
        break;
    case 1:
        switch (length) {
        case 0:
            output = removePosition(input, characterCounter);
            break;
        default:
            output = removePattern(input, characterType, characterCounter);
            break;
        }
        break;
    case 2:
        output = findPattern(input, characterType);
    default:
        break;
    }
    stringOutput->setText(output);
}
