#define FREQ_ENVOI 2000
#include <lmic.h>
#include <hal/hal.h>
#include <SPI.h>

static const u1_t PROGMEM APPEUI[8] = {0x91, 0xB8, 0x43, 0xD0, 0x7E, 0xD5, 0xB3, 0x70};
void os_getArtEui (u1_t* buf) { memcpy_P(buf, APPEUI, 8);}
static const u1_t PROGMEM DEVEUI[8]={0x7C, 0x91, 0x04, 0xD0, 0x7E, 0xD5, 0xB3, 0x70};
void os_getDevEui (u1_t* buf) { memcpy_P(buf, DEVEUI, 8);}
static const u1_t PROGMEM APPKEY[16] = { 0x54, 0x6C, 0x4B, 0x03, 0xA2, 0x25, 0x45, 0x9B, 0x25, 0x12, 0xD4, 0xB0, 0x25, 0xD6, 0x34, 0xC1};
void os_getDevKey (u1_t* buf) {  memcpy_P(buf, APPKEY, 16);}
unsigned char loraData[3];
static osjob_t sendjob;
const unsigned TX_INTERVAL = 30;
const lmic_pinmap lmic_pins = {
    .nss = 8,
    .rxtx = LMIC_UNUSED_PIN,
    .rst = 4,
    .dio = {3, 6, LMIC_UNUSED_PIN},
    .rxtx_rx_active = 0,
    .rssi_cal = 8,              
    .spi_freq = 8000000,
};

bool LoraWanConnected = false;
bool DoorState;     // 0 = fermé, 1 = ouvert
int initialChickenNbr = 10;
int ChickenNbr;
uint32_t light;

int t_Time;

void setup() {
  delay(2000);
  Serial.begin(9600);
  setup_HCSR04();
  setup_LuxSensor();  
  setup_LoraWan();

  t_Time = millis();
}

void loop() {
  if (LoraWanConnected){
    light = getLight();
    Chicken_action();
  
    // nuit en dessous de 50 lux
    if (light >= 50 && ChickenNbr == initialChickenNbr){
      // portes fermées
      DoorState = 0;
    }
    else {
      // portes ouvertes
      DoorState = 1;
    }
  
    int current_time = millis();
    if (current_time >= t_Time + FREQ_ENVOI){
      Serial.print("light        | ");
      Serial.println(light);
      Serial.print("Chicken Nbr  | ");
      Serial.println(ChickenNbr);
      // send LoraWan
      os_runloop_once();
      // reset
      t_Time = millis();
    }
  }
}


void SendData(void){
  // send data with LorA
  
}
