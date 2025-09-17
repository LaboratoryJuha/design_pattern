#ifndef SINGLETON_H
#define SINGLETON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

static inline void auto_free(void *pp) {
    void **p = (void**)pp;
    if (p && *p) {
        free(*p);
        *p = NULL;
    }
}
#define AUTO_FREE __attribute__((__cleanup__(auto_free)))

#define SHAPE_API(_expend_) \
    _expend_(CIRCLE) \
    _expend_(RECTANGLE)

#define CREATE_ENUM(name) name,
#define CREATE_STRING(name) #name,

enum ShapeType {
    SHAPE_API(CREATE_ENUM)
    SHAPE_TYPE_MAX
};

// 제품 인터페이스: Shape
typedef struct Shape {
    void (*draw)(struct Shape *self);
} Shape;

// 구체 제품 1: Circle
typedef struct {
    Shape base;
    int radius;
} Circle;

// 구체 제품 2: Rectangle
typedef struct {
    Shape base;
    int width;
    int height;
} Rectangle;

// 팩토리 함수 시그니처
typedef Shape* (*ShapeFactory)(void);

void circle_draw(Shape *self);
Shape* create_circle(void);
void rectangle_draw(Shape *self);
Shape* create_rectangle(void);
ShapeFactory get_factory(const char *type);

#endif