//Christopher Swagler
#include "DE1SoCfpga.h"
#include "SevenSegment.h"

SevenSegment::SevenSegment() {
  //make the register values the 0 equivalent and write it
  dataReg1 = (63 << 24) + (63 << 16) + (63 << 8) + 63;
  dataReg2 = (63 << 8) + 63;
  RegisterWrite(HEX3_HEX0_BASE, dataReg1);
  RegisterWrite(HEX5_HEX4_BASE, dataReg2);
}

SevenSegment::~SevenSegment() {
  Hex_ClearAll();
}

void SevenSegment::Hex_ClearAll() {
  dataReg1 = 0;
  dataReg2 = 0;
  RegisterWrite(HEX3_HEX0_BASE, dataReg1);
  RegisterWrite(HEX5_HEX4_BASE, dataReg2);
}

void SevenSegment::Hex_ClearSpecific(int index) {
  //create mask to be all 1s in seven places
  int mask = 127;
  if (index <= 3) {
    //mask the value with the current state of LED
    //mask is negation of all ones in the seg place
    dataReg1 = dataReg1  & ~(mask << (index * 8));
    RegisterWrite(HEX3_HEX0_BASE, dataReg1);
  } else if (index <= 5) {
    //mask value with the current state of LED
    //mask is negation of all ones in the seg place
    dataReg2 = dataReg2 & ~((mask << (index - 4) * 8));
    RegisterWrite(HEX5_HEX4_BASE, dataReg2);
  }
}

void SevenSegment::Hex_WriteSpecific(int display_id, int value) {
  //first clear bits before writing
  Hex_ClearSpecific(display_id);
  if (display_id <=3) {
    //use the global bit_values to get corresponding value
    //use or operation on this and current state
    dataReg1 = dataReg1 | (bit_values[value] << (display_id * 8));
    RegisterWrite(HEX3_HEX0_BASE, dataReg1);
  } else if (display_id <= 5) {
    //use global bit_values to get corresponding value
    //use or operation on this and current state
    dataReg2 = dataReg2 | (bit_values[value] << ((display_id - 4) * 8));
    RegisterWrite(HEX5_HEX4_BASE, dataReg2);
  }
}

void SevenSegment::Hex_WriteNumber(int number) {
  //clear display to write new number
  Hex_ClearAll();
  //create variable for current hex to use when lighting up
  int hex = 0;
  //if the inputted number is negative
  if (number < 0) {
    //make negative sign on HEX 5 which is just 6 bit
    int neg = (0b1000000 << 8);
    //set dataReg2 to the or of this and neg, then write
    dataReg2 = dataReg2 | neg;
    RegisterWrite(HEX5_HEX4_BASE, dataReg2);
    //while the remainder operation can still be performed
    while (number != 0) {
      //remainder of number / 10
      int rem = 0;
      rem = number % 10;
      //write to the current hex
      //since negative, multiply -1 by rem for bit_values index
      Hex_WriteSpecific(hex, (-1 * rem));
      //change the number to be integer div with 10
      number = number / 10;
      //move to the next hex
      hex++;
    }
    //if the number is exactly 0
  } else if (number == 0){
    Hex_WriteSpecific(hex, 0);
  //if the number is positive
  } else {
    //while remainder operation can still be performed
    while (number != 0) {
      //remainder of number /10
      int rem = 0;
      rem = number % 10;
      //write to current hex with remainder
      Hex_WriteSpecific(hex, rem);
      //change the number to be integer div with 10
      number = number / 10;
      //move to the next hex
      hex++;
    }
  }
}
