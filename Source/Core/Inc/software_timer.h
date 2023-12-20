/*
 * software_timer.h
 *
 *  Created on: Dec 20, 2023
 *      Author: tuann
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

extern int timer1_flag;
extern int timer2_flag;

void settimer1(int duration);
void settimer2(int duration);
void timerrun();

#endif /* INC_SOFTWARE_TIMER_H_ */
