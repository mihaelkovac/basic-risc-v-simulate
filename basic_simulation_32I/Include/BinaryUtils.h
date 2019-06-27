#ifndef BINARYUTILS_H
#define BINARYUTILS_H

namespace risc
{
	
	enum Binary
	{
		B11111111 = 255,
		B01111111 = 127,
		B00111111 = 63,
		B00011111 = 31,
		B00001111 = 15,
		B00000111 = 7,
		B00000011 = 3,
		B00000001 = 1,
		B00000000 = 0,
		B11111110 = 254,
		B11111100 = 252,
		B11111000 = 248,
		B11110000 = 240,
		B11100000 = 224,
		B11000000 = 172,
		B10000000 = 128
	};
	
	struct BinaryUtils
	{
		BinaryUtils() = delete;
		
		static constexpr int binary_to_int(char * bin, const int value = 0)
		{
			return bin[0] == '\0' ? value : binary_to_int(&bin[1], (value << 1) + (bin[0] - '0') );
		}
		
		static constexpr int binary_to_int(const char * bin, const int value = 0)
		{
			return bin[0] == '\0' ? value : binary_to_int(&bin[1], (value << 1) + (bin[0] - '0') );
		}
		
		static constexpr int binary_to_long(char * bin, const long value = 0)
		{
			return bin[0] == '\0' ? value : binary_to_long(&bin[1], (value << 1) + (bin[0] - '0'));
		}
		
		static constexpr int binary_to_long(const char * bin, const long value = 0)
		{
			return bin[0] == '\0' ? value : binary_to_long(&bin[1], (value << 1) + (bin[0] - '0'));
		}
		
		static Binary get_binary(int num);
			
		static Binary get_binary_zeros_from_start(int num);
		
		private:
			static constexpr Binary binaries_storage[]
			{
				B00000000,
				B00000001,
				B00000011,
				B00000111,
				B00001111,
				B00011111,
				B00111111,
				B01111111,
				B11111111,
				B11111110,
				B11111100,
				B11111000,
				B11110000,
				B11100000,
				B11000000,
				B10000000
			};
			
			
	};
	
	
	#define BI(x) BinaryUtils::binary_to_int(x)
	#define BL(x) BinaryUtils::binary_to_long(x)
	
	
	using byte = unsigned char;


}
#endif
