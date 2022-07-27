#include "typewise-alert.h"
#include <stdio.h>
#include <string.h>

Limits parameterLimits[MAX_COOLINGTYPE] = {
  {PASSIVE_COOLING_MinLimit,PASSIVE_COOLING_MaxLimit},		 /* PASSIVE COOLING */
  {HI_ACTIVE_COOLING_MixLimit,HI_ACTIVE_COOLING_MaxLimit},	 /* HI ACTIVE COOLING */
  {MED_ACTIVE_COOLING_MinLimit,MED_ACTIVE_COOLING_MaxLimit}  /* MED ACTIVE COOLING */
};


BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC, Limits parameterLimits[]) {
  int lowerLimit = parameterLimits[coolingType].lowerLimit;
  int upperLimit = parameterLimits[coolingType].higherLimit;

  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

void checkAndAlert( BatteryCharacter batteryChar, double temperatureInC, void (*alertType) (BreachType breachType)) {
  BreachType breachType = classifyTemperatureBreach( batteryChar.coolingType, temperatureInC );
  (*alertType) (breachType);
}

void sendToController(BreachType breachType) {
  printf("%x : %x\n", MSG_HEADER, breachType);  
}

void sendToEmail(BreachType breachType) {
  if (TOO_LOW == message)
	{                              
        printf("To: %s\n %s", RECEPIENT, MSG(TOO_LOW));    
    } 
  else if(TOO_HIGH == message)
    {                                               
        printf("To: %s\n %s", RECEPIENT, MSG(TOO_HIGH));   
    }  
  else printf("To: %s\n %s", MSG(NORMAL))
}
