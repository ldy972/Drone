#ifndef MANAGEWDG_H
#define MANAGEWDG_H

#include <QThread>
#include <QTimer>
#include "com.h"

class Managewdg : public QThread
{
        Q_OBJECT
    void run()  Q_DECL_OVERRIDE {
         timer->start();
         reload_watchdog() ;
    }
public:
    Managewdg();
    ~Managewdg();
public slots :
    void timeout() ;
signals:
    void resultReady(const int &s);
private:
    int m_test_value;
    QTimer *timer;

};

#endif // MANAGEWDG_H
