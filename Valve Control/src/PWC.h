/*
 * PWC.h
 *
 *  Created on: Feb 20, 2013
 *      Author: Evan
 */

#ifndef PWC_H_
#define PWC_H_

#define P010 (!(((LPC_GPIO0 -> FIOPIN)&(1<<10)) == (1<<10)))
#define P011 (!(((LPC_GPIO0 -> FIOPIN)&(1<<11)) == (1<<11)))
#define P012 (!(((LPC_GPIO0 -> FIOPIN)&(1<<12)) == (1<<12)))
#define P013 (!(((LPC_GPIO0 -> FIOPIN)&(1<<13)) == (1<<13)))

#endif /* PWC_H_ */
