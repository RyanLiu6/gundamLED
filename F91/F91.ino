#include <IRremote.h>

#define RED_LED 11
#define GREEN_LED 10
#define BLUE_LED 9
#define RECV_PIN 3

/* 1- Red
 * 2. Green
 * 3. Blue
 * 4. Cyan
 * 5. Magenta
 * 6. Yellow
 * 7. Raspberry
 * 8. White
 * 9. Cycle all colours with 1 second in between
 * OK: Off
 */
#define IR_1 0xFFA25D
#define IR_2 0xFF629D
#define IR_3 0xFFE21D
#define IR_4 0xFF22DD
#define IR_5 0xFF02FD
#define IR_6 0xFFC23D
#define IR_7 0xFFE01F
#define IR_8 0xFFA857
#define IR_9 0xFF906F
#define IR_OK 0xFF38C7

IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;

void setup() {
    pinMode(RED_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(BLUE_LED, OUTPUT);

    irrecv.enableIRIn();
    irrecv.blink13(true);
}

void loop() {
    if (irrecv.decode(&results)){
        if (results.value == 0XFFFFFFFF)
            results.value = key_value;

        switch(results.value) {
            case IR_1:
                setRGB(255, 0, 0); // Red
                break;
            case IR_2:
                setRGB(0, 255, 0); // Green
                break;
            case IR_3:
                setRGB(0, 0, 255); // Blue
                break;
            case IR_4:
                setRGB(0, 255, 255); // Cyan
                break;
            case IR_5:
                setRGB(255, 0, 255); // Magenta
                break;
            case IR_6:
                setRGB(255, 255, 0); // Yellow
                break;
            case IR_7:
                setRGB(255, 255, 125); // Raspberry
                break;
            case IR_8:
                setRGB(255, 255, 255); // White
                break;
            case IR_9:
                cycleColours(1000);
                break;
            case IR_OK:
            default:
                setRGB(0, 0, 0); // Black
                break;
        }

        key_value = results.value;
        irrecv.resume();
    }
}

void setRGB(int red, int green, int blue)
 {
     analogWrite(RED_LED, red);
     analogWrite(GREEN_LED, green);
     analogWrite(BLUE_LED, blue);
}

void cycleColours(int delayTime)
{
    for (int i = 0; i < 10; i++)
    {
        setRGB(0, 0, 0); // Black

        delay(delayTime);

        setRGB(255, 0, 0); // Red

        delay(delayTime);

        setRGB(0, 255, 0); // Green

        delay(delayTime);

        setRGB(0, 0, 255); // Blue

        delay(delayTime);

        setRGB(0, 255, 255); // Cyan

        delay(delayTime);

        setRGB(255, 0, 255); // Magenta

        delay(delayTime);

        setRGB(255, 255, 0); // Yellow

        delay(delayTime);

        setRGB(255, 255, 125); // Raspberry

        delay(delayTime);

        setRGB(255, 255, 255); // White
    }
}
