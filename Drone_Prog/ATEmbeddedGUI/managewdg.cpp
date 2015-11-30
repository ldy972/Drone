#include "managewdg.h"

Managewdg::Managewdg()
{
    m_test_value=0 ;
    timer = new QTimer ;

    timer->setInterval(1000);

    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));

}
Managewdg::~Managewdg(){
    delete timer;
}


void Managewdg::timeout(){
    emit resultReady(++m_test_value);
}
