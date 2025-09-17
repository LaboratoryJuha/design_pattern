#include "singleton.h"

// 싱글톤을 위한 전역 변수
static pthread_mutex_t singleton_mutex = PTHREAD_MUTEX_INITIALIZER;
static Circle *c = NULL;
static Rectangle *r = NULL;

// 프로그램 종료 시 할당된 메모리 해제
void free_shape() {
    free(c);
    free(r);
}

void circle_draw(Shape *self) {
    Circle *c = (Circle*)self;
    printf("Draw Circle with radius=%d\n", c->radius);
}

Shape* create_circle() {
    // 이중 검사를 통한 싱글톤 구현
    pthread_mutex_lock(&singleton_mutex);
    if (!c) {
        c = malloc(sizeof(Circle));
        if (!c) {
            pthread_mutex_unlock(&singleton_mutex);
            return NULL;
        }
        c->base.draw = circle_draw;
        c->radius = 5;
    }
    pthread_mutex_unlock(&singleton_mutex);
    return (Shape*)c;
}

void rectangle_draw(Shape *self) {
    Rectangle *r = (Rectangle*)self;
    printf("Draw Rectangle %dx%d\n", r->width, r->height);
}


Shape* create_rectangle() {
    pthread_mutex_lock(&singleton_mutex);
    if (!r) {
        r = malloc(sizeof(Rectangle));
        if (!r) {
            pthread_mutex_unlock(&singleton_mutex);
            return NULL;
        }
        r->base.draw = rectangle_draw;
        r->width = 4;
        r->height = 3;
    }
    pthread_mutex_unlock(&singleton_mutex);
    return (Shape *)r;
}

ShapeFactory get_factory(const char *type) {
    static const char *types[] = { SHAPE_API(CREATE_STRING) NULL };
    int idx = 0;

    while (types[idx] != NULL \
        && strcmp(types[idx], type) == 0) {
        idx++;
    }

    switch (idx) {
        case CIRCLE: return create_circle;
        case RECTANGLE: return create_rectangle;
        default: return NULL;
    }
}
 
int main() {
    ShapeFactory factory = get_factory("circle");
    if (!factory) return 1;
    Shape AUTO_FREE *shape = factory();
    shape->draw(shape);

    factory = get_factory("rectangle");
    if (!factory) return 1;
    Shape AUTO_FREE *shape2 = factory();
    shape2->draw(shape2);

    free_shape();
    return 0;
}