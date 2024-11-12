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


private:
    QLineEdit *textField;
    QLineEdit *outputField;

    QLabel *displayLabel;

    QComboBox *encodingTypeDropdown;
    QComboBox *outputEncodingDropdown;

    QTabWidget *tabWidget;

    QWidget *homeTab;
    QWidget *encodingTab;
    QWidget *calculatorTab;
    QWidget *notesTab;
    QWidget *cheatSheetTab;

    void setupHomeTab();
    void setupEncodingTab();
    void setupCalculatorTab();
    void setupNotesTab();
    void setupCheatSheetTab();


};

#endif // MYWINDOW_H
