#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

#ifdef CLIENTE
extern cars_list_t * carros;
#else
cars_list_t * carros;
#endif

/**
 * Imprime pacote no formato de bytes em hexadecimal.
 * Para debug.
 * @param c Pacote com dados do carro
 */
void print_packet(car_packet_t c)
{
    int i, size = sizeof(car_packet_t);
    unsigned short c_buf[size];

    memcpy(c_buf, &c, size);
    for(i=0;i<size;i++)
    {
        printf("%02X ", c_buf[i]);
    }
    printf("\n");
}

/************** Funções para manipular listas **************/
/**
 * Inicializa uma lista vazia.
 * @return Ponteiro para a lista vazia
 */
cars_list_t * init_list()
{
    cars_list_t * new = NULL;

    return new;
}

/**
 * Procura carro com ID na lista.
 * @param  id ID do carro procurado
 * @return    Ponteiro para o carro, ou nulo se carro não for encontrado
 */
car_t * find_list(unsigned int id)
{
    cars_list_t * p = carros;
    car_t * car = NULL;

    if(p != NULL)
    {
        printf("Procurando na lista...\n");
        while (p != NULL && (p->car.car_id != id) && (p->next != NULL))
        {
            p = p->next;
        }

        if(p != NULL && p->car.car_id == id)
        {
            car = &p->car;
        }
    }

    return car;
}

/**
 * Retorna último carro inserido na lista.
 * @return Ponteiro para o último carro da lista
 */
car_t * get_last_car()
{
    cars_list_t * p = carros;

    printf("Último carro.\n");
    while (p->next != NULL)
    {
        p = p->next;
    }

    return &p->car;
}

/**
 * Insere novo carro no final da lista.
 * @param id ID do carro a ser inserido
 * @param c  Pacote com dados do carro a ser inserido
 */
void insert_list(unsigned int id, car_packet_t c)
{
    cars_list_t * p_car = carros;
    cars_list_t * new_car;

    new_car = malloc(sizeof(cars_list_t));
    new_car->car.car_id = id;
    new_car->car.delta_tempo = 0;
    new_car->car.ativo = true;
    memcpy(&new_car->car.car_info, &c, sizeof(car_packet_t));
    new_car->next = NULL;

    if(p_car != NULL)
    {
        printf("Insere no final.\n");
        while(p_car->next != NULL)
        {
            p_car = p_car->next;
        }

        p_car->next = new_car;
    }
    else
    {
        // insere primeiro elemento
        printf("Insere primeiro elemento\n");
        carros = new_car;
    }
}

/**
 * Remove carro da lista.
 * @param id ID do carro a ser removido
 */
void remove_list(unsigned int id)
{
    cars_list_t * p_car = carros;
    cars_list_t * prev_car = carros;

    if(p_car->car.car_id == id)
    {
        // Elemento a ser removido é o primeiro
        carros = p_car->next;
    }
    else
    {
        while (p_car->car.car_id != id)
        {
            prev_car = p_car;
            p_car = p_car->next;
        }
        prev_car->next = p_car->next;
    }

    free(p_car);
}

/**
 * Libera memória da lista.
 */
void free_list()
{
    cars_list_t * p = carros;

    if(carros != NULL)
    {
        while (carros->next != NULL)
        {
            carros = carros->next;
            free(p);
            p = carros;
        }
        free(p);    //último elemento
    }
}
