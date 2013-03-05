/*
 * BUTTONS.h
 *
 *  Created on: Feb 14, 2013
 *      Author: Evan
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_

#define P02 (!(((LPC_GPIO0 -> FIOPIN)&(1<<2)) == (1<<2)))
#define P03 (!(((LPC_GPIO0 -> FIOPIN)&(1<<3)) == (1<<3)))
#define P04 (!(((LPC_GPIO0 -> FIOPIN)&(1<<4)) == (1<<4)))
#define P05 (!(((LPC_GPIO0 -> FIOPIN)&(1<<5)) == (1<<5)))

#endif /* BUTTONS_H_ */
