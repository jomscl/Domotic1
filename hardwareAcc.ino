void conmutaRele(int id, boolean estado){
  digitalWrite(reles[id].pin,estado);
}

boolean leeRele(int id){
  return digitalRead(reles[id].pin); 
}

void leeSwitch(int i){
  if (releHabilitado && !apagadoTmp && !idPulsador){
    if (digitalRead(sw)==HIGH){
      // rebote
      delay(cMsRebote);
      if (digitalRead(sw)==HIGH){
        // switch apretado
        idPulsador=true;
        reles[i].estado=!leeRele(i);
		conmutaRele(i,reles[i].estado);
      }
    }  
  }
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
