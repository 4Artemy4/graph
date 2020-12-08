#include <QtWidgets/QApplication>
#include "GUI/MainWindow.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow mainWindow;
    return QApplication::exec();
}
