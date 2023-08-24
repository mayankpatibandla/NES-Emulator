#include "CPU.h"
#include "Bus.h"
#include <format>

CPU::CPU()
{
	lookup =
	{
		{ "BRK", &CPU::BRK, &CPU::IMM, 7 },{ "ORA", &CPU::ORA, &CPU::IZX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "???", &CPU::NOP, &CPU::IMP, 3 },{ "ORA", &CPU::ORA, &CPU::ZP0, 3 },{ "ASL", &CPU::ASL, &CPU::ZP0, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },{ "PHP", &CPU::PHP, &CPU::IMP, 3 },{ "ORA", &CPU::ORA, &CPU::IMM, 2 },{ "ASL", &CPU::ASL, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "ORA", &CPU::ORA, &CPU::ABS, 4 },{ "ASL", &CPU::ASL, &CPU::ABS, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },
		{ "BPL", &CPU::BPL, &CPU::REL, 2 },{ "ORA", &CPU::ORA, &CPU::IZY, 5 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "ORA", &CPU::ORA, &CPU::ZPX, 4 },{ "ASL", &CPU::ASL, &CPU::ZPX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },{ "CLC", &CPU::CLC, &CPU::IMP, 2 },{ "ORA", &CPU::ORA, &CPU::ABY, 4 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 7 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "ORA", &CPU::ORA, &CPU::ABX, 4 },{ "ASL", &CPU::ASL, &CPU::ABX, 7 },{ "???", &CPU::XXX, &CPU::IMP, 7 },
		{ "JSR", &CPU::JSR, &CPU::ABS, 6 },{ "AND", &CPU::AND, &CPU::IZX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "BIT", &CPU::BIT, &CPU::ZP0, 3 },{ "AND", &CPU::AND, &CPU::ZP0, 3 },{ "ROL", &CPU::ROL, &CPU::ZP0, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },{ "PLP", &CPU::PLP, &CPU::IMP, 4 },{ "AND", &CPU::AND, &CPU::IMM, 2 },{ "ROL", &CPU::ROL, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "BIT", &CPU::BIT, &CPU::ABS, 4 },{ "AND", &CPU::AND, &CPU::ABS, 4 },{ "ROL", &CPU::ROL, &CPU::ABS, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },
		{ "BMI", &CPU::BMI, &CPU::REL, 2 },{ "AND", &CPU::AND, &CPU::IZY, 5 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "AND", &CPU::AND, &CPU::ZPX, 4 },{ "ROL", &CPU::ROL, &CPU::ZPX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },{ "SEC", &CPU::SEC, &CPU::IMP, 2 },{ "AND", &CPU::AND, &CPU::ABY, 4 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 7 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "AND", &CPU::AND, &CPU::ABX, 4 },{ "ROL", &CPU::ROL, &CPU::ABX, 7 },{ "???", &CPU::XXX, &CPU::IMP, 7 },
		{ "RTI", &CPU::RTI, &CPU::IMP, 6 },{ "EOR", &CPU::EOR, &CPU::IZX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "???", &CPU::NOP, &CPU::IMP, 3 },{ "EOR", &CPU::EOR, &CPU::ZP0, 3 },{ "LSR", &CPU::LSR, &CPU::ZP0, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },{ "PHA", &CPU::PHA, &CPU::IMP, 3 },{ "EOR", &CPU::EOR, &CPU::IMM, 2 },{ "LSR", &CPU::LSR, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "JMP", &CPU::JMP, &CPU::ABS, 3 },{ "EOR", &CPU::EOR, &CPU::ABS, 4 },{ "LSR", &CPU::LSR, &CPU::ABS, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },
		{ "BVC", &CPU::BVC, &CPU::REL, 2 },{ "EOR", &CPU::EOR, &CPU::IZY, 5 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "EOR", &CPU::EOR, &CPU::ZPX, 4 },{ "LSR", &CPU::LSR, &CPU::ZPX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },{ "CLI", &CPU::CLI, &CPU::IMP, 2 },{ "EOR", &CPU::EOR, &CPU::ABY, 4 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 7 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "EOR", &CPU::EOR, &CPU::ABX, 4 },{ "LSR", &CPU::LSR, &CPU::ABX, 7 },{ "???", &CPU::XXX, &CPU::IMP, 7 },
		{ "RTS", &CPU::RTS, &CPU::IMP, 6 },{ "ADC", &CPU::ADC, &CPU::IZX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "???", &CPU::NOP, &CPU::IMP, 3 },{ "ADC", &CPU::ADC, &CPU::ZP0, 3 },{ "ROR", &CPU::ROR, &CPU::ZP0, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },{ "PLA", &CPU::PLA, &CPU::IMP, 4 },{ "ADC", &CPU::ADC, &CPU::IMM, 2 },{ "ROR", &CPU::ROR, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "JMP", &CPU::JMP, &CPU::IND, 5 },{ "ADC", &CPU::ADC, &CPU::ABS, 4 },{ "ROR", &CPU::ROR, &CPU::ABS, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },
		{ "BVS", &CPU::BVS, &CPU::REL, 2 },{ "ADC", &CPU::ADC, &CPU::IZY, 5 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "ADC", &CPU::ADC, &CPU::ZPX, 4 },{ "ROR", &CPU::ROR, &CPU::ZPX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },{ "SEI", &CPU::SEI, &CPU::IMP, 2 },{ "ADC", &CPU::ADC, &CPU::ABY, 4 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 7 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "ADC", &CPU::ADC, &CPU::ABX, 4 },{ "ROR", &CPU::ROR, &CPU::ABX, 7 },{ "???", &CPU::XXX, &CPU::IMP, 7 },
		{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "STA", &CPU::STA, &CPU::IZX, 6 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 6 },{ "STY", &CPU::STY, &CPU::ZP0, 3 },{ "STA", &CPU::STA, &CPU::ZP0, 3 },{ "STX", &CPU::STX, &CPU::ZP0, 3 },{ "???", &CPU::XXX, &CPU::IMP, 3 },{ "DEY", &CPU::DEY, &CPU::IMP, 2 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "TXA", &CPU::TXA, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "STY", &CPU::STY, &CPU::ABS, 4 },{ "STA", &CPU::STA, &CPU::ABS, 4 },{ "STX", &CPU::STX, &CPU::ABS, 4 },{ "???", &CPU::XXX, &CPU::IMP, 4 },
		{ "BCC", &CPU::BCC, &CPU::REL, 2 },{ "STA", &CPU::STA, &CPU::IZY, 6 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 6 },{ "STY", &CPU::STY, &CPU::ZPX, 4 },{ "STA", &CPU::STA, &CPU::ZPX, 4 },{ "STX", &CPU::STX, &CPU::ZPY, 4 },{ "???", &CPU::XXX, &CPU::IMP, 4 },{ "TYA", &CPU::TYA, &CPU::IMP, 2 },{ "STA", &CPU::STA, &CPU::ABY, 5 },{ "TXS", &CPU::TXS, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 5 },{ "???", &CPU::NOP, &CPU::IMP, 5 },{ "STA", &CPU::STA, &CPU::ABX, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },
		{ "LDY", &CPU::LDY, &CPU::IMM, 2 },{ "LDA", &CPU::LDA, &CPU::IZX, 6 },{ "LDX", &CPU::LDX, &CPU::IMM, 2 },{ "???", &CPU::XXX, &CPU::IMP, 6 },{ "LDY", &CPU::LDY, &CPU::ZP0, 3 },{ "LDA", &CPU::LDA, &CPU::ZP0, 3 },{ "LDX", &CPU::LDX, &CPU::ZP0, 3 },{ "???", &CPU::XXX, &CPU::IMP, 3 },{ "TAY", &CPU::TAY, &CPU::IMP, 2 },{ "LDA", &CPU::LDA, &CPU::IMM, 2 },{ "TAX", &CPU::TAX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "LDY", &CPU::LDY, &CPU::ABS, 4 },{ "LDA", &CPU::LDA, &CPU::ABS, 4 },{ "LDX", &CPU::LDX, &CPU::ABS, 4 },{ "???", &CPU::XXX, &CPU::IMP, 4 },
		{ "BCS", &CPU::BCS, &CPU::REL, 2 },{ "LDA", &CPU::LDA, &CPU::IZY, 5 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 5 },{ "LDY", &CPU::LDY, &CPU::ZPX, 4 },{ "LDA", &CPU::LDA, &CPU::ZPX, 4 },{ "LDX", &CPU::LDX, &CPU::ZPY, 4 },{ "???", &CPU::XXX, &CPU::IMP, 4 },{ "CLV", &CPU::CLV, &CPU::IMP, 2 },{ "LDA", &CPU::LDA, &CPU::ABY, 4 },{ "TSX", &CPU::TSX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 4 },{ "LDY", &CPU::LDY, &CPU::ABX, 4 },{ "LDA", &CPU::LDA, &CPU::ABX, 4 },{ "LDX", &CPU::LDX, &CPU::ABY, 4 },{ "???", &CPU::XXX, &CPU::IMP, 4 },
		{ "CPY", &CPU::CPY, &CPU::IMM, 2 },{ "CMP", &CPU::CMP, &CPU::IZX, 6 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "CPY", &CPU::CPY, &CPU::ZP0, 3 },{ "CMP", &CPU::CMP, &CPU::ZP0, 3 },{ "DEC", &CPU::DEC, &CPU::ZP0, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },{ "INY", &CPU::INY, &CPU::IMP, 2 },{ "CMP", &CPU::CMP, &CPU::IMM, 2 },{ "DEX", &CPU::DEX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "CPY", &CPU::CPY, &CPU::ABS, 4 },{ "CMP", &CPU::CMP, &CPU::ABS, 4 },{ "DEC", &CPU::DEC, &CPU::ABS, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },
		{ "BNE", &CPU::BNE, &CPU::REL, 2 },{ "CMP", &CPU::CMP, &CPU::IZY, 5 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "CMP", &CPU::CMP, &CPU::ZPX, 4 },{ "DEC", &CPU::DEC, &CPU::ZPX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },{ "CLD", &CPU::CLD, &CPU::IMP, 2 },{ "CMP", &CPU::CMP, &CPU::ABY, 4 },{ "NOP", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 7 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "CMP", &CPU::CMP, &CPU::ABX, 4 },{ "DEC", &CPU::DEC, &CPU::ABX, 7 },{ "???", &CPU::XXX, &CPU::IMP, 7 },
		{ "CPX", &CPU::CPX, &CPU::IMM, 2 },{ "SBC", &CPU::SBC, &CPU::IZX, 6 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "CPX", &CPU::CPX, &CPU::ZP0, 3 },{ "SBC", &CPU::SBC, &CPU::ZP0, 3 },{ "INC", &CPU::INC, &CPU::ZP0, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },{ "INX", &CPU::INX, &CPU::IMP, 2 },{ "SBC", &CPU::SBC, &CPU::IMM, 2 },{ "NOP", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::SBC, &CPU::IMP, 2 },{ "CPX", &CPU::CPX, &CPU::ABS, 4 },{ "SBC", &CPU::SBC, &CPU::ABS, 4 },{ "INC", &CPU::INC, &CPU::ABS, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },
		{ "BEQ", &CPU::BEQ, &CPU::REL, 2 },{ "SBC", &CPU::SBC, &CPU::IZY, 5 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "SBC", &CPU::SBC, &CPU::ZPX, 4 },{ "INC", &CPU::INC, &CPU::ZPX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },{ "SED", &CPU::SED, &CPU::IMP, 2 },{ "SBC", &CPU::SBC, &CPU::ABY, 4 },{ "NOP", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 7 },{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "SBC", &CPU::SBC, &CPU::ABX, 4 },{ "INC", &CPU::INC, &CPU::ABX, 7 },{ "???", &CPU::XXX, &CPU::IMP, 7 },
	};
}

CPU::~CPU()
= default;

void CPU::ConnectBus(Bus* n)
{
	bus = n;
}


void CPU::clock()
{
	if (cycles == 0)
	{
		opcode = read(pc);
		pc++;

		cycles = lookup[opcode].cycles;

		uint8_t additionalCycle1 = (this->*lookup[opcode].addrmode)();
		uint8_t additionalCycle2 = (this->*lookup[opcode].operate)();

		cycles += additionalCycle1 & additionalCycle2;
	}

	cycles--;
}

void CPU::reset()
{
	a = 0;
	x = 0;
	y = 0;
	stkp = 0xFD;
	status = 0x00 | U;

	addr_abs = 0xFFFC;
	uint16_t lo = read(addr_abs);
	uint16_t hi = read(addr_abs + 1);

	pc = (hi << 8) | lo;

	addr_rel = 0;
	addr_abs = 0;
	fetched = 0;

	cycles = 8;
}

void CPU::irq()
{
	if (!getFlag(I))
	{
		write(0x0100 + stkp--, (pc >> 8) & 0x00FF);
		write(0x0100 + stkp--, pc & 0x00FF);

		setFlag(B, false);
		setFlag(U, true);
		setFlag(I, true);
		write(0x0100 + stkp--, status);

		addr_abs = 0xFFFE;
		uint16_t lo = read(addr_abs);
		uint16_t hi = read(addr_abs + 1);

		pc = (hi << 8) | lo;

		cycles = 7;
	}
}

void CPU::nmi()
{
	write(0x0100 + stkp--, (pc >> 8) & 0x00FF);
	write(0x0100 + stkp--, pc & 0x00FF);

	setFlag(B, false);
	setFlag(U, true);
	setFlag(I, true);
	write(0x0100 + stkp--, status);

	addr_abs = 0xFFFA;
	uint16_t lo = read(addr_abs);
	uint16_t hi = read(addr_abs + 1);

	pc = (hi << 8) | lo;

	cycles = 8;
}

bool CPU::complete()
{
	return cycles == 0;
}

std::map<uint16_t, std::string> CPU::disassemble(uint16_t nStart, uint16_t nStop)
{
	uint32_t addr = nStart;
	uint16_t line_addr = 0;
	uint8_t value = 0x00, lo = 0x00, hi = 0x00;
	std::map<uint16_t, std::string> mapLines;

	auto hex = [](uint32_t n, uint8_t d)
		{
			return std::format("{:0{}X}", n, d);
		};

	while (addr <= (uint32_t)nStop)
	{
		line_addr = addr;

		std::string sInst = "$" + hex(addr, 4) + ": ";

		uint8_t opcode = bus->read(addr++, true);
		sInst += lookup[opcode].name + " ";

		if (lookup[opcode].addrmode == &CPU::IMP)
		{
			sInst += " {IMP}";
		}
		else if (lookup[opcode].addrmode == &CPU::IMM)
		{
			value = bus->read(addr, true); addr++;
			sInst += "#$" + hex(value, 2) + " {IMM}";
		}
		else if (lookup[opcode].addrmode == &CPU::ZP0)
		{
			lo = bus->read(addr, true); addr++;
			hi = 0x00;
			sInst += "$" + hex(lo, 2) + " {ZP0}";
		}
		else if (lookup[opcode].addrmode == &CPU::ZPX)
		{
			lo = bus->read(addr, true); addr++;
			hi = 0x00;
			sInst += "$" + hex(lo, 2) + ", X {ZPX}";
		}
		else if (lookup[opcode].addrmode == &CPU::ZPY)
		{
			lo = bus->read(addr, true); addr++;
			hi = 0x00;
			sInst += "$" + hex(lo, 2) + ", Y {ZPY}";
		}
		else if (lookup[opcode].addrmode == &CPU::IZX)
		{
			lo = bus->read(addr, true); addr++;
			hi = 0x00;
			sInst += "($" + hex(lo, 2) + ", X) {IZX}";
		}
		else if (lookup[opcode].addrmode == &CPU::IZY)
		{
			lo = bus->read(addr, true); addr++;
			hi = 0x00;
			sInst += "($" + hex(lo, 2) + "), Y {IZY}";
		}
		else if (lookup[opcode].addrmode == &CPU::ABS)
		{
			lo = bus->read(addr, true); addr++;
			hi = bus->read(addr, true); addr++;
			sInst += "$" + hex((uint16_t)(hi << 8) | lo, 4) + " {ABS}";
		}
		else if (lookup[opcode].addrmode == &CPU::ABX)
		{
			lo = bus->read(addr, true); addr++;
			hi = bus->read(addr, true); addr++;
			sInst += "$" + hex((uint16_t)(hi << 8) | lo, 4) + ", X {ABX}";
		}
		else if (lookup[opcode].addrmode == &CPU::ABY)
		{
			lo = bus->read(addr, true); addr++;
			hi = bus->read(addr, true); addr++;
			sInst += "$" + hex((uint16_t)(hi << 8) | lo, 4) + ", Y {ABY}";
		}
		else if (lookup[opcode].addrmode == &CPU::IND)
		{
			lo = bus->read(addr, true); addr++;
			hi = bus->read(addr, true); addr++;
			sInst += "($" + hex((uint16_t)(hi << 8) | lo, 4) + ") {IND}";
		}
		else if (lookup[opcode].addrmode == &CPU::REL)
		{
			value = bus->read(addr, true); addr++;
			sInst += "$" + hex(value, 2) + " [$" + hex(addr + value, 4) + "] {REL}";
		}

		mapLines[line_addr] = sInst;
	}

	return mapLines;
}

// Addressing Modes

uint8_t CPU::IMP()
{
	fetched = a;
	return 0;
}

uint8_t CPU::IMM()
{
	addr_abs = pc++;
	return 0;
}

uint8_t CPU::ZP0()
{
	addr_abs = read(pc++);
	addr_abs &= 0x00FF;
	return 0;
}

uint8_t CPU::ZPX()
{
	addr_abs = read(pc++) + x;
	addr_abs &= 0x00FF;
	return 0;
}

uint8_t CPU::ZPY()
{
	addr_abs = read(pc++) + y;
	addr_abs &= 0x00FF;
	return 0;
}

uint8_t CPU::REL()
{
	addr_rel = read(pc++);
	if (addr_rel & 0x80)
	{
		addr_rel |= 0xFF00;
	}
	return 0;
}

uint8_t CPU::ABS()
{
	uint16_t lo = read(pc++);
	uint16_t hi = read(pc++);

	addr_abs = (hi << 8) | lo;

	return 0;
}

uint8_t CPU::ABX()
{
	uint16_t lo = read(pc++);
	uint16_t hi = read(pc++);

	addr_abs = ((hi << 8) | lo) + x;

	return (addr_abs & 0xFF00) != (hi << 8);
}

uint8_t CPU::ABY()
{
	uint16_t lo = read(pc++);
	uint16_t hi = read(pc++);

	addr_abs = ((hi << 8) | lo) + y;

	return (addr_abs & 0xFF00) != (hi << 8);
}

uint8_t CPU::IND()
{
	uint16_t ptr_lo = read(pc++);
	uint16_t ptr_hi = read(pc++);

	uint16_t ptr = (ptr_hi << 8) | ptr_lo;

	if (ptr_lo == 0x00FF)
	{
		addr_abs = (read(ptr & 0xFF00) << 8) | read(ptr);
	}
	else
	{
		addr_abs = (read(ptr + 1) << 8) | read(ptr);
	}

	return 0;
}

uint8_t CPU::IZX()
{
	uint16_t t = read(pc++);

	uint16_t lo = read((uint16_t)(t + (uint16_t)x) & 0x00FF);
	uint16_t hi = read((uint16_t)(t + (uint16_t)x + 1) & 0x00FF);

	addr_abs = (hi << 8) | lo;

	return 0;
}

uint8_t CPU::IZY()
{
	uint16_t t = read(pc++);

	uint16_t lo = read(t & 0x00FF);
	uint16_t hi = read((t + 1) & 0x00FF);

	addr_abs = ((hi << 8) | lo) + y;

	return (addr_abs & 0xFF00) != (hi << 8);
}

// Instructions

uint8_t CPU::ADC()
{
	temp = (uint16_t)a + (uint16_t)fetch() + (uint16_t)getFlag(C);

	setFlag(C, temp > 0x00FF);
	setFlag(Z, (temp & 0x00FF) == 0x0000);
	setFlag(V, (~((uint16_t)a ^ (uint16_t)fetched) & ((uint16_t)a ^ temp)) & 0x0080);
	setFlag(N, temp & 0x0080);

	a = temp & 0x00FF;

	return 1;
}

uint8_t CPU::AND()
{
	a &= fetch();

	setFlag(Z, a == 0x00);
	setFlag(N, a & 0x80);

	return 1;
}

uint8_t CPU::ASL()
{
	temp = (uint16_t)fetch() << 1;

	setFlag(C, (temp & 0xFF00) > 0);
	setFlag(Z, (temp & 0x00FF) == 0x00);
	setFlag(N, temp & 0x80);

	if (lookup[opcode].addrmode == &CPU::IMP)
	{
		a = temp & 0x00FF;
	}
	else
	{
		write(addr_abs, temp & 0x00FF);
	}

	return 0;
}

uint8_t CPU::BCC()
{
	if (!getFlag(C))
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
		{
			cycles++;
		}

		pc = addr_abs;
	}

	return 0;
}

uint8_t CPU::BCS()
{
	if (getFlag(C))
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
		{
			cycles++;
		}

		pc = addr_abs;
	}

	return 0;
}

uint8_t CPU::BEQ()
{
	if (getFlag(Z))
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
		{
			cycles++;
		}

		pc = addr_abs;
	}

	return 0;
}

uint8_t CPU::BIT()
{
	temp = a & fetch();

	setFlag(Z, (temp & 0x00FF) == 0x00);
	setFlag(N, fetched & (1 << 7));
	setFlag(V, fetched & (1 << 6));

	return 0;
}

uint8_t CPU::BMI()
{
	if (getFlag(N))
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
		{
			cycles++;
		}

		pc = addr_abs;
	}

	return 0;
}

uint8_t CPU::BNE()
{
	if (!getFlag(Z))
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
		{
			cycles++;
		}

		pc = addr_abs;
	}

	return 0;
}

uint8_t CPU::BPL()
{
	if (!getFlag(N))
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
		{
			cycles++;
		}

		pc = addr_abs;
	}

	return 0;
}

uint8_t CPU::BRK()
{
	setFlag(I, true);
	write(0x0100 + stkp--, (++pc >> 8) & 0x00FF);
	write(0x0100 + stkp--, pc & 0x00FF);

	setFlag(B, true);
	write(0x0100 + stkp--, status);
	setFlag(B, false);

	pc = (uint16_t)read(0xFFFE) | ((uint16_t)read(0xFFFF) << 8);

	return 0;
}

uint8_t CPU::BVC()
{
	if (!getFlag(V))
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
		{
			cycles++;
		}

		pc = addr_abs;
	}

	return 0;
}

uint8_t CPU::BVS()
{
	if (getFlag(V))
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
		{
			cycles++;
		}

		pc = addr_abs;
	}

	return 0;
}

uint8_t CPU::CLC()
{
	setFlag(C, false);
	return 0;
}

uint8_t CPU::CLD()
{
	setFlag(D, false);
	return 0;
}

uint8_t CPU::CLI()
{
	setFlag(I, false);
	return 0;
}

uint8_t CPU::CLV()
{
	setFlag(V, false);
	return 0;
}

uint8_t CPU::CMP()
{
	temp = (uint16_t)a - (uint16_t)fetch();

	setFlag(C, a >= fetched);
	setFlag(Z, (temp & 0x00FF) == 0x0000);
	setFlag(N, temp & 0x0080);

	return 1;
}

uint8_t CPU::CPX()
{
	temp = (uint16_t)x - (uint16_t)fetch();

	setFlag(C, x >= fetched);
	setFlag(Z, (temp & 0x00FF) == 0x0000);
	setFlag(N, temp & 0x0080);

	return 0;
}

uint8_t CPU::CPY()
{
	temp = (uint16_t)y - (uint16_t)fetch();

	setFlag(C, y >= fetched);
	setFlag(Z, (temp & 0x00FF) == 0x0000);
	setFlag(N, temp & 0x0080);

	return 0;
}

uint8_t CPU::DEC()
{
	temp = fetch() - 1;
	write(addr_abs, temp & 0x00FF);

	setFlag(Z, (temp & 0x00FF) == 0x0000);
	setFlag(N, temp & 0x0080);

	return 0;
}

uint8_t CPU::DEX()
{
	x--;

	setFlag(Z, x == 0x00);
	setFlag(N, x & 0x80);

	return 0;
}

uint8_t CPU::DEY()
{
	y--;

	setFlag(Z, y == 0x00);
	setFlag(N, y & 0x80);

	return 0;
}

uint8_t CPU::EOR()
{
	a ^= fetch();

	setFlag(Z, a == 0x00);
	setFlag(N, a & 0x80);

	return 1;
}

uint8_t CPU::INC()
{
	temp = fetch() + 1;
	write(addr_abs, temp & 0x00FF);

	setFlag(Z, (temp & 0x00FF) == 0x0000);
	setFlag(N, temp & 0x0080);

	return 0;
}

uint8_t CPU::INX()
{
	x++;

	setFlag(Z, x == 0x00);
	setFlag(N, x & 0x80);

	return 0;
}

uint8_t CPU::INY()
{
	y++;

	setFlag(Z, y == 0x00);
	setFlag(N, y & 0x80);

	return 0;
}

uint8_t CPU::JMP()
{
	pc = addr_abs;
	return 0;
}

uint8_t CPU::JSR()
{
	write(0x0100 + stkp--, (--pc >> 8) & 0x00FF);
	write(0x0100 + stkp--, pc & 0x00FF);

	pc = addr_abs;

	return 0;
}

uint8_t CPU::LDA()
{
	a = fetch();

	setFlag(Z, a == 0x00);
	setFlag(N, a & 0x80);

	return 1;
}

uint8_t CPU::LDX()
{
	x = fetch();

	setFlag(Z, x == 0x00);
	setFlag(N, x & 0x80);

	return 1;
}

uint8_t CPU::LDY()
{
	y = fetch();

	setFlag(Z, y == 0x00);
	setFlag(N, y & 0x80);

	return 1;
}

uint8_t CPU::LSR()
{
	setFlag(C, fetch() & 0x0001);
	temp = fetched >> 1;
	setFlag(Z, (temp & 0x00FF) == 0x0000);
	setFlag(N, temp & 0x0080);

	if (lookup[opcode].addrmode == &CPU::IMP)
	{
		a = temp & 0x00FF;
	}
	else
	{
		write(addr_abs, temp & 0x00FF);
	}

	return 0;
}

uint8_t CPU::NOP()
{
	switch (opcode)
	{
	case 0x1C:
	case 0x3C:
	case 0x5C:
	case 0x7C:
	case 0xDC:
	case 0xFC:
		return 1;
	default:
		return 0;
	}
}

uint8_t CPU::ORA()
{
	a |= fetch();

	setFlag(Z, a == 0x00);
	setFlag(N, a & 0x80);

	return 1;
}

uint8_t CPU::PHA()
{
	write(0x0100 + stkp--, a);
	return 0;
}

uint8_t CPU::PHP()
{
	write(0x0100 + stkp--, status | B | U);

	setFlag(B, false);
	setFlag(U, false);

	return 0;
}

uint8_t CPU::PLA()
{
	a = read(0x0100 + ++stkp);

	setFlag(Z, a == 0x00);
	setFlag(N, a & 0x80);

	return 0;
}

uint8_t CPU::PLP()
{
	status = read(0x0100 + ++stkp);
	setFlag(U, true);
	return 0;
}

uint8_t CPU::ROL()
{
	temp = (uint16_t)(fetch() << 1) | getFlag(C);

	setFlag(C, temp & 0xFF00);
	setFlag(Z, (temp & 0x00FF) == 0x0000);
	setFlag(N, temp & 0x0080);

	if (lookup[opcode].addrmode == &CPU::IMP)
	{
		a = temp & 0x00FF;
	}
	else
	{
		write(addr_abs, temp & 0x00FF);
	}

	return 0;
}

uint8_t CPU::ROR()
{
	temp = (uint16_t)(getFlag(C) << 7) | (fetch() >> 1);

	setFlag(C, fetched & 0x01);
	setFlag(Z, (temp & 0x00FF) == 0x00);
	setFlag(N, temp & 0x0080);

	if (lookup[opcode].addrmode == &CPU::IMP)
	{
		a = temp & 0x00FF;
	}
	else
	{
		write(addr_abs, temp & 0x00FF);
	}

	return 0;
}

uint8_t CPU::RTI()
{
	status = read(0x0100 + ++stkp);
	status &= ~B;
	status &= ~U;

	pc = (uint16_t)read(0x0100 + ++stkp);
	pc |= (uint16_t)read(0x0100 + ++stkp) << 8;

	return 0;
}

uint8_t CPU::RTS()
{
	pc = (uint16_t)read(0x0100 + ++stkp);
	pc |= (uint16_t)read(0x0100 + ++stkp) << 8;
	pc++;

	return 0;
}

uint8_t CPU::SBC()
{
	uint16_t value = (uint16_t)fetch() ^ 0x00FF;

	temp = (uint16_t)a + value + (uint16_t)getFlag(C);

	setFlag(C, temp & 0xFF00);
	setFlag(Z, (temp & 0x00FF) == 0);
	setFlag(V, (temp ^ (uint16_t)a) & (temp ^ value) & 0x0080);
	setFlag(N, temp & 0x0080);

	a = temp & 0x00FF;

	return 1;
}

uint8_t CPU::SEC()
{
	setFlag(C, true);
	return 0;
}

uint8_t CPU::SED()
{
	setFlag(D, true);
	return 0;
}

uint8_t CPU::SEI()
{
	setFlag(I, true);
	return 0;
}

uint8_t CPU::STA()
{
	write(addr_abs, a);
	return 0;
}

uint8_t CPU::STX()
{
	write(addr_abs, x);
	return 0;
}

uint8_t CPU::STY()
{
	write(addr_abs, y);
	return 0;
}

uint8_t CPU::TAX()
{
	x = a;

	setFlag(Z, x == 0x00);
	setFlag(N, x & 0x80);

	return 0;
}

uint8_t CPU::TAY()
{
	y = a;

	setFlag(Z, y == 0x00);
	setFlag(N, y & 0x80);

	return 0;
}

uint8_t CPU::TSX()
{
	x = stkp;

	setFlag(Z, x == 0x00);
	setFlag(N, x & 0x80);

	return 0;
}

uint8_t CPU::TXA()
{
	a = x;

	setFlag(Z, a == 0x00);
	setFlag(N, a & 0x80);

	return 0;
}

uint8_t CPU::TXS()
{
	stkp = x;
	return 0;
}

uint8_t CPU::TYA()
{
	a = y;

	setFlag(Z, a == 0x00);
	setFlag(N, a & 0x80);

	return 0;
}

uint8_t CPU::XXX()
{
	return 0;
}

uint8_t CPU::fetch()
{
	if (lookup[opcode].addrmode != &CPU::IMP)
	{
		fetched = read(addr_abs);
	}
	return fetched;
}

uint8_t CPU::read(uint16_t addr)
{
	return bus->read(addr, false);
}

void CPU::write(uint16_t addr, uint8_t data)
{
	bus->write(addr, data);
}

uint8_t CPU::getFlag(FLAGS f)
{
	return (status & f) > 0;
}

void CPU::setFlag(FLAGS f, bool v)
{
	if (v)
	{
		status |= f;
	}
	else
	{
		status &= ~f;
	}
}
