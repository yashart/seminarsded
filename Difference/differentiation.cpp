#include "differentiation.h"

char* str;
char* str_pos;
const int MAX_STR_NUMBER = 50;
node* func_node;

node* node_constructor()
{
    node* new_node = (node*) calloc(1, sizeof(*new_node));
    assert(node_ok(new_node));
    return new_node;
}

bool node_ok(node *new_node)
{
    if(!new_node)
    {
        errno = EFAULT;
        perror("NULL pointer");
        return false;
    }
    return true;
}

void node_destructor(node *new_node)
{
    assert(node_ok(new_node));
    if(new_node->left != NULL)
    {
        node_destructor(new_node->left);
    }
    if(new_node->right != NULL)
    {
        node_destructor(new_node->right);
    }
    free(new_node);
}

node *get_G0()
{
    func_node = node_constructor();
    assert(node_ok(func_node));

    str = (char*) calloc(MAX_STR_NUMBER, sizeof(*str));
    if(!str)
    {
        errno = EFAULT;
        perror("NULL pointer");
    }
    if(!scanf("%s", str))
    {
        errno = SEEK_DATA;
        perror("bad scanf");
    }

    str_pos = str;

    func_node->left = get_sum();
    assert(node_ok(func_node->left));

    free(str);
    return func_node;
}

node* get_sum()
{
    node* sum_node = NULL;
    sum_node = node_constructor();
    assert(node_ok(sum_node));
    sum_node->left = get_mul();
    switch(*str_pos)
    {
        case '+':
            str_pos++;
            sum_node->right = get_sum();
            sum_node->math_operator = '+';
            break;
        case '-':
            str_pos++;
            sum_node->right = get_sum();
            sum_node->math_operator = '-';
            break;
        default:
            sum_node->math_operator = '\0';
            break;
    }
    assert(node_ok(sum_node));
    return sum_node;
}

node* get_mul()
{
    node* mul_node = NULL;
    mul_node = node_constructor();
    assert(node_ok(mul_node));
    mul_node->left = get_elementar_func();
    switch(*str_pos)
    {
        case '*':
            str_pos++;
            mul_node->right = get_mul();
            mul_node->math_operator = '*';
            break;
        case '/':
            str_pos++;
            mul_node->right = get_mul();
            mul_node->math_operator = '/';
            break;
        default:
            mul_node->math_operator = '\0';
            break;
    }
    assert(node_ok(mul_node));
    return mul_node;
}

node* get_elementar_func()
{
    node* elem_node = NULL;
    elem_node = node_constructor();
    assert(node_ok(elem_node));
    switch(*str_pos)
    {
        case 'l':
            str_pos++;
            elem_node->left = get_elementar_func();
            elem_node->math_operator = 'l';
            break;
        default:
            elem_node->math_operator = '\0';
            elem_node->left = get_bracket();
            break;
    }
    return elem_node;
}

node* get_bracket()
{
    node* brack_node = NULL;
    brack_node = node_constructor();
    assert(node_ok(brack_node));
    switch(*str_pos)
    {
        case '(':
            str_pos++;
            brack_node->left = get_sum();
            brack_node->math_operator = ')';
            if(*str_pos != ')')
            {
                errno = EINVAL;
                perror("Bad bracket");
            }
            str_pos++;
            break;
        default:
        {
            brack_node->left = get_data();
            brack_node->math_operator = '\0';
            break;
        }
    }
    return brack_node;
}

node* get_data()
{
    node* data_node = NULL;
    data_node = node_constructor();
    assert(node_ok(data_node));
    while(((0 <= (*str_pos - '0'))&&((*str_pos - '0') <= 9))||(*str_pos == 'x'))
    {
        if(*str_pos == 'x')
        {
            str_pos++;
            data_node->data.x_degree += 1;
        }else
        {
            data_node->data.number = 10*data_node->data.number + *str_pos - '0';
            str_pos++;
        }
    }
    return data_node;
}

void node_dump(node *new_node)
{
    if(new_node->math_operator == ')')
        printf("(");
    if(new_node->left != NULL)
        node_dump(new_node->left);

    if(new_node->data.number != 0)
        printf("%lgx^%lg", new_node->data.number, new_node->data.x_degree);
    printf("%c", new_node->math_operator);

    if(new_node->right != NULL)
        node_dump(new_node->right);
}
