#include "receivnavdata.h"

ReceivNavData::ReceivNavData()
{
    m_end_of_copy = false;
    m_freq = 500;
    m_timer = new QTimer;
    m_timer->setInterval(m_freq);

    QObject::connect(this->parent(),SIGNAL())

}

void ReceivNavData::end_of_copy(bool copy){
    m_end_of_copy = copy ;
}
