#include "FlashLight.h"

FlashLight::FlashLight(myByte ledPort0) : _ledPort0(ledPort0), _countOfMillis(0)
{}

void FlashLight::setup(const myByte startValue, const myByte startIntervall, const myByte lengthOfIntervall, const int * intervall)
{
	DDRB |= (1 << _ledPort0);	//set ports to output
	
	_lengthOfIntervall = lengthOfIntervall;
	
	if (startIntervall >= _lengthOfIntervall)
	_pointerIntervall = _lengthOfIntervall -1;
	else
	_pointerIntervall = startIntervall;
	
	setPort(startValue);
	_intervall = intervall;
}

void FlashLight::setPort(myByte value)
{
	if (value == 0)
	{
		PORTB &= ~(1 << _ledPort0);
	}
	else
	{
		PORTB |= (1 << _ledPort0);
	}
}

void FlashLight::tick(void)
{
	++_countOfMillis;
	if (_countOfMillis >= _intervall[_pointerIntervall])
	{
		_countOfMillis = 0;

		++_pointerIntervall;
		if (_pointerIntervall >= _lengthOfIntervall)
		_pointerIntervall = 0;
		PORTB ^= (1 << _ledPort0);
	}
}
