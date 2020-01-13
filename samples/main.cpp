#include "BrainPad.h"

BrainPad bp;
uint8_t ZERO_FRAME[4];

int main()
{
    bp.init();

    int state = 0;

    codal::Pin led_mosi(ID_PIN_BUTTON_LEFT, PB_8, PIN_CAPABILITY_DIGITAL);
    codal::Pin *led_miso = NULL;
    codal::Pin *led_sclk = NULL;
    ZSPI led(led_mosi, *led_miso, *led_sclk);
    led.setFrequency(3200000);

    while(1)
    {
        spi->transfer(ZERO_FRAME, sizeof(ZERO_FRAME), NULL, 0);
        bp.io.ledRed.setDigitalValue(state);
        fiber_sleep(1000);
        state = !state;
    }
}
