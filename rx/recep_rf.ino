#include <VirtualWire.h>
#include <LiquidCrystal.h>

#define pinRF  12 //pino comunicação rf
#define pinLEDboard 13   //led na placa

//pinos display
//LiquidCrystal lcd(11, 10, 5, 4, 3, 2);

//variaveis
char mov,port;

struct tipoPacoteRec {
  char start='w';
  int valor1=0;
  int valor2=0;
  int valor3=0;
  int valor4=0;
  int valor5=0;
  int valor6=0;
  char endd='w';
};
tipoPacoteRec pacote; 
uint8_t buf[sizeof(pacote)];
uint8_t buflen = sizeof(pacote);

void setup() {
  //conf pinos
  pinMode(pinLEDboard, OUTPUT);
  
  //serial
  Serial.begin(9600);
  
  //Modulo rf
  vw_set_rx_pin(pinRF);
  vw_setup(2000);   
  vw_rx_start();
  
 //configurado e iniciando o LCD
//  lcd.begin(16, 2);
//  //Limpa a tela
//  lcd.clear();
//  //Posiciona o cursor na coluna 3, linha 0;
//  lcd.setCursor(3, 0);
//  //Envia o texto entre aspas para o LCD
//  lcd.print("PROJECTO XX");
//  lcd.setCursor(3, 1);
//  lcd.print(" Monitoramento à distância");
//  delay(5000);
//   
//  //Rolagem para a esquerda
//  for (int posicao = 0; posicao < 3; posicao++)
//  {
//    lcd.scrollDisplayLeft();
//    delay(300);
//  }
//   
//  //Rolagem para a direita
//  for (int posicao = 0; posicao < 6; posicao++)
//  {
//    lcd.scrollDisplayRight();
//    delay(300);
//  }
//  
//  //imprimir no lcd
//  lcd.clear();
//  lcd.setCursor(3, 0);
//  lcd.print("Recebindo valores");
//  lcd.setCursor(3, 1);
//  lcd.print(" Esperando...");
//  delay(2000);
}

void loop() {

  //recebendo dados rf
  if ( vw_have_message() ) {
    vw_get_message(buf, &buflen);
    memcpy(&pacote,&buf,buflen);
  digitalWrite(pinLEDboard, HIGH); //liga led da placa  
  
  if (pacote.start=='i' && pacote.endd=='f')
  {
    //imprimir no pc
    Serial.println("Dados recebidos ok");
    Serial.print("Inicio");
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
    Serial.println("Fim");

    if (pacote.valor1==1){mov='S'; }
    else mov='N';
    if (pacote.valor5==1){port="Aberta"; }
    else port="Fechada";
    
  }
  else {Serial.println("Dados recebidos com erro");}
  digitalWrite(pinLEDboard, LOW);   //desliga led da placa
  }
  delay(300);
}
