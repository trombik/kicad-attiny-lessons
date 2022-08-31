#include <avr/io.h>

/* see 11.7.4 Phase Correct PWM Mode in the datasheet, */
int
main()
{
	/* use PB0 as output.
	 *
	 * see 10.2.1 Configuring the Pin, and 10.4.3 DDRB – Port B Data
	 * Direction Register.
	 */
	DDRB = (1 << PB0);

	/* enable PWM, Phase Correct mode. the timer increases the value from
	 * 0 to 255, decreases it from 255 to 0, and repeat.
	 * */
	TCCR0A |= (1 << WGM00);

	/* clear OC0A/OC0B on Compare Match when up-counting.
	 * set OC0A/OC0B on Compare Match when down-counting.
	 *
	 * set == HIGH, clear == LOW.
	 * Compare Match == when counter value equals to OCR0A.
	 *
	 * see 11.9.2 TCCR0A – Timer/Counter Control Register A
	 */
	TCCR0A |= (1 << COM0A1);

	/* prescale CLK(I/O) by 1024 prescale factor (1024 times slower).
	 *
	 * Fpwm = F_CPU / (N * 510)
	 *
	 * where N is the prescale factor. the factory default CPU clock for
	 * ATTiny85 is 1MHz.
	 *
	 * Fpwm = 1000000 / (1024 * 510) = 1.91 (Hz)
	 *
	 * N can be one of:
	 *
	 * * 1 (no prescaling)
	 * * 8 (8 times slower)
	 * * 64 (64 times slower)
	 * * 256 (256 times slower)
	 * * 1024 (1024 times slower)
	 *
	 * see 11.9.3 TCCR0B – Timer/Counter Control Register B
	 */
	TCCR0B |= (1 << CS00) | (1 << CS02);

	/* set value for compare match, when the timer value is less than this
	 * value, the level on OC0A goes HIGH.
	 *
	 * When OC0A = 150,
	 *
	 * | Timer value | Direction   | Output |
	 * |-------------|-------------|--------|
	 * | 0 - 149     | Upcouting   | HIGH   |
	 * | 150 - 255   | Upcouting   | LOW    |
	 * | 254 - 150   | Downcouting | LOW    |
	 * | 149 - 0     | Downcouting | HIGH   |
	 *
	 * Duty = Th / (Th + Tl) * 100 (%)
	 *
	 * where Th is time at HIGH, Tl is time at LOW.
	 *
	 * Duty = 150 * 2 / 512 * 100 = 58.59375 (%)
	 *
	 * see 11.9.5 OCR0A – Output Compare Register A
	 */
	OCR0A = 150;
	while (1) {
		/* you can do whatever here. the PWM signal is controlled by
		 * the hardware.
		 * */
	}
}
