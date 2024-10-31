#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>

class MyWindow : public QWidget {
    Q_OBJECT

public:
    MyWindow(QWidget *parent = nullptr);

private slots:
    void handleDropdownChange(int index);  // Slot for dropdown changes
    void handleInput();  // Declare the slot


private:
    QLineEdit *textField;
    QLabel *displayLabel;
    QComboBox *encodingTypeDropdown;
};

#endif // MYWINDOW_H
