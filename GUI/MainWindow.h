//
// Created by art on 11/22/20.
//

#ifndef LABA4_MAINWINDOW_H
#define LABA4_MAINWINDOW_H

#define HIGH 1080
#define WIDTH 1920
#define windowHigh 830
#define windowWidth 1200

#include <QtWidgets/QPushButton>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QVBoxLayout>
#include <QAction>
#include "GraphWindow.h"

class MainWindow {
private:
    QWidget *window;
    QVBoxLayout *mainLayout;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QMenu *menuEdit;

    int tabNumber = 0;
    QTabWidget *tabs;
    QAction *newTab;
    QAction *delTab;
public:
    MainWindow() {
        window = new QWidget();
        window->setGeometry((WIDTH / 2 - windowWidth / 2), (HIGH / 2 - windowHigh / 2), windowWidth, windowHigh);
        mainLayout = new QVBoxLayout;
        menuBarActionsInit();
        menuBarInit();
        tabs = new QTabWidget(window);
        mainLayout->addWidget(tabs);
        window->setLayout(mainLayout);
        window->show();
    }

    void menuBarActionsInit() {
        newTab = new QAction("Add tab");
        QWidget::connect(newTab, &QAction::triggered, window, [=] {
            tabs->addTab(new GraphWindow(window), "tab" + QString::number(++tabNumber));
        });
        delTab = new QAction("Del tab");
        QWidget::connect(delTab, &QAction::triggered, window, [=] {
            tabs->removeTab(tabs->currentIndex());
        });
    }

    void menuBarInit() {
        menuFile = new QMenu("File");
        menuFile->addAction(newTab);
        menuFile->addAction(delTab);
        menuEdit = new QMenu("Edit");
        menuHelp = new QMenu("Help");
        menuBar = new QMenuBar();
        menuBar->addMenu(menuFile);
        menuBar->addMenu(menuEdit);
        menuBar->addMenu(menuHelp);
        mainLayout->addWidget(menuBar);
    }

    ~MainWindow() {
        delete menuBar;
        delete menuFile;
        delete menuHelp;
        delete menuEdit;
        delete newTab;
        delete delTab;
        delete tabs;
        delete window;
    }
};


#endif //LABA4_MAINWINDOW_H
