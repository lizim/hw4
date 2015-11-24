#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cmath>

using namespace std;

double* read_data(int N);
void filter(double* p, int N);
void makefile(double* p, int N);


int main(){  
  const int N = 237;
  
  double* p = read_data(N);
  
  filter(p,N);
   
  makefile(p,N);
  
  delete[] p;
  
  return 0;
}


double* read_data(int N){
  
  double* p = new double[N];
  
  const string filename = "noisy.txt";
  ifstream in(filename.c_str());
  for(int i=0; i<N; i++){
    in >> p[i];
  }
  in.close();
  return p;
}

void filter(double* p, int N){
  
  //Zwischenvariablen zur Filterung 
    //fuer Schleife
    double temp1 = p[0];
    double temp2;
    
    //fuer Randbedingungen
    double temp_p0  = p[0];
    double temp_p1  = p[1];
    double temp_pN2 = p[N-2];
  
  for(int i=1; i<(N-1); i++){
    
    temp2 = temp1;
    temp1 = p[i];
    p[i] = (temp2 + p[i] + p[i+1])/3;
  }
   
  //periodische Randbedingungen    
  p[0] = (p[N-1] + p[0] + temp_p1)/3;
  p[N-1] = (temp_pN2 + p[N-1] + temp_p0)/3;
}

void makefile(double* p, int N){
  ofstream out("filtered.txt");
  for (int i=0; i<N; i++)   out << p[i] << endl;
  out.close();
}
