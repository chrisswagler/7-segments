//Christopher Swagler 001328396

const unsigned int bit_values[16] = {63,6,91,79,102,109,125,7,127,111,119,124,57,94,121,113};

class SevenSegment : public DE1SoCfpga
{
private:
	//private members to store value of data registers for LED segs
	unsigned int dataReg1;
	unsigned int dataReg2;
public:
	//constructor initializing LED reg values to display 0s
	SevenSegment();

	//destructor to clear displays
	~SevenSegment();

	//function to turn off all 7 seg displays
	void Hex_ClearAll();

	//function to clear specific display
	void Hex_ClearSpecific(int index);

	//function to write to a specific hex seg
	void Hex_WriteSpecific(int display_id, int value);

	//function to write a number on the 7 segment display
	void Hex_WriteNumber(int number);

};
