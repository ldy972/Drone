#include "receivnavdata.h"

ReceivNavData::ReceivNavData()
{
    m_freq = 500;
    m_timer = new QTimer;
    m_timer->setInterval(m_freq);

    QObject::connect(m_timer,SIGNAL(timeout()),this,SLOT(process_nav_data()));
}


void ReceivNavData::init_navdata(){
    init_connection();
}

void ReceivNavData::close_navdata(){
    close_connection();
}

void ReceivNavData::process_nav_data(){
    receive_nav_data(&nav_data);
    emit copy_nav_data(nav_data);
}
