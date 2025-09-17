// Abstract Factory Pattern Example
#ifndef ABSTRACT_FACTORY_H
#define ABSTRACT_FACTORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

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
typedef struct AbstractFactory {
    Shape* (*createCircle)(void);
    Shape* (*createRectangle)(void);
} AbstractFactory;

// 구체 팩토리 선언 (예시: Modern, Classic)
extern AbstractFactory ModernFactory;
extern AbstractFactory ClassicFactory;

void Circle_draw(Shape *self);
void Rectangle_draw(Shape *self) ;

Shape* Modern_createCircle(void);
Shape* Modern_createRectangle(void);
Shape* Classic_createCircle(void);
Shape* Classic_createRectangle(void);
#endif