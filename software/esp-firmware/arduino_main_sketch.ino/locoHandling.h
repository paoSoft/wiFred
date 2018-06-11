#ifndef _LOCO_HANDLING_H_
#define _LOCO_HANDLING_H_

#define MAX_FUNCTION 16

#include <ESP8266WiFi.h>

#include <stdint.h>
#include <stdbool.h>

enum functionInfo { THROTTLE, ALWAYS_ON, ALWAYS_OFF, UNKNOWN = THROTTLE };

enum eLocoState { LOCO_OFFLINE, LOCO_CONNECTED, LOCO_ACQUIRING, LOCO_ACQUIRE_SINGLE, LOCO_ONLINE };

extern eLocoState locoState;

typedef struct
{
  int16_t address;
  bool longAddress;
  functionInfo functions[MAX_FUNCTION + 1];
  bool reverse;
} locoInfo;

#include "config.h"

extern locoInfo locos[4];
extern bool locoActive;
extern serverInfo locoServer;
extern bool locoRunning[4];
extern bool e_allLocosOff;

#define LOCO1_INPUT 5
#define LOCO2_INPUT 4
#define LOCO3_INPUT 12
#define LOCO4_INPUT 13

extern const uint8_t inputPins[];

void locoInit(void);

void locoHandler(void);

bool getInputState(uint8_t input);

bool getInputChanged(uint8_t input);

/**
 * Acquire a new loco for this throttle, including function setting according to function infos
 * 
 * Will return the same value if needs to be called more than once, loco + 1 if finished
 */
uint8_t requestLoco(uint8_t loco);

#endif

