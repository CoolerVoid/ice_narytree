#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "icenarytree.h"



// user custom data to use in NODE of n-ary tree
struct data {
    bool taint;
    char *label;
    char *exp;
    char *var_name;
    int line;
};


typedef struct data data;


void *form_data(bool taint, char * label, char *exp, char *varname, int line)
{
	data *in=malloc(sizeof(data));

	in->label = strdup(label);
	in->var_name = strdup(varname);
        in->exp = strdup (exp);
        in->line = line;
        in->taint = taint;

	return (void *)in;
}

void inter_data(void *argv)
{
	data *in=(data *)argv;

	if(in != NULL)
	{
		printf("Label: %s\n var_name: %s\n Expression: %s\n", in->label,in->var_name,in->exp);
		printf("Line: %d\n ",in->line);
	}
}



void inter_free_treeleafs(void *argv)
{
	data *in=(data *)argv;

	if(in != NULL)
	{
		free(in->label);
		in->label=NULL;

		free(in->var_name);
		in->var_name=NULL;
	
		free(in->exp);
		in->exp=NULL;
	}
	free(in);
}



int main(int argc, char *argv[])
{

	// Insert data in nodes
	void *A=form_data(false,"attribute","x=0","x",10);
	node *root = new_node(0,A);

	void *B=form_data(false,"attribute","x+=2","x",11);
        append_child(root, 2,B);

	void *C=form_data(false,"attribute","x+=8","x",12);
        append_child(root, 3,C);

	void *D=form_data(false,"attribute","z+=8","z",14);
	append_sibling(root, 4,D);

	void *E=form_data(false,"attribute","z+=12","z",15);
        append_child(root, 5,E);

	// Show all data of N-ARY TREE
    	traversal_tree_dbg(root);

	//Search by POSITION NODE
	node *ret=search_in_tree_per_position(root,3);
	if(ret != NULL && ret->position != 0)
		printf("\nResult found: %d \n",ret->position);

	//INSERT NODE BEFORE
	void *F=form_data(false,"attribute","y+=2","y",16);
	insert_child_before(root,4,23,F);

	// CUSTOM SHOW ALL DATA
//	interate_traversal_tree(root,inter_data);
	
	// liberate heap memory, destroy all tree
	traversal_and_destroy(root,inter_free_treeleafs);

	return 0;
}

