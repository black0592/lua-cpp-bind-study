#include "Tweener.h"
#include "BaseTweener.h"

namespace Aurora
{

	Tweener::Tweener() : impl_(NULL)
	{

	}

	Tweener::Tweener( const Tweener& that )
		: impl_( that.impl_ == NULL ? NULL : that.impl_->Clone() )
	{

	}

	Tweener::Tweener( const BaseTweener& that )
		: impl_( that.Clone() )
	{

	}

	Tweener::~Tweener()
	{
		delete impl_;
	} 

	Tweener& Tweener::operator=( const Tweener& that )
	{
		Tweener tmp(that);
		Swap(tmp);
		return *this;
	}

	void Tweener::Swap( Tweener& that )/* throw()*/
	{
		std::swap(impl_, that.impl_);
	} 

	bool Tweener::IsFinished() const
	{
		if ( impl_ == NULL )
			return true;
		else
			return impl_->IsFinished();
	} 

	double Tweener::Update( double dt )
	{
		if ( impl_ == NULL )
			return dt;
		else
			return impl_->Update(dt);
	} 

	void Tweener::OnFinished( finish_callback f )
	{
		if ( impl_ != NULL )
			impl_->OnFinished(f);
	} 
}


template<>
void std::swap( Aurora::Tweener& a, Aurora::Tweener& b )
{
  a.Swap(b);
} // std::swap()
