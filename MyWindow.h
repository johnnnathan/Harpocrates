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
    void onTabChanged(int index);

private:
    QTabWidget *tabWidget;
};

#endif // MYWINDOW_H
