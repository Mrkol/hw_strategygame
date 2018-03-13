#include "QuadTree.hpp"
//A back-include is needed for the code editor to
//autocomplete properly

template<typename ValueType>
QuadTree<ValueType>::QuadTree(std::size_t height, std::size_t width,
	ValueType value)
	: root_(new SolidQuadrant)
{

}

template<typename ValueType>
void QuadTree<ValueType>::Set(std::size_t y, 
	std::size_t x, ValueType value)
{
	root_->Set(y, x, value);
}

template<typename ValueType>
ValueType QuadTree<ValueType>::Get(std::size_t y, 
	std::size_t x) const
{
	root_->Get(y, x);
}

template<typename ValueType>
void QuadTree<ValueType>::SetArea(std::size_t left, std::size_t top, 
	std::size_t right, std::size_t bottom, ValueType value)
{
	root_->SetArea(left, top, right, bottom, value);
}

template<typename ValueType>
bool QuadTree<ValueType>::SolidQuadrant::needsFracturing_(
	std::size_t left, std::size_t top, 
	std::size_t right, std::size_t bottom) const
{
	return left > left_ || right < right_ 
		|| top > top_ || bottom < bottom_;
}

template<typename ValueType>
bool QuadTree<ValueType>::SolidQuadrant::needsSolidifying_(
	std::size_t left, std::size_t top, 
	std::size_t right, std::size_t bottom) const
{
	return false;
}

template<typename ValueType>
QuadTree<ValueType>::SolidQuadrant::SolidQuadrant(
	std::size_t left, std::size_t top, 
	std::size_t right, std::size_t bottom, ValueType value)
	: QuadTree<ValueType>::Quadrant(left, top, right, bottom)
{
	value_ = value;
}

template<typename ValueType>
void QuadTree<ValueType>::SolidQuadrant::Set(
	std::size_t y, std::size_t x, ValueType value)
{
	value_ = value;
}

template<typename ValueType>
ValueType QuadTree<ValueType>::SolidQuadrant::Get(
	std::size_t y, std::size_t x) const
{
	return value_;
}

template<typename ValueType>
void QuadTree<ValueType>::SolidQuadrant::SetArea(
	std::size_t left, std::size_t top, 
	std::size_t right, std::size_t bottom, ValueType value)
{
	value_ = value;
}


template<typename ValueType>
bool QuadTree<ValueType>::FracturedQuadrant::needsFracturing_(
	std::size_t left, std::size_t top, 
	std::size_t right, std::size_t bottom) const
{
	return false;
}


template<typename ValueType>
bool QuadTree<ValueType>::FracturedQuadrant::needsSolidifying_(
	std::size_t left, std::size_t top, 
	std::size_t right, std::size_t bottom) const
{
	return left <= left_ && top <= top_ 
		&& right >= right_ && bottom >= bottom_;
}

template<typename ValueType>
QuadTree<ValueType>::FracturedQuadrant::FracturedQuadrant(
	std::size_t left, std::size_t top, 
	std::size_t right, std::size_t bottom, ValueType value)
	: Quadrant(left, top, right, bottom)
{
	for (int j = 0; j < 2; ++j)
	{
		for (int i = 0; i < 2; ++i)
		{
			parts_[j][i] = 
				std::make_unique<SolidQuadrant>(
					i ? (left + right) / 2 : left,
					j ? (top + bottom) / 2 : top,
					i ? right : (left + right) / 2,
					j ? bottom : (top + bottom) / 2,
					value);
		}
	}
}

template<typename ValueType>
void QuadTree<ValueType>::FracturedQuadrant::fracture_(
	std::size_t j, std::size_t i)
{
	parts_[j][i].release();

	parts_[j][i] = 
		std::make_unique<FracturedQuadrant>(
			i ? (left + right) / 2 : left,
			j ? (top + bottom) / 2 : top,
			i ? right : (left + right) / 2,
			j ? bottom : (top + bottom) / 2,
			value);
}

template<typename ValueType>
void QuadTree<ValueType>::FracturedQuadrant::solidify_(
	std::size_t j, std::size_t i)
{
	parts_[j][i].release();

	parts_[j][i] = 
		std::make_unique<SolidQuadrant>(
			i ? (left + right) / 2 : left,
			j ? (top + bottom) / 2 : top,
			i ? right : (left + right) / 2,
			j ? bottom : (top + bottom) / 2,
			value);
}

template<typename ValueType>
void QuadTree<ValueType>::FracturedQuadrant::Set(
	std::size_t y, std::size_t x, ValueType value)
{
	int i = x >= (left_ + right_)/2;
	int j = y >= (top_ + bottom_)/2;

	if (parts_[j][i].needsFracturing_(x, y, x + 1, y + 1))
		fracture_(j, i);

	parts_[j][i].Set(y, x, value);
}

template<typename ValueType>
ValueType QuadTree<ValueType>::FracturedQuadrant::Get(
	std::size_t y, std::size_t x) const
{
	return parts_[j][i].Get(y, x);
}

template<typename ValueType>
void QuadTree<ValueType>::FracturedQuadrant::SetArea(
	std::size_t left, std::size_t top, 
	std::size_t right, std::size_t bottom, ValueType value)
{
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			std::size_t l = i ? (left + right) / 2 : left;
			std::size_t u = j ? (top + bottom) / 2 : top;
			std::size_t r = i ? right : (left + right) / 2;
			std::size_t d = j ? bottom : (top + bottom) / 2;

			if (r <= l || d <= u) continue;

			if (parts_[j][i].needsSolidifying_(l, u, r, d))
				solidify_(j, i);

			parts_[j][i].SetArea(l, u, r, d, value);
		}
	}
}
