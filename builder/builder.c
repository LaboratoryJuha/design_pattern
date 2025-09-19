#include "builder.h"

static ComputerBuilder* set_cpu(ComputerBuilder* builder, const char* cpu) {
	strncpy(builder->computer.cpu, cpu, sizeof(builder->computer.cpu) - 1);
	builder->computer.cpu[sizeof(builder->computer.cpu) - 1] = '\0';
	return builder;
}

static ComputerBuilder* set_gpu(ComputerBuilder* builder, const char* gpu) {
	strncpy(builder->computer.gpu, gpu, sizeof(builder->computer.gpu) - 1);
	builder->computer.gpu[sizeof(builder->computer.gpu) - 1] = '\0';
	return builder;
}

static ComputerBuilder* set_ram(ComputerBuilder* builder, int ram_gb) {
	builder->computer.ram_gb = ram_gb;
	return builder;
}

static ComputerBuilder* set_ssd(ComputerBuilder* builder, int ssd_gb) {
	builder->computer.ssd_gb = ssd_gb;
	return builder;
}

static Computer build(ComputerBuilder* builder) {
	return builder->computer;
}

ComputerBuilder create_computer_builder() {
	ComputerBuilder builder;
	memset(&builder.computer, 0, sizeof(Computer));
	builder.set_cpu = set_cpu;
	builder.set_gpu = set_gpu;
	builder.set_ram = set_ram;
	builder.set_ssd = set_ssd;
	builder.build = build;
	return builder;
}

int main() {
    ComputerBuilder builder = create_computer_builder();
    Computer my_pc = builder
        .set_cpu(&builder, "Intel i9")
        ->set_gpu(&builder, "NVIDIA RTX 4090")
        ->set_ram(&builder, 64)
        ->set_ssd(&builder, 2000)
        ->build(&builder);

    printf("CPU: %s\nGPU: %s\nRAM: %dGB\nSSD: %dGB\n",
        my_pc.cpu, my_pc.gpu, my_pc.ram_gb, my_pc.ssd_gb);

    return 0;
}