/*
 * PWM_Modes.h
 *
 * Created: 3/10/2018 5:25:17 AM
 *  Author: Prashant
 */ 


#ifndef PWM_MODES_H_
#define PWM_MODES_H_

#include "PWM_Params.hpp"

class Mode
{
public:
	template<u8 channel>
	void non_inverting(const PWM_Params & pwm_ ){
		switch (channel)
		{
		case 1:
			*(pwm_.tccra_) |= _bv(PWM::comxa1);
			*(pwm_.tccra_) &= ~_bv(PWM::comxa0);
			break;
		case 2:
			*(pwm_.tccra_) |= _bv(PWM::comxb1);
			*(pwm_.tccra_) &= ~_bv(PWM::comxb0);
			break;
		case 3:
			*(pwm_.tccra_) |= _bv(PWM::comxc1);
			*(pwm_.tccra_) &= ~_bv(PWM::comxc0); 	
		}
	}
	
	template<u8 channel>	
	void inverting(const PWM_Params & pwm_ ){
		switch (channel)
		{
			case 1:
			*(pwm_.tccra_) |= _bv(PWM::comxa1) |_bv(PWM::comxa0);
			break;
			case 2:
			*(pwm_.tccra_) |= _bv(PWM::comxb1) |_bv(PWM::comxb0);
			break;
			case 3:
			*(pwm_.tccra_) |= _bv(PWM::comxc1) |_bv(PWM::comxc0);
		}
	}
	
protected:
private:
};



#endif /* PWM_MODES_H_ */