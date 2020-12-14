byte trig1 = 13;
byte echo1 = 12;
byte trig2 = 11;
byte echo2 = 10;
byte trig3 = 9;
byte echo3 = 8;


byte disc1 = 3;
byte disc2 = 6;
byte disc3 = 5;

int num_rand;
bool state;
float cm1, cm2, cm3, duration, distance;


unsigned long millisTask1 = millis();
unsigned long millisTask2 = millis();
unsigned long millisTask3 = millis();

void setup(){
  
  randomSeed(analogRead(0));
  
  pinMode(trig1, OUTPUT);
  pinMode(trig2, OUTPUT);
  pinMode(trig3, OUTPUT);
  
  pinMode(echo1, INPUT);
  pinMode(echo2, INPUT);
  pinMode(echo3, INPUT);
  
  pinMode(disc1, OUTPUT);
  pinMode(disc2, OUTPUT);
  pinMode(disc3, OUTPUT);
  
  Serial.begin(9600);
  
}

void loop(){

  if(state==false){
    num_rand = random(1, 4);
    state=true;
  }
  
  cm1 =  get_distance(trig1, echo1);
  cm2 =  get_distance(trig2, echo2);
  cm3 =  get_distance(trig3, echo3);
  
  Serial.print("Disco: ");
  Serial.print(num_rand);
  Serial.print(" - Sensor 1: ");
  Serial.print(cm1);
  Serial.print("cm");
  Serial.print(" - Sensor 2: ");
  Serial.print(cm2);
  Serial.print("cm");
  Serial.print(" - Sensor 3: ");
  Serial.print(cm3);
  Serial.println("cm");
 
  if(num_rand == 1 && (millis() - millisTask1) < 3000.0){
    red();
    if(cm1 <= 20){
      Serial.println("Entrou 1A");
      apaga();
      num_rand = random(1, 4); 
      reset();
 	}
  }else{
  	if(num_rand == 1 && (millis() - millisTask1) >= 3000.0){
      Serial.println("Entrou 1B");
      apaga();
      num_rand = random(1, 4); 
      reset();
  	}
  }
  
  
  if(num_rand == 2 && (millis() - millisTask2) < 3000.0){
    green();
    if(cm2 <= 20){
      	Serial.println("Entrou 2A");
    	apaga();
    	num_rand = random(1, 4);
      	reset();
 	}
  }else{
     if(num_rand == 2 && ((millis() - millisTask2) >= 3000.0)){
      	Serial.println("Entrou 2B");
    	apaga();
    	num_rand = random(1, 4);
      	reset();
  	}
  }
  

  if(num_rand == 3 &&(millis() - millisTask3) < 3000.0){
    blue();
    if(cm3 <= 20){
       	Serial.println("Entrou 3A");
        apaga();
    	num_rand = random(1, 4); 
       	reset();
  	}
  }else{
    if(num_rand == 3 && ((millis() - millisTask3) >= 3000.0)){
       	Serial.println("Entrou 3B");
        apaga();
    	num_rand = random(1, 4); 
       	reset();
 	}
  }
}


void red(){
    digitalWrite(disc1, 1);
    digitalWrite(disc2, 0);
    digitalWrite(disc3, 0);
}

void green(){
    digitalWrite(disc1, 0);
    digitalWrite(disc2, 1);
    digitalWrite(disc3, 0);
}  

void blue(){
    digitalWrite(disc1, 0);
    digitalWrite(disc2, 0);
    digitalWrite(disc3, 1);
}  

void apaga(){
    digitalWrite(disc1, 0);
    digitalWrite(disc2, 0);
    digitalWrite(disc3, 0);
} 

float get_distance(byte pinTransmitter, byte pinReceiver){   
  
  digitalWrite(pinTransmitter,0);
  delayMicroseconds(2);       
  
  digitalWrite(pinTransmitter,1);   
  delayMicroseconds(10);   
  digitalWrite(pinTransmitter,0); 
  
  distance=pulseIn(pinReceiver,1);    
  distance = distance/58;

  return distance;  
}

void reset(){
	millisTask1 = millis();
	millisTask2 = millis();
	millisTask3 = millis();
}
