#ifndef ENCODINGTAB_H
#define ENCODINGTAB_H



#include <qcombobox.h>
#include <qlabel.h>
#include <qlineedit.h>
#pragma once
#include <QWidget>

class QVBoxLayout;
class QTabWidget;

class EncodingTab: public QWidget {
    Q_OBJECT

public:
    explicit EncodingTab(QWidget *parent = nullptr);
    void addToTabWidget(QTabWidget *tabWidget);  // call this from MyWindow
    void handleInput();
private:
    QLineEdit *encoderInputField;
    QLineEdit *encoderOutputField;
    QComboBox *encodingTypeDropdown;
    QComboBox *outputEncodingDropdown;
    QWidget *encodingTab;
    QLabel *displayLabel;
};

#endif // ENCODINGTAB_H
