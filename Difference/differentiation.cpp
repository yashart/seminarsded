#include "differentiation.h"

lexem* str_pos;

node* node_constructor()
{
    
    node* new_node = (node*) calloc(1, sizeof(*new_node));
    assert(node_ok(new_node));
    new_node->is_simular = false;
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
    return get_separator();
}

node* get_separator()
{
    
    node* left = get_while();
    if((str_pos->type == SEPARATOR)&&(str_pos->value == ';'))
    {
        node* separator_node = NULL;
        separator_node = node_constructor();
        assert(node_ok(separator_node));
        separator_node->right = NULL;
        separator_node->type = SEPARATOR;
        separator_node->data = str_pos->value;
        separator_node->prior = P_SEPARATOR;
        separator_node->pos  = INFIX;
        str_pos++;
        separator_node->left = left;
        separator_node->right = get_separator();
        assert(node_ok(separator_node));
        return separator_node;
    }
    return left;
}
node* get_while()
{
    if((str_pos->type == COMMAND)&&(str_pos->value == 'w'))
    {
        node* while_node = NULL;
        while_node = node_constructor();
        assert(node_ok(while_node));
        while_node->type  = COMMAND;
        while_node->data  = str_pos->value;
        while_node->prior = P_WHILE;
        while_node->pos   = PREFIX;
        str_pos++;
        while_node->left  = get_compare();
        while_node->right = get_while();
        assert(node_ok(while_node));
        return while_node;
    }
    return get_if();
}

node* get_if()
{
    
    if((str_pos->type == COMMAND)&&(str_pos->value == 'i'))
    {
        node* if_node = NULL;
        if_node = node_constructor();
        assert(node_ok(if_node));
        if_node->type  = COMMAND;
        if_node->data  = str_pos->value;
        if_node->prior = P_IF;
        if_node->pos   = PREFIX;
        str_pos++;
        if_node->left  = get_compare();
        if_node->right = get_if();
        assert(node_ok(if_node));
        return if_node;
    }
    return get_com_bracket();
}
node* get_com_bracket()
{
    
    node* bracket = NULL;
    if((str_pos->type == OPERATOR)&&(str_pos->value == '{'))
    {
        str_pos++;
        bracket = get_separator();
        if(str_pos->value == '}')
        {
            str_pos++;
        }
        return bracket;
    }
    bracket = get_command();
    return bracket;
}

node* get_command()
{
    if(str_pos->type == PRINTF)
    {
        node* printf_node = NULL;
        printf_node = node_constructor();
        assert(node_ok(printf_node));
        printf_node->type = PRINTF;
        printf_node->data = str_pos->value;
        printf_node->prior = P_PRINTF;
        printf_node->pos  = PREFIX;
        str_pos++;
        assert(node_ok(printf_node));
        return printf_node;
    }
    node* left = get_compare();
    if((str_pos->type == OPERATOR)&&(str_pos->value == '='))
    {
        node* assign_node = NULL;
        assign_node = node_constructor();
        assert(node_ok(assign_node));
        assign_node->type = OPERATOR;
        assign_node->data = str_pos->value;
        assign_node->prior = P_ASSIGN;
        assign_node->pos  = INFIX;
        assign_node->left = left;
        str_pos++;
        assign_node->right = get_compare();

        assert(node_ok(assign_node));
        return assign_node;
    }
    return left;
}

node* get_compare()
{
    
    node* left = get_sum();
    if((str_pos->type == OPERATOR)&&((str_pos->value == 'e')||(str_pos->value == '>')||(str_pos->value == '<')))
    {
        node* compare_node = NULL;
        compare_node = node_constructor();
        assert(node_ok(compare_node));

        compare_node->type = OPERATOR;
        compare_node->data = str_pos->value;
        compare_node->prior = P_COMPARE;
        compare_node->pos   = INFIX;
        compare_node->left  = left;
        str_pos++;
        compare_node->right = get_compare();

        assert(node_ok(compare_node));
        return compare_node;
    }
    return left;
}

node* get_sum()
{
    
    node* left = get_mul();
    if((str_pos->type == OPERATOR)&&((str_pos->value == '+')||(str_pos->value == '-')))
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
        bracket = get_compare();
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
        data_node->right = NULL;
        data_node->left  = NULL;
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

void node_dump_formul(node *new_node)
{
    FILE** file = &TEXT_LATEXT;
    if(new_node->is_simular)
        fprintf(*file ,"(");
    if(new_node->pos == INFIX)
    {
        if(new_node->data == '/')
        {
            fprintf(*file, "\\frac");
            if(new_node->left != NULL)
            {
                fprintf(*file, "{");
                if(new_node->left->pos != PREFIX)
                    fprintf(*file, "(");
                node_dump_formul(new_node->left);
                if(new_node->left->pos != PREFIX)
                    fprintf(*file, ")");
                fprintf(*file, "}");
            }
            if(new_node->right != NULL)
            {
                fprintf(*file, "{");
                if(new_node->right->pos != PREFIX)
                    fprintf(*file, "(");
                node_dump_formul(new_node->right);
                if(new_node->right->pos != PREFIX)
                    fprintf(*file, ")");
                fprintf(*file, "}");
            }
        }
        else {
            if (new_node->left != NULL)
            {
                if ((new_node->prior > new_node->left->prior) && (new_node->type == new_node->left->type))
                    fprintf(*file, "(");
                node_dump_formul(new_node->left);
                if ((new_node->prior > new_node->left->prior) && (new_node->type == new_node->left->type))
                    fprintf(*file, ")");
            }

            if((new_node->data == '*')&&(new_node->type == OPERATOR))
                fprintf(*file, "\\cdot{");
            else if (new_node->type == OPERATOR)
                fprintf(*file, "%c", new_node->data);
            if (new_node->type == NUMBER)
                fprintf(*file, "%d", new_node->data);
            if (new_node->type == VARIABLE)
                fprintf(*file, "%c", new_node->data);

            if (new_node->right != NULL)
            {
                if ((new_node->prior > new_node->right->prior) && (new_node->type == new_node->right->type))
                    fprintf(*file, "(");
                node_dump_formul(new_node->right);
                if ((new_node->prior > new_node->right->prior) && (new_node->type == new_node->right->type))
                    fprintf(*file, ")");
            }
            if((new_node->data == '*')&&(new_node->type == OPERATOR))
                fprintf(*file, "}");
        }
    }
    if(new_node->pos == PREFIX)
    {
        if(new_node->type == OPERATOR)
        {
            if (new_node->data == 'c')
                fprintf(*file, "cos");
            if (new_node->data == 's')
                fprintf(*file, "sin");
        }

        if(new_node->type == NUMBER)
            fprintf(*file, "%d", new_node->data);
        if(new_node->type == VARIABLE)
            fprintf(*file, "%c", new_node->data);
        if(new_node->left != NULL)
        {
            if(new_node->left->pos != PREFIX)
                fprintf(*file, "(");
            node_dump_formul(new_node->left);
            if(new_node->left->pos != PREFIX)
                fprintf(*file, ")");
        }
        if(new_node->right != NULL)
        {
            node_dump_formul(new_node->right);
        }
    }
    if(new_node->pos == POSTFIX)
    {
        if(new_node->left != NULL)
        {
            node_dump_formul(new_node->left);
        }
        if(new_node->right != NULL)
        {
            node_dump_formul(new_node->right);
        }
        if(new_node->type == OPERATOR)
            fprintf(*file, "%c", new_node->data);
        if(new_node->type == NUMBER)
            fprintf(*file, "%d", new_node->data);
        if(new_node->type == VARIABLE)
            fprintf(*file, "%c", new_node->data);
    }
    if(new_node->is_simular)
        fprintf(*file ,")'");
}

void node_dump_tex(node *old_node, node *new_node)
{
    char* phrases = dump_phrases(old_node->data);
    fprintf(TEXT_LATEXT ,"%s:\\\\\n", phrases);
    free(phrases);
    fprintf(TEXT_LATEXT, "$");
    node_dump_formul(old_node);
    fprintf(TEXT_LATEXT, "$");
    fprintf(TEXT_LATEXT, " -> ");
    fprintf(TEXT_LATEXT, "$");
    node_dump_formul(new_node);
    fprintf(TEXT_LATEXT, "$");
    fprintf(TEXT_LATEXT ,"\\\\\n");
}

node* difference(node *tree)
{
    node* new_node = NULL;
    node* func_node = NULL;
    node* simul_node = NULL;

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
                simul_node = node_mul(copy_tree(func_node), simular_difference(tree->left));
                node_dump_tex(tree, simul_node);
                new_node = node_mul(func_node, difference(tree->left));
                break;
            }
            if(tree->data == 'c')
            {
                func_node = node_constructor();
                func_node->data  = -1;
                func_node->type  = NUMBER;
                func_node->pos   = INFIX;
                func_node->prior = P_NUM;
                func_node = node_mul(func_node, copy_tree(tree));
                func_node->right->data = 's';
                func_node->right->pos   = PREFIX;

                simul_node = node_mul(copy_tree(func_node), simular_difference(tree->left));
                node_dump_tex(tree, simul_node);
                new_node = node_mul(func_node, difference(tree->left));
                break;
            }
            new_node = node_mul(copy_tree(tree->left), difference(tree->left));
            break;
        case P_MULT:
            if(tree->data == '*')
            {
                simul_node = node_sum(node_mul(copy_tree(tree->left), simular_difference(tree->right)), \
                                    node_mul(simular_difference(tree->left), copy_tree(tree->right)));
                node_dump_tex(tree, simul_node);
                new_node = node_sum(node_mul(copy_tree(tree->left), difference(tree->right)), \
                                    node_mul(difference(tree->left), copy_tree(tree->right)));
            }
            if(tree->data == '/')
            {
                simul_node = node_del(node_min(node_mul(simular_difference(tree->left), copy_tree(tree->right)),
                                node_mul(copy_tree(tree->left), simular_difference(tree->right))),
                        node_mul(copy_tree(tree->right), copy_tree(tree->right)));
                node_dump_tex(tree, simul_node);
                new_node = node_del(node_min(node_mul(difference(tree->left), copy_tree(tree->right)),
                                node_mul(copy_tree(tree->left), difference(tree->right))),
                        node_mul(copy_tree(tree->right), copy_tree(tree->right)));
            }
            break;
        case P_SUM:
            if(tree->data == '+')
            {
                simul_node = node_sum(simular_difference(tree->left), simular_difference(tree->right));
                node_dump_tex(tree, simul_node);
                new_node = node_sum(difference(tree->left), difference(tree->right));
            }
            if(tree->data == '-')
            {
                simul_node = node_min(simular_difference(tree->left), simular_difference(tree->right));
                node_dump_tex(tree, simul_node);
                new_node = node_min(difference(tree->left), difference(tree->right));
            }
            break;
        default:
            perror("Plack Plak");
    }
    if(simul_node)
        node_destructor(simul_node);

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

node* node_min(node* left, node* right)
{
    node* new_node = node_constructor();
    assert(node_ok(new_node));

    new_node->type  = OPERATOR;
    new_node->data  = '-';
    new_node->prior = P_SUM;
    new_node->pos   = INFIX;
    new_node->left  = left;
    new_node->right = right;

    return new_node;
}

node* node_del(node *left, node *right)
{
    node* new_node = node_constructor();
    assert(node_ok(new_node));

    new_node->type  = OPERATOR;
    new_node->data  = '/';
    new_node->prior = P_MULT;
    new_node->pos   = INFIX;
    new_node->left  = left;
    new_node->right = right;

    return new_node;
}

node *simular_difference(node *tree)
{
    node_ok(tree);
    node* simul_node = copy_tree(tree);
    simul_node->is_simular = true;
    return simul_node;
}



char* dump_phrases(int node_data)
{
    const int PHRASES_QUANTITY = 7;
    char const* phrases[] = {"Найдём производную ",
                            "Ищем производную ",
                            "Поиск производной ",
                            "Очевидно, это производная ",
                            "Да познаешь ты путь нахождения производной ",
                            "Wolfram знает, как искать производную ",
                            "Сам попробуй в 2 часа ночи найти производную "};
    char* message = (char*) calloc(1000, sizeof(*message));
    message = strcpy(message, phrases[rand()%PHRASES_QUANTITY]);
    switch(node_data)
    {
        case '+':
            message = strcat(message, "суммы");
            break;
        case '-':
            message = strcat(message, "разности");
            break;
        case '*':
            message = strcat(message, "произведения");
            break;
        case '/':
            message = strcat(message, "частного");
            break;
        case 's':
            message = strcat(message, "синуса");
            break;
        case 'с':
            message = strcat(message, "косинуса");
            break;
        default:
            message = strcpy(message, "Да пребудет с вами матан");
    }
    return message;
}

void simplification(node **tree)
{
    node_ok(*tree);
    if((*tree)->left != NULL)
    {
        simplification(&(*tree)->left);
    }
    if((*tree)->right != NULL)
    {
        simplification(&(*tree)->right);
    }
    node* func_node = NULL;
    switch((*tree)->prior)
    {
        case P_SUM:
            if(((*tree)->left->type == NUMBER)&&((*tree)->left->data == 0))
            {
                if((*tree)->data == '+')
                {
                    func_node = copy_tree((*tree)->right);
                    node_dump_simplification((*tree), func_node);
                    fprintf(TEXT_LATEXT, "\\\\\n");
                    node_destructor((*tree));
                    *tree = func_node;
                    break;
                }
            }
            if(((*tree)->right->type == NUMBER)&&((*tree)->right->data == 0))
            {
                func_node = copy_tree((*tree)->left);
                node_dump_simplification((*tree), func_node);
                fprintf(TEXT_LATEXT, "\\\\\n");
                node_destructor((*tree));
                *tree = func_node;
                break;
            }
            if(((*tree)->right->type == NUMBER)&&((*tree)->left->type == NUMBER))
            {
                func_node = copy_tree((*tree)->left);
                if((*tree)->data == '+')
                    func_node->data += (*tree)->right->data;
                else
                    func_node->data -= (*tree)->right->data;
                node_dump_simplification((*tree), func_node);
                fprintf(TEXT_LATEXT, "\\\\\n");
                node_destructor((*tree));
                *tree = func_node;
                break;
            }
            break;
        case P_MULT:
            if(((*tree)->left->type == NUMBER)&&((*tree)->left->data == 0))
            {
                func_node = copy_tree((*tree)->left);
                node_dump_simplification((*tree), func_node);
                fprintf(TEXT_LATEXT, "\\\\\n");
                node_destructor((*tree));
                *tree = func_node;
                break;
            }
            if(((*tree)->right->type == NUMBER)&&((*tree)->right->data == 0))
            {
                if((*tree)->data == '*')
                {
                    func_node = copy_tree((*tree)->right);
                    node_dump_simplification((*tree), func_node);
                    fprintf(TEXT_LATEXT, "\\\\\n");
                    node_destructor((*tree));
                    *tree = func_node;
                    break;
                }
            }
            if(((*tree)->right->type == NUMBER)&&((*tree)->right->data == 1))
            {
                func_node = copy_tree((*tree)->left);
                node_dump_simplification((*tree), func_node);
                fprintf(TEXT_LATEXT, "\\\\\n");
                node_destructor((*tree));
                *tree = func_node;
                break;
            }
            if(((*tree)->left->type == NUMBER)&&((*tree)->left->data == 1))
            {
                if((*tree)->data == '*')
                {
                    func_node = copy_tree((*tree)->right);
                    node_dump_simplification((*tree), func_node);
                    fprintf(TEXT_LATEXT, "\\\\\n");
                    node_destructor((*tree));
                    *tree = func_node;
                    break;
                }
            }
            break;
        default:
            break;
    }
}

void node_dump_simplification(node *old_node, node *new_node)
{
    char* phrases = dump_phrases_simplification(old_node->data);
    fprintf(TEXT_LATEXT ,"%s:\\\\\n", phrases);
    free(phrases);
    fprintf(TEXT_LATEXT, "$");
    node_dump_formul(old_node);
    fprintf(TEXT_LATEXT, "$");
    fprintf(TEXT_LATEXT, " -> ");
    fprintf(TEXT_LATEXT, "$");
    node_dump_formul(new_node);
    fprintf(TEXT_LATEXT, "$");
    fprintf(TEXT_LATEXT ,"\\\\\n");
}

char *dump_phrases_simplification(int node_data)
{
    const int PHRASES_QUANTITY = 7;
    char const* phrases[] = {"Упростим выражение ",
            "Оптимизация ",
            "Выполняем операцию оптимизации для ",
            "Простыми преобразованиями находим оптимизацию ",
            "Отправь смс на номер 322223, и ты узнаешь, как преобразовать ",
            "Здесь могла бы быть ваша реклама другой ",
            "Никто не дочитает до этого места преобразования "};
    char* message = (char*) calloc(1000, sizeof(*message));
    message = strcpy(message, phrases[rand()%PHRASES_QUANTITY]);
    switch(node_data)
    {
        case '+':
            message = strcat(message, "суммы");
            break;
        case '-':
            message = strcat(message, "разности");
            break;
        case '*':
            message = strcat(message, "произведения");
            break;
        case '/':
            message = strcat(message, "частного");
            break;
        case 's':
            message = strcat(message, "синуса");
            break;
        case 'с':
            message = strcat(message, "косинуса");
            break;
        default:
            message = strcpy(message, "Да пребудет с вами матан");
    }
    return message;
}


void node_dump_program(node *tree, int *label_num)
{
    int pos = *label_num;
    if((tree->type == COMMAND)&&(tree->data == 'w'))
    {
        fprintf(PROGRAM_TEXT, "label %d\n", *label_num);
        (*label_num)++;
    }

    if(tree->left != NULL)
        node_dump_program(tree->left, label_num);
    if((tree->type == COMMAND)&&(tree->data == 'i'))
    {
        fprintf(PROGRAM_TEXT, "push 0\njae :%d\n", *label_num);
        (*label_num)++;
    }

    if((tree->type == COMMAND)&&(tree->data == 'w'))
    {
        fprintf(PROGRAM_TEXT, "push 0\njae :%d\n", *label_num);
        (*label_num)++;
    }
    if(tree->right != NULL)
        node_dump_program(tree->right, label_num);

    switch (tree->prior)
    {
        case P_NUM:
            if(tree->type == NUMBER)
            {
                fprintf(PROGRAM_TEXT, "push %d\n", tree->data);
            }
            if(tree->type == VARIABLE)
            {
                fprintf(PROGRAM_TEXT, "push_%cx\n", tree->data);
            }
            break;
        case P_MULT:
            if(tree->data == '*')
                fprintf(PROGRAM_TEXT, "mul\n");
            if(tree->data == '/')
                fprintf(PROGRAM_TEXT, "del\n");
            break;
        case P_SINUS:
            if(tree->data == 's')
                fprintf(PROGRAM_TEXT, "sin\n");
            if(tree->data == 'c')
                fprintf(PROGRAM_TEXT, "cos\n");
            break;
        case P_SUM:
            if(tree->data == '+')
                fprintf(PROGRAM_TEXT, "add\n");
            if(tree->data == '-')
                fprintf(PROGRAM_TEXT, "sub\n");
            break;
        case P_ASSIGN:
            fprintf(PROGRAM_TEXT, "pop_%cx\npop\n", tree->left->data);
            break;
        case P_PRINTF:
            fprintf(PROGRAM_TEXT, "push_%cx\nout\n", tree->data);
            break;
        case P_COMPARE:
            if(tree->data == '>')
            {
                fprintf(PROGRAM_TEXT, "sub\n");
            }
            if(tree->data == '<')
            {
                fprintf(PROGRAM_TEXT, "sub\npush -1\nmul\n");
            }
            if(tree->data == 'e')
            {
                fprintf(PROGRAM_TEXT, "sub");
            }
            break;
        case P_IF:
            if(tree->data == 'i')
            {
                fprintf(PROGRAM_TEXT, "label %d\n", pos);
            }
            break;
        case P_WHILE:
            if(tree->data == 'w')
            {
                fprintf(PROGRAM_TEXT, "jmp :%d\nlabel %d", pos, (pos+1));
            }
            break;
        default:
            break;
    }
}
