#include <SPI.h>
#include <MFRC522.h>


#define RST_PIN    9
#define SS_PIN    10


MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.


void setup() {
    Serial.begin(9600);         // Inicia a serial
    SPI.begin();                // Inicia  SPI bus
    mfrc522.PCD_Init();         // Inicia MFRC522

    Serial.println("Aproxime o seu cartao do leitor...\n");
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
    
    //Mostra UID na serial
    Serial.print("UID da tag:  ");
    String conteudo= "";
    byte letra;    
    for (byte i = 0; i < mfrc522.uid.size; i++) {
        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(mfrc522.uid.uidByte[i], HEX);
        conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
        conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    
    Serial.println();
    Serial.println();
    Serial.println();
    
    Serial.println("Aproxime o seu cartao do leitor...\n");    
}




