#include "pico/stdlib.h"

int main() {
	// 40 hardware pins
	// 3, 8, 13, 18 are GND
	// GPIO0 is Pin 1
	// So, GPIO15 is pin 20,
	// 4 slots of GND + GPIO 0
	const uint LED_PIN = 15;  // GP15 = pin 20

	gpio_init(LED_PIN);
	gpio_set_dir(LED_PIN, GPIO_OUT);

	while (true) {
		gpio_put(LED_PIN, 1);
		sleep_ms(500);

		gpio_put(LED_PIN, 0);
		sleep_ms(500);
	}
}
