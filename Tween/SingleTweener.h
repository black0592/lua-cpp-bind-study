#ifndef __TWEEN_SINGLE_TWEENER_H__
#define __TWEEN_SINGLE_TWEENER_H__

#include "BaseTweener.h"
#include "EasingFunc.h"

namespace Aurora
{
  class SingleTweener: public BaseTweener
    {
    public:
      typedef std::function<void (double)> UpdateFunction;
      typedef std::function<double (double)> EasingFunction;

    public:
      SingleTweener();
      SingleTweener( double init, double end, double duration, UpdateFunction callback, EasingFunction e );
      SingleTweener( double& val, double end, double duration, EasingFunction e );

      double GetInitValue() const;
      void SetInitValue( double v );

      double GetEndValue() const;
      void SetEndValue( double v );

      double GetDuration() const;
      void SetDuration( double v );

      void SetUpdateCallback( UpdateFunction f );
      void SetEasingCallback( EasingFunction f );

      double GetValue() const;

    private:
      SingleTweener* DoClone() const;
      bool DoIsFinished() const;
      double DoUpdate( double dt );

    private:
      double init_value_;		// The initial value
      double end_value_;			// The final value
      double date_;		// The current date in the timeline of the single_tweener
      double duration_;	// The total duration of the single_tweener

      UpdateFunction update_callback_;
      EasingFunction easing_callback_;
      
    }; // class single_tweener

} // namespace aurora

#endif // __TWEEN_SINGLE_TWEENER_H__
