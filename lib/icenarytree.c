#include "icenarytree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

// alocation tasks
void icetree_xfree(void **ptr) 
{
	assert(ptr);
	if( ptr != NULL )
        {
		free(*ptr);
		*ptr=NULL;	
        }
	
}

   
volatile void *icetree_burn_mem(volatile void *dst, int c, size_t len) 
{
	volatile char *buf;
   
	for(buf = (volatile char *)dst;  len;  buf[--len] = c);

	return dst;
}


static void *icetree_xmalloc_fatal(size_t size) 
{
	if ( size == 0 ) 
		return NULL;

	ICETREE_DEBUG("\n Memory FAILURE...\n");

	exit(1);
}

void *icetree_xmalloc(size_t size) 
{
	void *ptr = malloc(size);

	if (ptr == NULL) 
		return icetree_xmalloc_fatal(size);

	return ptr;
}



void traversal_and_destroy(struct node *root,void (*lambda)(void *argvs))
{
	if(root == NULL) 
		return;

	traversal_and_destroy(root->next,lambda);
	traversal_and_destroy(root->child,lambda);

	lambda(root->data);

    	free(root);
	root=NULL;
	// XFREE_ICETREE(root);
}


// based on glib n-ary tree
void interate_traversal_tree(struct node *root, void (*lambda)(void *argvs))
{

	if(root != NULL) 
	{
		lambda(root->data);
		// TREE_DEBUG("Node Value : %d\n",root->position);
		interate_traversal_tree(root->next,lambda);
		// TREE_DEBUG("The Child have the position: ");
		interate_traversal_tree(root->child,lambda);
	} 
}



node * search_in_tree_per_position(struct node *root, int position) 
{
	struct node *current = root;

	if(current!=NULL)
	{
 		if(current->position == position) 
			return current;
	
		struct node *test1=search_in_tree_per_position(current->next,position);	
		struct node *test2=search_in_tree_per_position(current->child,position);
	
		if(test1!=NULL && test1->position == position)
			return test1;

		if(test2 != NULL && test2->position == position)
			return test2;

//		if(test1!=NULL)
//			free(test1);
//		if(test2!=NULL)
//			free(test2);
	}

	return current;
}



node * insert_sibling_before(struct node *root, int position,int new_position, void *data) 
{
	struct node *current = root;

	while(current->position != position) 
	{
		if(current->position > position) 
			current = current->child;
      		else 
         		current = current->next;
      		if(current == NULL) 
         		return NULL;   
   	}
   
   	node *new_node = icetree_xmalloc(sizeof(node));

   	if(new_node) 
   	{
		new_node->next = NULL;
		new_node->child = NULL;
		new_node->position = new_position;
		new_node->data = data;
   	}

   	current->next=new_node;

   	return current;
}


node * insert_child_before(struct node *root, int position,int new_position, void *data) 
{
	struct node *current = root;

	while(current->position != position) 
	{
		if(current->position > position) 
			current = current->child;
      		else 
         		current = current->next;
      		if(current == NULL) 
         		return NULL;   
   	}
   
   	node *new_node = icetree_xmalloc(sizeof(node));

   	if(new_node) 
   	{
		new_node->next = NULL;
		new_node->child = NULL;
		new_node->position = new_position;
		new_node->data = data;
   	}

   	current->child=new_node;

   	return current;
}

void traversal_tree_dbg(struct node *root)
{
	if(root != NULL) 
	{
		ICETREE_DEBUG("Node Value : %d\n",root->position);
		traversal_tree_dbg(root->next);
		ICETREE_DEBUG("Child:");
		traversal_tree_dbg(root->child);
	} 
}


node * new_node(int position, void *data)
{
	node *new_node = icetree_xmalloc(sizeof(node));

	if(new_node) 
	{
		new_node->next = NULL;
		new_node->child = NULL;
		new_node->data = data;
		new_node->position = position;
    	}

	return new_node;
}

node * append_sibling(node * n, int position,void *data)
{
	if(n == NULL)
		return NULL;

    	while(n->next)
		n = n->next;

	return(n->next = new_node(position,data));
}

node * append_child(node * n, int position, void *data)
{
	if(n == NULL)
		return NULL;

    	if(n->child)
		return append_sibling(n->child, position,data);
	else
		return (n->child = new_node(position,data));
}
