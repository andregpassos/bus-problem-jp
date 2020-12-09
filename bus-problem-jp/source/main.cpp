/*
  Solucao do problema das linhas de onibus de Joao Pessoa

  Grupo: Andre Passos
         Julio Cesar

  * Main *

  Credits to Cristopher Freitas
*/

#include <iostream>
#include "graph.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    // initializing the map
    Graph * map = new Graph();

    // travelling from point s to t.
    map->travel(1,5);
    return 0;
}
