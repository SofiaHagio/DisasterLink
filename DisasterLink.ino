//pinos 

int ledVerde    = A0; // LED verde = sistema ligado e funcionando
int ledVermelho = A1; // LED vermelho = piscaa quando recebe um SOS
int ledAzul     = A2; // LED azul = modulo LoRa ativo (recebe sinais)
int buzzer      = A3; // buzzer = apita quando recebe e quando envia SOS
int botao       = A4; // botao = simula o chaveiro SOS da vitima
int contadorSOS = 0; // guarda quantos SOS foram recebidos no total

void setup() {

  Serial.begin(9600); 

  // OUTPUT = manda sinal
  // INPUT = recebe sinal
  pinMode(ledVerde,    OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledAzul,     OUTPUT);
  pinMode(buzzer,      OUTPUT);
  pinMode(botao,       INPUT_PULLUP); 

  digitalWrite(ledVerde, HIGH); 
  digitalWrite(ledAzul,  HIGH); 

  // imprime as mensagens de inicializacao no monitor serial
  Serial.println("----------------------------");
  Serial.println("   DisasterLink - LIGADO");
  Serial.println("----------------------------");
  Serial.println("LoRa: OK");      
  Serial.println("GPS: OK");       
  Serial.println("Satelite: OK");  
  Serial.println("");
  Serial.println("Aperte o botao SOS!");
  Serial.println("----------------------------");
}

void loop() {

  if (digitalRead(botao) == LOW) {

    contadorSOS = contadorSOS + 1;

    float lat      = -30.0 - (random(0, 100) / 1000.0); 
    float lng      = -51.0 - (random(0, 100) / 1000.0); 
    int distancia  = random(100, 2000);                  

    // avisa que recebeu o SOS 
    Serial.println("");
    Serial.println(">>> BOTAO SOS APERTADO! <<<");
    Serial.print("SOS numero: ");
    Serial.println(contadorSOS); // mostra qual e o numero desse SOS

    // mostra os dados do sinal LoRa recebido
    Serial.println("");
    Serial.println("[1] Sinal LoRa recebido do chaveiro");
    Serial.print("    Latitude:  ");
    Serial.println(lat, 4);  
    Serial.print("    Longitude: ");
    Serial.println(lng, 4);
    Serial.print("    Distancia: ");
    Serial.print(distancia);
    Serial.println("m do kit");

    // pisca o LED vermelho para indicar alerta visual
    digitalWrite(ledVermelho, HIGH); 
    delay(300);                      
    digitalWrite(ledVermelho, LOW);  

    // tenta enviar pelo 4G 
    Serial.println("");
    Serial.println("[2] Tentando pelo 4G...");
    Serial.println("    Sem sinal na area!");

    // envia pelo satelite Iridium 
    Serial.println("");
    Serial.println("[3] Enviando pelo satelite Iridium...");
    Serial.print("    Aguardando");
    delay(300); Serial.print("."); 
    delay(300); Serial.print(".");
    delay(300); Serial.println(".");
    Serial.println("    ENVIADO COM SUCESSO!");
    Serial.println("    Defesa Civil avisada!");
    Serial.println("    Resgate a caminho!");
    Serial.println("----------------------------");

    // apita duas vezes para confirmar o envio
    tone(buzzer, 1000, 200); 
    delay(300);
    tone(buzzer, 1500, 200); 

    while (digitalRead(botao) == LOW) {} 
    delay(300); 
  }
}