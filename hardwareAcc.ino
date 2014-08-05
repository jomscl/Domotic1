void conmutaRele(int id, boolean estado){
  digitalWrite(reles[id].pin,estado);
}

boolean leeRele(int id){
  return digitalRead(reles[id].pin); 
}

void leeSwitch(int id){
	if (releHabilitado && !apagadoTmp){// solo entra si el sistema esta activo
		if (!swt[id].estadoPulsador){ // solo entra si anteriormente el swt esta apagado
			if (leeSR(swt[id].pin)==HIGH){
				// switch apretado
				swt[id].estadoPulsador=true;
				reles[id].estado=!leeRele(id);
				conmutaRele(id,reles[id].estado);
				// avisar al cloud
			}
		}else{ // entra si anteriormente el boton estaba encendido
			if (leeSR(swt[id].pin)==LOW){
				// switch suelto
				swt[id].estadoPulsador=false;
				reles[id].estado=!leeRele(id);
				conmutaRele(id,reles[id].estado);
				// avisar al cloud
			}
		}// fin if según estado anterior del sw
	} // fin if sistema activo
}

void revisaTemperatura(int pin){
  int tempActual=analogRead(pin);
  int i;

  if (tempActual>=cTempMax && apagadoTmp==false){

    // apagar los reles
	for (int i=0;i<=nreles;i++){
		conmutaRele(i,LOW);
	}
    // alertar por wifi
    
    // Cambio estado LED
    
    apagadoTmp=true;
  }
  
  if (tempActual<cTempMax && apagadoTmp==true){
    // dejar como estaban antes
	for (int i=0;i<=nreles;i++){
		conmutaRele(i,reles[i].estado);
	}
 
     // alertar por wifi
    
     // Cambio estado LED
    
    apagadoTmp=false;  
  }
}

bool leeSR(int pin){
	// funcion que lee entradas sin rebote
	boolean estable=false;
	boolean ultimoEstado=digitalRead(pin);
	boolean tmp;
	while (!estable){
		delay(cMsRebote);
		tmp=digitalRead(pin);
		if (tmp==ultimoEstado){
			estable=true;
		}else{
			ultimoEstado=tmp;
		}
	}
	return ultimoEstado;
}