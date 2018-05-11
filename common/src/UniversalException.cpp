#include "UniversalException.hpp"

namespace Common
{
	const char* UniversalException::what() const noexcept
	{
		return message_.str().c_str();
	}
}
