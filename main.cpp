#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Q");
    MainWindow w;
    w.setWindowIcon(QIcon("./ss_icon.ico"));
    w.setWindowIconText("Q");
    w.show();
    return a.exec();
}
