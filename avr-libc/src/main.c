/* header files provides various functions. to use a function in AVR libc, the
 * header file of the function must be included.
 *
 * for instance, stdlib.h header file provides general utility functions, such
 * as abs(), which computes the absolute value of the given argument, rand(),
 * which returns a random integer.
 *
 * see the list of header files at:
 * https://www.nongnu.org/avr-libc/user-manual/modules.html
 *
 * to include a header file, use `include` C preprocessor directive. there
 * are two forms:
 *
 * #include <foo.h>
 *
 * and
 *
 * #include "foo.h"
 *
 * use #include <foo.h> to include external header files. an external header
 * file is a header file that you do not write.
 *
 * use #include "foo.h" to include your own header file.
 *
 * note that "#" in front of "include" is NOT the start of a comment.
 *
 * for more details, see:
 * https://www.nongnu.org/avr-libc/user-manual/group__util__delay.html
 * https://www.nongnu.org/avr-libc/user-manual/group__avr__io.html
 */

/* include avr/io.h, which provides functions and macro definitions to control
 * GPIO pins, and avr/delay.h, which provides delay functions.
 */
#include <avr/delay.h>
#include <avr/io.h>

/* a simple Blink example. the program blinks an LED at 1Hz.
 *
 * main() function is where the program starts. the MCU does some
 * initialization, and executes main() function.
 */
int
main()
{

	/* configure PB0 as an output.
	 *
	 * DDRB and DDB0 is macro defined in avr/io.h.
	 *
	 * see `gpio` lessson for more details.
	 */
	DDRB |= (1 << DDB0);

	/* drive PB0 HIGH.
	 *
	 * PORTB is also defined in avr/io.h.
	 */
	PORTB |= (1 << PORTB0);

	while (1) {

		/* delay 500ms
		 *
		 * _delay_ms() is defined in avr/delay.h.
		 */
		_delay_ms(500);

		/* toggle the logic level on PB0 */
		PORTB ^= (1 << PORTB0);
	}
}
