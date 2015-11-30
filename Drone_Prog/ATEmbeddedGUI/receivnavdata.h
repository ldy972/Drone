#ifndef RECEIVNAVDATA_H
#define RECEIVNAVDATA_H

#include <QThread>
#include <QTimer>
#include "navdata.h"
#include "perform_nav_data.h"


class ReceivNavData : public QThread
{
        Q_OBJECT
    void run() Q_DECL_OVERRIDE{
        m_timer->start();
    }
public:
    ReceivNavData() ;
    ~ReceivNavData() ;
    void init_navdata() ;
    void close_navdata() ;
    void duplicate_nav_data(nav_data_type* navdata) ;

public slots:
    void process_nav_data() ;
    void end_of_receiv_data() ;
signals:
    void copy_nav_data();
private:
    Perform_Nav_Data *t_perform_nav_data;
    QTimer *m_timer ;
    int m_freq ;

};

#endif // RECEIVNAVDATA_H
