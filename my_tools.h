//
// Created by Lenovo on 2021/6/28.
//

#ifndef RISCV_SIMULATION_1_MY_TOOLS_H
#define RISCV_SIMULATION_1_MY_TOOLS_H
#include <string>
using namespace std;

unsigned int to_int(char input)
{
    if(input-'0'>=0&&input-'0'<=9)return input-'0';
    return input-'A'+10;
}

unsigned int get_address_two(string& mid)
{
    unsigned int sum=0;
        for (int i = 0; i <= 1; i++) {
            sum = sum * 16 + to_int(mid[i]);
        }

    return sum;
}


unsigned int get_address(string& mid,bool is_aite)
{
    unsigned int sum=0;
    if (is_aite) {
        for (int i = 1; i <= 8; i++) {
            sum = sum * 16 + to_int(mid[i]);
        }
    } else{
        for (int i = 0; i <= 7; i++) {
            sum = sum * 16 + to_int(mid[i]);
        }
    }
    return sum;
}
//v
unsigned int get_J_imm(unsigned int now_introduction)
{
    unsigned int imm_1=(now_introduction&1044480U);
    //unsigned int imm_1=(now_introduction<<12u>>24u<<12u);
    unsigned int imm_2=(now_introduction&1048576u)>>9u;
    //unsigned int imm_2=(now_introduction<<11u>>31u<<11u);
    unsigned int imm_3=(now_introduction<<1u>>22u)<<1u;
    if ((now_introduction>>31u)==1u){
        now_introduction=imm_3|(4095u<<20u)|imm_1|imm_2;
    } else{
        now_introduction=imm_3|imm_1|imm_2;
    }
    return now_introduction;
}
//v
unsigned int get_I_imm(unsigned int now_introduction)
{
    unsigned int imm_1=now_introduction>>20u;
    if (imm_1>>11u==1u){
        now_introduction=(2097151u<<11u)|imm_1;
    } else{
        now_introduction=imm_1;
    }
    return now_introduction;
}
//v
unsigned int get_S_imm(unsigned int now_introduction)
{
    unsigned int imm_1=now_introduction<<20u>>20u>>7u;
    unsigned int imm_2=now_introduction>>25u<<5u;
    if ((now_introduction>>31u)==1u)
    {
        now_introduction=(2097151u<<11u)|imm_1|imm_2;
    } else now_introduction=imm_1|imm_2;
    return now_introduction;
}
//v
unsigned int get_B_imm(unsigned int now_introduction)
{
    unsigned int imm_1=now_introduction<<20u>>28u<<1u;
    unsigned int imm_2=now_introduction<<24u>>31u<<11u;
    unsigned int imm_3=now_introduction<<1u>>26u<<5u;
    if ((now_introduction>>31u)==1u)
    {
        now_introduction=(1048575u<<12u)|imm_1|imm_2|imm_3;
    } else now_introduction=imm_1|imm_2|imm_3;
    return now_introduction;
}
//v
unsigned get_U_imm(unsigned int now_introduction)
{
    return (now_introduction>>12u<<12u);
}

unsigned get_rd(unsigned int now_introduction)
{
    unsigned int rd=(now_introduction>>7u)&(31u);
    return rd;
}


unsigned get_rs1(unsigned int now_introduction)
{
    return now_introduction<<12u>>27u;
}

unsigned get_rs2(unsigned int now_introduction)
{
    return now_introduction<<7u>>27u;
}

unsigned get_func(unsigned int now_introduction)
{
    return now_introduction<<17U>>29u;
}

unsigned get_30_bit(unsigned int now_introduction)
{
    return (now_introduction&(1u<<30u))>>30u;
}

unsigned get_7_bit(unsigned int now_introduction)
{
    return (now_introduction&(1u<<7u))>>7u;
}

unsigned get_15_bit(unsigned int now_introduction)
{
    return (now_introduction&(1u<<15u))>>15u;
}

unsigned get_shamt(unsigned int now_introduction)
{
    return now_introduction<<7u>>27u;
   // return (now_introduction<<6u)>>26u;
}

#endif //RISCV_SIMULATION_1_MY_TOOLS_H
