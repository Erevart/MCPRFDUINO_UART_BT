/*
    Lectura Contador de Energia

*/
/* ==================================================================================== */
/*                              Seleccion de Placa
/* ==================================================================================== */
#define RFDUINO        // Compilacion en RFDUINO.
/* ==================================================================================== */
/* ==================================================================================== */

#include <RFduinoBLE.h>
// Descomentar para RFDUINO
__attribute__ ((section(".flash")))
#ifndef RFDUINO
  #include <EEPROM.h>
#endif

#include <stdint.h>
#include "DEFINICIONES.h"
#include "DATOS_MEMORIA.h"
#include "COMUNICACION.h"
#include "CALIBRACION.h"
#include "RFDUINO.h"

void setup() {

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
    uart.begin(9600);
    RFduinoBLE.begin();
    delay(500);

    /****************************/
    /* Inicializacion Memoria   */
    /***************************/
    // Inicializacion de la Memoria solo es necesario realizar lo una vez.

#ifdef DATOS_MEMORY

#ifdef NOCOMPILAR

    // Se Comprueba si los Parametros han sido cargados o se encuentran almacenados en memoria
#ifdef RFDUINO
    if (memory->READ_OK_ADR != READ_OK)  {
#else
    if (read_u8(READ_OK_ADR) != READ_OK) {
#endif

            // Se solicita espacio de memoria ram.
            REGISTRO = (info_reg*)malloc(LAST_REGISTER*sizeof(info_reg));

            // Avisar de un error en la Lectura
            error(MEMORIA);

            initMEMORY();   // Se inicializan las estructuras de datos.
            writeMEMORY();  // Se guarda en memoria los datos. Solo es necesario realizarlo una vez.
            // Se libera el espacio de memoria ram, para futuros usos.
            free(REGISTRO);
    }
#endif

#endif



    /******************************/
    /* Comprobacion Comunicacion  */
    /******************************/

    // Se verifica antes de comenzar la ejecucion
    // del programa que el chips se encuentra
    // conectado y listo para comunicarse
 //   chip_is_ready();

     // Se inicializa la estructura de datos history_data y current_data.
    for (int i=0; i< MAXDATA; i++){
        temp.consumo_actual.power_act[i] = 0;
        temp2.consumo_actual.power_react[i] = 0;
        if (i < 7){
            temp.consumo_historico.power_act[i] = 0;
            temp.consumo_historico.power_react[i] = 0;
        }
    }
    temp.consumo_actual.numdata = 0;


// Se guarda la viaralbe tiempo
  previousMillis = 0;

}

void loop() {

  // Se actualiza la variable tiempo, para conocer el tiempo transcurrido
  currentMillis = millis();

  if (currentMillis - previousMillis >= MAX_FRECUENCIA) {

    // Se guarda en el último instante de tiempo en el,
    // que se ejecuta el contenido del bucle principal.
    previousMillis = currentMillis;

    /**************************************
      Frecuencia de Refresco: 333 mHz (3 segundos)
    *************************************/
    if (timecounter % TAREA_333mHz == 0){
        // Transmision de informacion a RFduino
          RFactualizar();
          RFsendgrafica();
   }

    /**************************************
      Frecuencia de Refresco: 200 mHz (5 segundos)
    *************************************/
    if (timecounter % TAREA_200mHz == 0){
      // Se realiza la lectura de las registros POWER_ACT,
      // I_RMS y V_RMS
//      read_chips(NULL,POWER_ACT);
//      delay(5);
//      read_chips(NULL,I_RMS);
//      delay(5);
//      read_chips(NULL,V_RMS);

    }
    else if ( (currentMillis - TAREA2_200mHzpreviousTime) >= 5000){

      // Se guarda en el último instante de tiempo en el,
      // que se ejecuta el contenido de la TAREA2_200mHz.
      TAREA2_200mHzpreviousTime = currentMillis;

      // Se realiza la lectura de las registros POWER_REACT,
      // POWER_APP y FREQUENCY
//      read_chips(NULL,POWER_REACT);
//      delay(5);
//      read_chips(NULL,POWER_APP);
//      delay(5);
//      read_chips(NULL,FREQUENCY);

    }

    /**************************************
      Frecuencia de Refresco: 3 mHz (6 mimutos)
    *************************************/
    if (timecounter % TAREA_3mHz == 0){
        actualizacion_medida();
    }


    // La variable timecounter debe reiniciarse cuando se alcance
    // el numero de ciclos de las acciones de menor prioridad.
    if (timecounter == 1200)
      timecounter = 0;
    else
      timecounter++;

  }
}
