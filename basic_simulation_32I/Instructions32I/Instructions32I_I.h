#ifndef INSTRUCTIONS32I_I_H
#define INSTRUCTIONS32I_I_H

#include "Include/Memory.h"
#include "Include/Registers.h"

namespace risc
{
	
	namespace instructions_32I
	{
		void addi(int rd, int rs1, int imm, Memory& memory, Registers<int>& registers);
		void slti(int rd, int rs1, int imm, Memory& memory, Registers<int>& registers);
		void sltiu(int rd, int rs1, int imm, Memory& memory, Registers<int>& registers);
		void andi(int rd, int rs1, int imm, Memory& memory, Registers<int>& registers);
		void ori(int rd, int rs1, int imm, Memory& memory, Registers<int>& registers);
		void xori(int rd, int rs1, int imm, Memory& memory, Registers<int>& registers);
		void slli(int rd, int rs1, int imm, Memory& memory, Registers<int>& registers);
		void sri(int rd, int rs1, int imm, Memory& memory, Registers<int>& registers);
//		void srai(int rd, int rs1, int imm, Memory& memory, Registers<int>& registers);
		void jalr(int rd, int rs1, int imm, Memory& memory, Registers<int>& registers);
		void lb(int rd, int rs1, int imm, Memory& memory, Registers<int>& registers);
		void lh(int rd, int rs1, int imm, Memory& memory, Registers<int>& registers);
		void lw(int rd, int rs1, int imm, Memory& memory, Registers<int>& registers);
		void lbu(int rd, int rs1, int imm, Memory& memory, Registers<int>& registers);
		void lhu(int rd, int rs1, int imm, Memory& memory, Registers<int>& registers);
		void fence(int rd, int rs1, int imm, Memory& memory, Registers<int>& registers);
		void fence_i(int rd, int rs1, int imm, Memory& memory, Registers<int>& registers);
		void csrrw(int rd, int rs1, int csr, Memory& memory, Registers<int>& registers);
		void csrrs(int rd, int rs1, int csr, Memory& memory, Registers<int>& registers);
		void csrrc(int rd, int rs1, int csr, Memory& memory, Registers<int>& registers);
		void csrrwi(int rd, int rs1, int csr, Memory& memory, Registers<int>& registers);
		void csrrsi(int rd, int rs1, int csr, Memory& memory, Registers<int>& registers);
		void csrrci(int rd, int rs1, int csr, Memory& memory, Registers<int>& registers);
		void sys_call(int rd, int rs1, int func12, Memory& memory, Registers<int>& registers);
	}
}

#endif
