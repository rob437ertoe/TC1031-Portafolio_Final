//Integrantes del equipo
//Samantha Benítez Rentería
//Felipe de Jesús González Acosta
//Jonathan Eliud Fernández Zamora
//Roberto Eduardo Cardona Luis
//Ariadna Daniela Medina García
//Luis Fernando Cabral
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

//Creamos los nodos de los grafos con los IP
//Entrada: Información de las IP del documento
//Salida:Ninguna
//Complejidad: O(n)
class NodeIP {
  private:
    int nVecinos, index;
    string IPstring;

  public:
    NodeIP();
    NodeIP(string,int);
    void addNeighbor(int);
    int getnVecinos();
    string getIP();
    vector<int> neighbors;
};

  NodeIP::NodeIP(){
    nVecinos=0;
    IPstring="";
    neighbors={0};
    index=0;
  }
  
  NodeIP::NodeIP(string _IPstring,int _index){
    nVecinos=0;;
    IPstring=_IPstring;
    index=_index;
  }
  
  void NodeIP::addNeighbor(int _inx){
    neighbors.push_back(_inx);
    nVecinos+=1;
  }
  
  int NodeIP::getnVecinos(){
    return nVecinos;
  }
  
  string NodeIP::getIP(){
    return IPstring;
  }

//Clase para derterminar las conexiones entre los nodos
//Entrada: Nodos
//Salida: Nada
//Complejidad O(n)
class Graph {
private:
  vector<NodeIP> v;
  int size;
  void swap(int,int);
  void Graphify(int);
  void GraphifyD(int,int);
public:
  Graph();
  void insertNode(NodeIP);
  void deleteRoot();
  NodeIP top();
  bool empty();
  int getSize();
  string print(int, int);
  string printBootMaster();
  void GraphSort();
};

  Graph::Graph() {
    v = {};
    size = 0;
  }

  void Graph::swap(int i,int j) {
    NodeIP temporal;
    temporal = v[i];
    v[i] = v[j];
    v[j] = temporal;
  }

  void Graph:: Graphify(int i) {
    int parent = (i - 1) / 2;
    if (v[parent].getnVecinos() > 0) {
      if (v[i].getnVecinos() < v[parent].getnVecinos()) {
          swap(i, parent);
          Graphify(parent);
      }
    }
  }

//Insertamos nodos
  void Graph::insertNode(NodeIP key) {
    size ++;
    v.push_back(key);
    Graphify(size - 1);
  }

//Se analiza el tamaño de conexiones
  void Graph::GraphifyD(int n, int i) {
    int small = i; 
    int l = 2 * i + 1; 
    int r = 2 * i + 2; 
    if (l < n && v[l].getnVecinos() < v[small].getnVecinos())
        small = l;
    if (r < n && v[r].getnVecinos() < v[small].getnVecinos())
        small = r;
    if (small != i) {
        swap(i,small);
        GraphifyD(n,small);
    }
  }

//ELiminar filas
//Complejidad O(1)
  void Graph::deleteRoot() {
    NodeIP lastElement = v[size - 1];
    v[0] = lastElement;
    v.pop_back();
    size = size - 1;
    GraphifyD(size,0);
  }

  NodeIP Graph::top() {
    return v[0];
  }

//Verificamos que este vacio
  bool Graph::empty() {
    return size == 0;
  }

//Tamaño de las conexiones (grado)
//Complejidad O(1)
  int Graph::getSize() {
    return size;
  }

//Imprimimos los ip con más conexiones
//Entrada: tamaño del grado
//Salida: Impresion de las conexiones
  string Graph::print(int start, int end) {
    stringstream aux;
    for (int i = start; i < end; i++) {
      aux << v[i].getIP() << ": " << v[i].getnVecinos() << endl;
    }
    return aux.str();
  }

//Imprimimos los que tengan las mayores conexiones
//Entrada: Nada
//Salida: Impresión de las direcciones
  string Graph::printBootMaster() {
    stringstream aux;
    int start = 0;
    int end = 2;
    for (int i = start; i < end; i++) {
      aux << v[i].getIP() << ": " <<v[i].getnVecinos() << endl;
    }
    return aux.str();
}

  void Graph::GraphSort() {
    for (int i = size - 1; i >= 0; i--) {
      swap(0, i);
      GraphifyD(i,0);
    }
  }

class BitGrafo {
private:
  int nNode;
  int nEdge;
  map<string, int> dic;
  ifstream inFile;
  vector<NodeIP> listaAdj;
  Graph Graph1;
  void loadList(const string &arch);

public:
  BitGrafo();
  BitGrafo(const string &arch);
  string printListaAdj();
  string DFS(int, int);
  string BFS(int, int);
  Graph create_sort();
  void printGrafo(const string &arch);
  void printGraph(const string &arch);
  void printNodos(int, int);
  void printBootMaster();
};

  BitGrafo::BitGrafo() {
    nNode = 0;
    nEdge = 0;
}

  BitGrafo::BitGrafo(const string &arch) { loadList(arch); }

//Leemos el documento y leemos linea por linea
  void BitGrafo::loadList(const string &arch) {
    inFile.open(arch);
    string line;
    int cont = -1;
    string trash;
    string ip1;
    string ip2;
    if (inFile.is_open()) {
      while (getline(inFile, line)) {
        if (line.empty()) {
          continue;
        }
        if (cont == -1) {
          istringstream strstr(line);
          strstr >> nNode >> nEdge;
          cont++;
          continue;
        } else if (cont < nNode) {
          NodeIP curr;
          curr = NodeIP(line, cont);
          dic[line] = cont;
          listaAdj.push_back(curr);
          cont++;
          continue;
        } else {
          istringstream ss(line);
          ss >> trash >> trash >> trash >> ip1 >> ip2 >> trash;
          string::size_type pos = ip1.find(':');
          if (pos != string::npos) {
            ip1 = ip1.substr(0, pos);
          }
          string::size_type pos1 = ip2.find(':');
          if (pos1 != string::npos) {
            ip2 = ip2.substr(0, pos1);
          }
          int ip1indx = dic[ip1];
          int ip2indx = dic[ip2];
          NodeIP from = NodeIP(ip1, ip1indx);
          listaAdj[ip1indx].addNeighbor(ip2indx);
          cont++;
          continue;
        }
      }
    } else {
      std::cout << "Unable to open file";
    };
  }

//Guardamos la lista completa en el nuevo archivo
  string BitGrafo::printListaAdj() {
    stringstream aux;
    for (int i = 0; i < nNode; i++) {
      aux << "IP " << listaAdj[i].getIP() << " :";
      for (int j = 0; j < listaAdj[i].getnVecinos(); j++) {
        aux << ": " << listaAdj[listaAdj[i].neighbors[j]].getIP();
      }
      aux << "\n";
    }
    return aux.str();
  }

//Imprimimos la lista
  void BitGrafo::printGrafo(const string &arch) {
    ofstream outfile(arch);
    outfile << printListaAdj();
  }

Graph BitGrafo::create_sort() {
    for (int i = 0; i < nNode; i++) {
      Graph1.insertNode(listaAdj[i]);
    }
    Graph1.GraphSort();
    return Graph1;
  }

  void BitGrafo::printGraph(const string &arch) {
    ofstream outfile(arch);
    outfile << Graph1.print(0, Graph1.getSize());
  }

  void BitGrafo::printNodos(int start, int end) {
    cout << Graph1.print(start, end);
  }

    void BitGrafo::printBootMaster() { cout << Graph1.printBootMaster(); }

int main(){
    BitGrafo bit1 = BitGrafo("bitacoraGrafos.txt");
    bit1.printGrafo("bitacoraGrafosFinal.txt");
    cout << "Lista de Adyacencia" << endl;
    cout << "La lista de adyacencia se almaceno en" << endl;     
    cout << "el archivo 'bitacoraGrafosFinal.txt'." << endl;
    bit1.create_sort();
    bit1.printGraph("bitacoraConexiones.txt");
    cout << endl;
    cout << "Las primeras 5 IPs con mas conexiones:" << endl;
    bit1.printNodos(0,5);
    cout<<endl;
    cout << "Direccion de los Boot Masters" << endl;
    bit1.printBootMaster();
    cout<<endl;
    cout<<"Las IPs ordenadas por conexiones se" << endl;
    cout << "almacenaron en el archivo 'bitacoraConexiones.txt'."<<endl;
    return 0;
}