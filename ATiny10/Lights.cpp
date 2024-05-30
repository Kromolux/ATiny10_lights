#include "Lights.h"

Light::Light(myByte ledPort) : _ledPort(ledPort), _countOfMillis(0)
{}

void Light::setup(const myByte startValue, const myByte startIntervall, const myByte lengthOfIntervall, const int * intervall)
{
	DDRB |= (1 << _ledPort);
	
	if (startIntervall >= _lengthOfIntervall)
		_pointerIntervall = _lengthOfIntervall -1;
	else
		_pointerIntervall = startIntervall;
		
	setPort(startValue);
	_intervall = intervall;
}

void Light::setPort(myByte value)
{
	//set 1 | (1 << _port)
	//set 0 & ~(1 << _port)
	if (value == 0)
		PORTB &= ~(1 << _ledPort);
	else
		PORTB |= (1 << _ledPort);
}

void Light::tick(void)
{
	++_countOfMillis;
	if (_countOfMillis >= _intervall[_pointerIntervall])
	{
		_countOfMillis = 0;
		PORTB ^= (1 << _ledPort);
		++_pointerIntervall;
		if (_pointerIntervall >= _lengthOfIntervall)
			_pointerIntervall = 0;
		//_value ^= 1;
		//setPort(_value);
		/*
		if (_value == 0)
			_value = 1;
		else
			_value = 0;
		setPort(_value);
		*/
	}
}
