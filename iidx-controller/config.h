#ifndef _CONFIG_H_
#define _CONFIG_H_

// Pins where the buttons are connected to
static const uint8_t button_pins[] = {
    2,  // button 1
    4,  // button 2
    5,  // button 3
    6,  // button 4
    7,  // button 5
    8,  // button 6
    9,  // button 7
    10, // start
    14, // effect
    16  // vefx
};

#define TOTAL_LED_COUNT 50 // 10 button leds + 40 for the turntable
#define BUTTON_COUNT 10
#define FASTLED_PIN 3

// Pins where the encoder is connected to
#define ENCODER_PIN_A 18 // green wire (a phase)
#define ENCODER_PIN_B 19 // white wire (b phase)

/* OPTIONS */
// Your encoder pulses per rotation
#define ENCODER_PPR 600

// Spoof the konami premium controller (UM/Infinitas compatibility)
#define KONAMI_SPOOF 0

#if KONAMI_SPOOF == 0
#define VID 0x0001
#define PID 0x0001
// The manufacturer name of this controller (leave the L in front of the ")
#define MF_NAME L"Renard"
#define PROD_NAME L"IIDX Controller"
static const uint8_t encoder_pin0 = ENCODER_PIN_A;
static const uint8_t encoder_pin1 = ENCODER_PIN_B;
#else
#define VID 0x1ccf
#define PID 0x8048
#define MF_NAME L"Konami Amusement"
#define PROD_NAME L"beatmania IIDX controller premium model"
static const uint8_t encoder_pin0 = ENCODER_PIN_B;
static const uint8_t encoder_pin1 = ENCODER_PIN_A;
#endif

#endif
