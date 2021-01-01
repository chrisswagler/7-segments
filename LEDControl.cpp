//Christopher Swagler
#include "DE1SoCfpga.h"
#include "LEDControl.h"

LEDControl::LEDControl() {
  leds_regValue = ReadAllSwitches();
}

LEDControl::~LEDControl() {
  cout << "Closing LEDs, Switches, & Buttons..." << endl;
}

void LEDControl::Write1Led(int ledNum, int state) {
  //create variable to store which bit to change
  int bit;
  //if the state value is to turn off the bit
  if (state == 0) {
  //create a mask that is the flipped bits of the one to switch
    bit = ~(1 << ledNum);
    //taking the & of all 1's except the bit to change and the current state of the LEDs will just change the one bit
    leds_regValue = (bit & RegisterRead(LEDR_BASE));
  //if the state value is to turn on the bit
  } else if (state == 1) {
    //create a mask that has a 1 at the bit to turn on
    bit = (1 << ledNum);
    //taking the | of all 0's except the bit to change and the current state of the LEDs will just change the one bit
    leds_regValue = (bit | RegisterRead(LEDR_BASE));
  }
  //write the value to the LEDs
  WriteAllLeds(leds_regValue);
}

void LEDControl::WriteAllLeds(int value) {
  //write to the LEDs whatever value was passed to function
  leds_regValue = value;
  RegisterWrite(LEDR_BASE, leds_regValue);
}

int LEDControl::Read1Switch(int switchNum) {
  //create variable to store current state of switches
  int switchval;
  switchval = ReadAllSwitches();
  //shift bits right so that the 2^0 bit is the bit for the switchNum
  switchval = (switchval >> switchNum);
  //if the remainder of switchval % 2 is 1 then the bit was on and 0 if itwas off
  return (switchval % 2);
}

int LEDControl::ReadAllSwitches() {
  //create variable to store RegisterRead return value with switches offset
  int switchesvalue;
  switchesvalue = RegisterRead(SW_BASE);
  //set bitmask to 1023, which is decimal representation of the first 10 bits
  int bitmask = 1023;
  //using bitwise & will clear the higher 22 bits since x&0=0
  switchesvalue = switchesvalue & bitmask;
  return switchesvalue;
}

int LEDControl::PushButtonGet() {
  //read the value from the buttons
  int buttonval = RegisterRead(KEY_BASE);
    switch (buttonval) {
    //no buttons pressed
    case 0:
      return -1;
      break;
    //key0 pressed
    case 1:
      return 0;
      break;
    //key1 pressed
    case 2:
      return 1;
      break;
    //key2 pressed
    case 4:
      return 2;
      break;
    //key3 pressed
    case 8:
      return 3;
      break;
    //otherwise multiple buttons pressed
    default:
      return 4;
      break;
  }
}
