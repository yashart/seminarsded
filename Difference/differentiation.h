#ifndef DIFFERENTIATION_H
#define DIFFERENTIATION_H

#include <errno.h>
#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include "operator_type.h"
#include "lexical.h"

enum priority
{
    P_NUM,
    P_SUM,
    P_MULT,
    P_SINUS
};

struct node
{
    int data;
    char type;
    priority prior;
    operator_pos pos;
    node* left;
    node* right;
};


extern lexem*    str_pos;

bool node_ok(node* new_node);
node* node_constructor();
void node_destructor(node* new_node);
void node_dump(node* new_node);

node* get_data();
node* get_bracket();
node* get_elementar_func();
node* get_mul();
node* get_sum();
node* get_G0(lexem *str);


node* copy_tree(node* tree);

node* difference(node* tree);
node* node_mul(node* left, node* right);
node* node_sum(node* left, node* right);
#endif