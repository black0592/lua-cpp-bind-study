#include "BaseTweener.h"
#include <assert.h>

namespace Aurora
{

	BaseTweener::~BaseTweener()
	{

	} 

	BaseTweener* BaseTweener::Clone() const
	{
		return DoClone();
	} 

	bool BaseTweener::IsFinished() const
	{
		return DoIsFinished();
	}

	double BaseTweener::Update( double dt )
	{
		assert( dt >= 0 );

		const double result = DoUpdate(dt);

		if ( IsFinished() )
			NotifyFinished();

		assert( result <= dt );
		assert( result >= 0 );

		return result;
	} 

	void BaseTweener::OnFinished( FinishCallback f )
	{
		finished_callbacks_.push_back(f);
	}

	void BaseTweener::NotifyFinished() const
	{
		// If one of the callbacks deletes the tweener, then m_on_finished will not be
		// available. Since we still want to execute all the callbacks, we iterate on
		// a copy of it.
		const std::list<FinishCallback> callbacks(finished_callbacks_);

		for ( auto it=callbacks.begin(); it!=callbacks.end(); ++it )
			(*it)();
	}
}

