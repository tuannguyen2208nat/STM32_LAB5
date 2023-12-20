/*
 * soft_ware_timer.c
 *
 *  Created on: Dec 20, 2023
 *      Author: tuann
 */


#include "software_timer.h"

int timer1_flag=0;
int timer1_counter;
int timer2_flag=0;
int timer2_counter;

void settimer1(int duration)
{
	timer1_flag=0;
	timer1_counter=duration;
}

void settimer2(int duration)
{
	timer2_flag=0;
	timer2_counter=duration;
}

void timerrun()
{
	if(timer1_counter>0)
	{
		timer1_counter--;
	}
	if(timer1_counter<=0)
	{
		timer1_flag=1;
	}

	if(timer2_counter>0)
	{
		timer2_counter--;
	}
	if(timer2_counter<=0)
	{
		timer2_flag=1;
	}
}
