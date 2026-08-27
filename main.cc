#include "pico/stdlib.h"

// 40 hardware pins
// 3, 8, 13, 18 are GND
// GPIO0 is Pin 1
// So, GPIO15 is pin 20,
// 4 slots of GND + GPIO 0
constexpr uint GPIO15 = 15; // GP15 = pin 20

class Blinker {
	public:
		Blinker(uint led) : led_(led) {
			gpio_init(led_);
			gpio_set_dir(led_, GPIO_OUT);
		}

		void blink() {
			gpio_put(led_, 1);
			sleep_ms(500);

			gpio_put(led_, 0);
			sleep_ms(500);
		}
		
	private:
		uint led_;
};

int main() {
	Blinker blinker{GPIO15};

	while (true) {
		blinker.blink();
	}
}
