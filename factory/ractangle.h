#ifndef RACTANGLE_H
#define RACTANGLE_H

#include "factory.h"

// 구체 제품 2: Rectangle
typedef struct {
    Shape base;
    int width;
    int height;
} Rectangle;

/* factory function prototype */
Shape* create_RECTANGLE(void);

#endif