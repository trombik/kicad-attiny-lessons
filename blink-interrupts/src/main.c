#include <avr/interrupt.h>
#include <avr/io.h>

/* an example to blink an LED at 1Hz using interrupts.
 *
 * interrupt version of blink program is effecient because the program can do
 * other things instead of doing nothing but waiting for a time period to pass
 * (delay() in Arduino).
 */

/* timer0 increases its value by one until the value reaches to 255 (0xff, 8
 * bit timer), the timer0 restarts from zero after that (an overflow).
 *
 * the frequency of timer0 is:
 *
 * CPU clock / prescale factor (Hz)
 *
 * in case of ATTiny85, CPU clock is 1,000,000Hz, or 1Mhz.
 *
 * a prescale factor can be one of:
 * * 1 (no prescale)
 * * 8
 * * 64
 * * 256
 * * 1024
 *
 * when the prescale factor is 1 (no prescale), the time to increment the
 * timer value is:
 *
 * T = 1 / F
 *   = 1 / 1000000
 *   = 0.001ms
 *   = 1us
 *
 * the time of an overflow is:
 *
 * 1us * 256 = 256us
 *
 * by counting times of overflows, it is possible to measure time. for
 * instance, divide the time to measure by the time of an overflow.
 *
 * 1s / 256us = 3906.25
 *
 * when approximately 3906 overflows occur, it is 1s.
 *
 * to measure 1min, the number of overflows are:
 *
 * 1min = 60s
 * 60s / 256us = 234375
 *
 * the number is too huge for ATTiny85. with a prescale factor, the size of
 * counter can be decreased. for instance, with a prescale factor of 1024,
 *
 * T = 1 / (F / prescale factor)
 *   = 1 / (1000000 / 1024)
 *   = 0.001024s
 *   = 1.024ms
 *
 * the time of an overflow is:
 * 1.024ms * 256 = 0.262144s
 *               = 262ms
 * 1min = 60s
 * 60s / 262ms = 229
 *
 * it is now 229 times to count overflows, instead of couting 234375 times.
 *
 * in summary, to measure time,
 *
 * * enable timer0 (with a prescale factor if necessary)
 * * count the number of overflows
 * * do something when the number of overflows reaches to the desired number
 *
 * an interrupt function is a function that is called when something happens.
 * the CPU stops executing the code, such as main() function, executes the
 * interrupt function, and returns to where it has stopped execution. AVR MCUs
 * have many interrupts, such as "when the voltage of GPIO goes HIGH". the
 * name of interrupts is called a "vector".
 *
 * TIMER0_OVF_vect (timer0 overflow vector) is the name of an interrupt called
 * when timer0 overflows.  to create an interrupt function, use `ISR()` macro.
 * the argument is a name of interrupts.
 *
 * see also:
 * https://avr-libc.nongnu.org/user-manual/group__avr__interrupts.html
 */

/* the counter to count how many times an overflow occurs. */
int overflow_count;

ISR(TIMER0_OVF_vect)
{
	/* to blink an LED at 1Hz, the LED is on for 500ms, and off for 500ms.
	 *
	 * a prescaler factor of 64 will be used below.
	 *
	 * the frequency of timer0 is:
	 * F = 1000000 / 64
	 *
	 * the time of an overflow is:
	 * T = 1 / F * 256
	 *   = 1 / (1000000 / 64) * 256
	 *   = 0.016384 (s)
	 *   = 16.38 (ms)
	 *
	 * to measure 500ms:
	 * 0.5s / 0.016384s = 30.51 (times)
	 *
	 * when an overflows occurs approximately 31 times, it is (almost)
	 * 500ms.
	 */

	/* an overflow occured */
	overflow_count++;

	if (overflow_count >= 31) {

		/* it is the time to change the status of LED */
		PORTB ^= (1 << PB0);

		/* reset the counter and start couting again */
		overflow_count = 0;
	}
}

int
main()
{

	/* enable timer0 interrupt.
	 *
	 * see 11.9.7 TIMSK – Timer/Counter Interrupt Mask Register
	 */
	TIMSK |= (1 << TOIE0);

	/* use a prescale factor of 64.
	 *
	 * see 11.9.3 TCCR0B – Timer/Counter Control Register B
	 */
	TCCR0B |= (1 << CS01) | (1 << CS00);

	/* configure PB0 as an output */
	DDRB |= (1 << DDB0);

	/* drive PB0 HIGH */
	PORTB |= (1 << PB0);

	/* enable global interrupt. sei() is defined in avr/interrupt.h.
	 *
	 * to use interrupts, sei() must be called. after this,
	 * TIMER0_OVF_vect is called when an overflow occurs.
	 */
	sei();

	while (1) {
	}
}
