#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#define RCCLEDPORT (RCC_GPIOC)
#define LEDPORT (GPIOC)
#define LEDPIN (GPIO13)

static void gpio_setup(void)
{
	// Enable GPIOC clock
	rcc_periph_clock_enable(RCCLEDPORT);

	// Configure PC13 as output
#ifdef STM32F1
	gpio_set_mode(LEDPORT, GPIO_MODE_OUTPUT_2_MHZ,
	              GPIO_CNF_OUTPUT_PUSHPULL, LEDPIN);
#else
	gpio_mode_setup(LEDPORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LEDPIN);
#endif
}

static void delay_ms(uint32_t ms)
{
	// Simple blocking delay loop (not accurate, for rough timing only)
	for (uint32_t i = 0; i < ms * 8000; i++) {
		__asm__("nop");
	}
}

int main(void)
{
	gpio_setup();

	while (1) {
		gpio_toggle(LEDPORT, LEDPIN); // Toggle LED
		delay_ms(100);               // 1 second delay
	}

	return 0;
}