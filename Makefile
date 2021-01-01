# lab4a Makefile
lab4a: DE1SoCfpga.o SevenSegment.o LEDControl.o main.o
	g++ DE1SoCfpga.o SevenSegment.o LEDControl.o main.o -o lab4a
DE1SoCfpga.o: DE1SoCfpga.cpp DE1SoCfpga.h
	g++ -c DE1SoCfpga.cpp
SevenSegment.o: SevenSegment.cpp SevenSegment.h DE1SoCfpga.h
	g++ -c SevenSegment.cpp
LEDControl.o: LEDControl.cpp LEDControl.h DE1SoCfpga.h
	g++ -c LEDControl.cpp
main.o: main.cpp DE1SoCfpga.h SevenSegment.h LEDControl.h
	g++ -c main.cpp
clean:
	rm DE1SoCfpga.o SevenSegment.o LEDControl.o main.o
