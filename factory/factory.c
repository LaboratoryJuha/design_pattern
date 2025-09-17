#include "factory.h"

void circle_draw(Shape *self) {
    Circle *c = (Circle*)self;
    printf("Draw Circle with radius=%d\n", c->radius);
}

// 구체 팩토리 1: Circle 생성
Shape* create_circle(void) {
    Circle *c = malloc(sizeof(Circle));
    if (!c) {
        return NULL;
    }

    c->base.draw = circle_draw;
    c->radius = 5;
    return (Shape*)c;
}

void rectangle_draw(Shape *self) {
    Rectangle *r = (Rectangle*)self;
    printf("Draw Rectangle %dx%d\n", r->width, r->height);
}

// 구체 팩토리 2: Rectangle 생성
Shape* create_rectangle(void) {
    Rectangle *r = malloc(sizeof(Rectangle));
    if (!r) {
        return NULL;
    }
    r->base.draw = rectangle_draw;
    r->width = 4;
    r->height = 3;
    return (Shape *)r;
}

// 팩토리 제공 함수
ShapeFactory get_factory(const char *type) {
    // 올바른 문자열 매칭: 입력 문자열과 테이블 항목을 비교
    const char *types[] = { SHAPE_API(CREATE_STRING) NULL };
    for (int i = 0; types[i] != NULL; ++i) {
        if (strcmp(types[i], type) == 0) {
            switch (i) {
                case CIRCLE: return create_circle;
                case RECTANGLE: return create_rectangle;
            }
        }
    }
    return NULL;
}
 
// 클라이언트 코드
int main(void) {
    ShapeFactory factory = get_factory("circle");
    if (!factory) return 1;
    Shape AUTO_FREE *shape = factory();
    shape->draw(shape);

    factory = get_factory("rect");
    if (!factory) return 1;
    Shape AUTO_FREE *shape2 = factory();
    shape2->draw(shape2);

    return 0;
}