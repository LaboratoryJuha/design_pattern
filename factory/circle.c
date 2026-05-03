#include <stdlib.h>
#include <stdio.h>
#include "circle.h"

void circle_draw(Shape *self) {
    Circle *c = (Circle*)self;
    printf("Draw Circle with radius=%d\n", c->radius);
}

/* 구체 팩토리 1: Circle 생성 */
Shape* create_CIRCLE(void) {
    Circle *c = malloc(sizeof(Circle));
    if (!c) {
        return NULL;
    }

    c->base.draw = circle_draw;
    c->radius = 5;
    return (Shape*)c;
}