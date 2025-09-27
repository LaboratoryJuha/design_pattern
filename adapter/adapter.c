#include "adapter.h"

static void default_legacy_print(LegacyPrinter *self, const char *msg) {
  (void)self;
  printf("[Legacy] %s\n", msg);
}

LegacyPrinter *new_legacy_printer(void *user_data) {
  LegacyPrinter *p = malloc(sizeof(*p));

  if (p == NULL) {
    return NULL;
  }

  p->legacy_print = default_legacy_print;
  p->user_data = user_data;

  return p;
}

void legacy_printer_destroy(LegacyPrinter *p) {
  if (p == NULL) {
    return;
  }

  free(p);
}

void legacy_printer_set_func(LegacyPrinter *p, void (*fn)(LegacyPrinter *, const char *)) {
  if (p == NULL) {
    return;
  }

  if (fn == NULL) {
    p->legacy_print = default_legacy_print;
  } else {
    p->legacy_print = fn;
  }
}


static void adapter_print(Printer *self, const char *msg) {
  if (self == NULL) {
    return;
  }

  if (msg == NULL) {
    return;
  }

  PrinterAdapter *a = (PrinterAdapter *)self->impl;

  if (a != NULL) {
    if (a->legacy != NULL) {
      if (a->legacy->legacy_print != NULL) {
        /* Translate/transform if needed. */
        a->legacy->legacy_print(a->legacy, msg);
      }
    }
  }
}

Printer *printer_create_from_legacy(LegacyPrinter *legacy) {
  if (legacy == NULL) {
    return NULL;
  }

  Printer *p = malloc(sizeof(*p));
  if (p == NULL) {
    return NULL;
  }

  PrinterAdapter *a = malloc(sizeof(*a));
  if (a == NULL) {
    free(p);
    return NULL;
  }

  a->legacy = legacy;

  p->impl = a;
  p->print = adapter_print;

  return p;
}

void printer_destroy(Printer *p) {
  if (p == NULL) {
    return;
  }

  if (p->impl != NULL) {
    free(p->impl);
  }

  free(p);
}

static void custom_legacy_print(LegacyPrinter *s, const char *m) {
  (void)s;
  printf("[CustomLegacy] >> %s\n", m);
}

int main(void) {
  LegacyPrinter *legacy = NULL;
  Printer *printer = NULL;

  legacy = new_legacy_printer(NULL);
  if (legacy == NULL) {
    return 1;
  }

  legacy_printer_set_func(legacy, custom_legacy_print);

  printer = printer_create_from_legacy(legacy);
  if (printer == NULL) {
    legacy_printer_destroy(legacy);
    return 2;
  }

  printer->print(printer, "Hello Adapter Pattern");

  printer_destroy(printer);
  legacy_printer_destroy(legacy);

  return 0;
}
