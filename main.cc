#include "hardware/clocks.h"
#include "hardware/pwm.h"
#include "pico/stdlib.h"

#include <string>
#include <string_view>
#include <unordered_map>

// 40 hardware pins
// 3, 8, 13, 18 are GND
// GPIO0 is Pin 1
// So, GPIO15 is pin 20,
// 4 slots of GND + GPIO 0
constexpr uint GPIO15 = 15; // GP15 = pin 20

const std::unordered_map<std::string_view, float> NOTE_TO_FREQUENCY{
    {"A", 440.00f},
    {"B", 493.88f},
    {"C", 261.63f},
    {"D", 293.66f},
    {"E", 329.63f},
    {"F", 349.23f},
    {"G", 392.00f}
};

// It's a common concept to scale a high frequency system clock to
// a slower, more manageable speed before the signal is used for a
// peripheral.
constexpr float PWM_PRESCALER = 100.0f;

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

class Buzzer {
	public:
		Buzzer(uint buzzer) : buzzer_(buzzer) {
			slice_ = pwm_gpio_to_slice_num(buzzer_);  // One of eight "slice"s of electricity modulator
			gpio_set_function(buzzer_, GPIO_FUNC_PWM);  // Where the electricity pulses to

			//  Ticks per second. Pico 2 only holds 2**16 numbers (65536 is the max).
			//  Ticks is a "time slice" of one cycle of the clock.
			//  High frequency, which the human ear interprets as high pitch, requires
			//  more buzzes (fewer ticks before we modulate within one clock cycle).
 	    pwm_clock_ =
        static_cast<float>(clock_get_hz(clk_sys)) / PWM_PRESCALER;
 	    pwm_set_clkdiv(slice_, PWM_PRESCALER);
		}

		void buzz(std::string_view note, int ms) {
			// hz is wave cycles per second.
			// pwm_clock_ is clock cycles per second.
			// wrap is clock cycles per wave cycles -1,
			// since counting start at 0.
			//
			// If wrap = 2, it means 2 full sound wave cycles
			// per second. This would be a very low frequency pitch.
			float hz = NOTE_TO_FREQUENCY.at(note);
	    uint32_t wrap =
        static_cast<uint32_t>(pwm_clock_ / hz) - 1;

      pwm_set_wrap(slice_, wrap);
			pwm_set_gpio_level(buzzer_, wrap / 2);  // ~50% duty cycle
	    pwm_set_enabled(slice_, true);

    	sleep_ms(ms);

	    pwm_set_enabled(slice_, false);
	 	  gpio_put(buzzer_, 0);
 		  sleep_ms(40);	
		}

  private:
   	uint buzzer_;	
		uint slice_;
		float pwm_clock_;
};

int main() {
	//	Blinker blinker{GPIO15};
	Buzzer buzzer{GPIO15};

	const std::string melody[] = {
    "D", "E", "F", "A", "A", "A", "G", "F", 
    "G", "A", "A", "A", "G", "F", "G", "D"
	};


	while (true) {
		//	blinker.blink();
		for (std::string_view note : melody) {
			buzzer.buzz(note, 250);
		}
	}
}
