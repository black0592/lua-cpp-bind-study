#ifndef __TWEEN_TWEENER_SEQUENCE_H__
#define __TWEEN_TWEENER_SEQUENCE_H__

#include "BaseTweener.h"
#include "Tweener.h"
#include <list>

namespace Aurora
{
	class TweenerSequence: public BaseTweener
	{
	public:
		void Insert( const Tweener& t );
		void Clear();
		bool Empty() const;

	private:
		TweenerSequence* DoClone() const;
		bool DoIsFinished() const;
		double DoUpdate( double dt );

	private:
		std::list<Tweener> tweeners_;
	};
} // namespace aurora

#endif // __TWEEN_TWEENER_SEQUENCE_H__
