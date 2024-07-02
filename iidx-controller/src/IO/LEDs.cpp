#include <stdint.h>

#include <Arduino.h>
#include <FastLED.h>

#include "../Configuration.h"

#include "Encoder.h"
#include "LEDs.h"

CRGB leds[TOTAL_LED_COUNT];

DEFINE_GRADIENT_PALETTE(Spectral_11_gp){
    0, 73, 1, 8,
    23, 73, 1, 8,
    23, 159, 11, 13,
    46, 159, 11, 13,
    46, 227, 39, 9,
    69, 227, 39, 9,
    69, 249, 109, 22,
    92, 249, 109, 22,
    92, 252, 191, 55,
    115, 252, 191, 55,
    115, 255, 255, 123,
    139, 255, 255, 123,
    139, 194, 233, 69,
    162, 194, 233, 69,
    162, 90, 186, 84,
    185, 90, 186, 84,
    185, 23, 139, 85,
    208, 23, 139, 85,
    208, 3, 63, 120,
    231, 3, 63, 120,
    231, 19, 19, 82,
    255, 19, 19, 82};

CRGBPalette16 colorPalette = Spectral_11_gp;

uint8_t turntableBrightness = 200;

void initialise_leds()
{
    FastLED.addLeds<WS2812B, FASTLED_PIN, GRB>(leds, TOTAL_LED_COUNT); // GRB ordering is typical
}

void write_leds(uint16_t led_status, bool flipped)
{
    if (flipped)
    {
        led_status = led_status << (16 - BUTTON_COUNT);

        // thanks http://graphics.stanford.edu/~seander/bithacks.html#ReverseByteWith32Bits
        // flip first half of led_status
        uint8_t a = led_status >> 8;
        a = ((a * 0x0802LU & 0x22110LU) | (a * 0x8020LU & 0x88440LU)) * 0x10101LU >> 16;

        // flip second half of led_status
        uint8_t b = led_status & 0x00FF;
        b = ((b * 0x0802LU & 0x22110LU) | (b * 0x8020LU & 0x88440LU)) * 0x10101LU >> 16;

        // combine part a and b back into a 16-bit number, but flipped, to complete the reversal of led_status
        led_status = (b << 8) | a;
    }

    int encoderValue = get_encoder_virtual_state();

    // handle the leds for the buttons
    for (int i = 0; i < BUTTON_COUNT; i++)
    {
        bool ledStatus = ((led_status >> i) & 1);
        if (ledStatus)
        {
            leds[i] = ColorFromPalette(colorPalette, encoderValue + (i * 255 / (TOTAL_LED_COUNT - BUTTON_COUNT)));
        }
        else
        {
            // turn leds slowly to black instead of turning them off instantly
            leds[i].fadeToBlackBy(25);
        }
    }

    // handle the leds for the turntable
    int ledPosition = map(encoderValue, 0, 255, 0, (TOTAL_LED_COUNT - BUTTON_COUNT) - 1);

    for (int i = BUTTON_COUNT; i < TOTAL_LED_COUNT; i++)
    {
        leds[i] = ColorFromPalette(colorPalette, encoderValue + (i * 255 / (TOTAL_LED_COUNT - BUTTON_COUNT) / 8), turntableBrightness);
    }

    FastLED.show();
}