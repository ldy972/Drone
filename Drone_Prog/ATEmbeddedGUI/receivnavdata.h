#ifndef RECEIVNAVDATA_H
#define RECEIVNAVDATA_H

#include <QThread>
#include <QTimer>
#include "navdata.h"


class ReceivNavData : public QThread
{
    void run() : Q_DECL_OVERRIDE{

        init_connection();
        while(){
            receive_nav_data();
            emit copy_nav_data(navdata) ;
            while(!m_end_of_copy)
                m_timer->start(50);
            m_timer->start(m_freq);
        }
        close_connection();

    }
public:
    ReceivNavData();
public slots:
    void end_of_copy(bool copy);

signals:
    void copy_nav_data(navdata);
private:
    bool m_end_of_copy;
    QTimer *m_timer ;
    int m_freq ;
};

#endif // RECEIVNAVDATA_H
