//O código a seguir recebe o nome de duas tabelas
//de aretas e retorna quais são as interseções
//entre elas
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

double frand(double limit){
    return (rand()%2?1:-1) * (rand())/(RAND_MAX/limit);
}

int main(int argc, char* argv[]) {
    srand(time(0));
    int n = atoi(argv[2]);
    cout << argv[1] << "\n";
    cout << n << "\n";
    for(int i = 0; i < n; i++){
        cout << i << " " << frand(100.0) << " " << frand(100.0) << " " << frand(100.0) << " " << frand(100.0) << "\n"; 
    }    
}