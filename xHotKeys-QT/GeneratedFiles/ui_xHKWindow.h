/********************************************************************************
** Form generated from reading UI file 'xHKWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XHKWINDOW_H
#define UI_XHKWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_xHKWindowClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *xHKWindowClass)
    {
        if (xHKWindowClass->objectName().isEmpty())
            xHKWindowClass->setObjectName(QStringLiteral("xHKWindowClass"));
        xHKWindowClass->resize(600, 400);
        menuBar = new QMenuBar(xHKWindowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        xHKWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(xHKWindowClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        xHKWindowClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(xHKWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        xHKWindowClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(xHKWindowClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        xHKWindowClass->setStatusBar(statusBar);

        retranslateUi(xHKWindowClass);

        QMetaObject::connectSlotsByName(xHKWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *xHKWindowClass)
    {
        xHKWindowClass->setWindowTitle(QApplication::translate("xHKWindowClass", "xHKWindow", 0));
    } // retranslateUi

};

namespace Ui {
    class xHKWindowClass: public Ui_xHKWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XHKWINDOW_H
