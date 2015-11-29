#ifndef RECEIVNAVDATA_H
#define RECEIVNAVDATA_H

#include <QThread>
#include <QTimer>
#include "navdata.h"
#include "navdata_structs.h"


class ReceivNavData : public QThread
{
        Q_OBJECT
    void run() Q_DECL_OVERRIDE{
        m_timer->start();
    }
public:
    ReceivNavData() ;
    void init_navdata() ;
    void close_navdata() ;

public slots:
    void process_nav_data() ;
signals:
    void copy_nav_data(nav_data_type);
private:
    QTimer *m_timer ;
    int m_freq ;
    nav_data_type nav_data ;

};

#endif // RECEIVNAVDATA_H
