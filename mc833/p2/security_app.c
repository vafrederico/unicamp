#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include "security_app.h"
#include "utils.h"

#define ACCEL true
// Variáveis dos carros
int grcar_id[100][100];
//TODO mutex para carros
cars_list_t *carros = NULL;
int num_carros = 0;

/**
 * Thread que atualiza posição dos carros no grid.
 * @param  thread_arg Vazio
 * @return            Vazio
 */
void *thread_update_cars_pos(void *thread_arg) {
    //TODO corpo da thread
    while (true) {
        if (num_carros != 0) {
            // ajusta posição dos carros no grid
            // carro é removido quando passa do cruzamento (?)
            // atualiza posição dos carros no vetor carros
        }
        usleep(5000); //5ms
    }
}

/**
 * Procura carro na lista
 * @param  id ID do carro procurado
 * @return    Ponteiro para carro procurado, ou nulo se não for achado
 */
car_t *get_car(unsigned int id) {
    car_t *p;

    p = find_list(id);
    printf("Carro encontrado\n");

    return p;
}

/**
 * Atualiza posição do carro no grid após receber um novo pacotes
 * @param p_car  Ponteiro para elemento da lista que contém o carro
 * @param recv_c Pacote recebido com novos dados do carro
 */
void update_car_pos(car_t *p_car, car_packet_t recv_c) {
    int x_back, x_front, y_back, y_front;

    //if(grid[c.pos_x][c.pos_y] == id)
    {
        //TODO como atualizar posição???
    }
}

/**
 * Insere novo carro na lista de carros
 * @param id ID do carro a ser inserido
 * @param c  Pacote com dados do carro recebido
 */
void insert_car_list(unsigned int id, car_packet_t c) {
    insert_list(id, c);
    num_carros++;
}

/**
 * Insere o último carro recebido no grid.
 * Índices: (-50, 50]
 *  xy(1,-1)  = grid[50][49]
 *  xy(1,1)   = grid[50][50]
 *  xy(-1,-1) = grid[49][49]
 *  xy(-1,1)  = grid[49][50]
 */
void insert_car_grid() {
    int i, x, y;
    unsigned int curr_id;
    car_packet_t curr;
    car_t *p_car;

    p_car = get_last_car();
    printf("%u\n", p_car->car_id);
    curr_id = p_car->car_id;
    memcpy(&curr, &p_car->car_info, sizeof(car_packet_t));
    x = curr.pos_x;
    y = curr.pos_y;

    pthread_mutex_lock(&mutex_grid);
    for (i = 0; i < curr.size; i++) {
        printf("[%u] grid(%d, %d)\n", curr_id, x, y);
//        grid[x+50][y+50] = curr_id;

        switch (curr.dir) {
            case up:
                y -= 1;
                break;
            case down:
                y += 1;
                break;
            case left:
                x -= 1;
                break;
            case right:
                x += 1;
                break;
        }
    }
    pthread_mutex_unlock(&mutex_grid);
}

/**
 * Verifica qual ação o carro que mandou um pacote deve tomar para evitar uma colisão,
 * ou se uma colisão é inevitável.
 * @param  id ID do carro
 * @param  c  Pacote com dados do carro
 * @return    Inteiro que representa qual ação deve ser tomada
 */
int detect_collision(unsigned int id, car_packet_t c, bool test_change) {
    if (!test_change) printf("--------------------------------------\n");
    car_t *p_car;
    car_t *p_car_check;
    cars_list_t *p_car_check_list;
    int curr_grid[100][100];
    int x_center, y_center, delta_pos, delta_tempo;

    if ((p_car = get_car(id)) != NULL) {
        memcpy(&p_car->car_info, &c, sizeof(c));
        printf("[%u] Carro existente.\n", id);
        printf("Direction: %d\n", c.dir);
        update_car_pos(p_car, c);
    } else {
        printf("[%u] Carro não existente.\n", id);
        insert_car_list(id, c);
        p_car = get_last_car();
        p_car->original_vel = c.vel;
        //insert_car_grid();
    }

//    pthread_mutex_lock(&mutex_grid);
//    memcpy(curr_grid, grid, sizeof(grid));
//    pthread_mutex_unlock(&mutex_grid);

    //TODO detectar colisão
    printf("POS X POS Y SIZE: %d %d %d\n", p_car->car_info.pos_x, p_car->car_info.pos_y, p_car->car_info.size);
    switch (p_car->car_info.dir) {
        case up:
            if (p_car->car_info.pos_y < p_car->car_info.size) //0 + tamanho
            {
                x_center = 1;
                y_center = -1;
                delta_pos = abs(p_car->car_info.pos_y - y_center);
            } else {
                //já passou do cruzamento
                p_car->ativo = false;
                return MSG_OK;
            }
            break;
        case down:
            if (p_car->car_info.pos_y > -p_car->car_info.size) //0 - tamanho
            {
                x_center = -1;
                y_center = 1;
                delta_pos = abs(p_car->car_info.pos_y - y_center);
            } else {
                //já passou do cruzamento
                p_car->ativo = false;
                return MSG_OK;
            }
            break;
        case left:
            if (p_car->car_info.pos_x > -p_car->car_info.size) //0 + tamanho
            {
                x_center = 1;
                y_center = 1;
                delta_pos = abs(p_car->car_info.pos_x - x_center);
            } else {
                //já passou do cruzamento
                p_car->ativo = false;
                return MSG_OK;
            }
            break;
        case right:
            if (p_car->car_info.pos_x < p_car->car_info.size) //0 - tamanho
            {
                x_center = -1;
                y_center = -1;
                delta_pos = abs(p_car->car_info.pos_x - x_center);
            } else {;
                //já passou do cruzamento
                p_car->ativo = false;
                return MSG_OK;
            }
            break;
    }

    p_car->delta_tempo = (c.vel == 0? 9999: (int) floor(delta_pos / c.vel));
    p_car_check_list = carros;
    double t_init, t_end;
    double car_tempo_inicio;
    car_packet_t curr;
    memcpy(&curr, &p_car->car_info, sizeof(car_packet_t));
    printf("Num carros: %d\n", num_carros);
    for (int i = 0; i < num_carros; i++) {
        p_car_check = &(p_car_check_list->car);
        if (!p_car_check->ativo) {
            printf("Skipping car %d\n", i);
        }
        if ((p_car_check->ativo) &&
            (((p_car->car_info.dir <= down) && (p_car_check->car_info.dir >= left)) ||
             ((p_car_check->car_info.dir <= down) && (p_car->car_info.dir >= left))) &&
            (p_car->car_id != p_car_check->car_id)) {
            printf("Checking with car %d Delta Tempo: %d\n: ", i, p_car_check->delta_tempo);
            t_init = p_car_check->car_info.ts + p_car_check->delta_tempo;
            car_tempo_inicio = p_car->car_info.ts + p_car->delta_tempo;
            if ((p_car->car_info.dir == right && p_car_check->car_info.dir == up) ||
                (p_car->car_info.dir == down && p_car_check->car_info.dir == right) ||
                (p_car->car_info.dir == left && p_car_check->car_info.dir == down) ||
                (p_car->car_info.dir == up && p_car_check->car_info.dir == left)) {
                if (p_car->car_info.vel > 0)
                    car_tempo_inicio += (1 / p_car->car_info.vel); // segunda casa
            } else {
                if (p_car_check->car_info.vel > 0)
                    t_init += (1 / p_car_check->car_info.vel); // segunda casa
            }
            t_end = t_init + p_car_check->car_info.size / (1.0*p_car_check->car_info.vel);
            printf("P_car_check__ts : %f, %f\n", t_init, t_end);
            for (int j = 0; j < p_car->car_info.size; j++) {
                if (j > 0)
                    car_tempo_inicio -= (1.0 / p_car->car_info.vel); // tamanho
                printf("P_car_ts : %f\n", car_tempo_inicio);
                if (car_tempo_inicio >= t_init && car_tempo_inicio <= t_end) {
                    if (!test_change) {
                        printf("======== Teste freio\n");
                        c.vel /= 2;
                        if (detect_collision(id, c, true) == MSG_OK) {
                            return MSG_SLOW;
                        } else {
                            memcpy(&p_car->car_info, &curr, sizeof(car_packet_t));
                        }
                    }
                    return MSG_AMBULANCE;
                }
            }
        }

        p_car_check_list = p_car_check_list->next;
    }

    if(!test_change && ACCEL && c.vel < p_car->original_vel){
        bool old_ativo = p_car->ativo;
        int old_tempo = p_car->delta_tempo;
        printf("======== Teste accel\n");
        c.vel = curr.vel * 2;
        if (c.vel == 0) c.vel = 1;
        if (c.dir == up)
            c.pos_y += c.vel;
        if (c.dir == down)
            c.pos_y -= c.vel;
        if (c.dir == left)
            c.pos_x -= c.vel;
        if (c.dir == right)
            c.pos_x += c.vel;
        if (detect_collision(id, c, true) == MSG_OK) {
            return MSG_ACC;
        } else {
            memcpy(&p_car->car_info, &curr, sizeof(car_packet_t));
            p_car->ativo = old_ativo;
            p_car->delta_tempo = old_tempo;
        }
    }
    return MSG_OK;
}
