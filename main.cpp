#include "mainwindow.h"
#include "myapplication.h"

int main(int argc, char *argv[])
{
    myApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
