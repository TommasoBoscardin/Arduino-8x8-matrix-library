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
	void parameters(int t1, int n1, bool p1=0); //t frequenza, n numero di fotogrammi p: 0=rowanod 1=rowcathod
	void image(byte A1[]);//A array di 8 byte
	void printMat();
	void printNum(int n, int k); //n intero di 2 cifre, k numero di fotogrammi
	void rotation(float s, float c); //s e c parametri reali(seno,coseno,...)
	void printMessage(String messaggio, byte s);//stampa il messaggio, s è il numero di fotogrammi per passo (5-10)

};

#endif
