
#include "SingleTweener.h"
#include <algorithm>

static void local_set_value( double& a, const double& b )
{
  a = b;
}

namespace Aurora
{
	
	SingleTweener::SingleTweener() : date_(0), easing_callback_( EaseNone::EaseInOut )
	{

	} 

	/**
	 * \brief Constructor.
	 * \param init The initial value.
	 * \param end The final value.
	 * \param duration The total duration.
	 * \param callback The function called when the single_tweener is updated.
	 * \param e The function used to compute the new value.
	 */
	SingleTweener::SingleTweener( double init, double end, double duration, UpdateFunction callback, EasingFunction e )
	  : init_value_(init), end_value_(end), date_(0), duration_(duration), update_callback_(callback), easing_callback_(e)
	{

	} 

	/**
	 * \brief Constructor.
	 * \param val The value to tween (and to use as the The initial value).
	 * \param end The final value.
	 * \param duration The total duration.
	 * \param e The function used to compute the new value.
	 */
	SingleTweener::SingleTweener( double& val, double end, double duration, EasingFunction e )
	  : init_value_(val), end_value_(end), date_(0), duration_(duration), easing_callback_(e)
	{
		update_callback_ = std::bind(&local_set_value, std::ref(val), std::placeholders::_1);
	}

	double SingleTweener::GetInitValue() const
	{
	  return init_value_;
	}

	void SingleTweener::SetInitValue( double v )
	{
	  init_value_ = v;
	}

	double SingleTweener::GetEndValue() const
	{
	  return end_value_;
	}

	void SingleTweener::SetEndValue( double v )
	{
	  end_value_ = v;
	}

	double SingleTweener::GetDuration() const
	{
	  return duration_;
	} 

	void SingleTweener::SetDuration( double v )
	{
	  duration_ = v;
	}

	void SingleTweener::SetUpdateCallback( UpdateFunction f )
	{
	  update_callback_ = f;
	}

	void SingleTweener::SetEasingCallback( EasingFunction f )
	{
	  easing_callback_ = f;
	}

	double SingleTweener::GetValue() const
	{
	  const double coeff = easing_callback_( date_ / duration_ );
	  return init_value_ + coeff * (end_value_ - init_value_);
	}

	SingleTweener* SingleTweener::DoClone() const
	{
	  return new SingleTweener(*this);
	}

	bool SingleTweener::DoIsFinished() const
	{
	  return date_ >= duration_;
	}

	double SingleTweener::DoUpdate( double dt )
	{
	  const double t( std::min(duration_ - date_, dt) );
	  const double result = dt - t;
	  date_ += t;

	  const double val( GetValue() );

	  update_callback_(val);

	  return result;
	}

}
