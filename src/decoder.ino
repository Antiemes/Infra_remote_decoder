#define IR_PIN 2
#define N_OF_BUTTONS 21

uint32_t code = 0;
uint16_t remoteCodes[] =
{0b1010001001011101, 0b0110001010011101, 0b1110001000011101,
0b0010001011011101, 0b0000001011111101, 0b1100001000111101,
0b1110000000011111, 0b1010100001010111, 0b1001000001101111,
0b0110100010010111, 0b1001100001100111, 0b1011000001001111,
0b0011000011001111, 0b0001100011100111, 0b0111101010000101,
0b0001000011101111, 0b0011100011000111, 0b0101101010100101,
0b0100001010111101, 0b0100101010110101, 0b0101001010101101};
uint16_t detected = 0;



void pinChange()
{
    static volatile uint32_t t0 = 0;
    uint8_t pulseLevel = digitalRead(IR_PIN);
    uint32_t tNow = micros();
    uint32_t pulseLength = tNow - t0;
    t0 = tNow;
    if (pulseLevel == 0)
    {
        if (pulseLength > 300 && pulseLength < 600)
//        if (pulseLength > 700 && pulseLength < 1200) //szurke
        {
            code = code << 1;
//            Serial.print("0");
		}
        else if (pulseLength > 1200 && pulseLength < 2000)
//        else if (pulseLength > 1600 && pulseLength < 2000) //szurke
        {
            code = (code << 1) + 1;
//            Serial.print("1");
        }
        else
        {
//            Serial.println(code, HEX);
            detected = code & 0xFFFF;
            code = 0;
        }
    }
    else
    {
        if (pulseLength > 500 && pulseLength < 800)
//        if (pulseLength > 700 && pulseLength < 1200) //szurke
        {
//            Serial.print("1");
            //Serial.print("Ry ");
            //Serial.println(pulseLength);
        }
        /*
        else if (pulseLength > 1600 && pulseLength < 2000) //szurke
        {
            Serial.print("11");
        }*/
    }

}

void setup()
{
    Serial.begin(115200);
    pinMode(IR_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(IR_PIN), pinChange, CHANGE);
}

void loop()
{
    for (int i = 0; i < N_OF_BUTTONS; i++)
    {
        if (detected == remoteCodes[i])
        {
            Serial.println(i);
            detected = 0;
        }
    }
}
