#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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


void Circle_draw(Shape *self) {
    Circle *c = (Circle*)self;
    printf("Draw Circle with radius=%d\n", c->radius);
}


// 구체 팩토리 1: Circle 생성
Shape* createCircle(void) {
    Circle *c = malloc(sizeof(Circle));
    if (!c) {
        return NULL;
    }

    c->base.draw = Circle_draw;
    c->radius = 5;
    return (Shape*)c;
}

//-----------------------------
void Rectangle_draw(Shape *self) {
    Rectangle *r = (Rectangle*)self;
    printf("Draw Rectangle %dx%d\n", r->width, r->height);
}


// 구체 팩토리 2: Rectangle 생성
Shape* createRectangle(void) {
    Rectangle *r = malloc(sizeof(Rectangle));
    if (!r) {
        return NULL;
    }
    r->base.draw = Rectangle_draw;
    r->width = 4;
    r->height = 3;
    return (Shape *)r;
}

// 팩토리 제공 함수
ShapeFactory getFactory(const char *type) {
    const char *types[] = { SHAPE_API(CREATE_STRING) NULL };
    int idx = 0;

    while (type[idx] != NULL \
        && strcmp(type[idx], type) == 0) {
        idx++;
    }

    switch (idx) {
        case CIRCLE: return createCircle;
        case RECTANGLE: return createRectangle;
        default: return NULL;
    }
}
 
// 클라이언트 코드
int main(void) {
    ShapeFactory factory = getFactory("circle");
    if (!factory) return 1;

    Shape *shape = factory();
    shape->draw(shape);
    free(shape);

    factory = getFactory("rect");
    Shape *shape2 = factory();
    shape2->draw(shape2);
    free(shape2);

    return 0;
}