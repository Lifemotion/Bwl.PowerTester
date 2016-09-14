
void set_relay(int relay_code)
{
	if (relay_code<0) {relay_code=0;}
	setbit(DDRB,6,1);setbit(PORTB,6,relay_code&1);//200
	setbit(DDRB,3,1);setbit(PORTB,3,relay_code&2);//100
	setbit(DDRB,0,1);setbit(PORTB,0,relay_code&4);//62
	setbit(DDRD,6,1);setbit(PORTD,6,relay_code&8);//32
	setbit(DDRB,7,1);setbit(PORTB,7,relay_code&16);//16
	setbit(DDRB,5,1);setbit(PORTB,5,relay_code&32);//10
	setbit(DDRB,4,1);setbit(PORTB,4,relay_code&64);//4.7
	setbit(DDRB,2,1);setbit(PORTB,2,relay_code&128);//2
	setbit(DDRB,1,1);setbit(PORTB,1,relay_code&256);//1
}

float relay_get_resistance(int relay_code)
{
	float rev_sum=0.0;
	if (relay_code&1) {rev_sum+=1.0/214.1;}
	if (relay_code&2) {rev_sum+=1.0/147.1;}
	if (relay_code&4) {rev_sum+=1.0/67.1;}
	if (relay_code&8) {rev_sum+=1.0/30.6;}
	if (relay_code&16) {rev_sum+=1.0/12.1;}
	if (relay_code&32) {rev_sum+=1.0/8.2;}
	if (relay_code&64) {rev_sum+=1.0/3.9;}
	if (relay_code&128) {rev_sum+=1.0/2.0;}
	if (relay_code&256) {rev_sum+=1.0/1.0;}
	if (rev_sum==0.0)
	{
		return -1;
	}else
	{
		float resistance= 1.0/rev_sum;
		return resistance;
	}
}
