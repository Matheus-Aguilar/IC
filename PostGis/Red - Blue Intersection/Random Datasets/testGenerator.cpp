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
        double a = frand(100.0);
        double b = frand(100.0);
        cout << i << " " << a << " " << b << " " << a + frand(30.0) << " " << b + frand(30.0) << "\n"; 
    }    
}
