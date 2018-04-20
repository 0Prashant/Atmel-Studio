/*
 * PWM.h
 *
 * Created: 3/7/2018 5:10:52 PM
 *  Author: RMS
 *   email: 073bex433.rishav@gmail.com
 */ 


#ifndef PWM_H_
#define PWM_H_

#include "basics/AVR.hpp"
#include "PWM_Params.hpp"
#include "PWM_Modes.hpp"

class CTC
{
	public:
	template <u8 channel>
	void set_duty_cycle(const PWM_Params & pwm_ , const u16 duty_cycle){
		/*static_assert(channel == 0, "DutyCycle is 50% by default for CTC mode.");*/
	}
	protected:
	private:
};


template <class PWM_Type>
class HardwarePWM : public PWM_Type
{
private:
	PWM_Params pwm_;

public:
	
	template <typename T, size_t N>
	HardwarePWM(T(&arr)[N]): pwm_(arr){}		
	
	void initialize() const {
		PWM_Type::initialize(pwm_);
	}
	
	void set_prescale(u16 value){
		PWM_Type::set_prescale(pwm_, value);
	}
	 
	template <u8 channel>
	void set_duty_cycle(const u16 duty_cycle){
		PWM_Type::template set_duty_cycle<channel>(pwm_, duty_cycle);
	}
 	
	void set_frequency(u16 freq){
		PWM_Type::set_frequency(pwm_, freq);
	}
	
	template <u8 channel>
	void inverting(){
		PWM_Type::inverting<channel>(pwm_);
	}
	
	
};


					
					
					
#endif /* PWM_H_ */					
					
								