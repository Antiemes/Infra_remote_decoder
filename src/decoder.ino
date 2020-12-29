#define RX_PIN 2

void pinChange()
{
	static volatile uint32_t t0=0;
  uint8_t pulseLevel=digitalRead(RX_PIN);
  uint32_t tNow=micros();
	uint32_t pulseLength=tNow-t0;
	t0=tNow;
  Serial.print(pulseLength);
  Serial.print(" ");
  Serial.print(pulseLevel);
  Serial.print("\n");
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
