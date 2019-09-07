#include "0949_header_A3.h"
void init_state(state_t *ptr_state)//initialising all jug's initial water = 0
{
	ptr_state -> eight = 0;
	ptr_state -> five = 0;
	ptr_state -> three = 0;
    ptr_state -> fn_index = 0;
}
void disp_state(const state_t * ptr_state)//function to display each state
{
	printf("%d %d %d\n",ptr_state -> eight,ptr_state -> five,ptr_state -> three);
}
void set_state(state_t * ptr_state,int eight,int five,int three)//function to set state to give values
{
	ptr_state -> eight = eight;
	ptr_state -> five = five;
	ptr_state -> three = three;
	ptr_state -> fn_index = 0;
}
void eight_five(const state_t * src,state_t * dest){
	int required = 5 - src -> five; //calculate amount of water required to fill five litre
	if(src -> eight >= required)//check if we have sufficient amount of water in eight litre jug to fill five liter
	{
		dest -> eight = src -> eight - required;
		dest -> five = src -> five + required;
		dest -> three = src -> three;
	}
	else{
		dest -> eight = 0;
		dest -> five = src -> five + src -> eight;
		dest -> three = src -> three;
	}
	dest -> fn_index = 0;
}
void eight_three(const state_t * src,state_t * dest){
	int required = 3 - src -> three;//calculate amount of water required to fill three litre
	if(src -> eight >= required)//check if we have sufficient amount of water in eight litre jug to fill three liter
	{
		dest -> eight = src -> eight - required;
		dest -> five = src -> five;
		dest -> three = src -> three + required;
	}
	else{
		dest -> eight = 0;
		dest -> five = src -> five;
		dest -> three = src -> three + src -> eight;
	}
	dest -> fn_index = 0;
}
void five_eight(const state_t * src,state_t * dest){
	int required = 8 - src -> eight;//calculate amount of water required to fill eight litre
	if(src -> five >= required)//check if we have sufficient amount of water in five litre jug to fill eight litre
	{
		dest -> eight = src -> eight + required;
		dest -> five = src -> five - required;
		dest -> three = src -> three;
	}
	else{
		dest -> eight = src -> eight + src -> five;
		dest -> five = 0;
		dest -> three = src -> three;
	}
	dest -> fn_index = 0;
}
void five_three(const state_t * src,state_t * dest){
	int required = 3 - src -> three;//calculate amount of water required to fill three litre
	if(src -> five >= required)//check if we have sufficient amount of water in five litre jug to fill three litre
	{
		dest -> eight = src -> eight;
		dest -> five = src -> five - required;
		dest -> three = src -> three + required;
	}
	else{
		dest -> eight = src -> eight;
		dest -> five = 0;
		dest -> three = src -> three + src -> five;
	}
	dest -> fn_index = 0;
}
void three_eight(const state_t * src,state_t * dest){
	int required = 8 - src -> eight;//calculate amount of water required to fill eight litre
	if(src -> three >= required)//check if we have sufficient amount of water in three litre jug to fill eight litre
	{
		dest -> three = src -> three - required;
		dest -> five = src -> five;
		dest -> eight = src -> eight + required;
	}
	else{
		dest -> three = 0;
		dest -> eight = src -> three + src -> eight;
		dest -> five = src -> five;
	}
	dest -> fn_index = 0;
}
void three_five(const state_t * src,state_t * dest){
	int required = 5 - src -> five;//calculate amount of water required to fill five litre
	if(src -> three >= required)//check if we have sufficient amount of water in three litre jug to fill five litre
	{
		dest -> three = src -> three - required;
		dest -> five = src -> five + required;
		dest -> eight = src -> eight;
	}
	else{
		dest -> three = 0;
		dest -> five = src -> five + src -> three;
		dest -> eight = src -> eight;
	}
	dest -> fn_index = 0;
}
int are_same(const state_t *lhs, const state_t *rhs)//check if given two states are same or not
{
	return lhs -> eight == rhs -> eight && lhs -> five == rhs -> five && lhs -> three == rhs -> three;
}


//list operations
void init_list(list_t *ptr_list)
{
	ptr_list->head = NULL;
	ptr_list->tail = NULL;
}

void add_at_end(list_t *ptr_list, const state_t* ptr_state)

{
	node_t* temp = (node_t*) malloc(sizeof(node_t));
	//temp->key = key;
	temp->st = *ptr_state; 
	temp->next = temp->prev = NULL;

	if(ptr_list->tail == NULL)
	{
		temp->prev = temp->next = NULL;
		ptr_list->head = ptr_list->tail = temp;
	}
	else
	{
		temp->prev = ptr_list->tail;
		temp->next = NULL;
		ptr_list->tail = ptr_list->tail->next = temp;
	}
}
void remove_at_end(list_t *ptr_list)
{
	if(ptr_list->tail == NULL)
	{
		printf("empty list\n");
	}
	else  
	{
		node_t* temp = ptr_list->tail;
		ptr_list->tail = ptr_list->tail->prev;	
		if(ptr_list->tail == NULL)
		{
			ptr_list->head = NULL;
		}
		else
		{
			ptr_list->tail->next = NULL;
		}
		free(temp);		
	}
}
void disp_list(const list_t *ptr_list)
{
	node_t* temp = ptr_list->head;
	while(temp)
	{
		//printf("%d ", temp->key);
		disp_state(&temp->st);
		temp = temp->next;
	}
}



int is_repeated(const list_t* ptr_list, const state_t* ptr_state)//function to check if our state is already present in the list
{
	node_t* temp = ptr_list->head;
	int found = 0;
	while(temp && ! found)
	{
		found  = are_same(&temp->st, ptr_state);
		temp = temp->next;
	}
	return found;
}

int is_safe(const state_t* ptr_state)//function to check if a state is valid or not 
{
	return ((ptr_state -> eight >= 0 && ptr_state -> eight <= 8) && 
		    (ptr_state -> three >= 0 && ptr_state -> three <= 3) &&
		     (ptr_state -> five >= 0 && ptr_state -> five <= 5)  &&
		     (ptr_state -> five + ptr_state -> eight + ptr_state -> three == 8));
}