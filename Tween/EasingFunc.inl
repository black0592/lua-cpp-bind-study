
namespace Aurora
{

	template<double (*Function)(double)>
	inline double EaseFunctor<Function>::EaseIn( double t )
	{
		return Function(t);
	}

	template<double (*Function)(double)>
	inline double EaseFunctor<Function>::EaseOut( double t )
	{
		return 1 - EaseIn( 1 - t );
	}

	template<double (*Function)(double)>
	inline double EaseFunctor<Function>::EaseInOut( double t )
	{
		if ( t < 0.5 )
			return EaseIn( 2 * t ) * 0.5;
		else
			return 0.5 + EaseOut( 2 * t - 1 ) * 0.5;
	} 

}