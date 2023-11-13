#ifndef BIT_MATH_H_
#define BIT_MATH_H_


#define Set_Bit( Var, Bit_no )              ( Var |= ( 1 << Bit_no ) )
#define Clear_Bit( Var, Bit_no )            ( Var &= ( ~(1 << Bit_no) ) )
#define Toggle_Bit( Var, Bit_no )           ( Var ^= ( 1 << Bit_no ) )
#define Get_Bit( Var, Bit_no )              ( (Var >> Bit_no) & 0x01 )

#endif
