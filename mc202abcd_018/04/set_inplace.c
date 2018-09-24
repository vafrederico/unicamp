#include <stdio.h>
#include <stdlib.h>

#define PRINT_OP 0

typedef struct node {
	int value;
	struct node* next;
} node;

typedef struct list {
	node* head;
} list;

void clear(list *set) {
	node* n = set->head;
	node* temp;
	while (n != NULL){
		temp = n->next;
		free(n);
		n = temp;
	}
	set->head = NULL;
}

node* new_node(int val) {
	node* n = malloc(sizeof(node));
	n->value = val;
	n->next = NULL;
	return n;
}

void insert_node(list* set, int val){
	if (set->head == NULL) {
		set->head = new_node(val);
	} else if (set->head->value > val){
		node* node = new_node(val);
		node->next = set->head;
		set->head = node;
	} else if(set->head->value == val) {
		return;
	} else {
		node* n = set->head->next;
		node* prev = set->head;
		while (n != NULL && val > n->value) {
			prev = n;
			n = n->next;
		}
		if (n && val == n->value){
			return;
		}
		// if (n)
		// 	printf("N: %d, val: %d\n", n->value, val);
		node* val_node = new_node(val);
		val_node->next = n;
		prev->next = val_node;
	}
}

void remove_node(list* set, int val){
	if (set->head == NULL || set->head->value > val) {
		return;
	} else if (set->head->value == val) {
		node* temp = set->head;
		set->head = temp->next;
		free(temp);
	} else {
		node* n = set->head->next;
		node* prev = set->head;
		while (n != NULL && val > n->value) {
			prev = n;
			n = n->next;
		}
		if (n && n->value == val) {
			prev->next = n->next;
			free(n);
			n = prev->next;
		}
	}
}

void uniao(list* set_a, list* set_b) {
	node* a = set_a->head;
	node* b = set_b->head;
	if (a == NULL) {
		if (b == NULL){
			return;
		}

		set_a->head = new_node(b->value);
		b = b->next;
		a = set_a->head;
	}
	node* prev_a = NULL;
	while (b != NULL) {
		while (a && a->value < b->value) {
			prev_a = a;
			a = a->next;
		}
		if (a == NULL || a->value != b->value){
			node* n = new_node(b->value);
			n->next = a;
			if (prev_a == NULL) {
				set_a->head = n;
				a = n;
			} else {
				prev_a->next = n;
				a = n;
			}	
		}
		b = b->next;
	}
}

void subtracao(list* set_a, list* set_b) {
	node* a = set_a->head;
	node* b = set_b->head;
	if (a == NULL || b == NULL) {
		return;
	}
	node* prev_a = NULL;
	while (b != NULL && a != NULL) {
		while (a && a->value < b->value) {
			prev_a = a;
			a = a->next;
		}
		if (a != NULL && a->value == b->value){
			if (prev_a == NULL) {
				set_a->head = a->next;
				free(a);
				a = set_a->head;
			} else {
				prev_a->next = a->next;
				free(a);
				a = prev_a->next;
			}
		}
		b = b->next;
	}
}

void interseccao(list* set_a, list* set_b) {
	node* a = set_a->head;
	node* b = set_b->head;
	if (a == NULL || b == NULL) {
		clear(set_a);
		return;
	}
	node* prev_a = NULL;
	while (b != NULL && a != NULL) {
		while (a && a->value < b->value) {
			// printf("A: %d, B: %d\n", a->value, b->value);
			if (prev_a == NULL) {
				// printf("PREV_A == NULL\n");
				set_a->head = a->next;
				free(a);
				a = set_a->head;
			} else {
				// printf("PREV_A != NULL\n");
				prev_a->next = a->next;
				free(a);
				a = prev_a->next;
			}
		}
		if (a) {
			// printf("- A: %d, B: %d\n", a->value, b->value);
			if(a->value == b->value) {
				// printf("-- A: %d, B: %d\n", a->value, b->value);
				prev_a = a;
				a = a->next;
				// printf("-- A: %d, B: %d\n", a->value, b->value);
			}
		}
		b = b->next;
	}
	if (b == NULL) {
		if (prev_a == NULL) {
			clear(set_a);
			return;
		}
		while (a != NULL){
			prev_a->next = a->next;
			free(a);
			a = prev_a->next;
		}
	}

}

void pertence(list* set, int val) {
	node* a = set->head;
	while (a != NULL && a->value < val) {
		a = a->next;
	}

	if (a != NULL && a->value == val) {
		printf("SIM\n");
	} else {
		printf("NAO\n");
	}

}

void imprime(list* set) {
	node* n = set->head;
	int prev = -1;
	printf("{");
	if (n != NULL){
		printf("%d", n->value);
		prev = n->value;
		n = n->next;
	}
	while (n != NULL) {
		printf(",%d", n->value);
		if (prev == n->value)
			exit(1);
		n = n->next;
	}
	printf("}\n");
}

list* new_list() {
	list* l = malloc(sizeof(list));
	l->head = NULL;
	return l;
}

int main() {
	list* set1 = new_list();
	list* set2 = new_list();
	char op;
	int val;
	int set_num;
	list* target_set;
	while (scanf(" %c", &op) != -1) {
#if PRINT_OP
		printf("%c", op);
#endif
		if (op == 's') {
			imprime(set1);
			imprime(set2);
			clear(set1);
			clear(set2);
			break;
		} else {
			if (op == 'u') {
				uniao(set1, set2);
			} else if(op == 'x') {
				interseccao(set1, set2);
			} else if (op == 'b') {
				subtracao(set1, set2);
			} else {
				scanf("%d %d", &val, &set_num);
#if PRINT_OP
				printf(" %d %d", val, set_num);
#endif
				if (set_num == 1) {
					target_set = set1;
				} else {
					target_set = set2;
				}
				if (op == 'i') {
					insert_node(target_set, val);
				} else if (op == 'r') {
					remove_node(target_set, val);
				} else if (op == 'p') {
					pertence(target_set, val);
				}
			}
#if PRINT_OP
				printf("\n");
#endif
			imprime(set1);
			imprime(set2);
		}

	}

	return 0;
}
