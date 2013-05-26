#include "myapplication.h"
#include "mynew.h"

myApplication::myApplication(int argc, char *argv[]) :
    QApplication(argc, argv)
{
}

myApplication::~myApplication() {
    printList();
    deleteList();
}
