#ifndef ADAPTER_H
#define ADAPTER_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct LegacyPrinter {
	void (*legacy_print)(LegacyPrinter *self, const char *msg);
	void *user_data; 
}LegacyPrinter;

typedef struct Printer {
	void (*print)(Printer *self, const char *msg);
	void *impl;
}Printer;

typedef struct PrinterAdapter {
  LegacyPrinter *legacy;
} PrinterAdapter;

Printer *printer_create_from_legacy(LegacyPrinter *legacy);
void printer_destroy(Printer *p);

LegacyPrinter *new_legacy_printer(void *user_data);
void legacy_printer_destroy(LegacyPrinter *p);
void legacy_printer_set_func(LegacyPrinter *p, void (*fn)(LegacyPrinter *, const char *));

#endif