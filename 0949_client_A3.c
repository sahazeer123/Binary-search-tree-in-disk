#include "0949_header_A3.h"
int main(){
    freopen("0949_A3_op.txt","w",stdout);
    int count = 0;
    state_t start_state;
    set_state(&start_state,8 ,0,0);
    state_t goal_state;
    set_state(&goal_state,3,5,0);
    list_t l;
    init_list(&l);
    state_t temp;
    int soln = 0;
    add_at_end(&l,&start_state);
    int index;
    void (*move[])(const state_t *src,state_t *dest) = {
        eight_five,
        eight_three,
        five_eight,
        five_three,
        three_eight,
        three_five
    };
    int i = 0;
    while(l.tail)//check if there is a solution
    {
        index = l.tail -> st.fn_index;
        move[index](&l.tail->st,&temp);
        if(is_safe(&temp) && !is_repeated(&l,&temp))//check if produced state valid or not
        {
            add_at_end(&l,&temp);
            soln = are_same(&temp,&goal_state);
            if(soln){
                disp_list(&l);
                remove_at_end(&l);//remove the goal state 
                while(l.tail && ++l.tail->st.fn_index == 6)//update function index and if fn index == 6 remove the last node
                {
                    remove_at_end(&l);
                }
                count += 1;
                printf("\n");
            }
        }
        else{
            while(l.tail && ++l.tail->st.fn_index == 6)//updating function index and backtracking 
            {
                remove_at_end(&l);
            }
            }
        }
        printf("%d",count);
        return 1;
    }
