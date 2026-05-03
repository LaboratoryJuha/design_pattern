#ifndef LIBFACTORY_H
#define LIBFACTORY_H

#include <stdlib.h>
#include <string.h>

typedef void* Object;
typedef struct {
    int max;
    Object *handler_entry; 
    char** names; 
} Instance;

void set_factory(Instance *i, int api_max, Object *handler_entry, char **names);

int get_factory_max(const Instance *instance);
const char* get_name(const Instance *instance, int index);
Object get_handler_by_index(const Instance *instance, int index);
Object get_handler_by_name(const Instance *instance, const char* name);

#endif