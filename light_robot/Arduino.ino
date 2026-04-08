
#include <Servo.h>

Servo s1;
Servo s2;

int micPin = 2;
int clapCount = 0;
unsigned long lastClapTime = 0;
unsigned long detectionWindow = 600; // დრო (მილიწამებში) მეორე ტაშის დასალოდებლად

void setup() {
  pinMode(micPin, INPUT);
  s1.attach(9);
  s2.attach(10);
  
  s1.write(0);
  s2.write(0);
  Serial.begin(9600); // სერიალ მონიტორი რომ ვნახოთ რა ხდება
}

void loop() {
  int sensorState = digitalRead(micPin);

  // 1. ტაშის დაფიქსირება და დათვლა
  if (sensorState == HIGH) {
    unsigned long currentTime = millis();
    // debounce: რომ ერთი ტაში რამდენჯერმე არ დათვალოს (0.2 წამიანი პაუზა)
    if (currentTime - lastClapTime > 200) {
      clapCount++;
      lastClapTime = currentTime;
      Serial.print("Tashi daitvala: ");
      Serial.println(clapCount);
    }
  }

  // 2. გადაწყვეტილების მიღება (როცა ტაშის მერე 0.6 წამი სიჩუმეა)
  if (clapCount > 0 && (millis() - lastClapTime > detectionWindow)) {
    
    if (clapCount == 1) {
      // მოქმედება 1 ტაშზე
      s1.write(80);
      delay(1000);
      s1.write(0);
    } 
    else if (clapCount == 2) {
      // მოქმედება 2 ტაშზე
      // s1.write(45);
      s2.write(80);
      delay(1000);
      // s1.write(0);
      s2.write(0);
    }
    
    // დათვლის განულება შემდეგი მცდელობისთვის
    clapCount = 0; 
  }
}