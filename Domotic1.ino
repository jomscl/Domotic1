/*
Pin	I/O	Uso
D7	O	relee 1
D6	O	relee 2
D5	O	Led MID
D4	I 	Pulsador gnd 1
D3	I	Pulsador gnd 2
D2	I/O	no definida
D1	I/O	no definida
D0	I/O	no definida
A7	I	Sensor Térmico
A6	I/O	no definida
A5	I/O	no definida
A4	NC	
A3	NC	
A2	NC	
A1	NC	
A0	NC	

Actividades.
físicas….
Al pulsar D4 se cambia estado de D7 
Al Pulsar D3 se cambia estado de D6
Al pulsar Clave de desbloqueo en D4 ( clave tipo morse de 4 dígitos espaciados por un parpadeo de D5) fuerza cambio de estado de D7 , de igual forma con D3 y D6.
Apagado del sistema por temperatura ( sensor sobre un parámetro de fabrica - eeprom interno)

Web-app
programar tiempo de encendido y apagado de D7 y D6
Bloqueo de estado ( clave tipo morse de 4 dígitos) por cada actuador.
almacenamiento de historia de encendidos por software o hardware
programar parámetros iniciales del sistema: estado al corte de luz, envió de historiales por email, ID de cada spark y de sus actuadores
indicación de estado del spark, historial de enlace a la nube
encender o apagar D7 o D6, indicador de tarea realizada …. Ejemplo cambio de color de algo….

*/
// includes
#include <Adafruit_NeoPixel.h>
#include <Metro.h>

// defines de hardware
#define rele1 7
#define rele2 6
#define puls1 4
#define puls2 3
#define tmp A7
#define neopixel 5

// constantes
#define cTimerTmp 6000 // 60 seg * 100 ms
#define cTempMax 2048 // corregir
#define cMsRebote 5 // constante de rebote
// variables
boolean releHabilitado = true; // usado para la desabilitacion remota
boolean apagadoTmp = false; // usado para apagado por sobretemperatura
int timerTmp=0;
boolean estadoRele1 = LOW;
boolean estadoRele2 = LOW;
boolean estadoPuls1 = false;
boolean estadoPuls2 = false;

// objetos
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, neopixel, NEO_GRB + NEO_KHZ800);
Metro timer = Metro(100); 

void setup() {
  // hardware
  pinMode(rele1, OUTPUT);
  pinMode(rele2, OUTPUT);
  pinMode(neopixel, OUTPUT);
  pinMode(puls1, INPUT);
  pinMode(puls2, INPUT);
  pinMode(tmp, INPUT);
  
  // neopixel
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.Color(255, 0, 0);
  
  // rutinas SPARK
  
  // variables SPARK
  
  // estado por defecto de los reles
  conmutaRele(rele1,estadoRele1);
  conmutaRele(rele2,estadoRele2);
}

void loop() {
  
  // acciones que se revisan cada 100ms
   if (timer.check() == 1){
     // switchs
     leeSwitch(puls1,rele1,estadoPuls1);
     leeSwitch(puls2,rele2,estadoPuls2);
     
     // temperatura, según su contador
     if (timerTmp++>cTimerTmp){
       timerTmp=0;
       revisaTemperatura(tmp);
     }
   }
}

