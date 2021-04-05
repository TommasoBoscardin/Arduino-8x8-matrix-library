#ifndef Matrix_h
#define Matrix_h
#include "Arduino.h"
class Matrix{
	private:
	byte A[8];
	int t;
	int n;
	bool p=0;
	int signal;//2
	int shiftClock;//3
	int registerClock;//4
	public:
	Matrix(int s, int sc, int rc); //s signal, sc shiftClock, rc registerClock
	void parameters(int t1, int n1, bool p1=0); //t frequenza, n numero di fotogrammi, p: 0=rowanod 1=rowcathod
	void image(byte A1[]);//A array di 8 byte
	void printMat();
	void printNum(int n, int k); //n intero di 2 cifre, k numero di fotogrammi
	void rotation(float s, float c); //s e c parametri reali(seno,coseno,...)
	void printMessage(String messaggio, byte s);//stampa il messaggio, s è il numero di fotogrammi per passo (5-10)
	
};
Matrix::Matrix(int s, int sc, int rc){
	signal=s;
	shiftClock=sc;
	registerClock=rc;
	pinMode(s,OUTPUT);
	pinMode(sc,OUTPUT);
	pinMode(rc,OUTPUT);
}
void Matrix::parameters(int t1, int n1, bool p1=0){
	t=t1;
	n=n1;
	p=p1;
}
void Matrix::image(byte A1[]){
	for(int i=0;i<8;i++){
		A[i]=A1[i];
	}
}
void Matrix::printMat(){
    //6 -5 8 -3 -2 7 5 3 -8 -7 2 -1 4 -6 -4 1
  byte r[16] = {22,8,24,32,64,23,21,19,1,2,18,128,20,4,16,17};
  int k=n;
  while (k>0){
    for (int i=0; i<8; i++){
      for(int j=0; j<16; j++){
        digitalWrite(shiftClock, LOW);
        if (16<r[j]&&r[j]<25){
            digitalWrite(signal, (r[j]==i+17)^p);
        }
        else{
            digitalWrite(signal, ((A[i] & r[j])==0)^p);
        }
        digitalWrite(shiftClock, HIGH);
      }
      digitalWrite(registerClock, LOW);
      digitalWrite(registerClock, HIGH);
      delayMicroseconds(1000000/(8*t));
    }
    k--;
  }
}

void Matrix::printNum(int n1, int k){
  byte cifre[10][4]{{105,153,153,150},
                    {38,162,34,39},
                    {105,147,38,207},
                    {105,23,17,150},
                    {38,175,34,39},
                    {248,142,17,150},
                    {105,142,153,150},
                    {249,34,68,136},
                    {105,150,153,150},
                    {105,153,113,150}};
  //byte A[8];
  int a=n1%10;
  int b=(n1/10)%10;
  for(int i=0; i<4; i++){
    A[2*i]=(cifre[b][i]/16)*16+cifre[a][i]/16;
    A[2*i+1]=(cifre[b][i]%16)*16+cifre[a][i]%16;
  }
  t=80;
  n=k;
  printMat();
}

void Matrix::rotation(float s, float c){
  byte B[8]={0,0,0,0,0,0,0,0};
  byte r[8]={128,64,32,16,8,4,2,1};
  int x=0;
  int y=0;
  for(int i=0; i<8; i++){
    for(int j=0; j<8;j++){
     if((A[i]&r[j])!=0){
        int fx=c*(2*i-7)-s*(2*j-7);
        int fy=s*(2*i-7)+c*(2*j-7);
        if(fx%2!=0){
          x=(fx-1)/2+4;
        }
        else {x=fx/2+4;}

        if(fy%2!=0){
          y=(fy-1)/2+4;
        }
        else {y=fy/2+4;}

       if(-1<x && x<8 && -1<y && y<8){
          B[x]=B[x]|r[y];
        }
      }
    }
  }
  for(int i=0;i<8;i++){
		A[i]=B[i];
	}
}
void Matrix::printMessage(String messaggio, byte s){
  n=s;
  t=80;
  messaggio=messaggio+"  ";
  byte lettere [52][5]={{254,17,17,254,0},//A
  {255,137,137,118,0},//B
  {126,129,129,66,0},//C
  {255,129,129,126,0},//D
  {255,137,137,129,0},//E
  {255,9,9,1,0},//F
  {126,129,145,114,0},//G
  {255,8,8,255,0},//H
  {255,0,0,0,0},//I
  {65,129,127,1,0},//J
  {255,8,20,227,0},//K
  {255,128,128,128,0},//L
  {255,2,4,2,255},//M
  {255,12,48,255,0},//N
  {126,129,129,126,0},//O
  {255,9,9,6,0},//P
  {126,161,193,254,0},//Q
  {255,9,57,230,0},//R
  {70,137,137,114,0},//S
  {1,255,1,0,0},//T
  {127,128,128,127,0},//U
  {15,48,192,48,15},//V
  {63,192,62,192,63},//W
  {195,52,8,52,195},//X
  {7,8,240,8,7},//Y
  {193,177,141,131,0},//Z
  {96,148,148,248,0},//a
  {255,136,136,112,0},//b
  {120,132,132,72,0},//c
  {112,136,136,255,0},//d
  {120,164,164,24,0},//e
  {16,254,17,2,0},//f
  {24,164,164,120,0},//g
  {255,16,16,224,0},//h
  {128,244,128,0,0},//i
  {64,136,120,8,0},//j
  {255,32,80,136,0},//k
  {127,128,0,0,0},//l
  {252,8,240,8,240},//m
  {252,8,8,240,0},//n
  {112,136,136,112,0},//o
  {248,36,36,24,0},//p
  {24,36,36,248,0},//q
  {252,16,16,8,0},//r
  {72,148,148,96,0},//s
  {4,127,132,64,0},//t
  {120,128,128,120,0},//u
  {56,64,128,64,56},//v
  {120,128,120,128,120},//w
  {136,80,32,80,136},//x
  {68,136,144,124,0},//y
  {196,164,148,140}//z
  };
  byte r[8]={1,2,4,8,16,32,64,128};
  for(int k=0; k<messaggio.length(); k++){
    int j=0;
    char a=messaggio[k];
    if(a==' '){
      for(int j=0; j<2; j++){
        for(int i=0; i<8; i++){
          A[i]=A[i]*2;
        }
		printMat();
      }
    }
    else{
      int n=(byte)a-65;
      if(n>26){
        n=n-6;
      }
      while(j<5 && lettere[n][j]!=0){
        for(int i=0; i<8; i++){
          A[i]=A[i]*2+((lettere[n][j]&r[i])!=0);
        }
		printMat();
        j++;
      }
    }
    for(int i=0; i<8; i++){
      A[i]=A[i]*2;
    }
	printMat();
  }
}

#endif
