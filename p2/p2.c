/*
 * Ficheiro:  p2.c
 * Autor: Catarina Soares da Costa Bento
 * Numero: 93230
 * Curso: LEIC-A
 * Descricao: solucao do segundo projecto de IAED1920: implementacao de um sistema
 *                     de logística de jogos em C.
 */


/*****************************************************************************************************
 * Bibliotecas e Ficheiros 
*****************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"

/*
*  A funcao main cria e inicializa as hashtables e Lista de Equipas, de seguida le os comandos dados 
* e chama as funcoes de interface das HashTables e da lista. No final da free a toda a memoria
* alocada ainda nao libertada.
*/
int main(){
    /* Variavel local onde e armazenado o caracter que indica o comando a ser executado*/
    char caracter;
    /*capacidadeJ: tamanho total do array da HashTable de Encademento Externo dos Jogos
       capacidadeE: tamanho total do array da HashTable de Encademento Externo das Equipas
       linha: variavel local que indica a linha em que o programa se encontra*/
    int capacidadeJ =  CAPACIDADEJ, capacidadeE = CAPACIDADEE, linha = 1;
    /**********************************Variaveis de Jogos*********************************************/

    /* headsJogo: variavel local que armazena as heads da HT de Encademento Externo dos Jogos*/
    ItemFirstHT ** headsJogo = (linkJogo **)malloc(capacidadeJ * sizeof(linkJogo));

    /* listaJogo: variavel local que armazena o ponteiros para o primeiro e ultimo elemento da lista
                            de Jogos*/
    lista * listaJogo = malloc(sizeof(lista));

    /* headsEquipa: variavel local que armazena as heads da HT de Encademento Externo das Equipas*/
    ItemSecondHT  ** headsEquipa = (linkEquipa **) malloc(capacidadeE * sizeof(linkEquipa));
    inicializarHT(headsJogo, listaJogo, headsEquipa, capacidadeJ, capacidadeE);
    while ((caracter = getchar()) != 'x'){
        switch (caracter){
            case 'a':
                adicionarJogo(headsJogo, listaJogo, headsEquipa, capacidadeE, capacidadeJ, linha);
                break;
            case 'l':
                listarJogos(listaJogo, linha);
                break;
            case 'p':
                encontrarJogo(capacidadeJ, headsJogo, linha);
                break;
            case 'r':
                removerJogo(headsJogo, capacidadeJ, listaJogo, linha);
                break;
            case 's':
                alterarPontuacao(capacidadeJ, headsJogo, linha);
                break;
            case 'A':
                adicionarEquipa(headsEquipa, capacidadeE, linha);
                break;
            case 'P':
                procurarEquipa(headsEquipa, capacidadeE, linha);
                break;
            case 'g':
                procurarMelhoresEquipas(headsEquipa, capacidadeE, linha);
                break;
            default:
                linha++;
        }
    }
    freeAll(headsJogo, headsEquipa, listaJogo, capacidadeE, capacidadeJ);
    return 0;
}