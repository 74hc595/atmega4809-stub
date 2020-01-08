/**
 * Blinks an LED on pin PD7 at 1 Hz.
 */
#include <avr/io.h>
#include <util/delay.h>

#define LED_PORT  VPORTD
#define LED_PIN   7

int main(void)
{
  /* disable clock prescaler, run at 20MHz */
  CCP = 0xD8; /* unlock CLKCTRL registers */
  CLKCTRL_MCLKCTRLB = 0;

  /* pin is an output */
  LED_PORT.DIR |= _BV(LED_PIN);

  while (1) {
    LED_PORT.IN |= _BV(LED_PIN);  /* writing to IN toggles output level */
    _delay_ms(500);
  }
}
