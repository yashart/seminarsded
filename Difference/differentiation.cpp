#include "differentiation.h"

lexem* str_pos;
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

node *get_G0(lexem *str)
{
    /*
    func_node = node_constructor();
    assert(node_ok(func_node));

    if(!str)
    {
        errno = EFAULT;
        perror("NULL pointer");
    }
    str_pos = str;

    func_node->left = get_sum();
    assert(node_ok(func_node->left));

    free(str);
    */
    str_pos = str;
    return get_sum();
}

node* get_sum()
{
    node* left = get_mul();
    if((str_pos->type == OPERATOR)&&(str_pos->value == '+')||(str_pos->value == '-'))
    {
        node* sum_node = NULL;
        sum_node = node_constructor();
        assert(node_ok(sum_node));

        sum_node->type  = OPERATOR;
        sum_node->data  = str_pos->value;
        sum_node->prior = P_SUM;
        sum_node->pos   = INFIX;
        sum_node->left  = left;
        str_pos++;
        sum_node->right = get_sum();

        assert(node_ok(sum_node));
        return sum_node;
    }
    return left;
}

node* get_mul()
{
    node* left = get_elementar_func();
    if((str_pos->type == OPERATOR)&&(str_pos->value == '*')||(str_pos->value == '/'))
    {
        node* mul_node = NULL;
        mul_node = node_constructor();
        assert(node_ok(mul_node));

        mul_node->type  = OPERATOR;
        mul_node->data  = str_pos->value;
        mul_node->prior = P_MULT;
        mul_node->pos   = INFIX;
        mul_node->left  = left;
        str_pos++;
        mul_node->right = get_mul();
        assert(node_ok(mul_node));
        return mul_node;
    }
    return left;
}

node* get_elementar_func()
{
    if((str_pos->type == OPERATOR)&&((str_pos->value == 's')||(str_pos->value == 'c')))
    {
        node* elem_node = NULL;
        elem_node = node_constructor();
        assert(node_ok(elem_node));

        elem_node->type  = OPERATOR;
        elem_node->data  = str_pos->value;
        elem_node->prior = P_SINUS;
        elem_node->pos   = PREFIX;
        str_pos++;
        elem_node->left  = get_elementar_func();
        assert(node_ok(elem_node));
        return elem_node;
    }
    return get_bracket();
}

node* get_bracket()
{
    node* bracket = NULL;
    if((str_pos->type == OPERATOR)&&(str_pos->value == '('))
    {
        str_pos++;
        bracket = get_sum();
        str_pos++;
    }else
    {
        bracket = get_data();
    }
   return bracket;
}

node* get_data()
{
    if((str_pos->type == VARIABLE)||(str_pos->type == NUMBER)||(str_pos->type == END_LEXEM))
    {
        node *data_node = NULL;
        data_node = node_constructor();
        assert(node_ok(data_node));

        data_node->type  = str_pos->type;
        data_node->data  = str_pos->value;
        data_node->prior = P_NUM;
        data_node->pos  = INFIX;
        str_pos++;

        assert(node_ok(data_node));
        return data_node;
    }
    perror("PLAK PLAK");
    return NULL;
}

void node_dump(node *new_node)
{
    if(new_node->pos == INFIX)
    {
        if(new_node->left != NULL)
        {
            if((new_node->prior > new_node->left->prior)&&(new_node->type == new_node->left->type))
                printf("(");
            node_dump(new_node->left);
            if((new_node->prior > new_node->left->prior)&&(new_node->type == new_node->left->type))
                printf(")");
        }

        if(new_node->type == OPERATOR)
            printf("%c", new_node->data);
        if(new_node->type == NUMBER)
            printf("%d", new_node->data);
        if(new_node->type == VARIABLE)
            printf("%c", new_node->data);

        if(new_node->right != NULL)
        {
            if((new_node->prior > new_node->right->prior)&&(new_node->type == new_node->right->type))
                printf("(");
            node_dump(new_node->right);
            if((new_node->prior > new_node->right->prior)&&(new_node->type == new_node->right->type))
                printf(")");
        }
    }
    if(new_node->pos == PREFIX)
    {
        if(new_node->type == OPERATOR)
            printf("%c", new_node->data);
        if(new_node->type == NUMBER)
            printf("%d", new_node->data);
        if(new_node->type == VARIABLE)
            printf("%c", new_node->data);
        if(new_node->left != NULL)
        {
            if(new_node->left->pos != PREFIX)
                printf("(");
            node_dump(new_node->left);
            if(new_node->left->pos != PREFIX)
                printf(")");
        }
        if(new_node->right != NULL)
        {
            node_dump(new_node->right);
        }
    }
    if(new_node->pos == POSTFIX)
    {
        if(new_node->left != NULL)
        {
            node_dump(new_node->left);
        }
        if(new_node->right != NULL)
        {
            node_dump(new_node->right);
        }
        if(new_node->type == OPERATOR)
            printf("%c", new_node->data);
        if(new_node->type == NUMBER)
            printf("%d", new_node->data);
        if(new_node->type == VARIABLE)
            printf("%c", new_node->data);
    }
}



node* difference(node *tree)
{
    node* new_node = NULL;
    node* func_node = NULL;
    switch(tree->prior)
    {
        case P_NUM:
            if(tree->type == VARIABLE)
            {
                new_node = node_constructor();
                assert(node_ok(new_node));

                new_node->type  = NUMBER;
                new_node->data  = 1;
                new_node->prior = P_NUM;
                new_node->pos   = INFIX;
                break;
            }
            if(tree->type == NUMBER)
            {
                new_node = node_constructor();
                assert(node_ok(new_node));

                new_node->type = NUMBER;
                new_node->data = 0;
                new_node->prior = P_NUM;
                new_node->pos   = INFIX;
                break;
            }
        case P_SINUS:
            if(tree->data == 's')
            {
                func_node = copy_tree(tree);
                func_node->data = 'c';
                func_node->pos   = PREFIX;
                new_node = node_mul(func_node, difference(tree->left));
                break;
            }
            new_node = node_mul(copy_tree(tree->left), difference(tree->left));
            break;
        case P_MULT:
            new_node = node_sum(node_mul(copy_tree(tree->left), difference(tree->right)),\
                                node_mul(difference(tree->left), copy_tree(tree->right)));
            break;
        case P_SUM:
            new_node = node_sum(difference(tree->left), difference(tree->right));
            break;
        default:
            perror("Plack Plak");
    }
    return new_node;
}

node* copy_tree(node *tree)
{
    node* new_node = node_constructor();
    assert(node_ok(new_node));

    new_node->type  = tree->type;
    new_node->data  = tree->data;
    new_node->prior = tree->prior;
    new_node->pos   = tree->pos;

    if(tree->left != NULL)
        new_node->left  = copy_tree(tree->left);
    if(tree->right != NULL)
        new_node->right = copy_tree(tree->right);

    return new_node;
}

node* node_mul(node* left, node* right)
{
    node* new_node = node_constructor();
    assert(node_ok(new_node));

    new_node->type  = OPERATOR;
    new_node->data  = '*';
    new_node->prior = P_MULT;
    new_node->pos   = INFIX;
    new_node->left  = left;
    new_node->right = right;

    return new_node;
}

node* node_sum(node* left, node* right)
{
    node* new_node = node_constructor();
    assert(node_ok(new_node));

    new_node->type  = OPERATOR;
    new_node->data  = '+';
    new_node->prior = P_SUM;
    new_node->pos   = INFIX;
    new_node->left  = left;
    new_node->right = right;

    return new_node;
}
