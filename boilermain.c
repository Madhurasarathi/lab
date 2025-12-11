#include "boiler.h"

int main()
{
    Boiler *b1 = init_boiler("Boiler-1");
    Boiler *b2 = init_boiler("Boiler-2");

    /* Safe range: 200°C – 450°C */

    assert(record_temperature(b1, 10, 300, 200, 450));
    assert(record_temperature(b1, 20, 480, 200, 450)); // Alarm
    assert(record_temperature(b1, 30, 350, 200, 450));

    assert(record_temperature(b2, 10, 250, 200, 450));
    assert(record_temperature(b2, 20, 190, 200, 450)); // Alarm

    display_statistics(b1);
    display_statistics(b2);

    view_logs(b1, 0, 40);

    free_boiler(b1);
    free_boiler(b2);

    printf("\n✅ All tests passed\n");
    return 0;
}
