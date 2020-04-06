
#include <stdio.h>
#include "a4.h"

int main()
{
	tree_t t;
	FILE *fp;
	fp = init_tree(&t,"mytree.dat");
	int key;
	int opt;
	printf("Enter the option : ");
	scanf("%d",&opt);
	while(opt)
	{
		switch(opt)
		{
			case 1:printf("Enter the key to insert : ");
			       scanf("%d",&key);
			       insert_key(&t,key,fp);
			       break;
			case 2:printf("Enter the key to delete : ");
			       scanf("%d",&key);
			       delete_key(&t,key,fp);
			       break;
			case 3:display_inorder(&t,fp);
			       break;
			case 4:display_preorder(&t,fp);
			       break;
		}
		printf("Enter the next option : ");
		scanf("%d",&opt);
	}
	close_tree(&t, fp);
}
