/**
 * This file is part of the wiFred wireless model railroading throttle project
 * Copyright (C) 2018  Heiko Rosemann
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>
 *
 * This file provides functions for reading the potentiometer and calculating the speed value
 */

#include <stdbool.h>
#include <stdint.h>
#include <avr/io.h>
#include "analog.h"
#include <avr/interrupt.h>

/**
 * Flag to notify everyone of a speed update
 */
volatile bool newSpeed = false;

/**
 * Current speed value from potentiometer (0...126)
 */
volatile uint8_t currentSpeed = 0;

/**
 * Flag to notify everyone of low battery status
 */
volatile bool lowBattery = false;
/**
 * Flag to notify everyone the battery is empty, system is shutting down
 */
volatile bool emptyBattery = false;

/**
 * Initialize A/D converter for single run conversion mode
 * and start first conversion
 */
void initADC(void)
{
  ADMUX = (1<<REFS0) | 7;
  ADCSRA = (1<<ADEN) | (1<<ADIE) | (1<<ADPS2) | (1<<ADPS1);
  ADCSRB = 0;
  ADCSRA |= (1<<ADSC);

  // enable power to speed potentiometer
  DDRC |= (1<<PC5);
  PORTC |= (1<<PC5);
}

/**
 * Report if there is a new speed value
 */
bool speedTriggered(void)
{
  if(newSpeed)
    {
      newSpeed = false;
      return true;
    }
  else
    {
      return false;
    }
}

/**
 * Returns current speed value read from potentiometer (0..126)
 */
uint8_t getADCSpeed(void)
{
  newSpeed = false;
  return currentSpeed;
}

/**
 * Interrupt handler for AD-converter
 */
ISR(ADC_vect)
{
  #if NUM_AD_SAMPLES > 16
  #warning "Change data type of buffer to accomodate more than 16 samples"
  #endif
  static uint16_t buffer = 0;
  static uint8_t counter = 0;
  static bool speed = true;

  buffer += ADC;
  if(++counter >= NUM_AD_SAMPLES)
    {
      counter = 0;

      if(speed)
	{
#if NUM_AD_SAMPLES != 16
#warning "Change divisor so 1023 * NUM_AD_SAMPLES / divisor = 126"
#endif
	  uint8_t temp;
	  temp = 126 - (buffer / 129);
	  if(temp > currentSpeed + SPEED_TOLERANCE
	     || currentSpeed > temp + SPEED_TOLERANCE
	     || ( temp != currentSpeed &&
		  (  (temp == 126 && currentSpeed >= 126 - SPEED_TOLERANCE)
		     || (temp == 0 && currentSpeed <= SPEED_TOLERANCE) ) ) )
	    {
	      newSpeed = true;
	      currentSpeed = temp;
	    }
	  // switch over to battery voltage measurement mode
	  speed = false;
	  ADMUX = (ADMUX & 0xf0) | 0x0e;
	}
      else
	{
	  // switch over to speed measurement mode
	  speed = true;
	  ADMUX = (ADMUX & 0xf0) | 7;
	}
      buffer = 0;
    }

  // Start next AD conversion
  ADCSRA |= (1<<ADSC);
}
