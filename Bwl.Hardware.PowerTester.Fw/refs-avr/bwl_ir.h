#ifndef BWL_IR_H_
#define BWL_IR_H_

//должны быть реализованы
void var_delay_ms(int ms);
void ir_modulation_delay();
void ir_led_set(char state);

//вызывать
void ir_send(char data);
void ir_send_string(char* string);
void ir_send_int(int data);
void ir_send_line(char* string);

#endif /* BWL_IR_H_ */

