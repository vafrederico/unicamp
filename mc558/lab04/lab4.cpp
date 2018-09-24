/*
 * Transforma-se a lista de reservas p/ um grafo de forma que toda reserva é um nó, cria-se um nó fonte e um nó destino
 * que ambos estão ligados a todos nós de reservas, e há uma aresta entre 2 nós de resrva, u e v, se e somente se, não
 * há conflito de horário entre u e v, e final de v > final de u. O peso de uma aresta (u, v) é o valor de aluguel de u
 * multiplicado por -1.
 * Temos então um grafo acíclico (graças à condição de que final de u < final de v), portanto podemos executar caminhos
 * mínimos nesse grafo, buscando o menor caminho entre o nó fonte e o nó destino. O resultado é o maior lucro possível
 * multiplicado por -1, pois como o valor de aluguel está negativo, o maior lucro é o menor caminho. Portanto, temos
 * solução para o problema, a partir da transformação da entrada.
 * A transformação da saída é a distância do menor caminho * -1, e as IDs (reservas) que compõe esse caminho.
*/
#include <algorithm>
#include <iostream>
#include <stdio.h>

#include "minpathcpp.h"

using namespace std;

typedef struct reserva{
    int inicio;
    int final;
    int valor;
    int id;
} reserva;

bool comparador(reserva a, reserva b) {
    return a.inicio < b.inicio;
}

int main(void) {

    // Entrada Ia
    int n;
    scanf("%d", &n);
    vector<reserva> reservas(n);
    for (int i = 0; i < n; i++){
        scanf("%d %d %d", &reservas[i].inicio, &reservas[i].final, &reservas[i].valor);
        reservas[i].id = i + 1;
        reservas[i].valor *= -1;
    }

    // Transformação da entrada Ia -> Ib
    Grafo g = Grafo(n + 2);
    int no_fonte = n;
    int no_destino = n + 1;
    sort(reservas.begin(), reservas.end(), comparador);
    for (int i = 0; i < n; ++i) {
        g.adicionaAresta(no_fonte, i, 0);
        g.adicionaAresta(i, no_destino, reservas[i].valor);
        for (int j = i+1; j < n; ++j) {
            if (reservas[j].inicio >= reservas[i].final) {
                g.adicionaAresta(i, j, reservas[i].valor);
            }
        }
    }

    // Transformção da solução Sb -> Sa
    vector<Grafo::Edge> P;
    int lucro = -g.min_path(no_fonte, no_destino, P);
    cout << lucro << endl;
    for (unsigned i = 0; i < P.size() - 1; i++){
      cout << reservas[P[i].y].id << " ";
    }
    cout << endl;        

}
