void conmutaRele(int pin, boolean estado){
  digitalWrite(pin,estado);
}

boolean leeRele(int pin){
  return digitalRead(pin); 
}

void leeSwitch(int sw, int rele, boolean &idPulsador){
  if (releHabilitado && !apagadoTmp && !idPulsador){
    if (digitalRead(sw)==HIGH){
      // rebote
      delay(cMsRebote);
      if (digitalRead(sw)==HIGH){
        // switch apretado
        idPulsador=true;
        
      }
    }  
  }
}

void revisaTemperatura(int pin){
  int tempActual=analogRead(pin);
  if (tempActual>=cTempMax && apagadoTmp==false){
    // respaldo el estado de los reles
    estadoRele1=leeRele(rele1);
    estadoRele2=leeRele(rele2);
    // apagar los reles
    conmutaRele(rele1,LOW);
    conmutaRele(rele2,LOW);
    // alertar por wifi
    
    // Cambio estado LED
    
    apagadoTmp=true;
  }
  
  if (tempActual<cTempMax && apagadoTmp==true){
    // dejar como estaban antes
    conmutaRele(rele1,estadoRele1);
    conmutaRele(rele2,estadoRele2);
 
     // alertar por wifi
    
     // Cambio estado LED
    
    apagadoTmp=false;  
  }
}
