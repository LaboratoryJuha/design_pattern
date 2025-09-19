#ifndef BUILDER_H
#define BUILDER_H

#include <string.h>

typedef struct {
	char cpu[32];
	char gpu[32];
	int ram_gb;
	int ssd_gb;
} Computer;

typedef struct ComputerBuilder {
	Computer computer;
	struct ComputerBuilder* (*set_cpu)(struct ComputerBuilder*, const char*);
	struct ComputerBuilder* (*set_gpu)(struct ComputerBuilder*, const char*);
	struct ComputerBuilder* (*set_ram)(struct ComputerBuilder*, int);
	struct ComputerBuilder* (*set_ssd)(struct ComputerBuilder*, int);
	Computer (*build)(struct ComputerBuilder*);
} ComputerBuilder;

ComputerBuilder create_computer_builder();

#endif // BUILDER_H
