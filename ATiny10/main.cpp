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
#include "FlashLight.h"

#define F_CPU 8000000UL  // 8 MHz clock speed
#define PRESCALER 64
#define COMPARE_MATCH_VALUE (F_CPU / PRESCALER / 1000) - 1  // 1 ms interval

ISR(TIMER1_COMPA_vect);
ISR(TIMER0_COMPA_vect);
void init_timer0();
void init_timer1();

FlashLight L0(0);
FlashLight L1(1);
FlashLight L2(2);
FlashLight L3(3);

const int intervall0[] = {40, 40, 40, 40, 40, 40, 40, 120};
const int intervall1[] = {1,20,1,20,1,19, 2,18, 3,17, 4, 16, 5,15, 80,0, 5,15, 4,16, 3,17, 2,18,1,19,1,20,1,20};
const int intervall3[] = {20, 180, 320};
			
int main(void)
{
	L0.setup(1, 0, sizeof(intervall0) / sizeof(intervall0[0]), intervall0);
	L1.setup(1, 4, sizeof(intervall0) / sizeof(intervall0[0]), intervall0);
	L2.setup(1, 0, sizeof(intervall1) / sizeof(intervall1[0]), intervall1);
	L3.setup(1, 15, sizeof(intervall1) / sizeof(intervall1[0]), intervall1);
	
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

void init_timer1()
{
	TCCR1A = 0;
	TCCR1B = 0;
	// Set Timer0 to CTC mode
	TCCR1B |= (1 << WGM12);  // WGM01:0 = 2 -> CTC mode

	// Set the compare match value for 1 ms
	OCR1A = COMPARE_MATCH_VALUE;

	// Set the prescaler to 64
	TCCR1B |= (1 << CS11) | (1 << CS10);  // CS01:0 = 3 -> Prescaler 64

	// Enable Timer0 compare match interrupt
	TIMSK1 |= (1 << OCIE1A);  // Enable compare match A interrupt
}

ISR(TIMER0_COMPA_vect)
{
	// Interrupt Service Routine (ISR) for Timer0 Compare Match A
	// This code will be executed every 1 ms
	// Add your code here
	L0.tick();
	L1.tick(),
	L2.tick();
	L3.tick();
}

ISR(TIMER1_COMPA_vect)
{
	// Interrupt Service Routine (ISR) for Timer0 Compare Match A
	// This code will be executed every 1 ms
	// Add your code here
	L0.tick();
	L1.tick(),
	L2.tick();
	L3.tick();
}
