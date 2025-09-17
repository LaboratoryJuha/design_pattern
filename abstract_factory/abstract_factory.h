// Abstract Factory Pattern Example
#ifndef ABSTRACT_FACTORY_H
#define ABSTRACT_FACTORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

// cleanup attribute는 변수의 주소를 인자로 넘기므로, 포인터를 free하려면 래퍼가 필요합니다.
static inline void auto_free(void *pp) {
    void **p = (void**)pp;
    if (p && *p) {
        free(*p);
        *p = NULL;
    }
}
#define AUTO_FACTORY_FREE __attribute__((__cleanup__(auto_free)))

// 제품 인터페이스: Shape
typedef struct Shape {
    void (*draw)(struct Shape *self);
} Shape;

typedef struct {
    Shape base;
    int radius;
} Circle;

typedef struct {
    Shape base;
    int width, height;
} Rectangle;

// 추상 팩토리 구조체
typedef struct Abstract_factory {
    Shape* (*create_circle)(void);
    Shape* (*create_rectangle)(void);
} Abstract_factory;

void circle_draw(Shape *self);
void rectangle_draw(Shape *self) ;

Shape* modern_create_circle(void);
Shape* modern_create_rectangle(void);
Shape* classic_create_circle(void);
Shape* classic_create_rectangle(void);
#endif