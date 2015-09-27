#ifndef __TWEEN_TWEENER_GROUP_H__
#define __TWEEN_TWEENER_GROUP_H__

#include "BaseTweener.h"
#include "Tweener.h"
#include <list>

namespace Aurora
{
	class TweenerGroup: public BaseTweener
	{
	public:
		void Insert( const Tweener& t );
		void Clear();
		bool Empty() const;

	private:
		TweenerGroup* DoClone() const;
		bool DoIsFinished() const;
		double DoUpdate( double dt );

	private:
		std::list<Tweener> tweeners_;

	};

} // namespace aurora

#endif // __TWEEN_TWEENER_GROUP_H__
