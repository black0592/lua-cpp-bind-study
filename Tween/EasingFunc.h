#ifndef __TWEEN_SYMMETRIC_EASING_H__
#define __TWEEN_SYMMETRIC_EASING_H__

namespace Aurora
{
	template<double (*Function)(double)>
	class EaseFunctor
	{
	public:
		inline static double EaseIn( double t );
		inline static double EaseOut( double t );
		inline static double EaseInOut( double t );
	};

	class EaseNone
	{
	public:
		static double EaseIn( double t );
		static double EaseOut( double t );
		static double EaseInOut( double t );
	};

	double easing_back_func( double t );
	double easing_bounce_func( double t );
	double easing_circ_func( double t );
	double easing_cubic_func( double t );
	double easing_elastic_func( double t );
	double easing_expo_func( double t );
	double easing_linear_func( double t );
	double easing_quad_func( double t );
	double easing_quart_func( double t );
	double easing_quint_func( double t );
	double easing_sine_func( double t );

	typedef EaseFunctor<easing_back_func>		EasingBack;
	typedef EaseFunctor<easing_bounce_func>		EasingBounce;
	typedef EaseFunctor<easing_circ_func>		EasingCirc;
	typedef EaseFunctor<easing_cubic_func>		EasingCubic;
	typedef EaseFunctor<easing_elastic_func>	EasingElastic;
	typedef EaseFunctor<easing_expo_func>		EasingExpo;
	typedef EaseFunctor<easing_linear_func>		EasingLinear;
	typedef EaseFunctor<easing_quad_func>		EasingQuad;
	typedef EaseFunctor<easing_quart_func>		EasingQuart;
	typedef EaseFunctor<easing_quint_func>		EasingQuint;
	typedef EaseFunctor<easing_sine_func>		EasingSine;


} // namespace aurora

#include "EasingFunc.inl"

#endif // __TWEEN_SYMMETRIC_EASING_H__
