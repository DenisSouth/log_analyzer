#include <MsTimer2.h>

volatile unsigned long   oldTime = micros();
volatile unsigned long  synch_oldTime = micros();
volatile unsigned long  currentTime = micros();
volatile unsigned long  synch_currentTime = micros();

const int datalen = 150;
volatile  unsigned long data[datalen] = {};
volatile int counter = 0;


volatile  unsigned long synch_data[datalen] = {};
volatile int synch_counter = 0;


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

  if (isnone(synch_data)) {
    for (int i = 0; i < datalen; i++) {
      Serial.print(synch_data[i]);
      Serial.print(":");
    }
    Serial.println();
    Serial.println();
    Serial.println();
  }
  memset(synch_data, 0, sizeof(synch_data)); //очистить вывод
  synch_counter = 0; //очистить счетчик
  
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

void by_synch_interrupt() {
   noInterrupts(); //отключить прерывания
  if (synch_counter < datalen) {
    synch_currentTime = micros(); //мс от вызова
    synch_data[synch_counter] = synch_currentTime - synch_oldTime; //добавить в массив (старое время минус текущее)  
    synch_data[synch_counter+1] = digitalRead(3);
    synch_counter = synch_counter + 2;
    synch_oldTime = synch_currentTime; //обовить минус текущее время
    interrupts(); //включить прерывания
    MsTimer2::start(); //если после последнего вызова прошло н секунд - вызовится by_timer()
  }
}


void setup() {
  Serial.begin(115200);
  MsTimer2::set(1000, by_timer);
  MsTimer2::start();
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  attachInterrupt(0, by_interrupt, CHANGE); //CHANGE FALLING
  attachInterrupt(1, by_synch_interrupt, CHANGE); //CHANGE FALLING
}

void loop() {
}
