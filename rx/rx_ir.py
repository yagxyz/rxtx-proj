import time
import RPi.GPIO as GPIO

from Adafruit_IO import Client, RequestError, Feed  #Importando biblioteca
ADAFRUIT_IO_USERNAME = "YuniorAG_io" # Nome de usuario Adafruit
ADAFRUIT_IO_KEY = "f02ab6736b0e4b23b0b95f661ce2e5ee" #Senha Adafuit
#Configurando Adafuit
aio = Client(ADAFRUIT_IO_USERNAME, ADAFRUIT_IO_KEY)
Light_room = aio.feeds('light-room')

LED_PIN = 36 # Led infrovermelho modulo comunicação

#Configurando GPIOs
GPIO.setwarnings(False) #Evitando falsas advertensias das GPIOs
GPIO.setmode(GPIO.BOARD)
GPIO.setup(LED_PIN, GPIO.IN)
GPIO.setup(32, GPIO.OUT)
GPIO.setup(22, GPIO.OUT)
GPIO.output(32,0)#led vermelho
GPIO.output(22,0)#led verde
#Criando variaveis para serem usadas
est=0;i=0;desv=0;
var_med=0;var_act=0;var_ant=0
v=[0,0,0,0,0,0,0,0]


#Introdução (;
print(' ')
print('Projeto de Microntroladores para Telecomunicação')
print('Leitura de sensor de iluminação por arduino. En-')
print('vio de valor ao rasperry por comunicação ótica. ')
print('Uso da plataforma <Adafruit.io> para compartilhar')
print('os resultados.')
print('Realizado por Yunior Alcantara Guevara     ')
print('Professor: Dr. Vitor Cristiano Bender ')
print(' ')      
print( "Inicio de Modulo de Comunicação")


#Loop geral
while True:
    
    Ir = GPIO.input(LED_PIN) #Receber valores do arduino
    time.sleep(0.01)
    #Maquina de 3 estados
    #Estado 1: Conta os miliseg. 1 ciclo
    if Ir==0 and est==0:
        ti=time.clock();
        while Ir ==0:#Repete a leitura do GPIO em log. 0
            Ir = GPIO.input(LED_PIN)   
        tf=time.clock();
        t1=ti
        #print(t1)
        if (tf-ti) >= 0.01:
            est=1
    time.sleep(0.01)
    #Estado 2: Conta os miliseg. 2 ciclo
    if Ir==0 and est==1:
        ti=time.clock();
        while Ir ==0:#Repete a leitura do GPIO em log. 0
            Ir = GPIO.input(LED_PIN)   
        tf=time.clock();
        t2=ti
        #print(t2)
        if (tf-ti) >= 0.01:
            est=2
    time.sleep(0.01)
    #Estado 3: Diferencial do 2 ciclo - 1 ciclo
    if est==2:
        tt=t2-t1
        #print(tt)
        if tt>0.08:#Determina o valor logico 0
            Log=0
            #print(Log)
            v[i]=Log
            i+=1
            #print(v)
            est=0
        if tt<0.08:#Determina o valor logico 0
            Log=1
            #print(Log)
            v[i]=Log
            i+=1
            #print(v)
            est=0
        if tt>0.3:#Determina algum erro de medida e retorna ao Estado 1
            print('erro')
            est=0
        if i >= 8:#Uma vez terminada a leitura do vetor
            i=0
            print('var_ant_1: ',var_ant)#valor recebido anterior
            var_act=int(''.join(map(str, v)),2)
            var_med=(var_act+var_ant)/2#Calcula Media
            
            #Calculo de desvio padrão
            desv=(((var_ant-var_med)**2+(var_act-var_med)**2)/2)**0.5;
            if var_ant!=var_act:
                var_ant=var_act
            print('var_ant_2: ',var_ant)
                
            if desv >= 5:#Minifiltragem e diminuição de erros
                print('Desvio muito alto')
                print('Esperando estabilizar valores...')
                est=0
                var_act=0
                time.sleep(1)
                continue #volta ao inicio do While
            print('Valores estabilizados!')
            print(' ')
            print('Sequencia recebida:',v)
            print('Equivalente em decimal: ',var_act)
            print('Desvio: ',desv)
            
            #Aqui são enviados e recebidos os valores da nuvem
            status1 = aio.receive('status1')
            print('Iluminação na sala (0-255): ',int(''.join(map(str, v)),2))
            print('Enviar para nuvem: {0}'.format(status1.value))

            if format(status1.value) == 'ON':#Algoritmo do botão do nuvem
                aio.send_data(Light_room.key, ((int(''.join(map(str, v)),2))*100)/255)
                GPIO.output(22,1)#verde on
                GPIO.output(32,0)#vermelho off
            else:
                GPIO.output(32,1)#vermelho on
                GPIO.output(22,0)#verde off
            est=0 #volta novamente ao Estado 1
            print(' ')
                
    
                            
                





   
