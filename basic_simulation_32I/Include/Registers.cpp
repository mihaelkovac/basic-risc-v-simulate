#include "Registers.h"

#include <stdexcept>

//namespace risc
//{
//	template<typename T>
//	std::size_t& Registers<T>::pc() 
//	{
//		return pc_;
//	}
//	
//	template<typename T>
//	void Registers<T>::set_pc(std::size_t value)
//	{
//		if(value < 0) throw std::runtime_error("Cannot set the pc register to a negative value");
//		this->pc_ = value + (value % 4);
//	}
//	
//	template<typename T>
//	void Registers<T>::add_to_pc(long value)
//	{
//		if(value < 0 && (value < -pc)) throw std::runtime_error("Cannot add to the pc a negative value that would set it below 0");
//		this->pc_ += value + (value % 4);
//	}
//	
//	template<typename T>
//	typename Registers<T>::reg_deref Registers<T>::operator[](int index)
//	{
//		return {*this, index};
//	}
//	
//	template<typename T>
//	void Registers<T>::set_x(int index, T value)
//	{
//		if(!index) return;
//		this->x[index] = value;
//	}
//}
