#define RX_PIN 2
#define LED_PIN 13

volatile uint32_t t0;
volatile uint8_t ledState=0;
volatile uint8_t rxPackets=0;

#define PACKET_N 40
volatile uint8_t packet[PACKET_N];
volatile uint8_t pulseCounter=0;

enum decoderState_t
{
  DECODER_IDLE=0,
  DECODER_PAYLOAD_PRE,
  DECODER_PAYLOAD_BIT,
};

enum pulseType_t
{
  PULSE_NONE=0,
  PULSE_RESET,
  PULSE_SHORT,
  PULSE_0,
  PULSE_1,
};

volatile decoderState_t decoderState=DECODER_IDLE;

//#define BIT_0 480, 975
//#define BIT_1 480, 1979
//uint16_t preamble[]={480, 480, 480, 480, 480, 9166, 0};
//uint16_t packet[]={  BIT_0,
//                     BIT_1,
//                     BIT_0,
//                     BIT_0,
//                     BIT_1,
//                     BIT_1,
//                     BIT_0,
//                     BIT_0,
//                     BIT_1,
//                     BIT_0,
//                     BIT_0,
//                     BIT_0,
//                     BIT_0,
//                     BIT_0,
//                     BIT_0,
//                     BIT_0,
//                     BIT_1,
//                     BIT_1,
//                     BIT_0,
//                     BIT_1,
//                     BIT_0,
//                     BIT_0,
//                     BIT_1,
//                     BIT_1,
//                     BIT_1,
//                     BIT_1,
//                     BIT_1,
//                     BIT_1,
//                     BIT_0,
//                     BIT_0,
//                     BIT_0,
//                     BIT_0,
//                     BIT_0,
//                     BIT_0,
//                     BIT_0,
//                     BIT_0,
//                     BIT_0,
//                     0};

void blink()
{
  ledState=1-ledState;
  pulseCounter=0;
  digitalWrite(LED_PIN, ledState);
}

void pinChange()
{
  uint8_t pulseLevel=digitalRead(RX_PIN);
  uint32_t tNow=micros();
	uint32_t pulseLength=tNow-t0;
  pulseType_t pulseType;
  decoderState_t newDecoderState;

  if ((pulseLevel==0) && (pulseLength>400) && (pulseLength<560))
  {
    pulseType=PULSE_SHORT;
  }
  else if ((pulseLevel==1) && (pulseLength>875) && (pulseLength<1075))
  {
    pulseType=PULSE_0;
  }
  else if ((pulseLevel==1) && (pulseLength>1879) && (pulseLength<2079))
  {
    pulseType=PULSE_1;
  }
  else if ((pulseLevel==1) && (pulseLength>2500) && (pulseLength<15000))
  {
    pulseType=PULSE_RESET;
  }
  else
  {
    pulseType=PULSE_NONE;
  }

  newDecoderState=decoderState;
  if (pulseType==PULSE_RESET)
  {
    if (pulseCounter>30)
    {
      blink();
      rxPackets++;
    }
    newDecoderState=DECODER_PAYLOAD_PRE;
    pulseCounter=0;
  }
  if (decoderState==DECODER_PAYLOAD_PRE)
  {
    if (pulseType==PULSE_SHORT)
    {
      newDecoderState=DECODER_PAYLOAD_BIT;
    }
    else
    {
      pulseCounter=0;
      newDecoderState=DECODER_IDLE;
    }
  }
  if (decoderState==DECODER_PAYLOAD_BIT)
  {
    if (pulseType==PULSE_0 || pulseType==PULSE_1)
    {
      if (pulseCounter<PACKET_N)
      {
        packet[pulseCounter]=(pulseType==PULSE_1)?1:0;
        pulseCounter++;
      }
      newDecoderState=DECODER_PAYLOAD_PRE;
    }
    else
    {
      pulseCounter=0;
      newDecoderState=DECODER_IDLE;
    }
  }
  decoderState=newDecoderState;

  t0=tNow;
}

void setup()
{
  Serial.begin(9600);
	pinMode(RX_PIN, INPUT);
	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, 0);
  t0=micros();
  attachInterrupt(digitalPinToInterrupt(RX_PIN), pinChange, CHANGE);
}

void sendPulse(uint8_t hl, uint16_t t)
{
//  digitalWrite(TX_PIN, hl);
//  delayMicroseconds(t-(micros()-t0));
}

void loop()
{
  uint8_t i;

  delay(100);
  if (rxPackets)
  {
    Serial.print("(");
    Serial.print(rxPackets);
    rxPackets=0;
    Serial.print(") ");
    for (i=0; i<30; i++)
    {
      Serial.print(packet[i]);
    }
    Serial.print("\n");
  }
}
