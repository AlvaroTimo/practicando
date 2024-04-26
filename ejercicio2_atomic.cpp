
#include <iostream>
#include <omp.h>

using namespace std;

static long num_steps = 100000;
double step;
double sumasTotal = 0.0;

void hacerSumaParcial(int ID, int start,int end){
    double x,pi,sumaParcial = 0.0;

    for(int i=start;i<end;i++){
        x = (i+0.5)*step;
        sumaParcial += 4.0/(1.0 + x * x);
    }
    pi = step * sumaParcial;
    #pragma omp atomic
        sumasTotal += pi;
}

int main(){
    int i;
    
    step = 1.0/(double)num_steps;
    
    double start = omp_get_wtime();
    omp_set_num_threads(20);
    #pragma omp parallel
    {
        int ID = omp_get_thread_num();
        int chunk_size = num_steps/double(omp_get_num_threads());
        int start = chunk_size*ID;
        int end = chunk_size*(ID+1);
        hacerSumaParcial(ID,start,end);
    }

    double end = omp_get_wtime();

    cout<<end-start<<endl;
    cout<<"El valor de PI aproximado es "<<sumasTotal<<endl;

    return 0;
}