#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
#include "trieTree.h"

int GetIndex(char value)
{
    return ((int)value - (int)'a');
}

int GetChar(int index)
{
    return (index + (int)'a');
}

int removeFromDatabase(FILE *arq, char* word)
{
    FILE *tempArq = fopen("Temp.txt", "w+");
    char auxWord[TAM_VETOR];
    fseek (arq, 0, SEEK_SET);

    while( (fscanf(arq, "%s", auxWord)) != EOF )
    {
        if( strcmp(word, auxWord) )
            fprintf(tempArq, "%s\n", auxWord);
    }

    fclose(tempArq);
    fclose(arq);
    remove("bancoDados.txt");
    rename("Temp.txt", "bancoDados.txt");
    arq = fopen("bancoDados.txt", "a+");
    return 1;
}

td_trieNode* CreateTrieNode()
{
    td_trieNode *node = (td_trieNode*) calloc (1, sizeof(td_trieNode));
    if(!node)
        return NULL;
    int i;
    for(i=0; i<ALPHABET_SIZE; i++)
        node->children[i] = NULL;

    node->finalWord = false;
    return node;
}

void InsertNewWord (td_trieNode *tree, char *word)
{
    int i, atualIndex;
    td_trieNode *node = tree;
    for(i=0; word[i]!='\0'; i++)
    {
        atualIndex = GetIndex(word[i]);
        if( !node->children[atualIndex] )
        {
            node->children[atualIndex] = CreateTrieNode();
            node->children[atualIndex]->parent = node;
        }

        node = node->children[atualIndex];
    }
    node->finalWord = true;
}

int SearchWord (td_trieNode *tree, char *word)
{
    int i, atualIndex;

    for(i=0; word[i]!='\0'; i++)
    {
        atualIndex = GetIndex(word[i]);
        if( tree->children[atualIndex] )
            tree = tree->children[atualIndex];
        else
            return 0;
    }
    if(tree->finalWord)
        return 1;

    return 0;
}

void PrintAllTree (td_trieNode *node, char *word, int atualPos)
{
    int i;
    if(!node)
        return;

    for(i=0; i<ALPHABET_SIZE; i++)
    {
        if( node->children[i] )
        {
            word[atualPos] = GetChar(i);
            PrintAllTree( node->children[i], word, atualPos+1);
        }
    }

    if(node->finalWord)
    {
        word[atualPos] = '\0';
        printf("%s\n", word);
    }
}

void findWordWith (td_trieNode *node, char *find)
{
    int i=0, fixedIndex;
    char word[TAM_VETOR];
    for(i=0; find[i] != '\0'; i++)
    {
        fixedIndex = GetIndex(find[i]);
        if( !node->children[fixedIndex] )
            return;
        node = node->children[fixedIndex];
    }
    PrintAllTree(node, word, 0);
}

int allNodeIsClear (td_trieNode *node)
{
    int i;
    for(i=0; i<ALPHABET_SIZE; i++)
        if( node->children[i] )
            return 0;
    return 1;
}

int removeWord (td_trieNode *node, char *word, int atualPos, int lengthWord)
{
    if( node )
    {
        if( atualPos == lengthWord )
        {
            if( node->finalWord )
            {
                node->finalWord = false;
                if( allNodeIsClear(node) )
                    return 1;
            }
        }
        else
        {
            int atualIndex = GetIndex(word[atualPos]);
            if( removeWord(node->children[atualIndex], word, atualPos+1, lengthWord) )
            {
                free(node->children[atualIndex]);
                return ( !node->finalWord && allNodeIsClear(node));
            }
        }
    }
    return 0;
}

int verifyRemotion (td_trieNode *node, char *word, FILE *arq)
{
    if(SearchWord(node, word))
    {
        removeWord(node, word, 0, strlen(word));
        removeFromDatabase(arq, word);
        if( !SearchWord(node, word) )
            return 1;
    }
    return 0;
}

void menu()
{
    printf("========== MENU ==========\n");
    printf("[1]. Exibir\n");
    printf("[2]. Inserir\n");
    printf("[3]. Excluir\n");
    printf("[4]. Buscar\n");
    printf("[5]. Autocomplemento\n");
    printf("[6]. Sair\n");
    printf("Opcao: ");
}

