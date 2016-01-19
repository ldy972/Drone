#include "io_manager.h"


int turn_right(int power, float heading_disp)
{
#ifdef SIMU
    return rotate_right_simu(power, heading_disp);
#else
    return rotate_right_mag(power, heading_disp);
#endif
}

int go_forward(int power, int times, float heading)
{
#ifdef SIMU
    return forward_simu(power, times, heading);
#else
    return forward_mag(power, times, heading);
#endif
}

float retrieve_heading()
{
#ifdef SIMU
    return get_simulated_heading();
#else
    return get_heading();
#endif
}

float retrieve_power()
{
#ifdef SIMU
    return get_simulated_power();
#else
    return get_simulated_power();
#endif
}

