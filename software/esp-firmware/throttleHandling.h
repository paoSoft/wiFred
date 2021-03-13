/**
 * This file is part of the wiFred wireless model railroading throttle project
 * Copyright (C) 2018-2021 Heiko Rosemann
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
 * This file handles reading in keys and pushbuttons as well as setting LEDs
 * and reading in the speed potentiometer
 */

#ifndef _THROTTLE_HANDLING_H_
#define _THROTTLE_HANDLING_H_

#define LED_STOP 14
#define LED_FWD 39
#define LED_REV 15
#define FLASHLIGHT 33

enum keys { KEY_F0, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8,
            KEY_ESTOP, KEY_SHIFT, KEY_FWD, KEY_REV,
            KEY_LOCO1, KEY_LOCO2, KEY_LOCO3, KEY_LOCO4 };

const int KEY_PIN[] = { 3, 11, 4, 37, 12, 5, 38, 13, 6,
            10, 40, 36, 16,
            34, 35, 2, 1 };

/**
 * Potentiometer value for zero speed (counterclockwise limit)
 */
extern unsigned int potiMin;

/**
 * Potentiometer value for max speed (clockwise limit)
 */
extern unsigned int potiMax;

/**
 * Battery voltage readout factor
 * Multiply readout by this value to correct it
 */
extern float battFactor;

/**
 * Change LED settings
 */
void setLEDvalues(String ledFwd, String ledRev, String ledStop);

/**
 * Periodically check for new key settings
 */
void handleThrottle(void);

/**
 * Initialize key settings and LED timer settings
 */
void initThrottle(void);

/**
 * Get state of input buttons
 * 
 * @param the key to query
 * @return true if input button is pressed (pin value is low)
 */
bool getInputState(keys key);

/**
 * Get input state changes from input button
 * 
 * @param the key to query
 * @returns true if button has been pressed since last call
 */
bool getInputPressed(keys key);

#endif
