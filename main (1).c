//Zahra Ramezani & Bahar Khalilian
//second project

#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
int Registers[16];
int usage[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int pc =0;
void print_R_usage();
void print_registers ();
void print_usages();
void I_type(int hex[7], int op);
void R_type(int hex[7], int op);
void J_type(int hex[7], int op);
int ConvertChartoInt(char a[]);
void print_registers(){
    for(int i=0 ; i<15 ; i++){
        printf("%s","Register ");
        printf("%i", i);
        printf("%s",": ");
        printf("%i\n",Registers[i]);

    }
    printf("%s\n", "*************************************");

}
void print_usages(){
    int sum=0;
    for(int i=0 ; i<=14 ; i++)
    {
        sum += usage[i];
    }
    printf("%s", "usage of add  is: ");
    printf("%i", (usage[0]*100/sum));
    printf("%s\n", "%");

    printf("%s", "usage of sub  is: ");
    printf("%i", (usage[1]*100/sum));
    printf("%s\n", "%");

    printf("%s", "usage of slt  is: ");
    printf("%i", (usage[2]*100/sum));
    printf("%s\n", "%");

    printf("%s", "usage of or   is: ");
    printf("%i", (usage[3]*100/sum));
    printf("%s\n", "%");

    printf("%s", "usage of nand is: ");
    printf("%i", (usage[4]*100/sum));
    printf("%s\n", "%");

    printf("%s", "usage of addi is: ");
    printf("%i", (usage[5]*100/sum));
    printf("%s\n", "%");

    printf("%s", "usage of slti is: ");
    printf("%i", (usage[6]*100/sum));
    printf("%s\n", "%");

    printf("%s", "usage of ori  is: ");
    printf("%i", (usage[7]*100/sum));
    printf("%s\n", "%");

    printf("%s", "usage of lui  is: ");
    printf("%i", (usage[8]*100/sum));
    printf("%s\n", "%");

    printf("%s", "usage of lw   is: ");
    printf("%i", (usage[9]*100/sum));
    printf("%s\n", "%");

    printf("%s", "usage of sw   is: ");
    printf("%i", (usage[10]*100/sum));
    printf("%s\n", "%");

    printf("%s", "usage of beq  is: ");
    printf("%i", (usage[11]*100/sum));
    printf("%s\n", "%");

    printf("%s", "usage of jalr is: ");
    printf("%i", (usage[12]*100/sum));
    printf("%s\n", "%");

    printf("%s", "usage of j    is: ");
    printf("%i", (usage[13]*100/sum));
    printf("%s\n", "%");

    printf("%s", "usage of halt is: ");
    printf("%i", (usage[14]*100/sum));
    printf("%s\n", "%");

    printf("%s\n", "*************************************");

}
void print_R_usage() {
    int sum = 0;
    for (int i = 0; i < 15; i++) {
        sum += Registers[i];
    }
    printf("%s", "percentage of registers used is  ");
    printf("%i", (sum*100/16));
    printf("%s\n", "%");

}
int binary_to_hex(int bin){
    if(bin==0000)return 0;
    if(bin==0001)return 1;
    if(bin==0010)return 2;
    if(bin==0011)return 3;
    if(bin==0100)return 4;
    if(bin==0101)return 5;
    if(bin==0110)return 6;
    if(bin==0111)return 7;
    if(bin==1000)return 8;
    if(bin==1001)return 9;
    if(bin==1010)return 10;
    if(bin==1011)return 11;
    if(bin==1100)return 12;
    if(bin==1101)return 13;
    if(bin==1110)return 14;
    if(bin==1111)return 15;
}
int hex_to_binary(int hex){
    if(hex==0)return 0000;
    if(hex==1)return 0001;
    if(hex==2)return 0010;
    if(hex==3)return 0011;
    if(hex==4)return 0100;
    if(hex==5)return 0101;
    if(hex==6)return 0110;
    if(hex==7)return 0111;
    if(hex==8)return 1000;
    if(hex==9)return 1001;
    if(hex==10)return 1010;
    if(hex==11)return 1011;
    if(hex==12)return 1100;
    if(hex==13)return 1101;
    if(hex==14)return 1110;
    if(hex==15)return 1111;

}
int instruction=0;
void Parse(long int a){
    int hex[7];
    for(int i=0 ; i<7 ; i++){
        hex[i]=0;
    }
    int i=0;
    while(a != 0){
        if(a==16){
            hex[6]=10;
            break;
        }
        else if(a==17){
            hex[6]=11;
            break;
        }
        else if(a==18){
            hex[6]=12;
            break;
        }
        else if(a==19){
            hex[6]=13;
            break;
        }
        else if(a==20){
            hex[6]=14;
            break;
        }
        else {
            hex[i] = a % 16;
            a /= 16;
            i++;
        }
    }
    int op = hex[6];
    if(op==0||op==1||op==2||op==3||op==4)
        R_type(hex,op);
    else if(op==5||op==6||op==7||op==8||op==9||op==10||op==11||op==12)
        I_type(hex,op);
    else if(op==13||op==14)
        J_type(hex, op);
}
void R_type(int hex[7], int op) {
    int rd = hex[3];
    int rt = hex[4];
    int rs = hex[5];
    if(op==0) {
        Registers[rd] = Registers[rs] + Registers[rt];
        usage[0]++;
        pc++;
    }
    else if(op==1){
        Registers[rd]=Registers[rs]-Registers[rt];
        usage[1]++;
        pc++;
    }
    else if(op==2){
        if(Registers[rs]<Registers[rt])
            Registers[rd]=1;
        else Registers[rd]=0;
        usage[2]++;
        pc++;
    }
    int bin_rs= hex_to_binary(Registers[rs]);
    int bin_rt= hex_to_binary(Registers[rt]);
    if(op==3) {
        Registers[rd] = binary_to_hex(bin_rs | bin_rt);
        usage[3]++;
        pc++;
    }
    if(op==4) {
        Registers[rd] = binary_to_hex(bin_rs & bin_rt);
        usage[4]++;
        pc++;
    }
}
void I_type(int hex[7], int op) {
    int offset =hex[0]+ hex[1] * 16 + hex[2]*16*16 +hex[3]*16*16*16;
    int rt = hex[4];
    int rs = hex[5];

    if (op == 5) {
        Registers[rt] = Registers[rs] + offset;
        usage[5]++;
        pc++;
    }
    if (op == 6) {//slti
        if (Registers[rs] < offset)Registers[rt] = 1;
        else Registers[rt] = 0;
        usage[6]++;
        pc++;
    }
    if (op == 7) {//ori
        Registers[rt] = binary_to_hex(hex_to_binary(Registers[rs]) | hex_to_binary(offset));
        usage[7]++;
        pc++;
    }
    if (op == 8){//lui
        Registers[rt] = offset << 16;
        usage[8]++;
        pc++;
    }
    if (op == 9) {//lw
        Registers[rt] = Registers[rs + offset];
        usage[9]++;
        pc++;
    }
    if (op == 10) {//sw
        Registers[rt + offset] = Registers[rt];
        usage[10]++;
        pc++;
    }
    if (op == 11) {//beq
        if (Registers[rt] == Registers[rs])pc = pc + 1 + offset;
        else pc++;
        usage[11]++;
    }
    if (op == 12) {//jalr
        Registers[rt]=pc+1;
        pc = Registers[rs];
        usage[12]++;
    }

}
void J_type(int hex[7], int op) {
    int offset =hex[0]+ hex[1] * 16 + hex[2]*16*16 +hex[3]*16*16*16;
    if(op==13){
        pc = offset;
        usage[13]++;
    }
    if(op==14){
        pc = -1;
        usage[14]++;
    }
}
int ConvertChartoInt(char a[]){
    long int i = atoi(a);
    return i;
}
int main() {
    FILE *fp;
    char c[255][20];
    fp = fopen("/Users/bahar/Desktop/Archive/3.txt" , "r");
    int size = 0;
    while (!feof(fp)){
        fgets(c[size], 255, (FILE *) fp);
        size++;
        if (size > 20)
            break;
    }
    long int lines[255];
    for(int i=0 ; i<255 ; i++){
        lines[i] = ConvertChartoInt(c[i]);
    }
    while(pc>=0){
        Parse(lines[pc]);
        instruction++;
        print_registers();
        print_usages();
        print_R_usage();
        printf("%s","number of processed instructions : ");
        printf("%i\n", instruction);
        if(pc>=0)
            printf("%s\n", "######### Next Instruction ############");
        else
            printf("%s\n", "#####################################");


    }

    return 0;
}
