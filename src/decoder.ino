#define RX_PIN 2

void pinChange()
{
    static volatile uint32_t t0=0;
    uint8_t pulseLevel=digitalRead(RX_PIN);
    uint32_t tNow=micros();
    uint32_t pulseLength=tNow-t0;
    t0=tNow;
    //Serial.print(pulseLength);
    //Serial.print(" ");
    //Serial.print(pulseLevel);
    //Serial.print("\n");
    if (pulseLevel==0)
    {
        if (pulseLength>300 && pulseLength<600)
//        if (pulseLength>700 && pulseLength<1200) //szurke
        {
            Serial.print("0");
		}
        else if (pulseLength>1200 && pulseLength<2000)
//        else if (pulseLength>1600 && pulseLength<2000) //szurke
        {
            Serial.print("1");
        }
        else
        {
//            Serial.print("Rx ");
//            Serial.println(pulseLength);
            Serial.print("\n");
        }
    }
    else
    {
        if (pulseLength>500 && pulseLength<800)
//        if (pulseLength>700 && pulseLength<1200) //szurke
        {
//            Serial.print("1");
            //Serial.print("Ry ");
            //Serial.println(pulseLength);
        }
        /*
        else if (pulseLength>1600 && pulseLength<2000) //szurke
        {
            Serial.print("11");
        }*/
        else
        {
//            Serial.print("Ry ");
//            Serial.println(pulseLength);
        }
    }

}

void setup()
{
    Serial.begin(115200);
    pinMode(RX_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(RX_PIN), pinChange, CHANGE);
}

void loop()
{
//  uint8_t i;
//  Serial.print("Foo\n");
//  delay(500);

  //delay(100);
  //if (rxPackets)
  //{
  //  Serial.print("(");
  //  Serial.print(rxPackets);
  //  rxPackets=0;
  //  Serial.print(") ");
  //  for (i=0; i<30; i++)
  //  {
  //    Serial.print(packet[i]);
  //  }
  //  Serial.print("\n");
  //}
}
