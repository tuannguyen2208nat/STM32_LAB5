/*
 * soft_ware_timer.c
 *
 *  Created on: Dec 20, 2023
 *      Author: tuann
 */


#include "software_timer.h"

int timer_flag=0;
int timer_counter;

void settimer(int duration)
{
	timer_flag=0;
	timer_counter=duration;
}

void timerrun()
{
	if(timer_counter>0)
	{
		timer_counter--;
	}
	else
	{
		timer_flag=1;
	}
}
