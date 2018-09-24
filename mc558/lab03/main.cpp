/*
 * Para todo encanamento de A <-> B, são adicionados ao grafo uma aresta A->B e uma aresta B->A.
 * Cada vértice é inicializado com a chave sendo o custo de instalação de um reservatório naquela cidade, pois este é o
 * custo mínmo inicial.
 * O algoritmo de Prim retornará na chave de cada vértice ao final da execução será o menor custo entre a instalação
 * de um reservatório na cidade ou de um encanamento até aquela cidade.
 * Note que o algoritmo, para o problema, poderia retornar uma floresta, pois pode ser mais vantajoso ter um
 * reservatório naquela cidade, sem nenhum encanamento.
*/
#include <queue>
#include <limits.h>
#include <stdio.h>
#include <iostream>

using namespace std;

typedef struct {
    int weight;
    unsigned dst;
} Edge;

typedef struct {
    vector<Edge*> *edges;
    int key;
    bool visited;
} Vertex;

typedef struct {
    vector<Vertex*> *vertexes;
} Graph;

struct comparator {
    bool operator()(pair<Vertex*, int> a, pair<Vertex*, int> b) {
        return a.second > b.second;
    }
};

void prim(Graph* graph);
void print_cost(Graph* graph);
Graph* parse_input();
Vertex* get_new_vertex(int weight);

int main(){
    Graph* graph = parse_input();
    prim(graph);
    print_cost(graph);
    return 0;
}

void print_cost(Graph* graph){
    int cost = 0;
    unsigned num_vertex = graph->vertexes->size();
    for (unsigned i = 1; i < num_vertex; i++){
        cost += graph->vertexes->at(i)->key;
    }
    cout << cost << endl;
}

Vertex* get_new_vertex(int key){
    Vertex* vertex = new Vertex;
    vertex->edges = new vector<Edge*> ();
    vertex->key = key;
    vertex->visited = false;
    return vertex;
}

Edge* create_edge (unsigned dst, int weight) {
    Edge *edge = new Edge();
    edge->weight = weight;
    edge->dst = dst;
    return edge;
}

void add_edge (Graph* graph, unsigned int src, unsigned int dst, int weight) {
    Edge* edge = create_edge(dst, weight);
    graph->vertexes->at(src)->edges->push_back(edge);
    edge = create_edge(src, weight);
    graph->vertexes->at(dst)->edges->push_back(edge);
}

void prim(Graph* graph){
    priority_queue<pair<Vertex*, int>, vector<pair<Vertex*, int> >, comparator> min_heap;
    for (unsigned i = 1; i < graph->vertexes->size(); ++i) {
        min_heap.push(make_pair(graph->vertexes->at(i), graph->vertexes->at(i)->key));
    }
    while (!min_heap.empty()){
        pair<Vertex*, int> p = min_heap.top();
        Vertex* u = p.first;
        min_heap.pop();
        if (u->visited) continue;
        u->visited = true;
        for (unsigned i = 0; i < u->edges->size(); i ++){
            Edge* edge = u->edges->at(i);
            Vertex* v = graph->vertexes->at(edge->dst);
            if (!v->visited && edge->weight < v->key){
                v->key = edge->weight;
                min_heap.push(make_pair(v, v->key));
            }
        }
    }
}

Graph* parse_input(){
    Graph* graph = new Graph;
    unsigned int n, m;
    unsigned int src, dst, weight;
    scanf("%u %u", &n, &m); // # of cities and edges
    graph->vertexes = new vector<Vertex*>(1);
    for (unsigned i = 0; i < n; i++){
        scanf("%u", &weight);
        Vertex* city = get_new_vertex(weight);
        graph->vertexes->push_back(city);
    }
    for (unsigned int i = 0; i < m; i++){
        scanf("%u %u %u", &src, &dst, &weight);
        add_edge(graph, src, dst, weight);
    }
    return graph;
}
