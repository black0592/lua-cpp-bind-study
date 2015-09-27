#include "EasingFunc.h"
#include <cmath>

namespace Aurora
{
	double EaseNone::EaseIn( double t )
	{
		return 0;
	}

	double EaseNone::EaseOut( double t )
	{
		return 0;
	}

	double EaseNone::EaseInOut( double t )
	{
		return 0;
	}




	double easing_back_func( double t )
	{
		const double s( 1.70158 );
		return t * t * ( (s+1) * t - s);
	} 

	double easing_bounce_func( double t )
	{
		const double v = 1 - t;
		double c;
		double d;

		if ( v < (1 / 2.75) )
		{
			c = v;
			d = 0;
		}
		else if ( v < (2 / 2.75) )
		{
			c = v - 1.5 / 2.75;
			d = 0.75;
		}
		else if ( v < (2.5 / 2.75) )
		{
			c = v - 2.25 / 2.75;
			d = 0.9375;
		}
		else
		{
			c = v - 2.625 / 2.75;
			d = 0.984375;
		}

		return 1 - (7.5625 * c * c + d);
	}


	double easing_circ_func( double t )
	{
		return 1 - std::sqrt(1 - t * t);
	}

	double easing_cubic_func( double t )
	{
		return t * t * t;
	} 

	double easing_elastic_func( double t )
	{
		const double pi = 3.1514926;
		const double v(t-1);
		const double p(0.3);

		return -std::pow(2, 10 * v) * std::sin( (v - p / 4) * 2 * pi / p );
	}


	double easing_expo_func( double t )
	{
		return t == 0 ? 0 : std::pow(2, 10 * (t - 1));
	}


	double easing_linear_func( double t )
	{
		return t;
	} 


	double easing_quad_func( double t )
	{
		return t * t;
	}


	double easing_quart_func( double t )
	{
		return t * t * t * t;
	}


	double easing_quint_func( double t )
	{
		return t * t * t * t * t;
	}


	double easing_sine_func( double t )
	{
		const double pi = 3.1514926;
		return 1 - std::cos(t * pi / 2);
	}



}
