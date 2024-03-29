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
    string name = argv[2];
    
    sql = sql + "CREATE TABLE " + name + " (id serial PRIMARY KEY, aresta geometry(LineString) NOT NULL, CONSTRAINT  enforce_srid CHECK (st_srid(aresta) = 4269));";

    if(argv[1][0] == '1')
        sql = sql + "CREATE INDEX " + name + "_index ON " + name + " USING GIST(aresta);";

    W.exec(sql); //Executando o SQL

    int n;
    cin >> n;

    vector<int>pid;
    vector<string>px;
    vector<string>py;

    pid.resize(n);
    px.resize(n);
    py.resize(n);

    for(int i = 0; i < n; i++){
        cin >> pid[i] >> px[i] >> py[i]; 
    }

    cin >> n;

    sql = "";

    cerr << n << "\n";

    //Inserindo as arestas
    for(int i = 0; i < n; i++){
        string id;
        int pid0, pid1, aux;
        cin >> id >> pid0 >> pid1 >> aux >> aux;
        sql = "INSERT INTO " + name + " VALUES(" + id + ", ST_GEOMFROMTEXT('LINESTRING(" + px[pid[pid0]] + " " + py[pid[pid0]] + ", " + px[pid[pid1]] + " " + py[pid[pid1]] + ")', 4269));";
        W.exec(sql);
        cerr << i << "\n";
    }

    //Executando e comitando o SQL
    W.commit();

    /*Encerrando a conexão*/
    C.disconnect();
}