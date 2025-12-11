#include "iceplant.h"

int main()
{
    /* Initialize plants */
    IcePlant *plant1 = init_plant("Plant-A");
    IcePlant *plant2 = init_plant("Plant-B");

    /* Insert readings */
    assert(insert_temperature(plant1, 10, -5, -10, 0) == 1);
    assert(insert_temperature(plant1, 15, -12, -10, 0) == 1); // anomaly
    assert(insert_temperature(plant1, 20, -7, -10, 0) == 1);

    assert(insert_temperature(plant2, 10, -3, -8, 2) == 1);
    assert(insert_temperature(plant2, 15, 5, -8, 2) == 1);    // anomaly

    /* Display stats */
    display_stats(plant1);
    display_stats(plant2);

    /* View logs */
    view_logs(plant1, 0, 30);

    /* Cleanup */
    free_plant(plant1);
    free_plant(plant2);

    printf("\nAll assertions passed ✅\n");
    return 0;
}
