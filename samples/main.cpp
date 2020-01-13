#include "BrainPad.h"

BrainPad bp;
uint8_t buf_bytes[] = {0x88, 0x8E, 0xE8, 0xEE};
uint8_t txBuffer[8*3*4 + 1];
uint32_t txSize = 8*3*4 + 1;

void show(int id, uint8_t red, uint8_t green, uint8_t blue, ZSPI &led) {

    if (id < 8) {
        uint8_t mask = 0x03;
        int index = id * 12;
        txBuffer[index] = buf_bytes[green >> 6 & mask];
        txBuffer[index + 1] = buf_bytes[green >> 4 & mask];
        txBuffer[index + 2] = buf_bytes[green >> 2 & mask];
        txBuffer[index + 3] = buf_bytes[green & mask];

        txBuffer[index + 4] = buf_bytes[red >> 6 & mask];
        txBuffer[index + 5] = buf_bytes[red >> 4 & mask];
        txBuffer[index + 6] = buf_bytes[red >> 2 & mask];
        txBuffer[index + 7] = buf_bytes[red & mask];

        txBuffer[index + 8] = buf_bytes[blue >> 6 & mask];
        txBuffer[index + 9] = buf_bytes[blue >> 4 & mask];
        txBuffer[index + 10] = buf_bytes[blue >> 2 & mask];
        txBuffer[index + 11] = buf_bytes[blue & mask];
    }

    led.transfer(txBuffer, txSize, NULL, 0);
}

int main()
{
    bp.init();

    int state = 0;
    memset(txBuffer, 0x88, txSize - 1);

    codal::Pin led_mosi(ID_PIN_BUTTON_LEFT, PB_8, PIN_CAPABILITY_DIGITAL);
    codal::Pin *led_miso = NULL;
    codal::Pin *led_sclk = NULL;
    ZSPI led(led_mosi, *led_miso, *led_sclk);
    led.setFrequency(3200000);
    show(1, 255, 0, 0, led);

    while(1)
    {
        led->transfer(ZERO_FRAME, sizeof(ZERO_FRAME), NULL, 0);
        bp.io.ledRed.setDigitalValue(state);
        fiber_sleep(1000);
        state = !state;
    }
}
