#ifndef ICEPLANT_H
#define ICEPLANT_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define MAX_READINGS 288   // 24 hours * 12 readings per hour

/* -------- LINKED LIST FOR LOG METADATA -------- */
typedef struct log_node {
    int time;                  // Minutes since start
    int temperature;
    int anomaly;               // 1 = anomaly, 0 = normal
    struct log_node *next;
} LogNode;

/* -------- ICE PLANT STRUCTURE -------- */
typedef struct {
    char plantName[20];

    /* Array for temperatures */
    int temps[MAX_READINGS];
    int count;

    /* O(1) statistics */
    int minTemp;
    int maxTemp;
    int sumTemp;

    /* Linked list for logs */
    LogNode *logHead;
} IcePlant;

/* -------- FUNCTION DECLARATIONS -------- */
IcePlant *init_plant(const char *name);
int insert_temperature(IcePlant *plant, int time, int temp, int minAllowed, int maxAllowed);
float get_mean(IcePlant *plant);
void display_stats(IcePlant *plant);
void view_logs(IcePlant *plant, int startTime, int endTime);
void free_plant(IcePlant *plant);

#endif
