#ifndef _LOCO_HANDLING_H_
#define _LOCO_HANDLING_H_

#define MAX_FUNCTION 12

#include <ESP8266WiFi.h>

#include <stdint.h>
#include <stdbool.h>

enum functionInfo
{
  THROTTLE, ALWAYS_ON, ALWAYS_OFF
};

typedef struct
{
  int16_t address;
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

void locoInit(void);

void locoHandler(void);

#endif
