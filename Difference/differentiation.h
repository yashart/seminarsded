#ifndef DIFFERENTIATION_H
#define DIFFERENTIATION_H

#include <errno.h>
#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <grp.h>
#include <printf.h>
#include <stdlib.h>
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
    bool is_simular;
    node* left;
    node* right;
};


extern lexem*    str_pos;
extern FILE* TEXT_LATEXT;
extern node* init_node;;

bool node_ok(node* new_node);
node* node_constructor();
void node_destructor(node* new_node);
void node_dump(node* new_node);
void node_dump_formul(node *new_node);
void node_dump_tex(node *old_node, node *new_node);
void node_dump_simplification(node * old_node, node *new_node);


node* get_data();
node* get_bracket();
node* get_elementar_func();
node* get_mul();
node* get_sum();
node* get_G0(lexem *str);

node* copy_tree(node* tree);

node* node_mul(node* left, node* right);
node* node_sum(node* left, node* right);
node* node_min(node* left, node* right);
node* node_del(node* left, node* right);

node* difference(node* tree);
void simplification(node **tree);

node* simular_difference(node* tree);

char* dump_phrases(int node_data);
char* dump_phrases_simplification(int node_data);
#endif