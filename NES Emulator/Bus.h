#pragma once
#include <cstdint>

#include "CPU.h"

class Bus
{

public:
	CPU cpu;

public:
	void write(uint16_t addr, uint8_t data);
	uint8_t read(uint16_t addr, bool bReadOnly = false);
};

