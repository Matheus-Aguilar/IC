//O código a seguir recebe o nome de duas tabelas
//de aretas e retorna quais são as interseções
//entre elas

#include <iostream>
#include <string>
#include <chrono>
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
    string name1 = argv[1], name2 = argv[2];
    
    if(argv[3][0] == '0')
        sql = sql + "SELECT COUNT(*) AS number_intersections FROM " + name1 + "," + name2 + " WHERE ST_DWITHIN(" + name1 + ".aresta," + name2 + ".aresta, 0);";
    else if(argv[3][0] == '1')
        sql = sql + "SELECT COUNT(*) AS number_intersections FROM " + name1 + " INNER JOIN " + name2 + " ON ST_DWITHIN(" + name1 + ".aresta," + name2 + ".aresta, 0);";
        
    auto begin = chrono::steady_clock().now();

    //Executando o SQL
    pqxx::result R(N.exec(sql));

    auto end = chrono::steady_clock().now();
    cout << chrono::duration_cast<chrono::milliseconds>(end - begin).count() / 1000.0 << " seconds\n";

    cout << R[0][0] << " intersections\n";

    /*Encerrando a conexão*/
    C.disconnect();
}
