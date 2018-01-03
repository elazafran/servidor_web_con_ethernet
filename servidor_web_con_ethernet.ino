#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>


#include <SPI.h>
#include <Ethernet.h>

//librerías para sensor

#define DHTTYPE DHT22  
const int DHTPin = 5; 
DHT dht(DHTPin, DHTTYPE);
const int sensorPin = A0;

//--------------------------------------------------------------------------------------------
//Declaración de la direcciones MAC e IP. También del puerto 80
byte mac[]={0xDE,0xAD,0xBE,0xEF,0xFE,0xED}; //MAC
IPAddress ip(192,168,1,117); //IP
EthernetServer servidor(80);
//--------------------------------------------------------------------------------------------


void setup()
{
 int humedad = analogRead(sensorPin);
   Serial.print(humedad);
  
   if(humedad < 500)
   {
      Serial.println("Encendido");  
      //hacer las acciones necesarias
   }
 //Inicializamos el servidor
  Ethernet.begin(mac, ip); 
  servidor.begin();

  //Se inicia el sensor
  dht.begin(); 
}

void loop()
{
   // Wait a few seconds between measurements.
   delay(3000);
 
   // Reading temperature or humidity takes about 250 milliseconds!
   float h = dht.readHumidity();
   float t = dht.readTemperature();
   Serial.print("Humidity: ");
   Serial.print(h);
   Serial.print(" %\t");
   Serial.print("Temperature: ");
   Serial.print(t);
   Serial.print(" *C ");
   
   if (isnan(h) || isnan(t)) {
      Serial.println("falló el lector del sensor DHT!");
      return;
   }
 
 
   
  
  EthernetClient cliente = servidor.available();
 
      if(cliente.available())
      {
   
//------------------------------------------------WEB--------------------------------------------------------------------------------------          
          
          
          cliente.print("<!DOCTYPE html>");
          cliente.print("<html lang='es'>");
          
          
          cliente.println("<head>");
          cliente.println("<title>Sensores hogar</title>");
          cliente.println("<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-beta.2/css/bootstrap.min.css' integrity='sha384-PsH8R72JQ3SOdhVi3uxftmaW6Vc51MKb0q5P2rRUpPvrszuE4W1povHYgTpBfshb' crossorigin='anonymous'>");//EL CSS
          cliente.println("<meta charset='utf-8'>");
          cliente.println("</head>");
          
          cliente.println("<body>");


          cliente.print("<center>");   
          cliente.print("<h1>Esta es la Página WEB</h1>");
          
          cliente.print("</center>");
          cliente.print("<h2>");   
          cliente.println("Humedad: "); 
           cliente.println(h);

          cliente.print("</h2>");   
          cliente.print("<h2>");   
          cliente.println("Temperatura: ");
           cliente.println(t);
          cliente.print("</h2>");   
     
          
          
          
          
          cliente.println("</body>");
          
          cliente.println("</html>");
          cliente.stop();//Cierro conexión con el cliente
        }
      }
    
  


