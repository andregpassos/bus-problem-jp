/*
  Solucao do problema das linhas de onibus de Joao Pessoa

  Grupo: Andre Passos
         Julio Cesar

  * Header File *

  Grafo das distancias, conexoes e linhas de onibus

  Credits to Cristopher Freitas
*/


#ifndef graph_hpp
#define graph_hpp

#include <iostream>
#include <vector>
#include "node.hpp"

using namespace std;

class Graph {

private:
    vector<vector<float>> distances;
    vector<vector<int>> adj;
    vector<vector<int>> lines;
    int t; // target
    Node * node;

protected:
    float calcTime(float distance);
    bool verify(Node * current, int target);
    void changeLine(Node * node, int line);
    vector<int> getLines(int source, int target);
    vector<Node *> getNext(Node * node);
    Node * move(vector<Node *> nexts);
public:
    Graph();
    int travel(int s, int t);
};

#endif /* graph_hpp */
