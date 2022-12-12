
#include <VirtualWire.h>
#include <dht.h>

dht DHT;

#define pinIlum A15       //leitura iluminação
#define pinPressao A0    //sensor de pressão
#define pinTemp A14    //sensor de pressão

#define pinRF  12        //pino comunicação rf    
#define pinPort 4        //sensor de porta
#define DHT11_PIN 2      //pino para leitura de temperatura e humidade
#define pinSenPres 9    //sensor de presencia
#define pinLED 53   //led na placa

//tempo para calibrar o sensor pir (10-60 secs)
int calibraTemp = 30; 

//variaveis da função pricipal
int movv = 0;
int temp=0,umid=0;
int ilum=0,pres=0;
int port=0;
int tempa;

 //variaveis da função de presencia
  int mov=0;
  boolean estLow = true; 
  boolean tomarLowTempo = false; 
  long unsigned int lowIn;         
  # define pause 5000

//estrutura de dados que será enviada
struct tipoPacote {
  char start='i';
  int valor1=0;
  int valor2=0;
  int valor3=0;
  int valor4=0;
  int valor5=0;
  int valor6=0;
  char endd='f';
};
tipoPacote pacote; 

//função retorna 1 se tiver movimento na sala
int SEN_PRESENCIA(){
     if(digitalRead(pinSenPres) == LOW){
       if(estLow){  
         estLow = false; 
         mov=1;           
         delay(50);
         } 
       tomarLowTempo = true;        
      }
     if(digitalRead(pinSenPres) == HIGH){       
       if(tomarLowTempo){
        lowIn = millis();          
        tomarLowTempo = false;
          }        
         if(!estLow && millis() - lowIn > pause){  
           estLow = true;                        
           mov=0;
         }
       }
   return mov;    
  }

//função retorna a temperatura e a umidade
int TEMP_UMID()
{
  int chk = DHT.read11(DHT11_PIN);
  int temp = DHT.temperature;
  int umid = DHT.humidity;
  return temp,umid;
}

void setup() {
  //configurando rf
  vw_set_tx_pin(pinRF);
  vw_set_ptt_inverted(true);
  vw_setup(2000);

  //conf pinos
  pinMode(pinLED, OUTPUT);
  pinMode(pinSenPres, INPUT);
  pinMode(pinIlum, INPUT);

  //conf serial
  Serial.begin(9600);

  //calibrado o sensor de presencia
  Serial.print("Calibrando e estabilizando sensores");
    for(int i = 0; i < calibraTemp; i++){
      Serial.print(calibraTemp-i);
      Serial.println(" segundos de 30");
      delay(1000);
      }
    Serial.println("Processo terminado");
    Serial.println("SENSORES PRONTOS");
    delay(50);
}

void loop() {

  ilum = map(analogRead(pinIlum), 0, 1023, 0, 100);
  temp,umid = TEMP_UMID();
  movv = SEN_PRESENCIA();
  port = digitalRead(pinPort);
  pres = 99.7-(((analogRead(pinPressao)*0.0048828125)+0.01)*0.2-0.04)*777.725929382+2;
  tempa = analogRead(pinTemp)*0.1632-17.842;
 
  //atrivuindo os valores que serão enviados
  pacote.valor1 = movv;
  pacote.valor2 = tempa;
  pacote.valor3 = umid;
  pacote.valor4 = ilum;
  pacote.valor5 = port;
  pacote.valor6 = pres;

  Serial.print(pacote.start);
  Serial.print(" | ");
  Serial.print(pacote.valor1);
  Serial.print(" | ");
  Serial.print(pacote.valor2);
  Serial.print(" | ");
  Serial.print(pacote.valor3);
  Serial.print(" | ");
  Serial.print(pacote.valor4);
  Serial.print(" | ");
  Serial.print(pacote.valor5);
  Serial.print(" | ");
  Serial.print(pacote.valor6);
  Serial.print(" | ");
  Serial.println(pacote.endd);
  
  digitalWrite(pinLED, HIGH); //liga led da placa
  //função de envio por rf
  vw_send((uint8_t *)&pacote, sizeof(pacote));
  vw_wait_tx(); 
  digitalWrite(pinLED, LOW);   //desliga led da placa
  delay(50);
}
