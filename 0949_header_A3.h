#include <stdio.h>
#include <stdlib.h>
typedef struct state{
	int eight;//eight Liter jug
	int five;//five Liter jug
	int three;//three Liter jug
	int fn_index;//function index to keep track which transition function used previous time
}state_t;
typedef struct node{
	state_t st;//our state
	struct node * prev;
	struct node * next;
}node_t;
typedef struct list{
	node_t * head;//points to the head of list
	node_t * tail;//points to the tail of list
}list_t;
//All state function declaration
void init_state(state_t * ptr_state);
void display_state(const state_t * ptr_state);
void set_state(state_t * ptr_state,int eight,int five,int three);
int are_same(const state_t *lhs, const state_t *rhs);
void eight_five(const state_t * src,state_t * dest);
void eight_three(const state_t * src,state_t * dest);
void five_eight(const state_t * src,state_t * dest);
void five_three(const state_t * src,state_t * dest);
void three_eight(const state_t * src,state_t * dest);
void three_five(const state_t * src,state_t * dest);
//list operation
void init_list(list_t *ptr_list);
void add_at_end(list_t *ptr_list, const state_t* ptr_state);
void remove_at_end(list_t *ptr_list);
void disp_list(const list_t *ptr_list);
int is_repeated(const list_t* ptr_list, const state_t* ptr_state);
int is_safe(const state_t* ptr_state);