/*
    Lectura Contador de Energia
*/

#include <RFduinoBLE.h>
// Descomentar para RFDUINO
__attribute__ ((section(".flash")))

#include "DEFINICIONES.h"
#include "RFDUINO.h"

void setup() {

    // Permite badurate > 96000
    override_uart_limit = true;

    /**********************************/
    /*   Definicion Puerto I/O        */
    /**********************************/
//    pinMode(13, OUTPUT);
//    digitalWrite(13,LOW);

    /**********************************/
    /*   Configuracion BLE            */
    /**********************************/
    init_BLE();

     /**********************************/
    /*   Inicializacion Comunicacion  */
    /**********************************/
    uart.begin(115200);
    RFduinoBLE.begin();
    delay(500);

}
void loop() {


 if (uart.available()>0 && isBLEconnect){
   RFduino_ULPDelay(1);
   while (uart.available()!=0){
     frametx[numframetx] = uart.read();
     numframetx++;
   }
     RFduinoBLE.send(reinterpret_cast<char*>(frametx), numframetx);
     numframetx = 0;

 }

   if (btdata != NULL){
     for (int i = 0; i < numframerx; i++){
       uart.write(btdata[i]);
       RFduino_ULPDelay(1);
     }
     //uart.write(tcpdata,numframe2);
     free(btdata);
     btdata = NULL;
   }
  ;
  RFduino_ULPDelay(10);

}
