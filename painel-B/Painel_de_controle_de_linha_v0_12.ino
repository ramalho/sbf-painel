/*
circuito de proteção e habilitação de linha para painel de controle v 0.12
Ernesto schwarz junior
07/11/2025
obs.: usado nos paineis da sbf com acionamento da fonte na chave rotativa
*/

int buzzer = 13;
int sensorldr = A0;
int ledcurto = 12;
int entradarele1 = A1; // liga desliga
int rele1 = 11;
int ledchavevm = 2;
int ledchavevd = 3;
int entradarele2 = A2;
int rele2 = 9;

bool ledpisca();
bool Buzzer();
bool Habilita();
bool Reversao();

void setup() {
    pinMode (buzzer, OUTPUT);
    pinMode (sensorldr, INPUT_PULLUP);
    pinMode (ledcurto, OUTPUT);
    pinMode (entradarele1, INPUT_PULLUP);
    pinMode (rele1, OUTPUT);
    pinMode (ledchavevm, OUTPUT);
    pinMode (ledchavevd, OUTPUT);
    pinMode (entradarele2, INPUT_PULLUP);
    pinMode (rele2, OUTPUT);
    digitalWrite(rele1, HIGH);
    digitalWrite(ledchavevm, LOW);
}

void loop() {
  if (Habilita()) {
    digitalWrite(ledchavevd, LOW);
    digitalWrite(rele1, HIGH);
  } else {
    Buzzer();
    digitalWrite(ledchavevd, HIGH);
    digitalWrite(rele1, LOW);
  }
  if (Reversao()) {
      digitalWrite(rele2, LOW);
    } else {
      digitalWrite(rele2, HIGH);
  }
}

bool ledpisca() {
  digitalWrite(ledchavevd, LOW);
  digitalWrite(ledchavevm, HIGH);
  //digitalWrite(ledcurto, HIGH);
  delay(100);
  digitalWrite(ledchavevd, LOW);
  digitalWrite(ledchavevm, LOW);
  //digitalWrite(ledcurto, LOW);
  delay(100);
}

bool Buzzer() {
  int leitura;
  int estado = 0;
  leitura = digitalRead(sensorldr);
  if (leitura != 1){
    ledpisca();
    tone(buzzer,900,170);
  } else {
    noTone(buzzer);
  }
}

bool Habilita() {
   #define tempoDebounce 100 //(tempo para eliminar o efeito Bounce EM MILISEGUNDOS)

   bool estadoBotao;
   static bool estadoBotaoAnt; 
   static bool estadoRet = true;
   static unsigned long delayBotao = 0;

   if ( (millis() - delayBotao) > tempoDebounce ) {
       estadoBotao = digitalRead(entradarele1);
       if ( estadoBotao && (estadoBotao != estadoBotaoAnt) ) {
          estadoRet = !estadoRet;
          delayBotao = millis();
       }
       estadoBotaoAnt = estadoBotao;
   }

   return estadoRet;
}
bool Reversao() {
   #define tempoDebounce 100 //(tempo para eliminar o efeito Bounce EM MILISEGUNDOS)

   bool estadoBotao;
   static bool estadoBotaoAnt; 
   static bool estadoRet = true;
   static unsigned long delayBotao = 0;

   if ( (millis() - delayBotao) > tempoDebounce ) {
       estadoBotao = digitalRead(entradarele2);
       if ( estadoBotao && (estadoBotao != estadoBotaoAnt) ) {
          estadoRet = !estadoRet;
          delayBotao = millis();
       }
       estadoBotaoAnt = estadoBotao;
   }

   return estadoRet;
}