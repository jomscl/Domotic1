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
#include <debug.h>

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
#define nreles 1 // n+1
#define nswitch 1

// estructuras
struct stRele
{
	byte pin;
	boolean estado;
	boolean estadoDefecto;
};

struct stSwt
{
	byte pin;
	boolean estadoPulsador;
};

// variables
boolean releHabilitado = true; // usado para la desabilitacion remota
boolean apagadoTmp = false; // usado para apagado por sobretemperatura
int timerTmp=0;
stRele reles[nreles];
stSwt swt[nreles];

// objetos
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, neopixel, NEO_GRB + NEO_KHZ800);
Metro timer = Metro(100); 

void setup() {
  // hardware
	Serial.begin(9600);
	DEBUGLN("Core online");
	creaRele(0,rele1,LOW);
	creaRele(1,rele2,LOW);
	pinMode(neopixel, OUTPUT);
	creaSwt(0,puls1);
	creaSwt(1,puls2);
	pinMode(tmp, INPUT);
  
	// neopixel
	strip.begin();
	strip.show(); // Initialize all pixels to 'off'
	strip.Color(255, 0, 0);
  
	// rutinas SPARK
  
	// variables SPARK
  

}

void loop() {
  
  // acciones que se revisan cada 100ms
   if (timer.check() == 1){
     // switchs
     for (int i=0;i<=nreles;i++){
		 leeSwitch(i);
	 }
     
     // temperatura, según su contador
     if (timerTmp++>cTimerTmp){
       timerTmp=0;
       revisaTemperatura(tmp);
     }
   }
}

void creaRele(int id, byte pin, byte estadoDefecto){
	// definicion del objeto
	reles[id].pin=pin;
	reles[id].estado=estadoDefecto;
	reles[id].estadoDefecto=estadoDefecto;
	pinMode(reles[id].pin, OUTPUT);
	conmutaRele(id,reles[id].estado);
}

void creaSwt(int id, byte pin){
	swt[id].pin=pin;
	swt[id].estadoPulsador=false;
	pinMode(swt[id].pin,INPUT);
}