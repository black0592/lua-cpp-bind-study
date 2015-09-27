#include "TweenerSequence.h"

namespace Aurora
{

	void TweenerSequence::Insert( const Tweener& t )
	{
		tweeners_.push_back(t);
	}

	void TweenerSequence::Clear()
	{
		tweeners_.clear();
	}

	TweenerSequence* TweenerSequence::DoClone() const
	{
		return new TweenerSequence(*this);
	}

	bool TweenerSequence::DoIsFinished() const
	{
		return tweeners_.empty();
	}

	double TweenerSequence::DoUpdate( double dt )
	{
		double result(dt);

		while ( (result != 0) && !tweeners_.empty() )
		{
			result = tweeners_.front().Update(result);

			if ( tweeners_.front().IsFinished() )
				tweeners_.pop_front();
		}

		return result;
	}

	bool TweenerSequence::Empty() const
	{
		return tweeners_.empty();
	}
}

