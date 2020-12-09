/*
  Solucao do problema das linhas de onibus de Joao Pessoa

  Grupo: Andre Passos
         Julio Cesar

  * Main *

  Credits to Cristopher Freitas
*/

#include <iostream>
#include "graph.cpp"

using namespace std;

int main(int argc, const char * argv[]) {
    Graph * map = new Graph();
    int start, finish;
    char resposta = 's';

    cout << "*** AGENTE DE VIAGENS - LINHAS DE ONIBUS JP ***" << endl << endl;
    cout << "Indique as paradas (de 1 a 11)" << endl;
    cout << "> Parada de partida: ";
    cin >> start;
    cout << "> Parada de chegada: ";
    cin >> finish;

    if (start < 1 || start > 11 || finish < 1 || finish > 11) {
        cout << endl << "ERRO: Uma das paradas eh invalida!" << endl;
        return (0);
    }

    cout << endl << "Melhor percurso: " << endl << endl;
    // travelling from start to finish.
    map->travel(start, finish);

    return (0);
}
