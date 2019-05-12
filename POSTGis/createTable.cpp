//O código a seguir cria uma tabela com um nome definido
//e insere um número n de arestas compostas por um id e
//2 pontos com 2 coordenadas

#include <iostream>
#include <string>
#include <pqxx/pqxx>

using namespace std;

int main(int argc, char* argv[]) {
    
    /*Conectando à base de dados*/
    pqxx::connection C("dbname = teste user = postgres password = 180700 \
    hostaddr = 127.0.0.1 port = 5432");
    if (C.is_open()) {
        cout << "Opened database successfully: " << C.dbname() << endl;
    } else {
        cout << "Can't open database" << endl;
        return 1;
    }

    //Variáveis que irão executar e armazenar a query SQL, respectivamente
    pqxx::work W(C);
    string sql = "";

    /*Criando a tabela e o índice geométrico*/
    string name;
    cin >> name;
    
    sql = sql + "CREATE TABLE " + name + " (id serial PRIMARY KEY, aresta geometry(LineString) NOT NULL);";

    sql = sql + "CREATE INDEX " + name + "_index ON " + name + " USING GIST(aresta);";


    W.exec(sql); //Executando o SQL

    int n;
    cin >> n;

    sql = "";

    //Inserindo as arestas
    for(int i = 0; i < n; i++){
        string id, px, py, qx, qy;
        cin >> id >> px >> py >> qx >> qy;
        sql = sql + "INSERT INTO " + name + " VALUES(" + id + ", 'LINESTRING(" + px + " " + py + ", " + qx + " " + qy + ")');";
    }

    //Executando e comitando o SQL
    W.exec(sql);
    W.commit();

    /*Encerrando a conexão*/
    C.disconnect();
}