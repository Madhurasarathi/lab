#ifndef BOILER_H
#define BOILER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_READINGS 144   // 24 hrs × 6 readings per hour

/* -------- LOG NODE (Linked List) -------- */
typedef struct log {
    int time;              // Minutes since start
    int temperature;
    int alarm;             // 1 = Unsafe temperature
    struct log *next;
} Log;

/* -------- BOILER STRUCTURE -------- */
typedef struct {
    char boilerName[20];

    /* Array storage */
    int tempArray[MAX_READINGS];
    int count;

    /* O(1) statistics */
    int minTemp;
    int maxTemp;
    int sumTemp;

    /* Log list */
    Log *logHead;
} Boiler;

/* -------- FUNCTION PROTOTYPES -------- */
Boiler *init_boiler(const char *name);
int record_temperature(Boiler *, int time, int temp, int minSafe, int maxSafe);
float average_temperature(Boiler *);
void display_statistics(Boiler *);
void view_logs(Boiler *, int start, int end);
void free_boiler(Boiler *);

#endif
