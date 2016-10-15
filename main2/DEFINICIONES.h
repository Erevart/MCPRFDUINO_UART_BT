/*
    Lectura Contador de Energia

*/

/* ============================================================================================================ */
/* ============================================================================================================ */
/*                                        PARAMETROS DE CONFIGURACION
/º* ============================================================================================================ */
/* ============================================================================================================ */

/* ============================================================================================================ */
/* ============================================================================================================ */
/* ============================================================================================================ */

/* Definicion de Parametros */
#define uart Serial     // Esta definición permite modificar el modulo de comunicación utilizado para
                        // comunicarse con el Contador de Energia.

/***************
/* Constantes */
/**************/


/* Pagina memoria RFduino */
#define FLASH_PAGE 249          // Pagina de escritura del RFDuino

/*********************************/
/* Definicion Puertos (RFduino) */
/********************************/

#define PIN3  3 // GPIO 3
#define PIN4  4 // GPIO 4
#define PIN5  5 // GPIO 5
#define PIN6  6 // GPIO 6


/* Prototipo de Funciones */
void init_BLE(void);



/* Variables */

uint8_t frametx[100];
uint16_t numframetx = 0;
uint16_t numframerx = 0;

char *btdata = NULL;

bool isBLEconnect = false;       // Variable para indicar cuando hay establecidad una conexion BLE.
