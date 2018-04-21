#include "UniversalException.hpp"

namespace Common
{
	template<class T>
	void UniversalException::Append(const T& t) const
	{
		message_ << t;
	}
}
