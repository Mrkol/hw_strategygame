#pragma once

#ifndef COMMON_QUAD_TREE_HPP_
#define COMMON_QUAD_TREE_HPP_

#include <cstddef>
#include <memory>

template<typename ValueType>
class QuadTree
{
public:
	QuadTree(std::size_t height, std::size_t width, 
		ValueType defaultValue = ValueType());

	void Set(std::size_t y, 
		std::size_t x, ValueType value);
	
	ValueType Get(std::size_t y, 
		std::size_t x) const;

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

		virtual bool needsFracturing_(std::size_t left, std::size_t top, 
			std::size_t right, std::size_t bottom) const = 0;

		virtual bool needsSolidifying_(std::size_t left, std::size_t top, 
			std::size_t right, std::size_t bottom) const = 0;

	public:
		Quadrant(std::size_t left, std::size_t top, 
			std::size_t right, std::size_t bottom);

		virtual void Set(std::size_t y, 
			std::size_t x, ValueType value) = 0;
		
		virtual ValueType Get(std::size_t y, 
			std::size_t x) const = 0;
		
		virtual void SetArea(std::size_t left, std::size_t top, 
			std::size_t right, std::size_t bottom, ValueType value);
	};

	class SolidQuadrant : Quadrant
	{
	private:
		ValueType value_;

		virtual bool needsFracturing_(std::size_t left, std::size_t top, 
			std::size_t right, std::size_t bottom) const override;

		virtual bool needsSolidifying_(std::size_t left, std::size_t top, 
			std::size_t right, std::size_t bottom) const override;
	public:
		SolidQuadrant(std::size_t left, std::size_t top, 
			std::size_t right, std::size_t bottom, ValueType value);

		virtual void Set(std::size_t y, 
			std::size_t x, ValueType value) override;

		virtual ValueType Get(std::size_t y, 
			std::size_t x) const override;
		
		virtual void SetArea(std::size_t left, std::size_t top, 
			std::size_t right, std::size_t bottom, ValueType value) override;
	};

	class FracturedQuadrant : Quadrant
	{
	private:
		std::unique_ptr<Quadrant> parts_[2][2];

		virtual bool needsFracturing_(std::size_t left, std::size_t top, 
			std::size_t right, std::size_t bottom) const override;

		virtual bool needsSolidifying_(std::size_t left, std::size_t top, 
			std::size_t right, std::size_t bottom) const override;

		void fracture_(std::size_t j, std::size_t i);
		void solidify_(std::size_t j, std::size_t i);

	public:
		FracturedQuadrant(std::size_t left, std::size_t top, 
			std::size_t right, std::size_t bottom, ValueType value);

		virtual void Set(std::size_t y, 
			std::size_t x, ValueType value) override;

		virtual ValueType Get(std::size_t y, 
			std::size_t x) const override;
		
		virtual void SetArea(std::size_t left, std::size_t top, 
			std::size_t right, std::size_t bottom, ValueType value) override;
	};

	std::unique_ptr<Quadrant> root_;
};

#include "QuadTree.tpp"
#endif // COMMON_QUAD_TREE_HPP_
