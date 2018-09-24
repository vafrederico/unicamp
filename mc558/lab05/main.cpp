/*
 *  Cria-se vértices referentes a posições na diagonal (que são ligados ao source) e vértices refrentes à linhas (que são ligados ao target).
 *  Para cada coluna j em cada linha i, se, linha[j] = 1, cria-se aresta da posição da diagonal j para a linha i.
 *  Como cada item pode ser usado somente uma vez para a diagonal, todas as capacidades são 1. Como não precisamos do
 *  grafo original, ele é usado como o seu próprio residual, então somente invertemos as arestas.
 *  Aplica-se o algoritmo de Edmonds-Karp, sobre esse grafo.
 *  No final, o número de arestas saindo de target no residual será o número de posições da diagonal satisfeitas, uma vez
 *  que essas posições estavam nos caminhos aumentadores.
*/

#include <queue>
#include <stdio.h>
#include <iostream>


using namespace std;
struct Edge;
struct Vertex;

typedef struct Edge {
    Vertex* src;
    Vertex* dst;
} Edge;

typedef struct Vertex {
    vector<Edge*> *edges;
    bool visited;
    Vertex* parent;
    int idx;
} Vertex;

typedef struct {
    vector<Vertex*> *vertexes;
    unsigned int size;
} Graph;

Graph* parse_input();
Vertex* get_new_vertex();
Vertex* find_increasing_path(Graph* graph);
void reverse_edge (Edge* edge);
void add_edge (Vertex* src, Vertex* dst);
void max_flow(Graph* graph);

int main(){
    Graph* graph = parse_input();
    max_flow(graph);
    Vertex* target = graph->vertexes->at(1);
    if (target->edges->size() == graph->size) {
        cout << "SIM" << endl;
    } else {
        cout << "NAO" << endl;
    }
    return 0;
}

void max_flow(Graph* graph) {
    // Get target node
    Vertex* v = find_increasing_path(graph);
    // While we can increase our flow
    while (v != NULL) {
        // Reverse all edges in the path
        while (v->parent != NULL) {
            Vertex *parent = v->parent;
            // Find edge from parent to v and reverse it
            for (unsigned int i = 0; i < parent->edges->size(); i++) {
                if (parent->edges->at(i)->dst == v) {
                    reverse_edge(parent->edges->at(i));
                    break;
                }
            }
            v = parent;
        }
        v = find_increasing_path(graph);
    }
}

// BFS
Vertex* find_increasing_path(Graph* graph){
    for (unsigned int i = 0; i < graph->vertexes->size(); i++){
        graph->vertexes->at(i)->parent = NULL;
        graph->vertexes->at(i)->visited = false;
    }
    Vertex* source = graph->vertexes->at(0);
    Vertex* target = graph->vertexes->at(1);
    queue<Vertex*> q;
    q.push(source);

    while (!q.empty()){
        Vertex* u = q.front();
        q.pop();
        if (u->visited) continue;
        u->visited = true;
        for (unsigned int i = 0; i < u->edges->size(); i++) {
            Vertex* v = u->edges->at(i)->dst;
            if (v->visited) continue;
            v->parent = u;
            q.push(v);
            if (v == target) {
                return v;
            }
        }
    }
    return NULL;
}

int idx = 0;
Vertex* get_new_vertex(){
    Vertex* vertex = new Vertex;
    vertex->idx = idx++;
    vertex->edges = new vector<Edge*> ();
    return vertex;
}

void add_edge (Vertex* src, Vertex* dst) {
    Edge *edge = new Edge();
    edge->src = src;
    edge->dst = dst;
    src->edges->push_back(edge);
}

void reverse_edge (Edge* edge) {
    for (unsigned int i = 0; i < edge->src->edges->size(); i++){
        if (edge->src->edges->at(i) == edge) {
            edge->src->edges->erase(edge->src->edges->begin()+i);
            break;
        }
    }
    Vertex* tmp = edge->src;
    edge->src = edge->dst;
    edge->dst = tmp;
    edge->src->edges->push_back(edge);
}

Graph* parse_input(){
    Graph* graph = new Graph;
    unsigned int n;
    graph->vertexes = new vector<Vertex*>;
    Vertex* source = get_new_vertex();
    graph->vertexes->push_back(source);
    Vertex* target = get_new_vertex();
    graph->vertexes->push_back(target);

    scanf("%u", &n); // matrix size
    graph->size = n;
    // Add diagonals
    for (unsigned int i = 0; i < n; i++){
        Vertex* diagonal_vertex = get_new_vertex();
        graph->vertexes->push_back(diagonal_vertex);
        add_edge(source, diagonal_vertex);
    }

    // Add columns
    for (unsigned int i = 0; i < n; i++){
        Vertex* column_vertex = get_new_vertex();
        graph->vertexes->push_back(column_vertex);
        add_edge(column_vertex, target);
    }

    // Add edges from diagonal to column if value in column = 1
    int val;
    for (unsigned int i = 0; i < n; i++){
        for (unsigned int j = 0; j < n; j++){
            scanf("%d", &val);
            if (val == 1) {
                add_edge(graph->vertexes->at(j+2), graph->vertexes->at(i+2+n));
            }
        }
    }

    return graph;
}
