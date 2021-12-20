// sound speed in cm/µs
#define SOUND_SPEED 0.034

const int trigPin_Front = 10;
const int echoPin_Front = 11;

const int trigPin_Rear = 12;
const int echoPin_Rear = 13;

int Direction;

float DoorWidth = 30;

bool Front;
bool Rear;
bool key_Front = false;
bool key_Rear = false;

unsigned long delaytime = 200;
unsigned long current_time = millis();
unsigned long time_Front;
unsigned long time_Rear;

void setup_HCSR04(void){
  pinMode(trigPin_Front, OUTPUT);
  pinMode(echoPin_Front, INPUT);

  pinMode(trigPin_Rear, OUTPUT);
  pinMode(echoPin_Rear, INPUT);
}

float getDistance_Front(void){
  // clear trigPin
  digitalWrite(trigPin_Front, LOW);
  delayMicroseconds(2);
  
  // Set trigPin HIGH for 10µs
  digitalWrite(trigPin_Front, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_Front, LOW);

  // Read echoPin and calculate distance
  long duration_Front = pulseIn(echoPin_Front, HIGH);
  float distance_Front = duration_Front * SOUND_SPEED / 2;
  return distance_Front;
}

float getDistance_Rear(void){
  // clear trigPin
  digitalWrite(trigPin_Rear, LOW);
  delayMicroseconds(2);
  
  // Set trigPin HIGH for 10µs
  digitalWrite(trigPin_Rear, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_Rear, LOW);

  // Read echoPin and calculate distance
  long duration_Rear = pulseIn(echoPin_Rear, HIGH);
  float distance_Rear = duration_Rear * SOUND_SPEED / 2;
  return distance_Rear;
}

void Chicken_action(void){
  /*
  Serial.println(getDistance_Front());
  Serial.println(getDistance_Rear());
  */
  if((getDistance_Front() < (DoorWidth - 5)) && (getDistance_Front() > 2) &&(key_Front == false)){
    Serial.println("poule devant capteur Front");
    time_Front = millis();
    Front = true;
    key_Front = true;
  }

  if((getDistance_Rear() < (DoorWidth - 5)) && (getDistance_Rear() > 2) &&(key_Rear == false)){
    Serial.println("poule devant capteur Rear");    
    time_Rear = millis();
    Rear = true;
    key_Rear = true;
  }

  if((Front == true) && (Rear == true)){
    Direction = time_Front - time_Rear;
    if (Direction < 0){
      // Poule Entre
      ChickenNbr += 1;
      Serial.println("One more chicken");
      os_runloop_once();
    }
     if (Direction > 0){
      // Poule Sort
      ChickenNbr -= 1;
      Serial.println("One less chicken");
      os_runloop_once();
    }
    SendData = true;
    
    Front = false;
    key_Front = false;
    Rear = false;
    key_Rear = false;
  }  
}
