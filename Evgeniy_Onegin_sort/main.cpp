//{=================================================================================
//!         @file    main.cpp
//!         @date    2014-10-2 2:06
//!         @author  Yashukhin Artem
//!
//!         Programm for sort books
//!
//}=================================================================================
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


long getFileLength(FILE *text); //< Get length of file in bytes

void printError(); //< Print ERROR message (for debugging)

void searchAllStr(char *text, int text_size, long long int *linksArray); //< Search starts of strings in *text and write address in *linksArray

long changeSymbolOnSymbolInString(char *text, int length, char symb1, char symb2); //< return quantity of string

int compareString(const void* number1, const void* number2); //< return 1 if 1-st string bigger, -1 if 2-st string bigger and 0 if they equal

void scanInArray(FILE* file, char* memory, int size); //< Write book in dynamic array

void printConvertText(char **string, int quantityString, FILE *book); //< Print converted text in file


int main()
{

    FILE* book = fopen("book.txt", "r");
    assert(book != NULL);
    fseek (book, 0, SEEK_SET);

    int lenBook = getFileLength(book);

    //!last symbol in text can be no enter
    char* textInMemory = (char*) calloc(lenBook + 1, sizeof(*textInMemory));
    assert(lenBook + 1> 0);
    textInMemory[lenBook] = '\0';

    fseek (book, 0, SEEK_SET);

    scanInArray(book, textInMemory, lenBook);

    int quantityString = changeSymbolOnSymbolInString(textInMemory, lenBook , '\n', '\0') + 1;

    long long int* beginningOfLines = (long long int*) calloc (quantityString, sizeof(*beginningOfLines));
    assert(quantityString * sizeof(*beginningOfLines) > 0);

    searchAllStr (textInMemory, lenBook, beginningOfLines);

    qsort(beginningOfLines, quantityString, sizeof(*beginningOfLines), compareString);

    FILE* alphabetBook = fopen("book3.txt", "wr");
    assert(alphabetBook != NULL);

    printConvertText((char **) beginningOfLines, quantityString, alphabetBook);

    free(beginningOfLines);
    beginningOfLines = NULL;

    free(textInMemory);
    textInMemory = NULL;

    fclose(book);
    book = NULL;

    return 0;
}


void printConvertText(char **string, int quantityString, FILE *book) {
    for (int i = 0; i < quantityString; i++)
    {
        if(fprintf(book ,"%s\n", string[i]) == 0)
        {
            printError();
        }
    }

}


void scanInArray(FILE* file, char* memory, int size) {
    for(int i = 0; i < size; i++ )
    {
        fscanf(file, "%c", &memory[i]);

    }
}

long getFileLength(FILE *text)
{
    FILE* local_file = text;
    if (local_file)
    {
        fseek (local_file, 0, SEEK_END);
        long length = ftell(local_file);
        fseek (local_file, 0, SEEK_SET);
        return length;
    }
    printError();
    assert(0);

}

void printError()
{
    printf("FAIL %s, %s(%d)", __PRETTY_FUNCTION__, __FILE__, __LINE__);
}

void searchAllStr(char *text, int text_size, long long int *linksArray)
{
    linksArray[0] = (long long int) &text[0];
    int numberString = 0;
    for(int i = 0; i < text_size; i++)
    {
        if(text[i] == '\0')
        {

            linksArray[numberString + 1] = (long long int) &text[i+1];
            numberString++;
        }
    }


}

long changeSymbolOnSymbolInString(char *text, int length, char symb1, char symb2)
{
    long quantityChanges = 0;

    char* p = text;

    for (quantityChanges = 0 ;; quantityChanges++)
    {
        p = strchr(p, symb1);
        if(p >= &text[length-1])
        {
            return quantityChanges;
        }
        *p = symb2;
        p++;
    }

}

int compareString(const void* number1, const void* number2)
{
    char* number_1 =   *(char**)number1;
    char* number_2 =   *(char**)number2;

    int i = 0;
    for(i = 0; number_1[i] != '\0' && number_2[i] !='\0'; i++)
    {
        if (number_1[i] > number_2[i]) {
            return 1;
        }
        if (number_1[i] < number_2[i]) {
            return -1;
        }
    }
    if(number_1[i] == 0 && number_2[i] == 0)
    {
        return 0;
    }
    if(number_1[i] > number_2[i])
    {
        return 1;
    }
    if(number_1[i] < number_2[i])
    {
        return -1;
    }
}