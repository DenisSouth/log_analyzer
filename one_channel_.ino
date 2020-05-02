#include <MsTimer2.h>

volatile unsigned long  oldTime = micros();
volatile unsigned long  currentTime = micros();

const int datalen = 150;
volatile  unsigned long data[datalen] = {};
volatile int counter = 0;


//есть ли что то кроме нулей?
boolean isnone(unsigned long  thedata[datalen]) {
  noInterrupts(); //отключить прерывания
  for (int i = 0; i < datalen; i++) {
    if (thedata[i] > 0) {
        interrupts(); //включить прерывания
      return true;
    }
  }
    interrupts(); //включить прерывания
  return false;
  
}


void by_timer() {
  noInterrupts(); //отключить прерывания
  
  if (isnone(data)) {
    for (int i = 0; i < datalen; i++) {
      Serial.print(data[i]);
      Serial.print(":");
    }
    Serial.println();
  }
  memset(data, 0, sizeof(data)); //очистить вывод
  counter = 0; //очистить счетчик  
  interrupts(); //включить прерывания
}

void by_interrupt() {
   noInterrupts(); //отключить прерывания
  if (counter < datalen) {
    currentTime = micros(); //мс от вызова
    data[counter] = currentTime - oldTime; //добавить в массив (старое время минус текущее)  
    data[counter+1] = digitalRead(2);
    counter = counter + 2;
    oldTime = currentTime; //обовить минус текущее время
    interrupts(); //включить прерывания
    MsTimer2::start(); //если после последнего вызова прошло н секунд - вызовится by_timer()
  }
}


void setup() {
  Serial.begin(115200);
  MsTimer2::set(1000, by_timer);
  MsTimer2::start();
//  pinMode(2, INPUT_PULLUP); //если нет поддтяжки к +5, надо через 10к-100к притянуть пин 2 к земле
  attachInterrupt(0, by_interrupt, CHANGE); //CHANGE FALLING

}

void loop() {
}
