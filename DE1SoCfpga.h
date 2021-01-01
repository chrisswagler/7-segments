//Christopher Swagler
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>
using namespace std;

// Physical base address of FPGA Devices
const unsigned int LW_BRIDGE_BASE 	= 0xFF200000;  // Base offset

// Length of memory-mapped IO window
const unsigned int LW_BRIDGE_SPAN 	= 0x00005000;  // Address map size

// Cyclone V FPGA device addresses
const unsigned int LEDR_BASE 		= 0x00000000;  // Leds offset
const unsigned int HEX3_HEX0_BASE       = 0x00000020;  // Data Reg1 offset
const unsigned int HEX5_HEX4_BASE       = 0x00000030;  // Data Reg2 offset
const unsigned int SW_BASE 		= 0x00000040;  // Switches offset
const unsigned int KEY_BASE 		= 0x00000050;  // Push buttons offset

//class for main functions of the de1soc board from previous program
class DE1SoCfpga
{
private:
	//private members
	char *pBase;
	int fd;
public:
	//default constructor (Initialize from previous program)
	DE1SoCfpga();
	//destructor (Finalize from previous program)
	~DE1SoCfpga();
	//write to the board
	void RegisterWrite(unsigned int offset, int value);
	//read from the board
	int RegisterRead(unsigned int offset);
};
