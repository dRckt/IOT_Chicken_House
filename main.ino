#define FREQ_ENVOI 2000

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
