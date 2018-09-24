#ifndef SECAPP_H
#define SECAPP_H

#include "utils.h"

pthread_mutex_t mutex_grid;

void *thread_update_cars_pos(void *);

int detect_collision(unsigned int, car_packet_t, bool test_changez);

#endif /* SECAPP_H */
