
#include <iostream>
#include <omp.h>

using namespace std;

static long num_steps = 100000;
double step;
double sumasTotal = 0.0;

// void hacerSumaParcial(int ID, int start,int end){
//     double x,pi,sumaParcial = 0.0;

//     for(int i=start;i<end;i++){
//         x = (i+0.5)*step;
//         sumaParcial += 4.0/(1.0 + x * x);
//     }
//     pi = step * sumaParcial;
//     #pragma omp atomic
//         sumasTotal += pi;
// }

int main(){
    int i;
    
    step = 1.0/(double)num_steps;
    
    double start = omp_get_wtime();
    omp_set_num_threads(20);
    double x,pi;
    #pragma omp parallel for reduction (+:sumasTotal)
        for(int i=0;i<num_steps;i++){
            x = (i+0.5)*step;
            sumasTotal += 4.0/(1.0 + x * x);
        }

    double end = omp_get_wtime();

    cout<<end-start<<endl;
    cout<<"El valor de PI aproximado es "<<sumasTotal*step<<endl;

    return 0;
}