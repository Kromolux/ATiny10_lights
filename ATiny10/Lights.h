#ifndef LIGHTS_H
# define LIGHTS_H

# include <avr/io.h>

typedef unsigned char myByte;
class Light 
{
	private:
	myByte _ledPort;
	int _countOfMillis;
	myByte _pointerIntervall;
	myByte _lengthOfIntervall;
	const int *_intervall;
	
	public:
	Light(myByte ledPort);
	
	void setup(const myByte startValue, const myByte startIntervall, const myByte lengthOfIntervall, const int * intervall);
	void setPort(myByte value);
	void tick(void);
	
};

#endif