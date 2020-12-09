/*
  Solucao do problema das linhas de onibus de Joao Pessoa

  Grupo: Andre Passos
         Julio Cesar

  * Source File *

  Grafo das distancias, conexoes e linhas de onibus

  Credits to Cristopher Freitas
*/

#include "graph.hpp"

Graph::Graph(){
    // Tabela de Distancias
    distances.push_back({0, 1.7, 8.2, 10.9, 10.7, 13.2, 15, 7.6, 7.5, 6.9, 0.6});       // P1
    distances.push_back({1.7, 0, 5.4, 8.1, 7.8, 10.3, 12.1, 5.4, 5.5, 4.1, 3.2});       // P2
    distances.push_back({8.2, 5.4, 0, 3.5, 5.8, 7.9, 13.9, 9.7, 3, 6.2, 8.1});          // P3
    distances.push_back({10.9, 8.1, 3.5, 0, 2.2, 4.4, 10.8, 13.2, 6.4, 4.4, 11.4});     // P4
    distances.push_back({10.7, 7.8, 5.8, 2.2, 0, 2.8, 9.4, 13.7, 8, 4.1, 11.1});        // P5
    distances.push_back({13.2, 10.3, 7.9, 4.4, 2.8, 0, 10.7, 14.1, 10.8, 5.4, 12.3});   // P6
    distances.push_back({15, 12.1, 13.9, 10.8, 9.4, 10.7, 0, 15.3, 15.3, 10.3, 17.5});  // P7
    distances.push_back({7.6, 5.4, 9.7, 13.2, 13.7, 14.1, 15.3, 0, 9.8, 9.3, 8.1});     // P8
    distances.push_back({7.5, 5.5, 3, 6.4, 8, 10.8, 15.3, 9.8, 0, 6.4, 6.9});           // P9
    distances.push_back({6.9, 4.1, 6.2, 4.4, 4.1, 5.4, 10.3, 9.3, 6.4, 0, 7});          // P10
    distances.push_back({0.6, 3.2, 8.1, 11.4, 11.1, 12.3, 17.5, 8.1, 6.9, 7, 0});       // P11

    // Tabela de Conexoes entre os pontos (paradas)
    adj.push_back({0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1});       // P1
    adj.push_back({1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0});       // P2
    adj.push_back({0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0});       // P3
    adj.push_back({0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0});       // P4
    adj.push_back({0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0});       // P5
    adj.push_back({0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0});       // P6
    adj.push_back({0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0});       // P7
    adj.push_back({1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});       // P8
    adj.push_back({0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0});       // P9
    adj.push_back({0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0});       // P10
    adj.push_back({1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});       // P11

    // linha 510 (marrom)
    lines.push_back({5, 6, 7});
    // linha 207 (azul claro)
    lines.push_back({1, 2, 3, 4, 8});
    // linha 301 (vermelho)
    lines.push_back({1, 2, 4, 5, 6, 10, 11});
    // linha 202 (cinza)
    lines.push_back({3, 4, 5, 6, 9});
}

// calculate time (in minutes) according to the approx distance given.
float Graph::calcTime(float distance){
    return (float(distance)/float(17))*60 ;
}

// get the possible lines for such station.
vector<int> Graph::getLines(int source, int target){
    vector<int> _lines;
    bool s = 0;
    bool t = 0;
    for(int i = 0; i < lines.size(); i++){
        for(int j = 0; j < lines[i].size(); j++){
            if(lines[i][j] == source){
                s = 1;
            } else if(lines[i][j] == target){
                t = 1;
            }
        }
        if(s && t){
            _lines.push_back(i);
        }
        s = 0;
        t = 0;
    }
    return _lines;
}


// change line between stations.
void Graph::changeLine(Node *node, int line){
    node->setLine(line);
    node->addCost(8); //custo da troca de linha (8 minutos)
}

// generate next possible childs.
vector<Node *> Graph::getNext(Node *node){
    vector<Node *> childs;
    // get the adjacent stations
    int station = node->getStation()-1;
    for(int i = 0; i < distances.size(); i++){
        if(adj[station][i] == 1){
            // check the lines for each stations
            vector<int> lines = getLines(station+1, i+1);
            vector<int> :: iterator itl = lines.begin();
            while(itl != lines.end()){
                // avoiding repetitions
                Node * prev = node->getParent();
                bool flag = false;
                if(prev != NULL){
                    if(prev->getStation() != i+1){
                        flag = false;
                    } else {
                        flag = true;
                    }
                }
                if(!flag){
                    // create the future possible nodes with costs.
                    Node * n = new Node(i+1,*itl+1);
                    n->setParent(node);
                    n->addCost(node->getCost());
                    n->addCost(calcTime(distances[station][i]));
                    // setting the expected cost from the point i to t;
                    n->g = calcTime(distances[i][this->t-1]);
                    // if there is a change of line, add this to the cost.
                    if(n->getLine() != node->getLine()){
                        n->addCost(4);
                    }
                    childs.push_back(n);
                }
                itl++;
            }

        }
    }
    return childs;
}

Node * Graph::move(vector<Node *> nodes){
    vector<Node *>::iterator itn = nodes.begin();
    Node * node = NULL;
    while(itn != nodes.end()){
        if((*itn)->isVisited() == false){
            if(node == NULL){
                node = *itn;
            } else {
                if(node->h() > (*itn)->h()){
                    (*itn)->visit();
                    node = *itn;
                }
            }
        }
        itn++;
    }
    return node;
}

// verify the actual state.
bool Graph::verify(Node *current, int target){
    if(current->getStation() == target){
        return true;
    } else {
        return false;
    }
}

// execute the travel between stations.
int Graph::travel(int s, int t){

    this->t = t;
    node = new Node(s, 0);
    node->setParent(NULL);
    cout << node->toString() << endl;

    while(!verify(node, t)){
        node = move(getNext(node));
        if(node == NULL){
            cout << "Solution not found" << endl;
            break;
        }
        cout << node->toString() << endl;;
    }

    return 0;
}
