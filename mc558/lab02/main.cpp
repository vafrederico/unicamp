/*
Para toda estrada e para toda ferrovia de A <-> B, são adicionados ao grafo uma aresta A->B e uma aresta B->A com mesmo identificador.
Ao executarmos o relax durante a execução de dijsktra, de A -> B utilizando a aresta E, se o caminho utilizando E é pior, ele é ignorado. 
Se ele for melhor, é utilizado. No caso em que seja igual, prevalece a aresta que seja uma rodovia.
Logo, em B, teremos marcado qual o menor caminho para chegar até ele. Portanto, ao final da execução de dijsktra, teremos em todos os vértices, qual a aresta para o menor caminho até ele, 
à partir da capital federal, e consequentemente, da capital mais próxima, pois todas capitais estão interligadas à federal com peso 0.
Dessa forma, basta contarmos qual identificadores de rodovia são utilizados, e portanto quantas podem ser desativadas.
*/

#include <queue>
#include <limits.h>
#include <stdio.h>
#include <iostream>

using namespace std;

enum RoadType {
    Railroad = 1,
    Road = 2
};

typedef struct {
    RoadType type;
    int weight;
    unsigned dst;
    int id;
} Edge;

typedef struct {
    bool capital;
    bool visited;
    vector<Edge*> *edges;
    Edge* edge_used;
    int distance_to_federal;
} Vertex;

typedef struct {
    vector<Vertex*> *cities;
    vector<Edge*> *edges;
    unsigned num_railroads;
} Graph;

struct comparator {
    bool operator()(Vertex *a, Vertex *b) {
        return a->distance_to_federal > b->distance_to_federal;
    }
};

void dijkstra(Graph* graph, Vertex* source);
Graph* parse_input();
Vertex* create_federal_district(Graph* graph);
void print_count_removable_railroads(Graph* graph);
Vertex* get_new_vertex();

int main(){
    Graph* graph = parse_input();
    Vertex* source = create_federal_district(graph);
    dijkstra(graph, source);
    print_count_removable_railroads(graph);
    return 0;
}

void print_count_removable_railroads(Graph* graph){
    vector <bool> railroad_used = vector<bool> (graph->num_railroads, false);
    unsigned num_used = 0;
    unsigned num_cities = graph->cities->size();
    for (unsigned i = 1; i < num_cities; i++){
        Edge* road = graph->cities->at(i)->edge_used;
        if (road->type == Railroad){
            railroad_used[road->id] = true;
        }
    }
    for (unsigned i = 0; i < graph->num_railroads; i++){
        if (railroad_used[i])
            num_used++;
    }
    cout << (graph->num_railroads - num_used) << endl;
}

Edge* create_edge (unsigned dst, RoadType type, int weight, int id) {
    Edge *edge = new Edge();
    edge->type = type;
    edge->weight = weight;
    edge->dst = dst;
    edge->id = id;
    return edge;
}

void add_edge (Graph* graph, unsigned int src , unsigned int dst, RoadType type, int weight, int id) {
    Edge* edge = create_edge(dst, type, weight, id);
    graph->cities->at(src)->edges->push_back(edge);
    edge = create_edge(src, type, weight, id);
    graph->cities->at(dst)->edges->push_back(edge);
}

Vertex* create_federal_district(Graph* graph){
    Vertex* federal_district = get_new_vertex();
    federal_district->capital = true;
    federal_district->distance_to_federal = 0;
    unsigned long num_cities = graph->cities->size();
    for (unsigned i = 1; i < num_cities; i++){
        if (!graph->cities->at(i)->capital) continue;
        Edge* edge = create_edge(i, Road, 0, 0);
        federal_district->edges->push_back(edge);
    }
    return federal_district;
}

void relax(Graph* graph, Vertex *u, Edge* road) {
    int path_distance = u->distance_to_federal + road->weight;
    Vertex* v = graph->cities->at(road->dst);
    if (v->distance_to_federal > path_distance) {
        v->distance_to_federal = path_distance;
        v->edge_used = road;
    } else if (v->distance_to_federal == path_distance && road->type == Road){
        v->edge_used = road;
    }
}

void dijkstra(Graph* graph, Vertex* source){
    priority_queue<Vertex*, vector<Vertex*>, comparator> min_heap;

    min_heap.push(source);

    while (!min_heap.empty()){
        Vertex* u = min_heap.top();
        min_heap.pop();
        if (u->visited) continue;
        u->visited = true;
        for (unsigned i = 0; i < u->edges->size(); i ++){
            Edge* road = u->edges->at(i);
            if (!graph->cities->at(road->dst)->visited){
                relax(graph, u, road);
                min_heap.push(graph->cities->at(road->dst));
            }
        }
    }
}

Graph* parse_input(){
    Graph* graph = new Graph;
    unsigned int n, m, p;
    unsigned int src, dst, weight;
    scanf("%u %u %u", &n, &m, &p); // # of cities, roads and railroads
    graph->num_railroads = p;
    graph->cities  = new vector<Vertex*>(1);
    for (unsigned i = 0; i < n; i++){
        Vertex* city = get_new_vertex();
        graph->cities->push_back(city);
    }

    graph->edges = new vector<Edge*>;
    for (unsigned int i = 0; i < m; i++){
        scanf("%u %u %u", &src, &dst, &weight);
        add_edge(graph, src, dst, Road, weight, i);
    }
    for (unsigned int i = 0; i < p; i++){
        scanf("%u %u %u", &src, &dst, &weight);
        add_edge(graph, src, dst, Railroad, weight, i);
        graph->cities->at(src)->capital = true;
    }
    return graph;
}

Vertex* get_new_vertex(){
    Vertex* vertex = new Vertex;
    vertex->capital = false;
    vertex->visited = false;
    vertex->edges = new vector<Edge*> ();
    vertex->edge_used = NULL;
    vertex->distance_to_federal = INT_MAX;
    return vertex;
}