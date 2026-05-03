#include <stdlib.h>
#include <stdio.h>
#include "ractangle.h"

void rectangle_draw(Shape *self) {
    Rectangle *r = (Rectangle*)self;
    printf("Draw Rectangle %dx%d\n", r->width, r->height);
}

/* 구체 팩토리 2: Rectangle 생성 */
Shape* create_RECTANGLE(void) {
    Rectangle *r = malloc(sizeof(Rectangle));
    if (!r) {
        return NULL;
    }
    r->base.draw = rectangle_draw;
    r->width = 4;
    r->height = 3;
    return (Shape *)r;
}