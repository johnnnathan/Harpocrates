
// HomeTab.cpp
#include "HomeTab.h"
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QLabel>
#include <QPixmap>
#include <QTabWidget>
#include <QFont>

HomeTab::HomeTab(QWidget *parent) : QWidget(parent) {}

void HomeTab::addToTabWidget(QTabWidget *tabWidget) {
    QWidget *homeTab = new QWidget(tabWidget);
    QVBoxLayout *homeLayout = new QVBoxLayout(homeTab);

    QSpacerItem *topSpacer = new QSpacerItem(20, 60, QSizePolicy::Minimum, QSizePolicy::Expanding);
    homeLayout->addItem(topSpacer);

    QLabel *titleLabel = new QLabel("Harpocrates", homeTab);
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(24);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    homeLayout->addWidget(titleLabel);

    QLabel *authorLabel = new QLabel("by: Dimitrios Tsiplakis", homeTab);
    authorLabel->setAlignment(Qt::AlignCenter);
    QFont authorFont = authorLabel->font();
    authorFont.setPointSize(14);
    authorLabel->setFont(authorFont);
    homeLayout->addWidget(authorLabel);

    QLabel *descriptionLabel = new QLabel("A Reverse Engineering multi-tool", homeTab);
    descriptionLabel->setAlignment(Qt::AlignCenter);
    QFont descriptionFont = descriptionLabel->font();
    descriptionFont.setPointSize(12);
    descriptionLabel->setFont(descriptionFont);
    homeLayout->addWidget(descriptionLabel);

    QSpacerItem *middleSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    homeLayout->addItem(middleSpacer);

    QPixmap pixmap(":/images/images/logo.png");
    QPixmap scaledPixmap = pixmap.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QLabel *imageLabel = new QLabel(homeTab);
    imageLabel->setPixmap(scaledPixmap);
    imageLabel->setAlignment(Qt::AlignCenter);
    homeLayout->addWidget(imageLabel);

    homeTab->setLayout(homeLayout);
    tabWidget->addTab(homeTab, "Home");
}
