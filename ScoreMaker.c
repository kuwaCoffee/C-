#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float Score[256];
FILE *file;

void Input_Data();
int Input_Score();
float Input_Avr(int);
void Rank(float);

int main(){
    char Transed[256],Before[256];
    float SIZE,AVR;
    
    file = fopen("/Users/kuwatakeidai/excelFiles/ScoreFile.csv","w"); //ファイルの設定とエラー出力
    if(file == NULL){
        printf("file cant open");
        exit(1);
    }

    Input_Data();//個人データの入力
    fprintf(file,"Subject,Score\n");
    SIZE = Input_Score();//点数の入力、ファイルへの出力
    AVR = Input_Avr(SIZE);//平均点の計算、Cファイルへの出力、引数SIZEは科目数
    Rank(AVR);//順位予想、引数は平均点
    fclose(file);
}

void Input_Data(){
    char Name[256],cls[256];
    printf("名前を入力\n");
    scanf("%s",Name);
    printf("学科を入力\n");
    scanf("%s",cls);
    fprintf(file,"%s,%s\n",Name,cls);
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

void Rank(float Avr){
    if(Avr <= 100 && Avr >= 95)
        fprintf(file,"Rank would be,1~5");
    else if(Avr < 95 && Avr >= 90)
        fprintf(file,"Rank would be,5~10");
    else if(Avr < 90 && Avr >= 80)
        fprintf(file,"Rank would be,10~20");
    else if(Avr < 80 && Avr >= 75)
        fprintf(file,"Rank would be,20~25");
    else if(Avr < 75 && Avr >= 70)
        fprintf(file,"Rank would be,25~30");
    else if(Avr < 70 && Avr >= 60)
        fprintf(file,"Rank would be,30~");    
}



