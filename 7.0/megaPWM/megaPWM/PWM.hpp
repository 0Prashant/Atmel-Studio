/*
 * PWM.h
 *
 * Created: 3/7/2018 5:10:52 PM
 *  Author: RMS
 *   email: 073bex433.rishav@gmail.com
 */ 


#ifndef PWM_H_
#define PWM_H_

//16 Bit PWM
#include <avr/pgmspace.h>

typedef uint8_t  u8;
typedef uint16_t u16;

struct PWM_Params  {
	
	volatile u8 * tccra_ ;
	volatile u8 * tccrb_ ;
	volatile u8 * tccrc_ ;
	
	volatile u8 * ocrla_ ;
	volatile u8 * ocrha_ ;
	volatile u8 * ocrlb_ ;
	volatile u8 * ocrhb_ ;
	volatile u8 * ocrlc_ ;
	volatile u8 * ocrhc_ ;

	volatile u8 * icrl_ ;
	volatile u8 * icrh_ ;

	volatile u8 * timsk_ ;
	
	template <typename T, size_t N>
	PWM_Params(const T (&arr)[N]){
		(arr);			
	}
	
	template <typename T, size_t N>
	void set_params(const T (&arr)[N]){
		
		tccra_ = (volatile u8 *)pgm_read_word(arr + 0);
		tccrb_ = (volatile u8 *)pgm_read_word(arr + 1);
		tccrc_ = (volatile u8 *)pgm_read_word(arr + 2);
		
		ocrla_ = (volatile u8 *)pgm_read_word(arr + 3);
		ocrha_ = (volatile u8 *)pgm_read_word(arr + 4);
		ocrlb_ = (volatile u8 *)pgm_read_word(arr + 5);
		ocrhb_ = (volatile u8 *)pgm_read_word(arr + 6);
		ocrlc_ = (volatile u8 *)pgm_read_word(arr + 7);
		ocrhc_ = (volatile u8 *)pgm_read_word(arr + 8);
		
		icrl_ = (volatile u8 *)pgm_read_word(arr + 9);
		icrh_ = (volatile u8 *)pgm_read_word(arr + 10);
		
		timsk_ = (volatile u8 *)pgm_read_word(arr + 11);
	}
	
			 
			
};

class FastPWM
{
public:
protected:
private:
};

// class PhaseCorrectPWM
// {
// 
// private:
// 	PWM_Params pwm;
// 	
// public:
// 
// 	PhaseCorrectPWM(volatile u8 * tccra, volatile, u8 * tccrb, volatile u8 *tccrc,
// 	volatile u8 * ocrla, volatile u8 * ocrha,
// 	volatile u8 * ocrlb, volatile u8 * ocrhb,
// 	volatile u8 * ocrlc, volatile u8 * ocrhc,
// 	volatile u8 * icrl,  volatile u8 * icrh):
// 	pwm(tccra,tccrb,tccrc,ocrla,ocrha,ocrlb,ocrhb,ocrlc,ocrhc,icrl,icrh){}
// 	
// 	void SetFreq(volatile u16 frequency);
// 	void SetDutyCycle(volatile u16 dutyCycle);
// 
// protected:
// 
// };


namespace PWM  {
	
	const u8 _1[] = {&TCCR1A, &TCCR1B, &TCCR1C, &OCR1AL, &OCR1AH, &OCR1BL, &OCR1BH, &OCR1CL, &OCR1CH, &ICR1L, &ICR1H, &TIMSK1};
	const u8 _3[] = {&TCCR3A, &TCCR3B, &TCCR3C, &OCR3AL, &OCR3AH, &OCR3BL, &OCR3BH, &OCR3CL, &OCR3CH, &ICR3L, &ICR3H, &TIMSK3};
	const u8 _4[] = {&TCCR4A, &TCCR4B, &TCCR4C, &OCR4AL, &OCR4AH, &OCR4BL, &OCR4BH, &OCR4CL, &OCR4CH, &ICR4L, &ICR4H, &TIMSK4};
	const u8 _5[] = {&TCCR5A, &TCCR5B, &TCCR5C, &OCR5AL, &OCR5AH, &OCR5BL, &OCR5BH, &OCR5CL, &OCR5CH, &ICR5L, &ICR5H, &TIMSK5};
		
}	

template <class Mode>
class HardwarePWM
{
private:
	PWM pwm_;

public:
	
	template <typename T, size_t N>
	HardwarePWM(T(&arr)[N]): pwm_(arr){}		
	
	u8 initialize() const {
		Mode::initialize(pwm_);
	}
	
	u8 dutyCycle(u16 setValue){
	
	}
	
	u8 frequency(u16 setValue){
		
	}
	

};

class CTC
{
public:
protected:
private:
};

class Fast_PWM
{
public:
protected:
private:
};

class Phase_PWM
{
public:
	u8 initialize(const PWM_Params & pwm_ ) const{
    *(pwm_.tccra_) = 		 
	}
protected:
private:
};
					
					
					
#endif /* PWM_H_ */					
					
					