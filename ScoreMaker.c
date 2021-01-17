#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float Score[256];
char cls[256];
int Num = 0;
FILE *file;
FILE *avrfile;
FILE *rank;
float table[256];

void Input_Num();
void Input_Data();
int Input_Score();
float Input_Avr(int);
void Output_Avr(float);
void Table_Maker(float);
void Rank_Maker(int);

int main(){
    float SIZE,AVR;
    int clsmate = 0;
    char filename[256];

    printf("クラスの人数を入力\n");
    scanf("%d",&clsmate);
    for(int i = 1;i <= clsmate;i++){   
    Input_Num();//番号学科入力
    sprintf(filename,"/Users/kuwatakeidai/excelFiles/%s-%d's Score.csv",cls,Num);
    file = fopen(filename,"w"); //ファイルの設定とエラー出力
    
    if(file == NULL){
        printf("file cant open");
        exit(1);
    }
    Input_Data();//個人データの入力
    fprintf(file,"Subject,Score\n");
    SIZE = Input_Score();//点数の入力、ファイルへの出力
    AVR = Input_Avr(SIZE);//平均点の計算、Cファイルへの出力、引数SIZEは科目数
    fclose(file);
    Output_Avr(AVR);//平均点を別ファイルに出力
    Table_Maker(AVR);
    }
    Rank_Maker(clsmate);
}


void Input_Num(){
    printf("番号を入力\n");
    scanf("%d",&Num);
    printf("学科を入力\n");
    scanf("%s",cls);
}

void Input_Data(){
    char Name[256];
    printf("名前を入力\n");
    scanf("%s",Name);
    fprintf(file,"%s,%s,%d\n",Name,cls,Num);
}

int Input_Score(){
    int size = 0;
    char sub[256];
    printf("科目数を入力\n");
    scanf("%d",&size);
    for(int i = 0;i < size;i++){
        printf("科目を入力\n");
        scanf("%s",sub);
        printf("%sの点数を入力\n",sub);
        scanf("%f",&Score[i]);
        fprintf(file,"%s,%f\n",sub,Score[i]);
    }
    return size;
}

float Input_Avr(int size){
    float Avr=0;
    for(int i = 0;i < size;i++){
        Avr += Score[i];
    }
    Avr /= size;
    fprintf(file,"Avarage,%f\n",Avr);
    return Avr;
}

void Output_Avr(float AVR){
    avrfile = fopen("/Users/kuwatakeidai/excelFiles/avr.csv","a");//平均点をavrファイルに出力
    
    if(avrfile == NULL){
        printf("avrfile cant open");
        exit(1);
    }
    for(int i = 0; i < Num; i++){
        fprintf(file,"\n");//番号のセルまで改行(要改善)
    }
    fprintf(file,"%d,%f",Num,AVR);//番号と平均点を書き込む
    fclose(avrfile);  
}

void Table_Maker(float AVR){
    table[Num] = AVR;
}

void Rank_Maker(int clsmate){
    float max;
    max = 0;
    char filename[256];
    for(int i = 1; i <= clsmate; i++ ){
        if(table[i] >= max){
            max = table[i];
        }
    }
    sprintf(filename,"/Users/kuwatakeidai/excelFiles/rank.csv");
    rank = fopen(filename,"w");
    for(int i = 1; i <= clsmate; i++){
        fprintf(rank,"%d,%f\n",i,table[i]);
    }

}