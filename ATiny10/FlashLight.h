#ifndef FLASHLIGHT_H
# define FLASHLIGHT_H

# include <avr/io.h>

typedef unsigned char myByte;

class FlashLight
{
	private:
	myByte _ledPort0;
	myByte _ledPort1;
	int _countOfMillis;
	myByte _pointerIntervall;
	myByte _lengthOfIntervall;
	const int *_intervall;
	
	public:
	FlashLight(myByte ledPort0);
	
	void setup(const myByte startValue, const myByte startIntervall, const myByte lengthOfIntervall, const int * intervall);
	void setPort(myByte value);
	void tick(void);
	
};

#endif