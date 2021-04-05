#include <Matrix.h>

void setup() {
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
}
byte Array1[8]={255,129,129,129,129,129,129,255};
byte Array2[8]={0,0,60,36,36,60,0,0};
byte Array3[8]={0,102,102,0,24,129,102,60};


void loop() {
  Matrix mat(2,3,4);
  mat.parameters(80,160);
  mat.image(Array1);
  mat.printMat();
  mat.image(Array2);
  mat.printMat();
  for(int i=11;i<100;i+=11){
    mat.printNum(i,80);
  }
  mat.image(Array3);
  mat.printMat();
  mat.rotation(0,-1);
  mat.printMat();
  mat.printMessage("Hello World",5);
}
