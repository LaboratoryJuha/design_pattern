#ifndef CIRCLE_H
#define CIRCLE_H

#include "factory.h"

// 구체 제품 1: Circle
typedef struct {
    Shape base;
    int radius;
} Circle;

/* factory function prototype */
Shape* create_CIRCLE(void);

#endif