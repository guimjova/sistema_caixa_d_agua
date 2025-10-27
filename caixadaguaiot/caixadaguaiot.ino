#define led_vd 4
#define led_a 5
#define led_vm 6
#define btn 7
#define trig 8
#define echo 9
float distancia = 0;
float ultima_distancia = 0;
float diferenca = distancia - ultima_distancia;
unsigned long ultima_leitura = 0;
unsigned long delay_millis = 5000;
int contador = 0;
bool estado_btn = false;

void setup() {
  Serial.begin(9600);
  pinMode(btn, INPUT_PULLUP);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(led_vd, OUTPUT);
  pinMode(led_a, OUTPUT);
  pinMode(led_vm, OUTPUT);

}

void loop() {
  unsigned long tempo_atual = millis();
  selo_btn();
  while (estado_btn == true){
    if (tempo_atual - ultima_leitura >= delay_millis){
      ultima_leitura = tempo_atual;
      if (contador > 0){
        distancia = medida();
        ultima_distancia = distancia;
        contador = contador + 1;
        if (ultima_distancia > (distancia +5) && ultima_distancia > (distancia -5)){
          Serial.print(distancia);
          Serial.println("cm");
          }
        if (distancia > 30){
          leds(1, 0, 0);
          }else if (distancia >= 15 && distancia < 30){
            leds(0, 1, 0);
            }else if (distancia < 15){
              leds(0, 0, 1);
              }
        }else{
          distancia = medida();
          Serial.print(distancia);
          Serial.println("cm");
          ultima_distancia = distancia;
          contador = contador + 1;
          if (distancia > 30){
          leds(1, 0, 0);
          }else if (distancia >= 15 && distancia < 30){
            leds(0, 1, 0);
            }else if (distancia < 15){
              leds(0, 0, 1);
              }
          }
      }
  
  }leds(0, 0, 0);

}

float medida() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long duracao = pulseIn(echo, HIGH);
  float distancia_cm = (duracao * 0.0343) / 2;
  return distancia_cm;

}

void leds(int estado1, int estado2, int estado3){
  digitalWrite(led_vd, estado1);
  digitalWrite(led_a, estado2);
  digitalWrite(led_vm, estado3);

}

bool selo_btn(){
  int pulso = 0;
  if(digitalRead(btn) == 0 && pulso%2 == 0){
    estado_btn = true;
    pulso = pulso + 1;
  }else if (digitalRead(btn) == 0 && pulso%2 != 0){
    estado_btn = false;
    pulso = pulso + 1;
  }
  return estado_btn;

}
