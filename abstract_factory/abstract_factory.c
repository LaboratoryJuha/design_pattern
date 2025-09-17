#include "abstract_factory.h"

// --- 구체 팩토리 구조체 정의 ---
const static Abstract_factory modern_factory = {
    .create_circle = modern_create_circle,
    .create_rectangle = modern_create_rectangle
};

const static Abstract_factory classic_factory = {
    .create_circle = classic_create_circle,
    .create_rectangle = classic_create_rectangle
};

// --- 제품 draw 함수 ---
void circle_draw(Shape *self) {
    Circle *c = (Circle*)self;
    printf("Draw Circle with radius=%d\n", c->radius);
}

void rectangle_draw(Shape *self) {
    Rectangle *r = (Rectangle*)self;
    printf("Draw Rectangle %dx%d\n", r->width, r->height);
}

// --- Modern 스타일 생성 함수 ---
Shape* modern_create_circle(void) {
    Circle *c = malloc(sizeof(Circle));
    if (!c) return NULL;
    c->base.draw = circle_draw;
    c->radius = 10; // Modern 스타일 반영
    return (Shape*)c;
}

Shape* modern_create_rectangle(void) {
    Rectangle *r = malloc(sizeof(Rectangle));
    if (!r) return NULL;
    r->base.draw = rectangle_draw;
    r->width = 20; r->height = 10; // Modern 스타일 반영
    return (Shape*)r;
}

// --- Classic 스타일 생성 함수 ---
Shape* classic_create_circle(void) {
    Circle *c = malloc(sizeof(Circle));
    if (!c) return NULL;
    c->base.draw = circle_draw;
    c->radius = 5; // Classic 스타일 반영
    return (Shape*)c;
}

Shape* classic_create_rectangle(void) {
    Rectangle *r = malloc(sizeof(Rectangle));
    if (!r) return NULL;
    r->base.draw = rectangle_draw;
    r->width = 4; r->height = 3; // Classic 스타일 반영
    return (Shape*)r;
}

// --- main 함수에서 추상 팩토리 사용 예시 ---
int main(void) {
    // Modern 스타일 팩토리 사용
    const Abstract_factory *factory = &modern_factory;
    Shape AUTO_FACTORY_FREE *shape = factory->create_circle();
    shape->draw(shape);

    Shape AUTO_FACTORY_FREE *shape2 = factory->create_rectangle();
    shape2->draw(shape2);

    // Classic 스타일 팩토리 사용
    factory = &classic_factory;
    Shape AUTO_FACTORY_FREE *shape3 = factory->create_circle();
    shape3->draw(shape3);

    Shape AUTO_FACTORY_FREE *shape4 = factory->create_rectangle();
    shape4->draw(shape4);

    return 0;
}