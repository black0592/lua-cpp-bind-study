
#ifndef __TWEEN_TWEENER_H__
#define __TWEEN_TWEENER_H__

#include <algorithm>
#include <functional>

namespace Aurora
{
	class BaseTweener;

	class Tweener
	{
	public:
		typedef std::function<void ()> finish_callback;

	public:
		Tweener();
		Tweener( const Tweener& that );
		Tweener( const BaseTweener& that );
		~Tweener();

		Tweener& operator=( const Tweener& that );

		void Swap( Tweener& that ) /*throw()*/;
		bool IsFinished() const;
		double Update( double dt );
		void OnFinished( finish_callback f );

	private:
		BaseTweener* impl_;
	};
} // namespace aurora

namespace std
{
  template<>
  void swap( Aurora::Tweener& a, Aurora::Tweener& b );
} // namespace std

#endif // __TWEEN_TWEENER_H__
