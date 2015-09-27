#ifndef __TWEEN_BASE_TWEENER_H__
#define __TWEEN_BASE_TWEENER_H__

#include <list>
#include <functional>

namespace Aurora
{
	class BaseTweener
	{
	public:
		typedef std::function<void ()> FinishCallback;

	public:
		virtual ~BaseTweener();

		BaseTweener* Clone() const;

		bool IsFinished() const;

		double Update( double dt );

		void OnFinished( FinishCallback f );

	private:
		void NotifyFinished() const;
		virtual BaseTweener* DoClone() const = 0;
		virtual bool DoIsFinished() const = 0;
		virtual double DoUpdate( double dt ) = 0;

	private:
		std::list<FinishCallback> finished_callbacks_;

	};

} // namespace aurora

#endif // __TWEEN_BASE_TWEENER_H__
