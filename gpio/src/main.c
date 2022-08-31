#include <avr/io.h>

/* see 10. I/O Ports */
int
main()
{
	/* use PB0 as an output. by setting 1, the pin is configured as an
	 * output. by setting 0. the pin is configured as an input.
	 *
	 * by default, all the pins are configured as an input (DDRB == 0x00).
	 *
	 * see 10.2.1 Configuring the Pin, and 10.4.3 DDRB – Port B Data
	 * Direction Register.
	 *
	 * the following is an idiom to "set 1 on DDB0 bit".
	 */
	DDRB |= (1 << DDB0);

	/* use PB1 as an input with pull-up resistor enabled by clearing DDB1,
	 * or setting 0 on the bit.
	 *
	 * note that it is not necessary to clear the bit here because pins
	 * are configured as an input by default. however, it is always a good
	 * idea to explicitly set 0.
	 *
	 * the following is an idiom to "clear DDB1 bit", or "set 0 on DDB1
	 * bit".
	 */
	DDRB &= ~(1 << DDB1);

	/* enable pull-up resistor of PB1.
	 *
	 * PORTB, or Port B Data Resister, behaves differently depending on
	 * the mode of the pin.
	 *
	 * when the pin is an input pin, the corresponding bit of PORTB
	 * enables or disables the pull-up resistor of the pin. logic 1
	 * enables the pull-up resistor, and logic 0 disables the pull-up
	 * resistor. by default, pull-up resistor is disabled.
	 *
	 * when the pin is an output pin, the corresponding bit of PORTB
	 * drives the pin HIGH or LOW. logic 1 drives the pin HIGH, logic 0
	 * drives the pin LOW. by default, the logic level is LOW.
	 *
	 * see 10.2.1 Configuring the Pin, and 10.4.2 PORTB – Port B Data
	 * Register.
	 */
	PORTB |= (1 << PORTB1);

	while (1) {

		/* read the logic level of PB1 and drive PB0 HIGH if PB1 is
		 * LOW.
		 *
		 * PINB, Port B Input Pins Address, is a resister that keeps
		 * logic levels of GPIO pins. regardless of the pin
		 * configuration (input or output), the value reflects digital
		 * logic levels of all GPIO pins.
		 *
		 * to test a specific pin is HIGH or LOW, use "&".
		 *
		 * PINB & (1 << PB1) is true when PB1 is HIGH, false when LOW.
		 *
		 * PINB & ((1 << PB0) | (1 << PB1)) == (1 << PB0) | (1 << PB1)
		 * is true when PB0 and PB1 are both HIGH.
		 *
		 * see 10.2.4 Reading the Pin Value.
		 */
		if (PINB & (1 << PB1)) {
			/* PB1 is HIGH, drive PB0 LOW */
			PORTB &= ~(1 << PORTB0)
		} else {
			/* PB1 is LOW. drive PB0 HIGH */
			PORTB |= (1 << PORTB0);
		}
	}
}
