#ifndef PERFORM_NAV_DATA_H
#define PERFORM_NAV_DATA_H

#include <QThread>
#include "navdata.h"

class Perform_Nav_Data : public QThread
{
    Q_OBJECT
    void run() Q_DECL_OVERRIDE {
        receive_nav_data() ;
        emit end_of_receiv();
    }
public:
    Perform_Nav_Data();
signals:
    void end_of_receiv();
};

#endif // PERFORM_NAV_DATA_H
