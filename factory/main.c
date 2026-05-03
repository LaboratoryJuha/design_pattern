#include "factory.h"
#include "circle.h"
#include "ractangle.h"
#include "libfactory.h"
#include <stdio.h>

static char *types[] = { SHAPE_API(CREATE_STRING) NULL };
static Object handlers[] = { SHAPE_API(CREATE_HANDLER) NULL };

int main(void) {
    Instance instance;
    set_factory(&instance, 2, handlers, types);

    Object f = get_handler_by_name(&instance, "CIRCLE");
    if (!f) return 1;
    Shape* (*shape_factory)(void) = (Shape*(*)(void))f;
    Shape AUTO_FREE *shape = shape_factory();
    shape->draw(shape);

    f = get_handler_by_index(&instance, RECTANGLE);
    if (!f) return 1;
    shape_factory = (Shape*(*)(void))f;
    Shape AUTO_FREE *shape2 = shape_factory();
    shape2->draw(shape2);

    return 0;
}