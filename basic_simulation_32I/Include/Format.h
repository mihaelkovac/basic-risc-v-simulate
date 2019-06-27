#ifndef FORMAT_H
#define FORMAT_H

#include <functional>
#include <type_traits>
#include <unordered_map>
#include <array>

#include "Registers.h"
#include "Memory.h"
#include "Include/BinaryUtils.h"
#include "Utilities.h"

#define KEY_R32 FNV32("R32")
#define KEY_I32 FNV32("I32")
#define KEY_S32 FNV32("S32")
#define KEY_B32 FNV32("B32")
#define KEY_U32 FNV32("U32")
#define KEY_J32 FNV32("J32")

namespace risc
{
	
	
	template<uint32_t FormatKey>
	struct FormatFunctionHash;
	
	template<typename InstructionKeyType, typename Function, uint32_t FormatKey, int InstructionSize>
	struct Format
	{
		enum 
		{
			size = InstructionSize,
			format_key = FormatKey
		};
		
		constexpr Format() = default;
		
		Function function(const InstructionKeyType& key) const
		{
			return functions.at(key);
		}
		
		
		using key_type = InstructionKeyType;
		using Hash = FormatFunctionHash<FormatKey>;
		
		const Hash hash{};
		
		protected:
			using function_map = std::unordered_map<InstructionKeyType, Function>;
			
			function_map functions{};
			
			virtual void init_functions() = 0;
			
			template<unsigned int N>
			static constexpr auto make_opcodes(int (&&opcodes)[N])
			{
				return make_opcodes_impl(std::move(opcodes), std::make_index_sequence<N>{});
			}
			
			template<unsigned int N, std::size_t ... I>
			static constexpr auto make_opcodes_impl(int (&&opcodes)[N], std::index_sequence<I...>)
			{
				return std::array<int, N>{std::move(opcodes[I])...};
			}
			
	};
	
	template<uint32_t FormatKey, typename ... Args>
	using Format32Base = Format<int, std::function<void(Args..., Memory&, Registers<int>&)>, FormatKey, 32>;
	
	
	template<typename FormatClass>
	struct ExtendedFormat : public FormatClass
	{
		using Super = FormatClass;
		
		enum
		{
			size = FormatClass::size,
			format_key = FormatClass::format_key	
		};
		
		constexpr ExtendedFormat() = default;
		
		protected:
			
			virtual void extend_functions() = 0;
			
			void init_functions() override
			{
				Super::init_functions();
				this->extend_functions();
			}
			
			template<unsigned int N>
			static constexpr auto extend_opcodes(int (&&opcodes)[N])
			{
				using Array = decltype(Super::opcodes);
				return extend_opcodes_impl(std::move(Super::opcodes), opcodes, std::make_index_sequence<std::tuple_size<Array>::value>{}, std::make_index_sequence<N>{});
			}
		
		private:
			template<typename Array,unsigned int N, std::size_t ... ArrayIs, std::size_t ... OpcodeIs>
			static constexpr auto extend_opcodes_impl(Array&& array, int (&opcodes)[N], std::index_sequence<ArrayIs...>, std::index_sequence<OpcodeIs...>)
			{
				return std::array<int, N + sizeof...(ArrayIs)>{std::move(array[ArrayIs])..., std::move(opcodes[OpcodeIs])...};
			}
	};
	
	
}
#endif
