#include "refs-avr/bwl_adc.h"

#define ADC_ADJ ADC_ADJUST_RIGHT
#define ADC_REF ADC_REFS_INTERNAL_1_1
#define ADC_CLK ADC_PRESCALER_128

float adc_get_voltage()
{
	adc_init(4,ADC_ADJ,ADC_REF,ADC_CLK);
	float result0=adc_read_average_float(64);
	float result=result0*1.1/1024.0*69.0;
	return result;
}

float adc_get_current()
{
	adc_init(3,ADC_ADJ,ADC_REF,ADC_CLK);
	float result0=adc_read_average_float(64);
	float result=result0*1.1/1024.0/0.01;
	return result;
}