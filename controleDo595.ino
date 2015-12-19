//Constantes associadas aos pinos do arduino
int const clock = 2; //ligado ao clock do 74HC595
int const latch = 3; //ligado ao latch do 74HC595
int const data = 4;
int myButtons[] = {0,0,0,0,0,0,0,0};
// deve ser igual ao numero de myButtons
int registros = 8;
const int botao = A5;
byte leds = 0;

int contador = 0;
int botaoPressionado = 0;
int botaoPressionadoAtual = 900;
int estadoBotaoPressionado = 0;
int cacheBotaoPressionado = 0;

void setup() {
  pinMode(clock,OUTPUT);
  pinMode(latch,OUTPUT);
  pinMode(data,OUTPUT);
}

void loop() {
  leds = 0;

  botaoDigital();
  updateShiftRegister();
  
  for (int i = 0; i < registros ;i++) {
    if(myButtons[i]) {
      bitSet(leds, i);
    }
    updateShiftRegister();
  }
}

void botaoDigital()
{
  botaoPressionado = eventButton();

  if (botaoPressionadoAtual != cacheBotaoPressionado && botaoPressionado != 900) {
    int posicaoBotao = (botaoPressionado-1);
      myButtons[posicaoBotao] = myButtons[posicaoBotao] ? 0 : 1;
      botaoPressionadoAtual = botaoPressionado;
      cacheBotaoPressionado = 0;
      for (int k = 0; k < 8 ;k++) {
      }
  } else {
      botaoPressionado = 900;
      cacheBotaoPressionado = 0;
  }
delay(300);
  
}

void updateShiftRegister()
{
  digitalWrite(latch, LOW);
  shiftOut(data, clock, LSBFIRST, leds);
  digitalWrite(latch, HIGH);
}

int eventButton()
{
  float clickButton = analogRead(botao);

  if (clickButton > 300 & clickButton < 400) {
    return 1;
  } else if (clickButton > 400 & clickButton < 600) {
    return 2;
  } else if (clickButton > 600 & clickButton < 700) {
    return 3;
  } else if (clickButton > 680 & clickButton < 800) {
    return 4;
  }

  return 900;
}

