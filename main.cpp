//Christopher Swagler

#include "DE1SoCfpga.h"
#include "SevenSegment.h"
#include "LEDControl.h"

int main()
{
	//initialize buttonstate variable to store what button was pressed
	int buttonstate;
	//create LEDControl and SevenSegment object
	LEDControl ledc;
	SevenSegment ss;
	//initialize variable as running counter, intially set to switches val
	int counter = ledc.ReadAllSwitches();

	while (1) {
		//use PushButtonGet() to determine what buttons are pressed
		buttonstate = ledc.PushButtonGet();
		//debounce time if a button was pressed
		if (buttonstate != -1) {
			sleep(1);
		}
		switch (buttonstate) {
			//key0 pressed, increment counter by 1
			case 0:
				counter++;
				break;
			//key1 pressed, decrement counter by 1
			case 1:
				counter--;
				break;
			//key2 pressed, shift right
			case 2:
				counter = (counter >> 1);
				break;
			//key3 pressed, shift left
			case 3:
				counter = (counter << 1);
				break;
			//multiple pressed, reset counter to current switches
			case 4:
				counter = ledc.ReadAllSwitches();
				break;
			//otherwise no buttons are pressed
			default:
				counter;
				break;
		}
		//write the counter value to the LEDs
		ledc.WriteAllLeds(counter);
		ss.Hex_WriteNumber(counter);
	}
}
