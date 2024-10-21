#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <queue>

using namespace std;

struct Transicion {
    int origen;
    int simbolo;
    int destino;
};

void leerArchivoEntrada(const string& nombreArchivo, vector<int>& estados, vector<int>& estadosAceptacion, vector<int>& simbolos, vector<Transicion>& transiciones) {
    ifstream archivo(nombreArchivo);
    string linea;
    int cantidad;

    // Leer estados
    while (getline(archivo, linea) && linea != "Estados");
    archivo >> cantidad;
    estados.resize(cantidad);
    for (int i = 0; i < cantidad; ++i) {
        archivo >> estados[i];
    }

    // Leer estados de aceptación
    while (getline(archivo, linea) && linea != "Estados_de_Aceptacion");
    archivo >> cantidad;
    estadosAceptacion.resize(cantidad);
    for (int i = 0; i < cantidad; ++i) {
        archivo >> estadosAceptacion[i];
    }

    // Leer símbolos de entrada
    while (getline(archivo, linea) && linea != "Entradas");
    archivo >> cantidad;
    simbolos.resize(cantidad);
    for (int i = 0; i < cantidad; ++i) {
        archivo >> simbolos[i];
    }

    // Leer transiciones
    while (getline(archivo, linea) && linea != "Transiciones_(x,y,z)_epsilon=-1");
    archivo >> cantidad;
    transiciones.resize(cantidad);
    for (int i = 0; i < cantidad; ++i) {
        archivo >> transiciones[i].origen >> transiciones[i].simbolo >> transiciones[i].destino;
    }
}

set<int> e_clausura(const set<int>& R, const map<int, vector<int>>& transicionesEpsilon) {
    set<int> clausura = R;
    queue<int> pila;
    for (int r : R) {
        pila.push(r);
    }

    while (!pila.empty()) {
        int r = pila.front();
        pila.pop();
        if (transicionesEpsilon.count(r)) {
            for (int s : transicionesEpsilon.at(r)) {
                if (clausura.find(s) == clausura.end()) {
                    clausura.insert(s);
                    pila.push(s);
                }
            }
        }
    }

    return clausura;
}

void convertirAFNaAFD(const vector<int>& estados, const vector<int>& estadosAceptacion, const vector<int>& simbolos, const vector<Transicion>& transiciones) {
    map<int, vector<int>> transicionesEpsilon;
    map<pair<int, int>, vector<int>> transicionesSimbolo;

    for (const auto& t : transiciones) {
        if (t.simbolo == -1) {
            transicionesEpsilon[t.origen].push_back(t.destino);
        } else {
            transicionesSimbolo[{t.origen, t.simbolo}].push_back(t.destino);
        }
    }

    set<int> estadoInicial = {estados[0]};
    set<int> e_clausuraInicial = e_clausura(estadoInicial, transicionesEpsilon);

    map<set<int>, int> estadosAFD;
    vector<set<int>> estadosAFDList = {e_clausuraInicial};
    estadosAFD[e_clausuraInicial] = 0;
    int contadorEstados = 1;

    map<pair<int, int>, set<int>> transicionesAFD;
    queue<set<int>> estadosNoMarcados;
    estadosNoMarcados.push(e_clausuraInicial);

    while (!estadosNoMarcados.empty()) {
        set<int> R = estadosNoMarcados.front();
        estadosNoMarcados.pop();

        for (int simbolo : simbolos) {
            set<int> U;
            for (int r : R) {
                if (transicionesSimbolo.count({r, simbolo})) {
                    for (int s : transicionesSimbolo[{r, simbolo}]) {
                        U.insert(s);
                    }
                }
            }
            U = e_clausura(U, transicionesEpsilon);

            if (!U.empty() && estadosAFD.find(U) == estadosAFD.end()) {
                estadosAFD[U] = contadorEstados++;
                estadosAFDList.push_back(U);
                estadosNoMarcados.push(U);
            }

            if (!U.empty()) {
                transicionesAFD[{estadosAFD[R], simbolo}] = U;
            }
        }
    }

    cout << "Estados:" << endl;
    for (const auto& estado : estadosAFDList) {
        cout << estadosAFD[estado] << " = { ";
        for (int e : estado) {
            cout << e << " ";
        }
        cout << "}" << endl;
    }

    cout << "Estados de Aceptacion:" << endl;
    for (const auto& estado : estadosAFDList) {
        for (int e : estado) {
            if (find(estadosAceptacion.begin(), estadosAceptacion.end(), e) != estadosAceptacion.end()) {
                cout << estadosAFD[estado] << " ";
                break;
            }
        }
    }
    cout << endl;

    cout << "Transiciones de Estados (x,y,z):" << endl;
    for (const auto& trans : transicionesAFD) {
        cout << trans.first.first << " " << trans.first.second << " " << estadosAFD[trans.second] << endl;
    }
}

int main() {
    vector<int> estados;
    vector<int> estadosAceptacion;
    vector<int> simbolos;
    vector<Transicion> transiciones;

    string nombreArchivo = "in.txt";
    leerArchivoEntrada(nombreArchivo, estados, estadosAceptacion, simbolos, transiciones);
    convertirAFNaAFD(estados, estadosAceptacion, simbolos, transiciones);

    return 0;
}
