
/* void init_BLE()
   Determina los parametros de identifcación y potencia
   del modulo de comunicacion BLE                      */

void init_BLE(){

    RFduinoBLE.advertisementData = "UEX";
  //  RFduinoBLE.advertisementInterval = 200;
    RFduinoBLE.deviceName = "RF-MCP";
    RFduinoBLE.txPowerLevel = 4;
}

/* void RFduinoBLE_onAdvertisement(bool start)
    Esta funcion sera invocada cada vez que se realice
    un Advertisement de la conexion BLE*/
/*
void RFduinoBLE_onAdvertisement(bool start)
{
  Serial.println("Advertisement");
}
*/

/* RFduinoBLE_onConnect()
    Esta funcion será invocada cuando establezca la
    comunicación Bluetooth */

void RFduinoBLE_onConnect()
{
  // Se ha establecido una conexion BLE
  isBLEconnect = true;
  Serial.println("Conectado");
  delay(50);

}


/* void RFduinoBLE_onDisconnect()
   Esta función será invocada cuando se finalice
    la comunicación Bluetooth */

void RFduinoBLE_onDisconnect()
{
  // Se ha cerrado la conexion BLE
  isBLEconnect = false;
  Serial.println("Desconectado");

}

/* void RFduinoBLE_onReceive(char *data, int len)
    Función que es invocada cuando se recibe informacion
    el receptor que ha establecido la informacion. Los datos
    recibidos se encuentra en la variable data, y el número de byte
    del array esta determiando por len. */

void RFduinoBLE_onReceive(char *data, int len)
{
    numframerx = len;

  if ((btdata = (char *) malloc (len*sizeof (char))) != NULL)
    memcpy(btdata,data,len);
}
