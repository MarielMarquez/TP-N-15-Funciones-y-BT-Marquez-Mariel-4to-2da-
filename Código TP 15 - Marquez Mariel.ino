//Librería
#include <SoftwareSerial.h>
SoftwareSerial BT( 7 , 8 );

//Leds
#define LedA 9
#define LedR 10
#define LedV 11

//Buzzer
#define Buzzer 5

//Sensor de temperatura
#define SensorTemp 3

//Interruptor deslizante
#define Config 13

String dato;

//////////////
void setup()
{
  //Monitor Serial
  Serial.begin( 9600 );
  
  pin();
  
}//Fin setup

//////////////
void loop()
{
  configuracionBT();
  
  if(!configuracionBT())
  {
    if(dato == "on")
    {
      ledsON();
    }
    else if(dato == "off")
    {
      ledsOFF();
    }
    else if(dato == "temperatura")
    {
     sensorTemperatura();
    } 
  } 
    
}//Fin loop

//////////////
void pin()
{
  int pin[6]={ Config , LedA ,  LedR ,  LedV , Buzzer, SensorTemp };
  int modo[6]={  0   ,   1  ,    1  ,   1   ,   1   ,     0 };

  for( int i = 0 ; i > 5 ; i++ )
  {
    pinMode( pin[i], modo[i] );
  }
  
}//Fin pin

//////////////
bool configuracionBT()
{
  if( digitalRead( Config ) )
  {
      if( BT.available() )
      {
        Serial.write( BT.read() ) ; 
      }
      if( Serial.available() )
      {
        BT.write( Serial.read() );
      }
    
    return true;
  } 
  
  return false;
  
}//Fin configurarBT

//////////////
void ledsON()
{
  delay( 500 );

  tone( Buzzer , 5 ) ;

  digitalWrite( LedA , HIGH );
  digitalWrite( LedR , LOW );
  digitalWrite( LedV , LOW );  
  delay( 3000 );

  tone( Buzzer , 10 ) ;
  digitalWrite( LedA , LOW );
  digitalWrite( LedR , HIGH );
  digitalWrite( LedV , LOW );
  delay( 3000 );

  tone( Buzzer , 15 ) ;
  digitalWrite( LedA , LOW );
  digitalWrite( LedR , LOW );
  digitalWrite( LedV , HIGH );
  delay( 3000 );
  
}

//////////////
void ledsOFF()
{
  noTone( Buzzer );

  digitalWrite( LedA , LOW );
  digitalWrite( LedR , LOW );
  digitalWrite( LedV , LOW );
}

//////////////
float sensorTemperatura()
{
  float vol = analogRead( SensorTemp );
  vol = vol * 5.0 ;
  vol /= 1024.0 ;
  float temperatura = ( vol - 0.5 ) * 100;
  
  Serial.print( "Temperatura: " );
  Serial.print( temperatura );
  Serial.println(" grados"); 
  
  return temperatura;
  
}//Fin sensorTemperatura

//////////////
void serialEvent()
{
  String aux = "";
  while( Serial.available())
  {
    dato = Serial.readString();
  }
  
}//Fin serialEvent