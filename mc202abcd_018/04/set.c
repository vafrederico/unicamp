#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int value;
	struct node* next;
} node;

void clear(node *n) {
	node* temp;
	while (n != NULL){
		temp = n->next;
		free(n);
		n = temp;
	}
}

node* new_node(int val) {
	node* n = malloc(sizeof(node));
	n->value = val;
	n->next = NULL;
	return n;
}

void insert_node(node** start, int val){
	node* n = *start;
	node* prev = NULL;
	while (n != NULL) {
		if (val < n->value) {
			break;
		}
		prev = n;
		n = n->next;
	}
	if (prev != NULL && prev->value == val) {
		return;
	}
	node* val_node = new_node(val);
	if (prev == NULL) {
		val_node->next = n;
		*start = val_node;
	} else {
		val_node->next = prev->next;
		prev->next = val_node;		
	}
}

void remove_node(node** start, int val){
	node *n = *start;
	node* prev = NULL;
	while (n != NULL) {
		if (val == n->value) {
			break;
		}
		prev = n;
		n = n->next;
	}
	if (!n) {
		return;
	}
	if (prev != NULL) {
		prev->next = n->next;
	} else {
		if (*start) {
			*start = n->next;
		}
	}
	free(n);
}

void uniao(node** start_a, node* b) {
	node* a = *start_a;
	node* new_list;
	if (a != NULL) {
		new_list = new_node(a->value);
		a = a->next;
	} else if (b != NULL) {
		new_list = new_node(b->value);
		b = b->next;
	}
	while (a != NULL) {
		insert_node(&new_list, a->value);
		a = a->next;
	}
	while (b != NULL) {
		insert_node(&new_list, b->value);
		b = b->next;
	}
	clear(*start_a);
	*start_a = new_list;
}

void subtracao(node** start_a, node* b) {
	node* a = *start_a;
	node* new_list = NULL;
	if (a == NULL)
		return;

	if (b == NULL)
		return;

	while (a != NULL) {
		while (a != NULL && (b == NULL || a->value < b->value)) {
			if (!new_list){
				new_list = new_node(a->value);
			} else {
				insert_node(&new_list, a->value);
			}
			a = a->next;
		}
		if (!a) {
			break;
		}
		if (a->value == b->value) {
			a = a->next;
		} else {
			b = b->next;
		}
	}
	clear(*start_a);
	*start_a = new_list;
}

void interseccao(node** start_a, node* b) {
	node* a = *start_a;
	node* new_list = NULL;
	if (a == NULL)
		return;

	if (b == NULL) {
		clear(*start_a);
		*start_a = NULL;
		return;
	}

	while (a != NULL && b != NULL) {
		while (a && b != NULL && a->value < b->value) {
			a = a->next;
		}
		if (!a)
			break;
		if (a->value == b->value) {
			if (new_list == NULL){
				// printf("NEW_LIST");
				new_list = new_node(a->value);
			}
			else {
				insert_node(&new_list, a->value);	
			}
			a = a->next;
		} else {
			b = b->next;
		}
	}
	clear(*start_a);
	*start_a = new_list;
}

void pertence(node* a, int val) {
	while (a != NULL && a->value < val) {
		a = a->next;
	}

	if (a != NULL && a->value == val) {
		printf("SIM\n");
	} else {
		printf("NAO\n");
	}

}

void imprime(node* n) {
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

int main() {
	node* set1 = NULL;
	node* set2 = NULL;
	char op;
	int val;
	int set_num;
	node** target_set;
	while (scanf(" %c", &op) != -1) {
		// printf("%c", op);
		if (op == 's') {
			imprime(set1);
			imprime(set2);
			clear(set1);
			clear(set2);
			break;
		} else {
			if (op == 'u') {
				uniao(&set1, set2);
			} else if(op == 'x') {
				interseccao(&set1, set2);
			} else if (op == 'b') {
				subtracao(&set1, set2);
			} else {
				scanf("%d %d", &val, &set_num);
				// printf(" %d %d", val, set_num);
				if (set_num == 1) {
					target_set = &set1;
				} else {
					target_set = &set2;
				}
				if (op == 'i') {
					if (*target_set == NULL) {
						*target_set = new_node(val);
					} else {
						insert_node(target_set, val);
					}
				} else if (op == 'r') {
					remove_node(target_set, val);
				} else if (op == 'p') {
					pertence(*target_set, val);
				}
			}
				// printf("\n");
			imprime(set1);
			imprime(set2);
		}

	}

	return 0;
}
