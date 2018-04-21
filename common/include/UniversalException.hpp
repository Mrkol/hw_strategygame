#pragma once

#ifndef COMMON_UNIVERSAL_EXCEPTION_HPP_
#define COMMON_UNIVERSAL_EXCEPTION_HPP_

#include <exception>
#include <sstream>
#include <type_traits>

namespace Common
{
	class UniversalException : public std::exception
	{
	public:
		const char* what() const noexcept override;

		template<class T>
		void Append(const T& t) const;

	private:
		mutable std::stringstream message_;
	};

	template <class E, class T>
	std::enable_if_t<std::is_same<UniversalException, std::remove_cv_t<std::remove_reference_t<E>>>::value, E&&> 
		operator<<(E&& e, const T& t)
	{
		e.Append(t);

		return std::forward<E>(e);
	}
}

#include "UniversalException.tpp"
#endif //COMMON_UNIVERSAL_EXCEPTION_HPP_
