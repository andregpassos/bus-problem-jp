/*
  Solucao do problema das linhas de onibus de Joao Pessoa

  Grupo: Andre Passos
         Julio Cesar

  * Source File *

  Nos dos caminhos (paradas de onibus)

  Credits to Cristopher Freitas
*/


#include "node.hpp"

Node::Node(int station, int line){
    this->line = line;
    this->station = station;
    this->cost = 0;
}

Node::Node(const Node & other){
    Node * n = new Node(other.line, other.station);
    n->setParent(other.prev);
    n->setCost(other.cost);
}

void Node::setParent(Node *prev){
    this->prev = prev;
}

Node * Node::getParent(){
    return this->prev;
}

void Node::setCost(float cost){
    this->cost = cost;
}

void Node::addCost(float cost){
    this->cost += cost;
}

float Node::getCost(){
    return this->cost;
}

void Node::setStation(int s){
    this->station = s;
}

int Node::getStation(){
    return this->station;
}

void Node::setLine(int l){
    this->line = l;
}

int Node::getLine(){
    return this->line;
}

float Node::h(){
    return this->cost + this->g;
}

string Node::toString(){
    vector<string> lines = {"linha 510","linha 207","linha 301","linha 202"};
    string s =  "(" + to_string(this->station) + "," + lines[this->line-1] + ")";
    return s;
}

void Node::visit(){
    this->visited = true;
}

bool Node::isVisited(){
    return this->visited;
}
