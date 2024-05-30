/*
 * ATiny10.cpp
 *
 * Created: 24/05/2024 15:39:54
 * Author : René Putzönius
 Sven braucht:
	zwei Doppelblitzer asynchron
	zwei Rundumleuchten asynchron
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Lights.h"

#define F_CPU 8000000UL  // 8 MHz clock speed
#define PRESCALER 64
#define COMPARE_MATCH_VALUE (F_CPU / PRESCALER / 1000) - 1  // 1 ms interval

ISR(TIM0_COMPA_vect);
void init_timer0();

Light L0(0);
Light L1(1);
Light L2(2);

const int intervallA[] = {40, 40, 40, 40, 40, 40, 40, 40, 120};
const int intervallB[] = {500, 500};
const int intervallC[] = {250, 250};	
			
int main(void)
{
	L0.setup(0, 0, sizeof(intervallA) / sizeof(intervallA[0]), intervallA);
	L1.setup(1, 0, sizeof(intervallB) / sizeof(intervallB[0]), intervallB);
	L2.setup(1, 0, sizeof(intervallC) / sizeof(intervallC[0]), intervallC);
	
	//DDRB |= (1 << 0) | (1 << 1) | (1 << 2);
	//PORTB = 0b00000111;
	
	// Initialize the timer
	init_timer0();

	// Enable global interrupts
	sei();

	// Main loop
	while (1) {
		// Main loop code
	}
}

void init_timer0()
{
	// Set Timer0 to CTC mode
	TCCR0A = (1 << WGM01);  // WGM01:0 = 2 -> CTC mode

	// Set the compare match value for 1 ms
	OCR0A = COMPARE_MATCH_VALUE;

	// Set the prescaler to 64
	TCCR0B = (1 << CS01) | (1 << CS00);  // CS01:0 = 3 -> Prescaler 64

	// Enable Timer0 compare match interrupt
	TIMSK0 = (1 << OCIE0A);  // Enable compare match A interrupt
}

ISR(TIM0_COMPA_vect)
{
	// Interrupt Service Routine (ISR) for Timer0 Compare Match A
	// This code will be executed every 1 ms
	// Add your code here
	L0.tick();
	L1.tick();
	L2.tick();
}