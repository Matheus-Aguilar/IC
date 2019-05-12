//O código a seguir recebe o nome de duas tabelas
//de aretas e retorna quais são as interseções
//entre elas

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
    pqxx::nontransaction N(C);
    string sql = "";

    /*Pegando os nomes das tabelas e realizando a consulta*/
    string name1, name2;
    cin >> name1 >> name2;
    
    sql = sql + "SELECT " + name1 + ".id AS " + name1 + "_id, ST_AsText(" + name1 + ".aresta) AS " + name1 + "_aresta, " + name2 + ".id AS " + name2 + "_id, ST_AsText(" + name2 + ".aresta) AS " + name2 + "_aresta FROM " + name1 + "," + name2 + " WHERE ST_INTERSECTS(" + name1 + ".aresta," + name2 + ".aresta);";

    //Executando o SQL
    pqxx::result R(N.exec(sql));
    
    for(auto i:R){
        cout << i[0] << " " << i[1] << " " << i[2] << " " << i[3] << "\n";
    }

    /*Encerrando a conexão*/
    C.disconnect();
}