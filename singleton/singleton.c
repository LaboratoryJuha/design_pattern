#include "singleton.h"

pthread_mutex_t singleton_mutex = PTHREAD_MUTEX_INITIALIZER;

void Circle_draw(Shape *self) {
    Circle *c = (Circle*)self;
    printf("Draw Circle with radius=%d\n", c->radius);
}

Shape* createCircle() {
    static Circle *c = NULL;
    pthread_mutex_lock(&singleton_mutex);
    if (!c) {
        c = malloc(sizeof(Circle));
        if (!c) {
            pthread_mutex_unlock(&singleton_mutex);
            return NULL;
        }
        c->base.draw = Circle_draw;
        c->radius = 5;
    }
    pthread_mutex_unlock(&singleton_mutex);
    return (Shape*)c;
}

void Rectangle_draw(Shape *self) {
    Rectangle *r = (Rectangle*)self;
    printf("Draw Rectangle %dx%d\n", r->width, r->height);
}


Shape* createRectangle() {
    static Rectangle *r = NULL;
    pthread_mutex_lock(&singleton_mutex);
    if (!r) {
        r = malloc(sizeof(Rectangle));
        if (!r) {
            pthread_mutex_unlock(&singleton_mutex);
            return NULL;
        }
        r->base.draw = Rectangle_draw;
        r->width = 4;
        r->height = 3;
    }
    pthread_mutex_unlock(&singleton_mutex);
    return (Shape *)r;
}

ShapeFactory getFactory(const char *type) {
    static const char *types[] = { SHAPE_API(CREATE_STRING) NULL };
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
 
int main() {
    ShapeFactory factory = getFactory("circle");
    if (!factory) return 1;

    Shape __attribute__((__cleanup__(free))) *shape = factory();
    shape->draw(shape);

    factory = getFactory("rect");
    Shape __attribute__((__cleanup__(free))) *shape2 = factory();
    shape2->draw(shape2);

    return 0;
}