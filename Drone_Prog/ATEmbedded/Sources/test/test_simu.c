#include "../core/sim_real.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
    trajectory_measure_t max;
    printf("INIT\n");
    initialize_simulation();

    print_drone_state(stdout);
    printf("Rotate 1\n");
    rotate_right_simu(100, 90);
    print_drone_state(stdout);
    printf("Rotate 2\n");
    rotate_right_simu(100, 90);
    print_drone_state(stdout);
    printf("Rotate 3\n");
    rotate_right_simu(100, 90);
    print_drone_state(stdout);
    printf("Rotate 4\n");
    rotate_right_simu(100, 90);
    print_drone_state(stdout);
    printf("Rotate 5\n");
    rotate_right_simu(100, 45);
    print_drone_state(stdout);

    max = get_max_simulated_measure();
    printf("Max power: %f for heading %f\n", max.power, max.cap);

    printf("Forward\n");
    forward_simu(100, 100, get_simulated_heading());
    print_drone_state(stdout);

    max = get_max_simulated_measure();
    printf("Max power: %f for heading %f\n", max.power, max.cap);

    printf("FINISH\n");
    finish_simulation();

    printf("EXIT\n");
    return 0;
}
