#pragma once
#include <array>
#include <cstdint>
#include "CPU.h"

class Bus
{
public:
	Bus();
	~Bus();

public: // Bus devices
	CPU cpu;

	std::array<uint8_t, 65536> ram;



public: // Bus read and write
	void write(uint16_t addr, uint8_t data);
	uint8_t read(uint16_t addr, bool bReadOnly = false);
};

