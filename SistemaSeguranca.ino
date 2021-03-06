#include <SPI.h>
#include <MFRC522.h>

#define PIR_PIN    3
#define RELAY_PIN  2
#define RST_PIN    9
#define SS_PIN    10


bool buscaCartao(String uid);
void acaoDetectaMovimento();


MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.


String cartoesCadastrados[] = {
    "B0 A2 A9 89", // Visitante (cartão branco)
    "AA 23 92 3E", // Carla
    "67 D5 02 6C", // Isadora
    "97 23 02 6C"  // Leticia
};



void setup() {
    Serial.begin(9600);         // Inicia a serial
    SPI.begin();                // Inicia  SPI bus
    
    mfrc522.PCD_Init();         // Inicia MFRC522
    
    pinMode(RELAY_PIN, OUTPUT); // Pino do relé como saída
    pinMode(PIR_PIN, INPUT);    // Pino do sensor de movimento

    attachInterrupt(digitalPinToInterrupt(PIR_PIN), acaoDetectaMovimento, RISING);
}


void loop() {     
    // Procura por cartao RFID
    if ( not mfrc522.PICC_IsNewCardPresent() ) {
        return;
    }
    
    // Seleciona o cartao RFID
    if ( not mfrc522.PICC_ReadCardSerial() ) {
        return;
    }
    
    // Pega UID do cartão passado
    String conteudo= "";
    byte letra;
    
    for (byte i = 0; i < mfrc522.uid.size; i++) {
        conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
        conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    
    conteudo.toUpperCase();    
    String uid = conteudo.substring(1);
    
    bool cartaoVerificado = buscaCartao(uid);
    
    if (cartaoVerificado) {
        digitalWrite(RELAY_PIN, HIGH); // ativa rele, abre a trava solenoide
        delay(3000);                   // espera 3 segundos
        digitalWrite(RELAY_PIN, LOW);  // desativa rele, fecha a trava solenoide
        Serial.write(2);               // manda sinal para salvar log
        Serial.print(uid);
    }  
}



bool buscaCartao(String uid) {
    for (String cartao : cartoesCadastrados) {
        if (cartao == uid) {
            return true;
        }
    }
    
    return false;
}

void acaoDetectaMovimento() {
    Serial.write(1);  // envia sinal para tirar foto do ambiente
}







