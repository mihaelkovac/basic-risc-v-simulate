#ifndef REGISTERS_H
#define REGISTERS_H

#include <type_traits>
#include <array>

namespace risc
{
	
	template<typename T>
	struct Registers
	{
		static_assert(std::is_integral<T>::value, "The template parameter of Registers has to be an integral type\n");
		
		std::size_t& pc()
		{
			return pc_;
		}
		
		void set_pc(std::size_t value)
		{
			if(value < 0) throw std::runtime_error("Cannot set the pc register to a negative value");
			this->pc_ = value + (value % 4);
		}
		
		void add_to_pc(long value)
		{
			if((pc_ + value) < 0) throw std::runtime_error("Cannot add to the pc a negative value that would set it below 0");
			this->pc_ += value + (value % 4);
		}
		
		
		struct reg_deref
		{
			reg_deref& operator=(T value)
			{
				regs.set_x(index, value);
				return *this;
			}
			operator T()
			{
				return regs.x[index];
			}
			reg_deref(Registers& rs, int i) : regs(rs), index(i) { }
			
			private:
				Registers& regs;
				int index;
		};
		
		reg_deref operator[](int index)
		{
			return {*this, index};
		}
		
		int size() const noexcept
		{
			return x.size();
		}
		
		constexpr Registers() = default;
		Registers(Registers<T>&& registers) : x(std::move(registers.x)), pc_(registers.pc_)
		{
			registers.pc_ = 0;
		}
		
		private:
			std::array<T, 32> x{0};
			std::size_t pc_ = 0;
		
			void set_x(int index, T value)
			{
				if(!index) return;
				this->x[index] = value;
			}
	};
	
	//Add misaligned exception !!

	
}
#endif
