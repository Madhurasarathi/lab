#include "iceplant.h"

/* Initialize ice plant */
IcePlant *init_plant(const char *name)
{
    IcePlant *plant = (IcePlant *)malloc(sizeof(IcePlant));
    assert(plant != NULL);

    strcpy(plant->plantName, name);
    plant->count = 0;
    plant->sumTemp = 0;
    plant->logHead = NULL;

    return plant;
}

/* Insert temperature in O(1) */
int insert_temperature(IcePlant *plant, int time, int temp,
                       int minAllowed, int maxAllowed)
{
    assert(plant != NULL);
    if (plant->count >= MAX_READINGS)
        return 0;

    /* Array insertion */
    plant->temps[plant->count++] = temp;
    plant->sumTemp += temp;

    if (plant->count == 1) {
        plant->minTemp = plant->maxTemp = temp;
    } else {
        if (temp < plant->minTemp) plant->minTemp = temp;
        if (temp > plant->maxTemp) plant->maxTemp = temp;
    }

    /* Linked list log entry */
    LogNode *node = (LogNode *)malloc(sizeof(LogNode));
    assert(node != NULL);

    node->time = time;
    node->temperature = temp;
    node->anomaly = (temp < minAllowed || temp > maxAllowed);
    node->next = plant->logHead;
    plant->logHead = node;

    /* Alarm */
    if (node->anomaly)
        printf("⚠ ALARM [%s] Time=%d Temp=%d\n",
               plant->plantName, time, temp);

    return 1;
}

/* Mean in O(1) */
float get_mean(IcePlant *plant)
{
    assert(plant->count > 0);
    return (float)plant->sumTemp / plant->count;
}

/* Display min, max, mean */
void display_stats(IcePlant *plant)
{
    printf("\nPlant: %s", plant->plantName);
    printf("\nMin Temp: %d", plant->minTemp);
    printf("\nMax Temp: %d", plant->maxTemp);
    printf("\nMean Temp: %.2f\n", get_mean(plant));
}

/* View logs by time window */
void view_logs(IcePlant *plant, int startTime, int endTime)
{
    LogNode *temp = plant->logHead;
    printf("\nLogs for %s (Time %d - %d)\n",
           plant->plantName, startTime, endTime);

    while (temp) {
        if (temp->time >= startTime && temp->time <= endTime) {
            printf("Time=%d Temp=%d %s\n",
                   temp->time,
                   temp->temperature,
                   temp->anomaly ? "[ANOMALY]" : "");
        }
        temp = temp->next;
    }
}

/* Free all memory */
void free_plant(IcePlant *plant)
{
    LogNode *temp;
    while (plant->logHead) {
        temp = plant->logHead;
        plant->logHead = temp->next;
        free(temp);
    }
    free(plant);
}
