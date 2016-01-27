#include "receivnavdata.h"

ReceivNavData::ReceivNavData()
{
    m_freq = 5000;
    m_timer = new QTimer;
    m_timer->setInterval(m_freq);

    t_perform_nav_data = new Perform_Nav_Data;

    QObject::connect(m_timer,SIGNAL(timeout()),this,SLOT(process_nav_data()));
    QObject::connect(t_perform_nav_data,SIGNAL(end_of_receiv()),this,SLOT(end_of_receiv_data()));
}


void ReceivNavData::init_navdata(){
    init_connection();
}

void ReceivNavData::close_navdata(){
    close_connection();
}

void ReceivNavData::process_nav_data(){
    t_perform_nav_data->start() ;
}

void ReceivNavData::end_of_receiv_data(){
    emit copy_nav_data();
}

void ReceivNavData::duplicate_nav_data(nav_data_type* navdata) {
    duplicate(navdata);
    navdata->is_ready=1 ;
}

ReceivNavData::~ReceivNavData(){
    t_perform_nav_data->quit();
    t_perform_nav_data->exit();
    delete m_timer;
}
