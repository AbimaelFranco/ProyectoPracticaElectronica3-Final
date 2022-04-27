#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial Blue(8,9);

Servo servoMotor1;
Servo servoMotor2;

const byte AlPush1 = 2;
const byte AlPush2 = 3;
const byte Push12 = A0;
const byte Push34 = A1;
const byte Push56 = A2;
const byte Spceci = A3;  //espacio y envio
const byte LED1 = 5;
const byte LED2 = 4;
const byte LED3 = 7;
const byte LED4 = 6;
const byte NextChar = 12;
const byte buzzer = 13;

int EntradasActivadas[8]={0,0,0,0,0,0,0,0};   //Lectura de entradas
int EntradasGuardadas[8]={0,0,0,0,0,0,0,0};   //Almacenamiento de entradas 6: Guardar, 7:Espacio, 77: Enviar
int i;

int LetraEnviar;      //Calculo de letra a enviar
char Letra;           //Letra a enviar
String MensajeEnviar; //Mensaje completo a enviar
bool ConfirmarEnvio;  //Confirma la acción de enviar si 77
char LentraEnviada;   //Envio de mensaje letra por letra

char LetraRecibir;
char LetraActiva;
int w;
String MensajeRecibir;
String MensajeRecibido;
//int SalidasActivas[6]={0,0,0,0,0,0};

void Buzzer();


void setup() {

  Serial.begin(9600);
  
  Blue.begin(9600);

  servoMotor1.attach(10);
  servoMotor2.attach(11);
  
  pinMode(AlPush1, OUTPUT);
  pinMode(AlPush2, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(NextChar,  INPUT);
  pinMode(buzzer, OUTPUT);
  //pinMode(Push12, INPUT);
  //pinMode(Push34, INPUT);
  //pinMode(Push56, INPUT);

  digitalWrite(AlPush1, LOW);
  digitalWrite(AlPush2, LOW);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(buzzer, LOW);

  servoMotor1.write(0);
  servoMotor2.write(0);

  LetraEnviar=0;
  ConfirmarEnvio=false;
  w=0;
}

void loop() {
  
  ////////////////////////////////////////////////Lectura y almacenamiento de push 0,2,4,6
  
  digitalWrite(AlPush1, HIGH);
  digitalWrite(AlPush2, LOW);

  EntradasActivadas[0] = analogRead(Push12);
  if(EntradasActivadas[0]>=50 && EntradasGuardadas[0]==0){
    EntradasGuardadas[0]=1;
    ConfirmarEnvio=false;
    Buzzer();
  }else if(EntradasActivadas[0]>=50 && EntradasGuardadas[0]==1){
    EntradasGuardadas[0]=0;
    Buzzer();
  }
  
  EntradasActivadas[2] = analogRead(Push34);
  if(EntradasActivadas[2]>=50 && EntradasGuardadas[2]==0){
    EntradasGuardadas[2]=1;
    ConfirmarEnvio=false;
    Buzzer();
  }else if(EntradasActivadas[2]>=50 && EntradasGuardadas[2]==1){
    EntradasGuardadas[2]=0;
    ConfirmarEnvio=false;
    Buzzer();
  }
  
  EntradasActivadas[4] = analogRead(Push56);
  if(EntradasActivadas[4]>=50 && EntradasGuardadas[4]==0){
    EntradasGuardadas[4]=1;
    ConfirmarEnvio=false;
    Buzzer();
  }else if(EntradasActivadas[4]>=50 && EntradasGuardadas[4]==1){
    EntradasGuardadas[4]=0;
    ConfirmarEnvio=false;
    Buzzer();
  }

  EntradasActivadas[6] = analogRead(Spceci);
  if(EntradasActivadas[6]>=50 && EntradasGuardadas[6]==0){
    EntradasGuardadas[6]=1;
    ConfirmarEnvio=false;
    Buzzer();
  }else if(EntradasActivadas[6]>=50 && EntradasGuardadas[6]==1){
    EntradasGuardadas[6]=0;
    Buzzer();
  }

  //delay(50);

  ////////////////////////////////////////////////Lectura y almacenamiento de push 1,3,5,7
  
  digitalWrite(AlPush1, LOW);
  digitalWrite(AlPush2, HIGH);

  EntradasActivadas[1] = analogRead(Push12);
  if(EntradasActivadas[1]>=50 && EntradasGuardadas[1]==0){
    EntradasGuardadas[1]=1;
    ConfirmarEnvio=false;
    Buzzer();
  }else if(EntradasActivadas[1]>=50 && EntradasGuardadas[1]==1){
    EntradasGuardadas[1]=0;
    Buzzer();
  }
  
  EntradasActivadas[3] = analogRead(Push34);
  if(EntradasActivadas[3]>=50 && EntradasGuardadas[3]==0){
    EntradasGuardadas[3]=1;
    ConfirmarEnvio=false;
    Buzzer();
  }else if(EntradasActivadas[3]>=50 && EntradasGuardadas[3]==1){
    EntradasGuardadas[3]=0;
    Buzzer();
  }
  
  EntradasActivadas[5] = analogRead(Push56);
  if(EntradasActivadas[5]>=50 && EntradasGuardadas[5]==0){
    EntradasGuardadas[5]=1;
    ConfirmarEnvio=false;
    Buzzer();
  }else if(EntradasActivadas[5]>=50 && EntradasGuardadas[5]==1){
    EntradasGuardadas[5]=0;
    Buzzer();
  }

  EntradasActivadas[7] = analogRead(Spceci);
  if(EntradasActivadas[7]>=50 && EntradasGuardadas[7]==0){
    EntradasGuardadas[7]=1;
    Buzzer();
  }else if(EntradasActivadas[7]>=50 && EntradasGuardadas[7]==1){
    EntradasGuardadas[7]=0;
    Buzzer();
  }
 delay(150);

  ////////////////////////////////////////////////Lectura de entradas guardadas
  
  /*for(i=0; i<=5; i++){
  Serial.print("Entrada ");
  Serial.print(i);
  Serial.print(" : ");
  Serial.print(EntradasGuardadas[i]);
  Serial.print("\r \n");
  }
  delay(50);*/
  
  ////////////////////////////////////////////////Calculo decimal equivalente

  LetraEnviar = (EntradasGuardadas[0]*1) + (EntradasGuardadas[1]*2) + (EntradasGuardadas[2]*4) + (EntradasGuardadas[3]*8) + (EntradasGuardadas[4]*16) + (EntradasGuardadas[5]*32);
  //Serial.println(LetraEnviar);

  ////////////////////////////////////////////////Calculo letra equivalente
  
  switch (LetraEnviar) {
  case 1:
    Letra = 'A';
    break;
  case 5:
    Letra = 'B';
    break;
  case 3:
    Letra = 'C';
    break;
  case 11:
    Letra = 'D';
    break;
  case 9:
    Letra = 'E';
    break;
  case 7:
    Letra = 'F';
    break;
  case 15:
    Letra = 'G';
    break;
  case 13:
    Letra = 'H';
    break;
  case 6:
    Letra = 'I';
    break;
  case 14:
    Letra = 'J';
    break;
  case 17:
    Letra = 'K';
    break;
  case 21:
    Letra = 'L';
    break;
  case 19:
    Letra = 'M';
    break;
  case 27:
    Letra = 'N';
    break;
  case 25:
    Letra = 'O';
    break;
  case 23:
    Letra = 'P';
    break;
  case 31:
    Letra = 'Q';
    break;
  case 29:
    Letra = 'R';
    break;
  case 22:
    Letra = 'S';
    break;
  case 30:
    Letra = 'T';
    break;
  case 49:
    Letra = 'U';
    break;
  case 53:
    Letra = 'V';
    break;
  case 46:
    Letra = 'W';
    break;
  case 51:
    Letra = 'X';
    break;
  case 59:
    Letra = 'Y';
    break;
  case 57:
    Letra = 'Z';
    break;
  case 44:
    Letra = '.';
    break;
  case 4:
    Letra = ',';
    break;
  case 52:
    Letra = '?';
    break;
  case 28:
    Letra = '!';
    break;
  case 16:
    Letra = '-';
    break;
  case 58:
    Letra = '#';
    break;
  case 63:
    Letra = ' ';
    break;
  default:
    Letra = ' ';
    break;
}
  Serial.println(Letra);

  ////////////////////////////////////////////////Estructurar mensaje
  
  if(EntradasGuardadas[6]==1){
      MensajeEnviar= MensajeEnviar+Letra;
      EntradasGuardadas[6]=0;
      for(i=0; i<=5; i++){
        EntradasActivadas[i]=0;
        EntradasGuardadas[i]=0;
      }
    }
    
  ////////////////////////////////////////////////7: Espaciar mensaje, 77: Enviar mensaje
  
  if(EntradasGuardadas[7]==1){
    if(ConfirmarEnvio==false){
      MensajeEnviar= MensajeEnviar+" ";
      EntradasGuardadas[7]=0;
      ConfirmarEnvio=true;
    }else if(ConfirmarEnvio==true){
      EntradasGuardadas[7]=0;
      ConfirmarEnvio=false;
      //Blue.write("\n");
      delay(250);
      Buzzer();
      delay(225);
      Buzzer();
      for(i=0; i<=MensajeEnviar.length(); i++){
        LentraEnviada = MensajeEnviar.charAt(i);
        Blue.write(LentraEnviada);
      }
      MensajeEnviar="";
      Serial.println("Mensaje Enviado!!!!!!!!!!!!!!!");
    }
  for(i=0; i<=5; i++){
    EntradasActivadas[i]=0;
    EntradasGuardadas[i]=0;
    }
  }

  Serial.println(MensajeEnviar);

  ////////////////////////////////////////////////Recepcion de Mensaje
  
  if(Blue.available()){     //Lee modulo blue y en via a placa
      LetraRecibir = Blue.read();
      if(LetraRecibir==';'){
        MensajeRecibido=MensajeRecibir;
        Serial.println(MensajeRecibido); 
        MensajeRecibir="";
        delay(250);
        Buzzer();
        delay(225);
        Buzzer();
      }else{
        MensajeRecibir=MensajeRecibir+LetraRecibir;
      }
    }




  LetraActiva=MensajeRecibido.charAt(w);

  switch(LetraActiva) {
  case 'a':
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    servoMotor1.write(50);
    servoMotor2.write(50);
    break;
  case 'b':
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, LOW);
    servoMotor1.write(50);
    servoMotor2.write(50);
    break;
  case 'c':
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    servoMotor1.write(50);
    servoMotor2.write(50);
    break;
  case 'd':
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, HIGH);
    servoMotor1.write(50);
    servoMotor2.write(50);
    break;    
  case 'e':
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, HIGH);
    servoMotor1.write(50);
    servoMotor2.write(50);
    break;
  case 'f':
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, LOW);
    servoMotor1.write(50);
    servoMotor2.write(50);
    break;
  case 'g':
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
    servoMotor1.write(50);
    servoMotor2.write(50);
    break;
  case 'h':
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
    servoMotor1.write(50);
    servoMotor2.write(50);
    break;
  case 'i':
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, LOW);
    servoMotor1.write(50);
    servoMotor2.write(50);
    break;
  case 'j':
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
    servoMotor1.write(50);
    servoMotor2.write(50);
    break;
  case 'k':
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, LOW);
    servoMotor1.write(50);
    servoMotor2.write(50);
    break;
  case 'l':
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, LOW);
    servoMotor1.write(0);
    servoMotor2.write(50);
    break;
  case 'm':
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    servoMotor1.write(0);
    servoMotor2.write(50);
    break;
  case 'n':
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, HIGH);
    servoMotor1.write(0);
    servoMotor2.write(50);
    break;
  case 'o':
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, HIGH);
    servoMotor1.write(0);
    servoMotor2.write(50);
    break;
  case 'p':
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, LOW);
    servoMotor1.write(0);
    servoMotor2.write(50);
    break;
  case 'q':
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
    servoMotor1.write(0);
    servoMotor2.write(50);
    break;
  case 'r':
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
    servoMotor1.write(0);
    servoMotor2.write(50);
    break;
  case 's':
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, LOW);
    servoMotor1.write(0);
    servoMotor2.write(50);
    break;
  case 't':
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
    servoMotor1.write(0);
    servoMotor2.write(50);
    break;
  case 'u':
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    servoMotor1.write(0);
    servoMotor2.write(0);
    break;
  case 'v':
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, LOW);
    servoMotor1.write(0);
    servoMotor2.write(0);
    break;
  case 'w':
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
    servoMotor1.write(50);
    servoMotor2.write(0);
    break;
  case 'x':
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    servoMotor1.write(0);
    servoMotor2.write(0);
    break;
  case 'y':
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, HIGH);
    servoMotor1.write(0);
    servoMotor2.write(0);
    break;
  case 'z':
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, HIGH);
    servoMotor1.write(0);
    servoMotor2.write(0);
    break; 
  default:
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    servoMotor1.write(50);      //Ajustar a 55° 
    servoMotor2.write(50);
    break;
  }


  if( digitalRead(NextChar) && w != MensajeRecibido.length()){
      w = w+1;
      Buzzer();
    } if(digitalRead(NextChar) && w == MensajeRecibido.length()){
      w=0;
      Buzzer();
      MensajeRecibido="";
    }
  Serial.println(w);
  
}

void Buzzer(){
  digitalWrite(buzzer, HIGH);
  delay(25);
  digitalWrite(buzzer, LOW);
}
