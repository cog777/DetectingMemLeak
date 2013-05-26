#ifndef MYCOREAPPLICATION_H
#define MYCOREAPPLICATION_H

#include <QApplication>

class myApplication : public QApplication
{
    Q_OBJECT
public:
    explicit myApplication(int argc, char *argv[]);
    virtual ~myApplication();
    
signals:
    
public slots:

};

#endif // MYCOREAPPLICATION_H
