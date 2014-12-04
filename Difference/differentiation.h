#ifndef DIFFERENTIATION_H
#define DIFFERENTIATION_H

#include <errno.h>
#include <stdio.h>
#include <assert.h>
#include <malloc.h>


typedef char func_operator;

struct function_data
{
    double number;
    double x_degree;
};

struct node
{
    function_data data;
    char math_operator;
    node* left;
    node* right;
};

extern char*    str;
extern char*    str_pos;
extern const int MAX_STR_NUMBER;

bool node_ok(node* new_node);
node* node_constructor();
void node_destructor(node* new_node);
void node_dump(node* new_node);

node* get_data();
node* get_bracket();
node* get_elementar_func();
node* get_mul();
node* get_sum();
node* get_G0();


#endif