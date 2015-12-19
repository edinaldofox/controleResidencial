//Constantes associadas aos pinos do arduino
int const clock = 2; //ligado ao clock do 74HC595
int const latch = 3; //ligado ao latch do 74HC595
int const data = 4;
int myLeds[] = {0,0,0,0,0,0,0,0};
const int botao = 5;
byte leds = 0;



int contador = 0;
int botaoPessionado = 0;
int botaoPessionadoAtual = 0;
int estadoBotaoPressionado = 0;
int ultimoEstado = 0;

void setup() {
  Serial.begin(57600);
  pinMode(clock,OUTPUT);
  pinMode(latch,OUTPUT);
  pinMode(data,OUTPUT);
}

void loop() {
  leds = 0;

  botaoDigital();
  updateShiftRegister();
  
  for (int i = 0; i < 8 ;i++) {
    if(getPosicaoValida(i)) {
      bitSet(leds, i);
    }
    updateShiftRegister();
  }
}

int getPosicaoValida(int posicao)
{
  verificaEstadoDispositivo();
  return myLeds[posicao];
}

void verificaEstadoDispositivo()
{
  myLeds[botaoPessionadoAtual] = estadoBotaoPressionado;
}

void botaoDigital()
{
  botaoPessionado = digitalRead(botao);
  if (botaoPessionado != ultimoEstado) {
    ultimoEstado = ultimoEstado ? 0 : 1;
    if(ultimoEstado){
      estadoBotaoPressionado = estadoBotaoPressionado  ? 0 : 1;
      botaoPessionadoAtual = botaoPessionado;
    }
  }
}

void updateShiftRegister()
{
  digitalWrite(latch, LOW);
  shiftOut(data, clock, LSBFIRST, leds);
  digitalWrite(latch, HIGH);
}

