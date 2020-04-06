#include <stdio.h>
#include "a4.h"
static void preorder1(const tree_t *ptr_tree,int root,FILE *fp);
static void inorder1(const tree_t *ptr_tree,int root,FILE *fp);
static node_t findMin(int root,FILE *fp);
static void delete_subtree(int root,int key,FILE *fp);
FILE * fp1 = NULL;//file containing final output
FILE * init_tree(tree_t * ptr_tree,const char *name)
{
	FILE* fp = fopen(name, "r+");
	fp1 = fopen("0949_op.txt","w");
	if(fp == NULL)
	{
		printf("empty file\n");
		fp = fopen(name, "w");
		ptr_tree->free_head = -1;
		ptr_tree->root = -1;
		fwrite(ptr_tree,sizeof(tree_t),1,fp);//writing root and free_head to the file
		fclose(fp);
		fp = fopen(name, "r+");
	}
	fread(ptr_tree,sizeof(tree_t),1,fp);//reading root and free_head from the file
	return fp;
}
void close_tree(tree_t *ptr_tree, FILE *fp)
{
	fclose(fp);
	fclose(fp1);//closing output file
}
void insert_key(tree_t *ptr_tree,int key,FILE *fp)
{
	node_t temp_node;//used to store the inserting node
	node_t pres_node;
	node_t prev_node;
	int temp;
	temp_node.key = key;//inseting key value to the node
	temp_node.left_offset = -1;
	temp_node.right_offset = -1;
	fseek(fp,0,SEEK_END);//finding a place where we can insert node
	temp = ftell(fp);
	fseek(fp,temp,SEEK_SET);
	fwrite(&temp_node,sizeof(node_t),1,fp);//write the node in the file
	if(ptr_tree -> root == -1)//if tree is empty
	{
		ptr_tree -> root = temp;//set the root to the first element inserted
		fseek(fp,0,SEEK_SET);
		fwrite(ptr_tree,sizeof(tree_t),1,fp);//write into file
	}
	else
	{
		int prev = -1;
		int pres = ptr_tree -> root;
		fseek(fp,pres,SEEK_SET);
		fread(&pres_node,sizeof(node_t),1,fp);
		while(pres_node.key != key && pres != -1)//first condition to check for duplicate keys
		{
			fseek(fp,pres,SEEK_SET);
			pres = ftell(fp);
			prev = pres;
            fread(&pres_node,sizeof(node_t),1,fp);
            if(key < pres_node.key)//if key is less than root key go to the left sub tree
            {
            	pres = pres_node.left_offset;
            }
            else
            {
            	pres = pres_node.right_offset;
            }
		}
		fseek(fp,prev,SEEK_SET);
		fread(&prev_node,sizeof(node_t),1,fp);
		if(pres_node.key == key)//if we found duplicate value return 
		{
			return ;
		}
		else if(key < prev_node.key)
		{
			prev_node.left_offset = temp;
			fseek(fp,prev,SEEK_SET);
			fwrite(&prev_node,sizeof(node_t),1,fp);
		}
		else
		{
			prev_node.right_offset = temp;
			fseek(fp,prev,SEEK_SET);
			fwrite(&prev_node,sizeof(node_t),1,fp);
		}
	}
}
void display_preorder(const tree_t *ptr_tree,FILE * fp)
{
	preorder1(ptr_tree,ptr_tree -> root,fp);//recursive function 
	fprintf(fp1,"\n");
}
static void preorder1(const tree_t *ptr_tree,int root,FILE *fp)
{
	fseek(fp,root,SEEK_SET);
	node_t temp_node;
	if(root != -1)
	{
		fread(&temp_node,sizeof(node_t),1,fp);
		fprintf(fp1,"%d ",temp_node.key);
		preorder1(ptr_tree,temp_node.left_offset,fp);
		preorder1(ptr_tree,temp_node.right_offset,fp);
	}
}
void display_inorder(const tree_t *ptr_tree,FILE * fp)
{
	inorder1(ptr_tree,ptr_tree -> root,fp);
	fprintf(fp1,"\n");
}
static void inorder1(const tree_t *ptr_tree,int root,FILE *fp)
{
	node_t temp_node;
	if(root != -1)
	{
		fseek(fp,root,SEEK_SET);
		fread(&temp_node,sizeof(node_t),1,fp);
		inorder1(ptr_tree,temp_node.left_offset,fp);
		fprintf(fp1,"%d ",temp_node.key);
		inorder1(ptr_tree,temp_node.right_offset,fp);
	}
}
void delete_key(tree_t *ptr_tree, int key, FILE *fp)
{
	node_t temp_node;
	node_t prev_node;
	node_t pres_node;
	if(ptr_tree -> root == -1)//tree is empty
	{
		printf("Tree is empty;Cannot be deleted\n");
	}
	else
	{
		int pres = ptr_tree -> root;//traversing tree start from root
		int prev = -1;
		fseek(fp,pres,SEEK_SET);
		pres = ftell(fp);
		fread(&pres_node,sizeof(node_t),1,fp);
		while(pres != -1 && pres_node.key != key)//travesing the tree
		{
			prev = pres;
			if(key < pres_node.key)
			{
				pres = pres_node.left_offset;
				fseek(fp,pres,SEEK_SET);
				fread(&pres_node,sizeof(node_t),1,fp);
			}
			else
			{
				pres = pres_node.right_offset;
				fseek(fp,pres,SEEK_SET);
				fread(&pres_node,sizeof(node_t),1,fp);
			}
		}
		if(pres == -1)//element dosen't exist
		{
			printf("Element not found\n");
		}
		else
		{
			//Case #1:Deleting Leaf node case
			if(pres_node.left_offset == -1 && pres_node.right_offset == -1)
			{
				fseek(fp,prev,SEEK_SET);
				fread(&prev_node,sizeof(node_t),1,fp);
				fseek(fp,prev_node.right_offset,SEEK_SET);
                fread(&temp_node,sizeof(node_t),1,fp);
				if(prev_node.right_offset != -1 && temp_node.key == key)
				{
					prev_node.right_offset = -1;
					fseek(fp,prev,SEEK_SET);
					fwrite(&prev_node,sizeof(node_t),1,fp);
				}
				else
				{
					prev_node.left_offset = -1;
					fseek(fp,prev,SEEK_SET);
					fwrite(&prev_node,sizeof(node_t),1,fp);
				}
			}
		    //Case #2:Deleting when right  subtree exist
		    else if(pres_node.left_offset == -1)
		    {
		    	fseek(fp,prev,SEEK_SET);
		    	fread(&prev_node,sizeof(node_t),1,fp);
		    	if(key < prev_node.key)
		    	{
		    		prev_node.left_offset = pres_node.right_offset;//update the parent pointer of the node to be deleted
		    		fseek(fp,prev,SEEK_SET);
		    		fwrite(&prev_node,sizeof(node_t),1,fp);
		    	}
		    	else
		    	{
		    		prev_node.right_offset = pres_node.right_offset;
		    		fseek(fp,prev,SEEK_SET);
		    		fwrite(&prev_node,sizeof(node_t),1,fp);
		    	}
		    }
		    //Case #3:Deleting when left subtree exists
		    else if(pres_node.right_offset == -1)
		    {
		    	fseek(fp,prev,SEEK_SET);
		    	fread(&prev_node,sizeof(node_t),1,fp);
		    	if(key < prev_node.key)
		    	{
		    		prev_node.left_offset = pres_node.left_offset;
		    		fseek(fp,prev,SEEK_SET);//go to the prev node
		    		fwrite(&prev_node,sizeof(node_t),1,fp);//write prev node to the file
		    	}
		    	else
		    	{
		    		prev_node.right_offset = pres_node.left_offset;
		    		fseek(fp,prev,SEEK_SET);
		    		fwrite(&prev_node,sizeof(node_t),1,fp);
		    	}
		    }
		    //Case #4 : Deleting when both subtree exits
		    else
		    {
		        temp_node = findMin(pres_node.right_offset,fp);//find inorder successor
		        pres_node.key = temp_node.key;
		        fseek(fp,pres,SEEK_SET);
		        fwrite(&pres_node,sizeof(node_t),1,fp);
		        delete_subtree(pres,temp_node.key,fp);//delete the minimum node in the right subtree	
		    }
		}
	}
}
static node_t findMin(int root,FILE *fp)//to find the minimum in the subtree
{
	node_t min;
	int minimum;
	fseek(fp,root,SEEK_SET);
	fread(&min,sizeof(node_t),1,fp);
	while(min.left_offset != -1)
	{
		minimum = min.left_offset;
		fseek(fp,minimum,SEEK_SET);
		fread(&min,sizeof(node_t),1,fp);
	}
	return min;
}
static void delete_subtree(int root,int key,FILE *fp)
{
	node_t temp_node;
	node_t prev_node;
	node_t pres_node;
	int prev = root;
	fseek(fp,root,SEEK_SET);
	fread(&prev_node,sizeof(node_t),1,fp);
	int pres = prev_node.right_offset;
	fseek(fp,pres,SEEK_SET);
	fread(&pres_node,sizeof(node_t),1,fp);
	while(pres != -1 && pres_node.key != key)//find the position of element
	{
		prev = pres;
		if(key < pres_node.key)
		{
			pres = pres_node.left_offset;
			fseek(fp,pres,SEEK_SET);
			fread(&pres_node,sizeof(node_t),1,fp);
		}
		else
		{
			pres = pres_node.right_offset;
			fseek(fp,pres,SEEK_SET);
			fread(&pres_node,sizeof(node_t),1,fp);
		}
	}
	if(pres_node.left_offset == -1 && pres_node.right_offset == -1)
	{
		fseek(fp,prev,SEEK_SET);
		fread(&prev_node,sizeof(node_t),1,fp);
		fseek(fp,prev_node.right_offset,SEEK_SET);
        fread(&temp_node,sizeof(node_t),1,fp);
        //case when deleting leaf node
		if(prev_node.right_offset != -1 && temp_node.key == key)
		{
			prev_node.right_offset = -1;
			fseek(fp,prev,SEEK_SET);
			fwrite(&prev_node,sizeof(node_t),1,fp);
		}
		else
		{
			prev_node.left_offset = -1;
			fseek(fp,prev,SEEK_SET);
			fwrite(&prev_node,sizeof(node_t),1,fp);
		}
	}
	    //case when only right subtree exists
	    else if(pres_node.left_offset == -1)
       {
		    fseek(fp,prev,SEEK_SET);
		    fread(&prev_node,sizeof(node_t),1,fp);
		    if(key < prev_node.key)
		   {
		    prev_node.left_offset = pres_node.right_offset;
		    fseek(fp,prev,SEEK_SET);
		    fwrite(&prev_node,sizeof(node_t),1,fp);
		    }
		else
		{
		    prev_node.right_offset = pres_node.right_offset;
		    fseek(fp,prev,SEEK_SET);
		    fwrite(&prev_node,sizeof(node_t),1,fp);
		}
	}
   //Case #3:Deleting when left subtree exists
    else if(pres_node.right_offset == -1)
    {
		fseek(fp,prev,SEEK_SET);
		fread(&prev_node,sizeof(node_t),1,fp);
		if(key < prev_node.key)
		{
		    prev_node.left_offset = pres_node.left_offset;
		    fseek(fp,prev,SEEK_SET);
		    fwrite(&prev_node,sizeof(node_t),1,fp);
		}
    }
}