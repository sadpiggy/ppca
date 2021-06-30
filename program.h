//
// Created by Lenovo on 2021/6/28.
//仅用于调试的代码line28 line42
//有问题的地方128
//int解释117
//97register[0]==0?必需得
//cout
#ifndef RISCV_SIMULATION_1_PROGRAM_H
#define RISCV_SIMULATION_1_PROGRAM_H
#include <iostream>
#include <string>
#include "my_tools.h"
using namespace std;
class program{
public:
    unsigned int my_register[32]={0u};
    unsigned int my_memory[500000]={0u};
    unsigned int intro_num=0u;
    unsigned int end_index=0u;
    unsigned int program_count=0u;
   // unsigned int count=0;register[31]
    program()=default;
    ~program()=default;
    //遇到跳转到某指令地址的时候，记得输入里面是以4为间隔的，而我是以一位间隔所以记得除以四
    void input()
    {
       string input_token,string_mid;
       unsigned int start_address;
       unsigned int single_introduction;
       while (cin>>input_token)
       {

           if (input_token[0]=='#')break;//仅用于调试代码

           if (input_token[0]=='@')
           {
              start_address=get_address(input_token, true);
           } else//输入指令
           {
               single_introduction=get_address_two(input_token);
               my_memory[start_address]=single_introduction;
               intro_num++;

               for (unsigned int i=1;i<=3;i++)
               {
                   cin>>input_token;
                   single_introduction=get_address_two(input_token);
                   my_memory[start_address+i]=single_introduction;
                   intro_num++;
               }


               start_address+=4;
               if (end_index<start_address) {
                   end_index = start_address;
               }
           }

       }
       //print_production();
    }

    //这个函数可以改进
    void print_production()
    {
        cout<<intro_num<<endl;
        for (int i=0;i<=intro_num;i++)cout<<my_memory[i]<<endl;
    }

    void run()
    {
        input();
       unsigned int now_introduction=0u;
       //while (program_count<end_index)
      while (true)
       {
           //now_introduction=my_memory[program_count];
           my_register[0]=0u;
           now_introduction=0u;
           for (unsigned int i=0;i<=3;i++)
           {
               //取马
               now_introduction=now_introduction*256+my_memory[program_count+3-i];
           }

         //  cout<<"pc=="<<program_count<<endl;

           if (now_introduction==267388179u)break;
           execute(now_introduction);
           my_register[0]=0;
           //program_count+=4;
           //program_count在应该哪里+=4，我也不清楚
          // cout<<"ans:"<<(my_register[10]&255u)<<endl;
       }
      cout<<(my_register[10]&255u)<<endl;
    }

    void execute(unsigned int now_introduction)
    {
        //这里几十个if肯定鞠妮马蛋疼的，之后要想办法优化才行
        unsigned execode=now_introduction&(127u);
        //cout<<now_introduction<<endl;
        //register[0]必需得是0，但是，这样做能不能保证，我不确定
        my_register[0]=0;

       // cout<<"exe"<<endl;

        if (execode==55u){//cout<<"lui"<<endl;
            exe_lui(now_introduction);return;}
        if (execode==23u){//cout<<"aquic"<<endl;
            exe_aquic(now_introduction);return;}
        if (execode==111u){//cout<<"jal"<<endl;
            exe_JAL(now_introduction);return;}
        if (execode==103u){//cout<<"jalr"<<endl;
            exe_JALR(now_introduction);return;}
        if (execode==99u){
            //cout<<"99u"<<endl;
            unsigned int func=get_func(now_introduction);
            if (func==0u){exe_beq(now_introduction);return;}
            if (func==1u){exe_bne(now_introduction);return;}
            if (func==4u){exe_blt(now_introduction);return;}
            if (func==5u){exe_bge(now_introduction);return;}
            if (func==6){exe_bltu(now_introduction);return;}
            if(func==7){exe_bgeu(now_introduction);return;}
        }
        if (execode==3u)
        {
            //cout<<"3u"<<endl;
            unsigned int func=get_func(now_introduction);
            if (func==0u){// cout<<"lb"<<endl;
                exe_lb(now_introduction);return;}
            if (func==1u){ //cout<<"lh"<<endl;
                exe_lh(now_introduction);return;}
            if (func==2u){ //cout<<"lw"<<endl;
                exe_lw(now_introduction);return;}
            if (func==4u){ //cout<<"lbu"<<endl;
                exe_lbu(now_introduction);return;}
            if (func==5u){ //cout<<"lhu"<<endl;
                exe_lhu(now_introduction);return;}
        }
        if (execode==35u)
        {
            //cout<<"35u"<<endl;
            unsigned int func=get_func(now_introduction);
            if (func==0u){//cout<<"sb"<<endl;
                exe_sb(now_introduction);return;}
            if (func==1u){
               // cout<<"sh"<<endl;
                exe_sh(now_introduction);return;}
            if (func==2u){
              //  cout<<"sw"<<endl;
                exe_sw(now_introduction);return;}
        }

        if (execode==19u)
        {
           // cout<<"19u"<<endl;
            unsigned int func=get_func(now_introduction);
            if (func==0u){
              //  cout<<"addi"<<endl;
                exe_addi(now_introduction);return;}
            if (func==2u){
               // cout<<"slti"<<endl;
                exe_slti(now_introduction);return;}
            if (func==3u){
               // cout<<"sltiu"<<endl;
                exe_sltiu(now_introduction);return;}
            if (func==4u){
                //cout<<"xori"<<endl;
                exe_xori(now_introduction);return;}
            if (func==6u){
                //cout<<"ori"<<endl;
                exe_ori(now_introduction);return;}
            if (func==7u){
              //  cout<<"andi"<<endl;
                exe_andi(now_introduction);return;}
            if (func==1u){
              //  cout<<"slli"<<endl;
                exe_slli(now_introduction);return;}
            if (func==5u)
            {
                if (get_30_bit(now_introduction)==0u){
                  //  cout<<"srli"<<endl;
                    exe_srli(now_introduction);return;}
               // cout<<"sraii"<<endl;
                exe_srai(now_introduction);return;
            }
        }

        if (execode==51u)
        {
          //  cout<<"51u"<<endl;
            unsigned int func=get_func(now_introduction);
            if (func==0u)
            {
                if (get_30_bit(now_introduction)==0u){exe_add(now_introduction);return;}
                exe_sub(now_introduction);return;
            }
            if (func==1u){exe_sll(now_introduction);return;}
            if (func==2u){exe_slt(now_introduction);return;}
            if (func==3u){exe_sltu(now_introduction);return;}
            if (func==4u){exe_xor(now_introduction);return;}
            if (func==5u){
                if (get_30_bit(now_introduction)==0u){exe_srl(now_introduction);return;}
                exe_sra(now_introduction);return;
            }
            if (func==6u){exe_or(now_introduction);return;}
            if (func==7u){exe_and(now_introduction);return;}
        }



    }

    void exe_lui(unsigned int now_introdution)
    {
        unsigned int imm=get_U_imm(now_introdution);
        unsigned int rd=get_rd(now_introdution);
        my_register[rd]=imm;
      //  cout<<"rd="<<rd<<endl;
        program_count+=4u;
    }
    //应该先++,还是应该后++
    void exe_aquic(unsigned int now_introdution)
    {
        unsigned int imm=get_U_imm(now_introdution);
        unsigned int rd=get_rd(now_introdution);
        my_register[rd]=(imm)+program_count;//这里应该要int解释吧？
        program_count+=4u;
    }

    void exe_JAL(unsigned int now_introdution)
    {
        unsigned int rd=get_rd(now_introdution);
        unsigned int imm=get_J_imm(now_introdution);
        my_register[rd]=program_count+4u;
        program_count+=(imm);//加上unsigned的imm还是加上int的imm????
    }

    void exe_JALR(unsigned int now_introduction)
    {
        unsigned int rd=get_rd(now_introduction);
        unsigned int rs1=get_rs1(now_introduction);
        unsigned int imm=get_I_imm(now_introduction);
        unsigned t=program_count+4u;
        program_count=(my_register[rs1]+(imm))&~1u;//int???
        my_register[rd]=t;
    }

    void exe_beq(unsigned int now_introduction)
    {
        unsigned int rs1=get_rs1(now_introduction);
        unsigned int rs2=get_rs2(now_introduction);
        unsigned imm=get_B_imm(now_introduction);
        if (my_register[rs1]==my_register[rs2]){
            program_count+=(imm);
        } else program_count+=4u;
        //int???
    }

    void exe_bne(unsigned int now_introduction)
    {
        unsigned int rs1=get_rs1(now_introduction);
        unsigned int rs2=get_rs2(now_introduction);
        unsigned int imm=get_B_imm(now_introduction);
        if (my_register[rs1]!=my_register[rs2]){
            program_count+=(imm);
        } else program_count+=4u;
        //int??
    }

    void exe_blt(unsigned int now_introduction)
    {
        unsigned int rs1=get_rs1(now_introduction);
        unsigned int rs2=get_rs2(now_introduction);
        unsigned int imm=get_B_imm(now_introduction);
        if (int(my_register[rs1])<int(my_register[rs2])){
            program_count+=(imm);
        } else program_count+=4u;
        //int???
    }

    void exe_bge(unsigned int now_introduction)
    {
        unsigned int rs1=get_rs1(now_introduction);
        unsigned int rs2=get_rs2(now_introduction);
        unsigned int imm=get_B_imm(now_introduction);
        if (int(my_register[rs1])>=int(my_register[rs2])){
            program_count+=(imm);
        } else program_count+=4u;
        //int???
    }

    void exe_bltu(unsigned int now_introduction)
    {
        unsigned int rs1=get_rs1(now_introduction);
        unsigned int rs2=get_rs2(now_introduction);
        unsigned int imm=get_B_imm(now_introduction);
        if ((my_register[rs1])<(my_register[rs2])){
            program_count+=(imm);
        } else program_count+=4u;
    }

    void exe_bgeu(unsigned int now_introduction)
    {
        unsigned int rs1=get_rs1(now_introduction);
        unsigned int rs2=get_rs2(now_introduction);
        unsigned int imm=get_B_imm(now_introduction);
        if ((my_register[rs1])>=(my_register[rs2])){
            program_count+=(imm);
        } else program_count+=4u;
    }

    void exe_lb(unsigned int now_introduction)
    {
        unsigned rs1=get_rs1(now_introduction);
        unsigned rd=get_rd(now_introduction);
        unsigned imm=get_I_imm(now_introduction);
        unsigned value=my_memory[my_register[rs1]+(imm)];
        if (get_7_bit(value)==1){
            value=((16777215u)<<8u)|value;
        }
        my_register[rd]=value;
        program_count+=4u;
    }

    void exe_lh(unsigned int now_introduction)
    {
        unsigned rs1=get_rs1(now_introduction);
        unsigned rd=get_rd(now_introduction);
        unsigned imm=get_I_imm(now_introduction);
        unsigned value=my_memory[my_register[rs1]+(imm)+1u];
        value=value*(256u)+my_memory[my_register[rs1]+(imm)];
        if (get_15_bit(value)==1){
            value=((65535u)<<16u)|value;
        }
        my_register[rd]=value;
        program_count+=4u;
    }

    void exe_lw(unsigned int now_introduction)
    {
       // cout<<"???"<<endl;
        unsigned rs1=get_rs1(now_introduction);
        unsigned rd=get_rd(now_introduction);
        unsigned imm=get_I_imm(now_introduction);
     //   unsigned value=my_memory[my_register[rs1]+imm];
        unsigned value=my_memory[my_register[rs1]+(imm)+3u];
     //  cout<< my_register[rs1]+(imm)<<endl;
        for ( int i=2;i>=0;i--)
        {
            //cout<< my_register[rs1]+(imm)+1<<endl;
            value=value*256u+my_memory[my_register[rs1]+(imm)+i];
        }



      //  if (rd==10){cout<<"jiushizheli"<<std::endl;}

        my_register[rd]=value;
        program_count+=4u;
        //cout<<"!!!"<<endl;
    }

    void exe_lbu(unsigned int now_introduction)
    {
        unsigned rs1=get_rs1(now_introduction);
        unsigned rd=get_rd(now_introduction);
        unsigned imm=get_I_imm(now_introduction);
        unsigned value=my_memory[my_register[rs1]+(imm)];
        my_register[rd]=value;
        program_count+=4u;
    }

    void exe_lhu(unsigned int now_introduction)
    {
        unsigned rs1=get_rs1(now_introduction);
        unsigned rd=get_rd(now_introduction);
        unsigned imm=get_I_imm(now_introduction);
        unsigned value=my_memory[my_register[rs1]+(imm)+1u];
        value=value*(256u)+my_memory[my_register[rs1]+(imm)];
        my_register[rd]=value;
        program_count+=4u;
    }

    void exe_sb(unsigned int now_introduction)
    {
        unsigned rs1=get_rs1(now_introduction);
        unsigned rs2=get_rs2(now_introduction);
        unsigned imm=get_S_imm(now_introduction);
        unsigned value=my_register[rs2];
        //value=(value<<24u)>>24u;
        value=value&255u;
        my_memory[my_register[rs1]+(imm)]=value;
        program_count+=4u;
    }

    void exe_sh(unsigned int now_introduction)
    {
        unsigned rs1=get_rs1(now_introduction);
        unsigned rs2=get_rs2(now_introduction);
        unsigned imm=get_S_imm(now_introduction);
        unsigned value1=my_register[rs2]&65535u;
       // value=(value<<16u)>>16u;
        unsigned value2=value1&255u;
        value1=value1>>8u;
        //value2=value2<<8u;
        my_memory[my_register[rs1]+(imm)]=value2;
        my_memory[my_register[rs1]+(imm)+1u]=value1;
        program_count+=4u;
    }

    void exe_sw(unsigned int now_introduction)
    {
        unsigned rs1=get_rs1(now_introduction);
        unsigned rs2=get_rs2(now_introduction);
        unsigned imm=get_S_imm(now_introduction);
        unsigned value1=my_register[rs2];
      //  cout<<value1<<endl;
        unsigned value4=value1&255u;
        value1=value1>>8u;
        unsigned value3=value1&255u;
        value1=value1>>8u;
        unsigned value2=value1&255u;
        value1=value1>>8u;

      //  cout<<"SWSWSW  "<<my_register[rs1]+imm<<endl;

        my_memory[my_register[rs1]+(imm)]=value4;
       (my_memory[my_register[rs1]+(imm)+1u]=value3);
        my_memory[my_register[rs1]+(imm)+2u]=value2;
        my_memory[my_register[rs1]+(imm)+3u]=value1;
        program_count+=4u;
    }

    void exe_addi(unsigned int now_introduction)
    {
        unsigned rs1=get_rs1(now_introduction);
        unsigned rd=get_rd(now_introduction);
        unsigned imm=get_I_imm(now_introduction);
        my_register[rd]=my_register[rs1]+(imm);
        program_count+=4u;
    }

    void exe_slti(unsigned int now_introduction)
    {
        unsigned rs1=get_rs1(now_introduction);
        unsigned rd=get_rd(now_introduction);
        unsigned imm=get_I_imm(now_introduction);
        if (int(my_register[rs1])<int(imm))my_register[rd]=1u;
        else my_register[rd]=0u;
        program_count+=4u;
    }

    void exe_sltiu(unsigned int now_introduction)
    {
        unsigned rs1=get_rs1(now_introduction);
        unsigned rd=get_rd(now_introduction);
        unsigned imm=get_I_imm(now_introduction);
        if ((my_register[rs1])<(imm))my_register[rd]=1u;
        else my_register[rd]=0u;
        program_count+=4u;
    }

    void exe_xori(unsigned int now_introduction)
    {
        unsigned rs1=get_rs1(now_introduction);
        unsigned rd=get_rd(now_introduction);
        unsigned imm=get_I_imm(now_introduction);
        my_register[rd]=my_register[rs1]^imm;
        program_count+=4u;
    }

    void exe_ori(unsigned int now_introduction)
    {
        unsigned rs1=get_rs1(now_introduction);
        unsigned rd=get_rd(now_introduction);
        unsigned imm=get_I_imm(now_introduction);
        my_register[rd]=my_register[rs1]|imm;
        program_count+=4u;
    }

    void exe_andi(unsigned int now_introduction)
    {
        unsigned rs1=get_rs1(now_introduction);
        unsigned rd=get_rd(now_introduction);
        unsigned imm=get_I_imm(now_introduction);
        my_register[rd]=my_register[rs1]&imm;
        program_count+=4u;
    }

    void exe_slli(unsigned int now_introduction)
    {
        unsigned rs1=get_rs1(now_introduction);
        unsigned rd=get_rd(now_introduction);
        unsigned shamt=get_shamt(now_introduction);
       // if ((shamt&32u)==0){
            my_register[rd]=my_register[rs1]<<shamt;
        //}
        program_count+=4u;
    }

    void exe_srli(unsigned int now_introduction)
    {
        unsigned rs1=get_rs1(now_introduction);
        unsigned rd=get_rd(now_introduction);
        unsigned shamt=get_shamt(now_introduction);
       // if ((shamt&32u)==0){
            my_register[rd]=my_register[rs1]>>shamt;
        //}
        program_count+=4u;
    }

    void exe_srai(unsigned int now_introduction)
    {
        unsigned rs1=get_rs1(now_introduction);
        unsigned rd=get_rd(now_introduction);
        unsigned shamt=get_shamt(now_introduction);
        unsigned head;
        if ((my_register[rs1]>>31u)==0u)head=0u;
        else head=1u;
        head=head<<31u;
       // if ((shamt&32u)==0){
            for (unsigned int i=1;i<=shamt;i++)
            {
                my_register[rd]=(my_register[rs1]>>1u)|head;
            }
        //}
        program_count+=4u;
    }

    void exe_add(unsigned int now_introduction)
    {
        unsigned rs1=get_rs1(now_introduction);
        unsigned rs2=get_rs2(now_introduction);
        unsigned rd=get_rd(now_introduction);
        my_register[rd]=my_register[rs1]+my_register[rs2];
        program_count+=4u;
    }
    //所以这应该是两个unsigned相加？？？
    void exe_sub(unsigned int now_introduction)
    {
        unsigned rs1=get_rs1(now_introduction);
        unsigned rs2=get_rs2(now_introduction);
        unsigned rd=get_rd(now_introduction);
        my_register[rd]=my_register[rs1]-my_register[rs2];
        program_count+=4u;
    }

    void exe_sll(unsigned int now_introduction)
    {
        unsigned rs1=get_rs1(now_introduction);
        unsigned rs2=get_rs2(now_introduction);
        unsigned rd=get_rd(now_introduction);
        my_register[rd]=my_register[rs1]<<(my_register[rs2]&(31u));
        program_count+=4u;
    }

    void exe_slt(unsigned int now_introduction)
    {
        unsigned rs1=get_rs1(now_introduction);
        unsigned rs2=get_rs2(now_introduction);
        unsigned rd=get_rd(now_introduction);
        if (int(my_register[rs1])<int(my_register[rs2]))my_register[rd]=1u;
        else my_register[rd]=0u;
        program_count+=4u;
    }

    void exe_sltu(unsigned int now_introduction)
    {
        unsigned rs1=get_rs1(now_introduction);
        unsigned rs2=get_rs2(now_introduction);
        unsigned rd=get_rd(now_introduction);
        if ((my_register[rs1])<(my_register[rs2]))my_register[rd]=1u;
        else my_register[rd]=0u;
        program_count+=4u;
    }

    void exe_xor(unsigned int now_introduction)
    {
        unsigned rs1=get_rs1(now_introduction);
        unsigned rs2=get_rs2(now_introduction);
        unsigned rd=get_rd(now_introduction);
        my_register[rd]=my_register[rs1]^my_register[rs2];
        program_count+=4u;
    }

    void exe_srl(unsigned int now_introduction)
    {
        unsigned rs1=get_rs1(now_introduction);
        unsigned rs2=get_rs2(now_introduction);
        unsigned rd=get_rd(now_introduction);
        my_register[rd]=my_register[rs1]>>(my_register[rs2]&(31u));
        program_count+=4u;
    }

    void exe_sra(unsigned int now_introduction)
    {
        unsigned rs1=get_rs1(now_introduction);
        unsigned rd=get_rd(now_introduction);
        unsigned rs2=get_rs2(now_introduction);
        unsigned head;
        if ((my_register[rs1]>>31u)==0u)head=0u;
        else head=1u;
        head=head<<31u;
        unsigned index=my_register[rs2]&(31u);
            for (unsigned int i=1;i<=index;i++)
            {
                my_register[rd]=(my_register[rs1]>>1u)|head;
            }
        program_count+=4u;
    }

    void exe_or(unsigned int now_introduction)
    {
        unsigned rs1=get_rs1(now_introduction);
        unsigned rd=get_rd(now_introduction);
        unsigned rs2=get_rs2(now_introduction);
        my_register[rd]=my_register[rs1]|my_register[rs2];
        program_count+=4u;
    }

    void exe_and(unsigned int now_introduction)
    {
        unsigned rs1=get_rs1(now_introduction);
        unsigned rd=get_rd(now_introduction);
        unsigned rs2=get_rs2(now_introduction);
        my_register[rd]=my_register[rs1]&my_register[rs2];
        program_count+=4u;
    }





};


#endif //RISCV_SIMULATION_1_PROGRAM_H
