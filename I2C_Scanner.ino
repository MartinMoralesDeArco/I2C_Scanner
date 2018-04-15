#include <Wire.h>
 
void setup()
{
  Wire.begin(); //Se inicializa el protocolo I2C
  Serial.begin(9600); //Se crea una comunicación serial a 9600 baudios
  Serial.println("\nI2C Scanner");
}
 
void loop()
{
  byte error, direccion; //Se crean dos bytes: uno en caso de error y el otro para la dirección
  int nDispositivos = 0; //Esta variables contabiliza el número de dispositivos encontrados. Se inicializa en 0.
 
  Serial.println("Escaneando...");
 
  for(direccion = 1; direccion < 127; direccion++ ) //Se crea un bucle que va de la dirección 1 hasta la 126
  {
    // El scanner I2C retorna el valor de "end.Transmistion" si un dispositivo confirma la dirección
    Wire.beginTransmission(direccion); //Comienza la transmisión con la dirección de la variable
    error = Wire.endTransmission(); //La variable error captura el número de error si se obtiene de la transmisión
 
    if (error == 0) //En caso de que no hay error en la transmisión
    {
      Serial.print("Dispositivo I2C encontrado en la direccion 0x");
      if (direccion<16) //Si la dirección es menor que 16
        Serial.print("0"); 
      Serial.print(direccion,HEX); 
      Serial.println("  !"); 
 
      nDispositivos++;
    }
    else if (error==4) //Si el error es igual a 4
    {
      Serial.print("Error desconocido en la direccion 0x");
      if (direccion<16) //Si la dirección es menor que 16
        Serial.print("0");
      Serial.println(direccion,HEX);
    }    
  }
  if (nDispositivos == 0) //Si no se encontraron dispositivos
    Serial.println("No se han encontrado dispositivos I2C\n");
  else //En caso de que si se encontraron
    Serial.println("Finalizado\n");
 
  delay(5000);
}
