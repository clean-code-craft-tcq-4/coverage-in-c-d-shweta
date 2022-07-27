#pragma once

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING,
  MAX_COOLINGTYPE
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} BreachType;

typedef struct {
    double lowerLimit;
    double higherLimit;
} Limits;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;


#define PASSIVE_COOLING_LOWLIMIT     0
#define PASSIVE_COOLING_HIGHLIMIT    35
#define MED_ACTIVE_COOLING_LOWLIMIT  PASSIVE_COOLING_LOWLIMIT
#define MED_ACTIVE_COOLING_HIGHLIMIT 40
#define HI_ACTIVE_COOLING_LOWLIMIT   PASSIVE_COOLING_LOWLIMIT
#define HI_ACTIVE_COOLING_HIGHLIMIT  45

#define MSG_HEADER 0xfeed

#define RECEPIENT        "a.b@c.com"
#define MSG_TOO_LOW      "Hi, the temperature is too low\n"
#define MSG_TOO_HIGH     "Hi, the temperature is too high\n"
#define MSG(message) 	  MSG_##message 

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);
void checkAndAlert(BatteryCharacter batteryChar, double temperatureInC, void (*alertType) (BreachType breachType));
void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);
