/*
 * Complementary_Filter.h
 *
 * Created: 2/19/2018 7:32:50 PM
 *  Author: Sherlock
 */


#ifndef COMPLEMENTARY_FILTER_H_
#define COMPLEMENTARY_FILTER_H_

#define dt 0.005	// Set  sample time
class complementaryFilter
{
	private:
	float alpha;	    // Tuning parameter
	float angle;	    // Angle (roll, pitch)
	int orderOfFilter;
	public:
	complementaryFilter(int selectOrderOfFilter)
	{
		orderOfFilter = selectOrderOfFilter;
		if (orderOfFilter == 1)
		{
			alpha = 0.98;
			angle = 0;
		}
		else
		{
			alpha = 10;
			angle = 0;
		}
		

	}
	float getAngle(float accelAngle, float gyroRate);  // To get angle from filter
	void setAngle(float newAngle);			   // To set angle
	void setTuneParameter(float newAlpha);             // To tune tuning parameter -> ?
};

float complementaryFilter::getAngle(float accelAngle, float gyroRate)
{
	if (orderOfFilter==1){

		angle = alpha*(angle + gyroRate*dt) + (1-alpha)*accelAngle;
		return angle;
	}

	else
	{       float x1=0.0,y1=0.0,x2=0.0;
		x1 = (accelAngle - angle)*alpha*alpha;
		y1 = dt*x1 + y1;
		x2 = y1 + (accelAngle - angle)*2*alpha + gyroRate;
		angle = dt*x2 + angle;
		return angle;
	}

}

void complementaryFilter::setAngle(float newAngle)
{
	angle = newAngle;
}

void complementaryFilter::setTuneParameter(float newAlpha)
{
	alpha = newAlpha;
}


#endif /* COMPLEMENTARY_FILTER_H_ */

// Algorithm implementation source : http://robottini.altervista.org/kalman-filter-vs-complementary-filter