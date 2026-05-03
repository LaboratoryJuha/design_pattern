#include "libfactory.h"
#include <string.h>

void set_factory(Instance *i, int api_max, Object *handler_entry, char **names) {
    i->handler_entry = handler_entry;
    i->max = api_max;
    i->names = names;
}

int get_factory_max(const Instance *instance) {
    return instance->max;
}

const char* get_name(const Instance *instance, int index) {
    if (!instance) {
        return NULL;
    }
    return instance->names[index];
}

Object get_handler_by_index(const Instance *instance, int index) {
    if (!instance) {
        return NULL;
    }
    return instance->handler_entry[index];
}

Object get_handler_by_name(const Instance *instance, const char* name) {
    if (!instance || !name) {
        return NULL;
    }
    for (int i = 0; i < instance->max; ++i) {
        if (strcmp(instance->names[i], name) == 0) {
            return instance->handler_entry[i];
        }
    }
    return NULL;
}
