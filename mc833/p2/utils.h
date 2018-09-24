#ifndef UTILS_H
#define UTILS_H

#include <time.h>

#define MAX_CARS				10

// Tipos de pacotes
#define PACKET_T_HELLO			0
#define	PACKET_T_SECURITY		1
#define	PACKET_T_ENTERTAINMENT 	2
#define	PACKET_T_TRAFFIC		3

// Tipos de mensagens de resposta
#define MSG_HELLO               0
#define MSG_OK                  1
#define MSG_SLOW                2
#define MSG_ACC                 3
#define MSG_AMBULANCE           4

typedef enum { false, true } bool;

typedef enum { up=0, down, left, right } direction;

typedef struct car_packet
{
    int type;
    unsigned int ts;	//inicia em 0
    int pos_x;			//cruzamento em (0,0)
    int pos_y;
    int vel;			//delta(pos)/delta(ts)
    direction dir;
    int size;
} car_packet_t;

typedef struct car
{
	unsigned int car_id;	//porta do cliente
    int delta_tempo;        //tempo que falta para chegar até o cruzamento
    bool ativo;             //carro está ativo se ainda não passou pelo cruzamento
	car_packet_t car_info;
	int original_vel;
} car_t;

typedef struct cars_list
{
    car_t car;
    struct cars_list * next;
} 	cars_list_t;

/* Funções */

void print_packet(car_packet_t);

cars_list_t * init_list(void);
car_t * find_list(unsigned int);
car_t * get_last_car(void);
void insert_list(unsigned int, car_packet_t);
void remove_list(unsigned int);
void free_list(void);

#endif /* UTILS_H */
