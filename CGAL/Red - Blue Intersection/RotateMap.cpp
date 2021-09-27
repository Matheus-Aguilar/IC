#include<bits/stdc++.h>
#define PI 3.14159265359

using namespace std; 

int main(int argc, char **argv){
    
    ifstream in; //Mapa de entrada
    ofstream out; //Mapa de saída

    //Abrindo os arquivos
    in.open(argv[1], ios_base::in);
    out.open(argv[2], ios_base::out);

    int NP; //Número de Pontos
    //Vetor de pontos (id, coord x, coord y)
    vector<tuple<int, double, double>> pontos;
    
    //Coord x e y minima e maxima (para o bbox)
    double minX, minY, maxX, maxY;

    int NE; //Número de arestas

    int id;
    double x, y;    

    in >> NP;
    in >> id >> x >> y;

    minX = maxX = x;
    minY = maxY = y;
    pontos.push_back({id, x, y});

    out << NP << '\n';

    //Le os pontos
    while(--NP){
        in >> id >> x >> y;

        minX = fmin(minX, x);
        minY = fmin(minY, y);
        maxX = fmax(maxX, x);
        maxY = fmax(maxY, y);
        
        pontos.push_back({id, x, y});
    }

    //Angulo de rotacao (convertido de graus para radianos)
    double angulo = (PI * atof(argv[3]))/180;

    //Novos centros, baseados no bbox
    double xCentro = (maxX + minX)/2;
    double yCentro = (maxY + minY)/2;

    for(auto i:pontos){
        
        //Passando para o novo eixo de coordenadas
        get<1>(i) -= xCentro;
        get<2>(i) -= yCentro;

        //Aplicando a matriz de rotacao
        double xNovo = get<1>(i) * cos(angulo) + get<2>(i) * sin(angulo);
        double yNovo = -get<1>(i) * sin(angulo) + get<2>(i) * cos(angulo);

        //Retornando para o eixo de coordenadas original
        get<1>(i) = xNovo + xCentro;
        get<2>(i) = yNovo + yCentro;
    
        out << get<0>(i) << " " << get<1>(i) << " " << get<2>(i) << "\n";
    }

    in >> NE;
    out << NE << "\n";
    
    while(NE--){
        int id, p1, p2, fp, fn;
        in >> id >> p1 >> p2 >> fp >> fn;
        out << id << " " << p1 << " " << p2 << " " << fp << " " << fn << "\n";
    }

    in.close();
    out.close();
}