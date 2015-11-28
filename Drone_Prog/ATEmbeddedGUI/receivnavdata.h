#ifndef RECEIVNAVDATA_H
#define RECEIVNAVDATA_H

#include "navdata.h"


class ReceivNavData
{
public:
    ReceivNavData();

    uint16_t get_id();                        // Navdata block ('option') identifier
    uint16_t get_size();                      // set this to the size of this structure

    uint32_t get_ctrl_state();               // Flying state (landed, flying, hovering, etc.) defined in CTRL_STATES enum.
    uint32_t get_vbat_flying_percentage();   // battery voltage filtered (mV)

    float32_t get_theta();                    // pitch angle in milli-degrees
    float32_t get_phi();                      // roll  angle
    float32_t get_psi();                      // yaw   angle

    int32_t get_altitude();                 // altitude in centimeters[??]

    float32_t get_vx();                       // estimated linear velocity
    float32_t get_vy();                       // estimated linear velocity
    float32_t get_vz();

signals:
    void copy_nav_data(nav_data_type &navdata);
private:
    //nav_data_type nav_data; //définie dans le navdata.h - zone partagée
};

#endif // RECEIVNAVDATA_H
