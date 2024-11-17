#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>
#include <QTabWidget>
#include <QTableWidget>
#include <QPixmap>

class MyWindow : public QWidget
{
    Q_OBJECT

public:
    MyWindow(QWidget *parent = nullptr);
private slots:
    void handleDropdownChange(int index); // Slot for dropdown changes
    void handleInput();                   // Declare the slot
    void onTabChanged(int index);
    void performCalculation();
    QComboBox* makeDropdown();

private:
    QLineEdit *encoderInputField;
    QLineEdit *encoderOutputField;
    QLineEdit *calculatorFirstInputField;
    QLineEdit *calculatorSecondInputField;
    QLineEdit *calculatorOutput;
    QLineEdit *stringInput;
    QLineEdit *stringOutput;
    QLineEdit *stringCharacterType;
    QLineEdit *stringCharacterCounter;


    QLabel *displayLabel;

    QComboBox *encodingTypeDropdown;
    QComboBox *outputEncodingDropdown;
    QComboBox *calculatorFirstInputDropdown;
    QComboBox *calculatorSecondInputDropdown;
    QComboBox *operationDropdown;
    QComboBox *calculatorOutputEncoding;
    QComboBox *stringOperationDropdown;

    QTabWidget *tabWidget;

    QWidget *homeTab;
    QWidget *encodingTab;
    QWidget *calculatorTab;
    QWidget *notesTab;
    QWidget *cheatSheetTab;
    QWidget *stringTab;

    void setupHomeTab();
    void setupEncodingTab();
    void setupCalculatorTab();
    void setupNotesTab();
    void setupCheatSheetTab();
    void setupStringTab();


};

#endif // MYWINDOW_H
