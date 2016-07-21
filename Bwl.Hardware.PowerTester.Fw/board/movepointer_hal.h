#ifndef MOVEPOINTER_HAL_H_
#define MOVEPOINTER_HAL_H_

void motor_horizontal_move(int distance, int stopdistanse)
{
	setbit(DDRB,5,1);
	setbit(DDRB,4,1);
	if (distance>0)
	{
		setbit(PORTB,5,1);
		setbit(PORTB,4,0);
		var_delay_ms(distance);
		setbit(PORTB,5,0);
		setbit(PORTB,4,1);
		var_delay_ms(stopdistanse);
	}else
	{
		setbit(PORTB,5,0);
		setbit(PORTB,4,1);
		var_delay_ms(-distance);
		setbit(PORTB,5,1);
		setbit(PORTB,4,0);
		var_delay_ms(stopdistanse);
	}
	setbit(PORTB,5,0);
	setbit(PORTB,4,0);
}

void motor_vertical_move(int distance, int stopdistanse)
{
	setbit(DDRH,5,1);
	setbit(DDRH,6,1);
	if (distance>0)
	{
		setbit(PORTH,5,0);
		setbit(PORTH,6,1);
		var_delay_ms(distance);
		setbit(PORTH,5,1);
		setbit(PORTH,6,0);
		var_delay_ms(stopdistanse);
	}else
	{
		setbit(PORTH,5,1);
		setbit(PORTH,6,0);
		var_delay_ms(-distance);
		setbit(PORTH,5,0);
		setbit(PORTH,6,1);
		var_delay_ms(stopdistanse);
	}
	setbit(PORTH,5,0);
	setbit(PORTH,6,0);
}

void pointer_laser(char state)
{
	setbit(DDRB,6,1);
	setbit(PORTB,6,state);
}

#endif /* MOVEPOINTER_HAL_H_ */