#include "TweenerGroup.h"

namespace Aurora
{

	void TweenerGroup::Insert( const Tweener& t )
	{
		tweeners_.push_back(t);
	}

	void TweenerGroup::Clear()
	{
		tweeners_.clear();
	} 

	TweenerGroup* TweenerGroup::DoClone() const
	{
		return new TweenerGroup(*this);
	}

	bool TweenerGroup::DoIsFinished() const
	{
		return tweeners_.empty();
	} 

	double TweenerGroup::DoUpdate( double dt )
	{
		typedef std::list<Tweener>::iterator iterator_type;
		double result(dt);

		iterator_type it = tweeners_.begin();

		while ( it != tweeners_.end() )
		{
			const double r = it->Update(dt);
			result = std::min(result, r);

			if ( it->IsFinished() )
			{
				const iterator_type tmp(it);
				++it;
				tweeners_.erase(tmp);
			}
			else
				++it;
		}

		return result;
	}

	bool TweenerGroup::Empty() const
	{
		return tweeners_.empty();
	} 
}

