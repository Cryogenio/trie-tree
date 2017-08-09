#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
#include <conio.h>
#include "trieTree.h"

enum MENU
{
    EXIBIR = 1,
    INSERIR,
    EXCLUIR,
    BUSCAR,
    AUTOCOMPLEMENTO,
    SAIR
};

int main()
{
    ///https://stackoverflow.com/questions/33267465/printing-out-a-trie-in-c
    char word[TAM_VETOR];
    int opcao=1, i;
    FILE *arq = fopen("bancoDados.txt", "a+");

    if(!arq)
    {
        printf("Erro ao abrir o arquivo");
        return 0;
    }

    td_trieNode *tree = CreateTrieNode();

    while( (fscanf(arq, "%s", word)) != EOF )
        InsertNewWord(tree, word);

    while(opcao != SAIR)
    {
        menu();
        scanf("%d", &opcao);

        switch(opcao)
        {
        case EXIBIR:
            system("cls");
            printf("Banco de Dados Completo:\n");
            PrintAllTree(tree, word, 0);
            system("pause");
            system("cls");
            break;

        case INSERIR:
            system("cls");
            printf("Insira a palavra:");
            getchar();
            gets(word);
            InsertNewWord(tree, word);
            fprintf(arq, "\n%s", word);
            printf("Palavra inserida no banco de dados com sucesso...\n");
            system("pause");
            system("cls");
            break;

        case EXCLUIR:
            system("cls");
            printf("Entre com a palavra que deseja excluir: ");
            getchar();
            gets(word);
            if( verifyRemotion(tree, word, arq) )
                printf("Palavra removida do banco de dados com sucesso...\n");
            else
                printf("Palavra nao encontrada ou nao existente...\n");
            system("pause");
            system("cls");
            break;

        case BUSCAR:
            system("cls");
            printf("Entre com a palavra que deseja buscar: ");
            getchar();
            gets(word);
            if( SearchWord(tree, word) )
                printf("A palavra foi encontrada na arvore...\n");
            else
                printf("A palavra nao foi encontrada na arvore...\n");
            system("pause");
            system("cls");
            break;

        case AUTOCOMPLEMENTO:
            getchar();
            system("cls");
            printf("OBS: Pressione ESC para retornar ao menu\n");
            system("pause");
            system("cls");

            char aux = 13;
            i = 0;
            while( aux != 47 )
            {
                printf("Entre com a palava que deseja buscar autocomplementos:\n");
                aux = getch();

                if(aux == ESC)
                    break;

                word[i++] = aux;
                if(aux == BACKSPACE)
                {
                    word[i] = '\0';
                    if(i >= 2)
                        i-= 2;
                    else
                        i--;
                }

                word[i] = '\0';
                system("cls");
                printf("%s\n", word);
                if(i > 0)
                    findWordWith(tree, word);
            }
            system("cls");
            break;

        case SAIR:
            break;
        }
    }
    fclose(arq);
    return 0;
}
