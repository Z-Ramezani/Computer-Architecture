#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

int lnum=0;
struct label{
    int address;
    char name[1][6];
    int num;
};
struct label l[255];
void checkOffset(int offset) {
    if (offset > 3277 || offset < -32768){
        printf("%s\n","offset larger than 16 bits error");
        exit(1);
    }


}
int search( char offset[6] ){
    for (int i = 0; i < lnum ; i++) {
        if(strcmp(l[i].name,offset)==0)
            return l[i].address;
    }
    return -1;
}
int fnum=0;
long int f[255];
void write_to_file( long int  a[]){
    FILE * fp;
    fp = fopen ("/Users/bahar/Desktop/result.txt","w");
    for(int i=0 ; i<fnum ; i++){
        fprintf (fp, " %d \n", a[i]);
    }
    fclose (fp);
}
long int hex(long int imm){
    int a[4];
    int i=0;
    long int sum = 0;
    while(imm != 0){
        a[i] = imm%16;
        imm /= 16;
        i++;
    }
    for(int i=0 ; i<4 ; i++){
        sum += a[i]*(pow(16,i));
    }
    return sum;
}
void label_error(){
    for(int i=0 ; i<lnum ; i++){
        for(int j=0 ; j<lnum ; j++){
            if(strcmp(l[i].name,l[j].name)==0 && l[i].address != l[j].address){
                printf("%s\n","repeated label error");
                exit(1);
            }
        }
    }
}
void sep(char x[5][6] ,int pc){
    for (int i = 0; i <1 ; i++)
    {
        if ( (strcmp(x[1],"add")==0) || strcmp(x[1],"sub")==0 || strcmp(x[1],"slt")==0
             || strcmp(x[1],"or")==0 || strcmp(x[1],"nand")==0) {
            int rd = atoi(x[2]);
            int rs = atoi(x[3]);
            int rt = atoi(x[4]);
            int op;
            if (strcmp(x[1],"add")==0)
                op=0;
            else if (strcmp(x[1],"sub")==0)
                op=1;
            else if (strcmp(x[1],"slt")==0)
                op=2;
            else if (strcmp(x[1],"or")==0)
                op=3;
            else if (strcmp(x[1],"nand")==0)
                op=4;
            long int a=0;
            a+= op*(pow(16,6));
            a+= rs*(pow(16,5));
            a+= rt*(pow(16,4));
            a+= rd*(pow(16,3));
            f[fnum]=a;
            fnum++;
        }

        else if (strcmp(x[1],"addi")==0 || strcmp(x[1],"lui")==0 || strcmp(x[1],"slti")==0
                 || strcmp(x[1],"ori")==0 || strcmp(x[1],"lw")==0 || strcmp(x[1],"sw")==0
                 || strcmp(x[1],"beq")==0 || strcmp(x[1],"jalr")==0) {
            int a=0;
            int offset=0;
            int rt;
            int rs;
            int op;
            long int imm;
            if (strcmp(x[1],"addi")==0){
                op=5;
                rt = atoi(x[2]);
                rs = atoi(x[3]);
                imm = atoi(x[4]);
                a+= hex(imm);
                a+= op*(pow(16,6));
                a+= rs*(pow(16,5));
                a+= rt*(pow(16,4));
                f[fnum]=a;
                fnum++;
            }
            else if (strcmp(x[1],"slti")==0){
                op=6;
                rt = atoi(x[2]);
                rs = atoi(x[3]);
                imm = atoi(x[4]);
                a+= hex(imm);
                a+= op*(pow(16,6));
                a+= rs*(pow(16,5));
                a+= rt*(pow(16,4));
                f[fnum]=a;
                fnum++;
            }
            else if (strcmp(x[1],"ori")==0){
                op=7;
                rt = atoi(x[2]);
                rs = atoi(x[3]);
                imm = atoi(x[4]);
                a+= hex(imm);
                a+= op*(pow(16,6));
                a+= rs*(pow(16,5));
                a+= rt*(pow(16,4));
                f[fnum]=a;
                fnum++;
            }
            else if (strcmp(x[1],"lui")==0){
                op=8;
                rt = atoi(x[2]);
                rs = 0;
                imm = atoi(x[3]);
                a+= hex(imm);
                a+= op*(pow(16,6));
                a+= rs*(pow(16,5));
                a+= rt*(pow(16,4));
                f[fnum]=a;
                fnum++;
            }
            else if (strcmp(x[1],"lw")==0){
                int isd=1;
                op=9;
                rt = atoi(x[2]);
                rs = atoi(x[3]);
                if(!(isdigit(x[4][0]))){
                    isd = 0;
                }
                a+= op*(pow(16,6));
                a+= rs*(pow(16,5));
                a+= rt*(pow(16,4));
                if(isd==1){
                    offset= atoi(x[4]);
                    checkOffset(offset);
                    a+= offset;
                    f[fnum]=a;
                    fnum++;
                }
                else{
                    offset = search(x[4]);
                    if(offset == -1){
                        printf("%s\n","use of undefined label");
                        exit(1);
                    }
                    else{
                        offset = offset-1-pc;
                        checkOffset(offset);
                        a+=offset;
                        f[fnum]=a;
                        fnum++;
                    }
                }
            }
            else if (strcmp(x[1],"sw")==0){
                int isd=1;
                op=10;
                rt = atoi(x[2]);
                rs = atoi(x[3]);
                if(!(isdigit(x[4][0]))){
                    isd = 0;
                }
                a+= op*(pow(16,6));
                a+= rs*(pow(16,5));
                a+= rt*(pow(16,4));
                if(isd==1){
                    offset= atoi(x[4]);
                    checkOffset(offset);
                    a+= offset;
                    f[fnum]=a;
                    fnum++;
                }
                else{
                    offset = search(x[4]);
                    if(offset == -1){
                        printf("%s\n","use of undefined label");
                        exit(1);
                    }
                    else{
                        checkOffset(offset);
                        a+=offset;
                        f[fnum]=a;
                        fnum++;
                    }
                }
            }
            else if (strcmp(x[1],"beq")==0){
                int isd=1;
                op=11;
                rt = atoi(x[2]);
                rs = atoi(x[3]);
                if(!(isdigit(x[4][0]))){
                    isd = 0;
                }
                a+= op*(pow(16,6));
                a+= rs*(pow(16,5));
                a+= rt*(pow(16,4));
                if(isd==1){
                    offset= atoi(x[4])-1-pc;
                    checkOffset(offset);
                    a+= offset;
                    f[fnum]=a;
                    fnum++;
                }
                else{
                    offset = search(x[4]);
                    if(offset == -1){
                        printf("%s\n","use of undefined label");
                        exit(1);
                    }
                    else{
                        offset = offset-1-pc;
                        a+=offset;
                        f[fnum]=a;
                        fnum++;
                    }
                }
            }
            else if (strcmp(x[1],"jalr")==0){
                op = 12;
                rt = atoi(x[2]);
                rs = atoi(x[3]);
                a+= op*(pow(16,6));
                a+= rs*(pow(16,5));
                a+= rt*(pow(16,4));
                write_to_file(a);
            }
        }
        else if (strcmp(x[1],"halt")==0 || strcmp(x[1],"j")==0) {
            int op;
            int rt;
            int rs;
            int a=0;
            int isd =1;
            long int offset;
            if (strcmp(x[1] , "halt")){
                op=14;
                a+= op*(pow(16,6));
                write_to_file(a);
            }
            else if (strcmp (x[1],"j")){
                op = 13;
                rt=0;
                rs=0;
                if(!(isdigit(x[4][0]))){
                    isd = 0;
                }
                a+= op*(pow(16,6));
                a+= rs*(pow(16,5));
                a+= rt*(pow(16,4));
                if(isd==1){
                    offset= atoi(x[4])-1-pc;
                    checkOffset(offset);
                    a+= offset;
                    f[fnum]=a;
                    fnum++;
                }
                else{
                    offset = search(x[4]);
                    if(offset == -1){
                        printf("%s\n","use of undefined label");
                        exit(1);
                    }
                    else{
                        offset = offset-1-pc;
                        checkOffset(offset);
                        a+=offset;
                        f[fnum]=a;
                        fnum++;
                    }
                }

            }
        }
        else if(strcmp(x[1], ".fill")==0){
            for(int i=0 ; i<lnum ; i++){
                if(strcmp(l[i].name,x[0])==0){
                    l[i].address = atoi(x[2]);

                }
            }
        }
        else if(strcmp(x[1],"add") !=0 && strcmp(x[1],"sub") !=0 && strcmp(x[1],"slt") !=0
                && strcmp(x[1],"or") !=0 && strcmp(x[1],"nand")!=0 && strcmp(x[1],"addi")!=0 &&
                strcmp(x[1],"ori")!=0 && strcmp(x[1],"beq")!=0 && strcmp(x[1],"lui")!=0 &&
                strcmp(x[1],"lw")!=0 && strcmp(x[1],"jalr")!=0 && strcmp(x[1],"slti")!=0 &&
                strcmp(x[1],"sw")!=0 && strcmp(x[1],"j")!=0 && strcmp(x[1],"halt")!=0){
            printf("%s\n","undefned opcode error");
            exit(1);
        }
    }

}
int main() {
    FILE *fp;
    char c[255][20];

    fp = fopen("/Users/bahar/Desktop/Test1.txt" , "r");

    int size = 0;
    while (!feof(fp)){
        fgets(c[size], 255, (FILE *) fp);
        size++;
        if (size > 20)
            break;
    }
    char copy[255][20];
    for(int i=0 ; i<size ; i++){
        strcpy(copy[i] , c[i]);
    }
    int size2=size;
    char a[5][6];
    int num=0;
    for(int i=0 ; i<size ; i++){
        int j=0;
        int init_size = strlen(c[i]);
        char delim[] = " ,";

        char *ptr = strtok(c[i], delim);

        while(ptr != NULL)
        {
            if(ptr[0] == '#')break;
            strcpy(a[j],ptr);
            j++;
            num=j;
            ptr = strtok(NULL, delim);
        }
        int haslabel=0;
        if(strcmp(a[0],"add") !=0 && strcmp(a[0],"sub") !=0 && strcmp(a[0],"slt") !=0
           && strcmp(a[0],"or") !=0 && strcmp(a[0],"nand")!=0 && strcmp(a[0],"addi")!=0 &&
           strcmp(a[0],"ori")!=0 && strcmp(a[0],"beq")!=0 && strcmp(a[0],"lui")!=0 &&
           strcmp(a[0],"lw")!=0 && strcmp(a[0],"jalr")!=0 && strcmp(a[0],"slti")!=0 &&
           strcmp(a[0],"sw")!=0 && strcmp(a[0],"j")!=0 && strcmp(a[0],"halt")!=0){
            haslabel=1;
        }
        if (haslabel ==1 ){
            l[lnum].address=i;
            strcpy(l[lnum].name , a[0]);
            lnum++;
        }
    }
    label_error();
    char b[5][6];
    int num2=0;
    for(int i=0 ; i<size2 ; i++){
        int j=0;
        int init_size = strlen(copy[i]);
        char delim[] = " ,";

        char *ptr = strtok(copy[i], delim);

        while(ptr != NULL)
        {
            if(ptr[0] == '#')break;
            strcpy(b[j],ptr);
            j++;
            num2=j;
            ptr = strtok(NULL, delim);
        }
        int haslabel=0;
        if(strcmp(b[0],"add") !=0 && strcmp(b[0],"sub") !=0 && strcmp(b[0],"slt") !=0
           && strcmp(b[0],"or") !=0 && strcmp(b[0],"nand")!=0 && strcmp(b[0],"addi")!=0 &&
           strcmp(b[0],"ori")!=0 && strcmp(b[0],"beq")!=0 && strcmp(b[0],"lui")!=0 &&
           strcmp(b[0],"lw")!=0 && strcmp(b[0],"jalr")!=0 && strcmp(b[0],"slti")!=0 &&
           strcmp(b[0],"sw")!=0 && strcmp(b[0],"j")!=0 && strcmp(b[0],"halt")!=0){
            haslabel=1;
        }
        if (haslabel == 0) {
            for (int i = num; i > 0; i--) {
                strcpy(b[i], b[i - 1]);
            }
            strcpy(b[0] ,"Z&B" ) ;
        }
        sep(b,i);
    }
    write_to_file(f);
    return 0;
}