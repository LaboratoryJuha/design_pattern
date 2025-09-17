#include "abstract_factory.h"

// --- 구체 팩토리 구조체 정의 ---
AbstractFactory ModernFactory = {
    .createCircle = Modern_createCircle,
    .createRectangle = Modern_createRectangle
};

AbstractFactory ClassicFactory = {
    .createCircle = Classic_createCircle,
    .createRectangle = Classic_createRectangle
};

// --- 제품 draw 함수 ---
void Circle_draw(Shape *self) {
    Circle *c = (Circle*)self;
    printf("Draw Circle with radius=%d\n", c->radius);
}

void Rectangle_draw(Shape *self) {
    Rectangle *r = (Rectangle*)self;
    printf("Draw Rectangle %dx%d\n", r->width, r->height);
}

// --- Modern 스타일 생성 함수 ---
Shape* Modern_createCircle(void) {
    Circle *c = malloc(sizeof(Circle));
    if (!c) return NULL;
    c->base.draw = Circle_draw;
    c->radius = 10; // Modern 스타일 반영
    return (Shape*)c;
}

Shape* Modern_createRectangle(void) {
    Rectangle *r = malloc(sizeof(Rectangle));
    if (!r) return NULL;
    r->base.draw = Rectangle_draw;
    r->width = 20; r->height = 10; // Modern 스타일 반영
    return (Shape*)r;
}

// --- Classic 스타일 생성 함수 ---
Shape* Classic_createCircle(void) {
    Circle *c = malloc(sizeof(Circle));
    if (!c) return NULL;
    c->base.draw = Circle_draw;
    c->radius = 5; // Classic 스타일 반영
    return (Shape*)c;
}

Shape* Classic_createRectangle(void) {
    Rectangle *r = malloc(sizeof(Rectangle));
    if (!r) return NULL;
    r->base.draw = Rectangle_draw;
    r->width = 4; r->height = 3; // Classic 스타일 반영
    return (Shape*)r;
}

// --- main 함수에서 추상 팩토리 사용 예시 ---
int main(void) {
    // Modern 스타일 팩토리 사용
    AbstractFactory *factory = &ModernFactory;
    Shape __attribute__((__cleanup__(free))) *shape = factory->createCircle();
    shape->draw(shape);

    Shape __attribute__((__cleanup__(free))) *shape2 = factory->createRectangle();
    shape2->draw(shape2);

    // Classic 스타일 팩토리 사용
    factory = &ClassicFactory;
    Shape __attribute__((__cleanup__(free))) *shape3 = factory->createCircle();
    shape3->draw(shape3);

    Shape __attribute__((__cleanup__(free))) *shape4 = factory->createRectangle();
    shape4->draw(shape4);

    return 0;
}