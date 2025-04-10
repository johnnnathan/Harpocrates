#ifndef HOMETAB_H
#define HOMETAB_H

// HomeTab.h
#pragma once
#include <QWidget>

class QVBoxLayout;
class QTabWidget;

class HomeTab : public QWidget {
    Q_OBJECT

public:
    explicit HomeTab(QWidget *parent = nullptr);
    void addToTabWidget(QTabWidget *tabWidget);  // call this from MyWindow
};


#endif // HOMETAB_H
