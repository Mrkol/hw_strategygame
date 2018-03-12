#pragma once

#ifndef COMMON_QUAD_TREE_HPP_
#define COMMON_QUAD_TREE_HPP_

#include <cstddef>
#include <memory>

template<typename ValueType>
class QuadTree
{
public:
	ValueType& operator()(std::size_t y, std::size_t x);

	const ValueType& operator()(std::size_t y, std::size_t x) const;		

	void SetArea(std::size_t left, std::size_t top, 
		std::size_t right, std::size_t bottom, ValueType value);

private:
	class Quadrant
	{
	private:
		std::size_t left_;
		std::size_t right_;
		std::size_t top_;
		std::size_t bottom_;

		bool solid_;
	public:
		Quadrant(std::size_t left, std::size_t top, 
			std::size_t right, std::size_t bottom);

		virtual ValueType& operator()(std::size_t y, 
			std::size_t x) = 0;
		
		virtual const ValueType& operator()(std::size_t y, 
			std::size_t x) const = 0;
		
		virtual void SetArea(std::size_t left, std::size_t top, 
			std::size_t right, std::size_t bottom, ValueType value);
	};

	class SolidQuadrant : Quadrant
	{
	private:
		ValueType value_;

	public:
		SolidQuadrant(std::size_t left, std::size_t top, 
			std::size_t right, std::size_t bottom, ValueType value);

		virtual ValueType& operator()(std::size_t y, 
			std::size_t x) override;

		virtual const ValueType& operator()(std::size_t y, 
			std::size_t x) const override;
		
		virtual void SetArea(std::size_t left, std::size_t top, 
			std::size_t right, std::size_t bottom, ValueType value) override;
	};

	class FracturedQuadrant : Quadrant
	{
	private:
		std::unique_ptr<Quadrant> parts_[2][2];

	public:
		FracturedQuadrant(std::size_t left, std::size_t top, 
			std::size_t right, std::size_t bottom, ValueType value);

		virtual ValueType& operator()(std::size_t y, 
			std::size_t x) override;

		virtual const ValueType& operator()(std::size_t y, 
			std::size_t x) const override;
		
		virtual void SetArea(std::size_t left, std::size_t top, 
			std::size_t right, std::size_t bottom, ValueType value) override;
	};
};


#endif // COMMON_QUAD_TREE_HPP_
