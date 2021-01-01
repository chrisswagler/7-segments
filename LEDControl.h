//Christopher Swagler

class LEDControl : public DE1SoCfpga {
private:
	unsigned int leds_regValue;
public:
	//constructor for LEDs initialized to switches value
	LEDControl();
	~LEDControl();
	//write to one LED
	void Write1Led(int ledNum, int state);

	//write to all LEDs
	void WriteAllLeds(int value);

	//read one switch
	int Read1Switch(int switchNum);

	//read all switches
	int ReadAllSwitches();

	//get what push button is pressed
	int PushButtonGet();
};
