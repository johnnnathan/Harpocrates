#include "MyWindow.h"
#include <QVBoxLayout>
#include "CalculatorTab.h"
#include "HomeTab.h"
#include "StringsTab.h"
#include "EncodingTab.h"
#include <QPushButton>

MyWindow::MyWindow(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    tabWidget = new QTabWidget(this);
    mainLayout->addWidget(tabWidget);

    this->setFixedSize(this->size());

    connect(tabWidget, &QTabWidget::currentChanged, this, &MyWindow::onTabChanged);

    HomeTab* home = new HomeTab();
    home->addToTabWidget(tabWidget);
    EncodingTab* enc = new EncodingTab();
    enc->addToTabWidget(tabWidget);
    CalculatorTab* calc = new CalculatorTab();
    calc->addToTabWidget(tabWidget);
    StringsTab* strings = new StringsTab();
    strings->addToTabWidget(tabWidget);




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



