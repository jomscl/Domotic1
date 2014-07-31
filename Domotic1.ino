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
#define rele1 7
#define rele2 6
#define puls1 4
#define puls2 3
//#define tmp A7

void setup() {
  // put your setup code here, to run once:
  pinMode(rele1, OUTPUT);
  pinMode(rele2, OUTPUT);
  
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
