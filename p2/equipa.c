/*
 * Ficheiro:  equipa.c
 * Autor: Catarina Soares da Costa Bento
 * Numero: 93230
 * Curso: LEIC-A
 * Descricao: este ficheiro contem as funcoes especificas a manipulacao da Hashtable das Equipas.
 */

/*****************************************************************************************************
 * Bibliotecas e Ficheiros 
*****************************************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "equipa.h"
#include "interface.h"

/*A funcao InitSecondHT inicializa a hashTable de Equipas
* headsEquipa: variavel que armazena as heads da HashTable de Equipas
* capacidadeE: tamanho total do array da HashTable de Encademento Externo das Equipas
*/
void InitSecondHT(ItemSecondHT ** headsEquipa, int capacidadeE){
    int i;
    for (i = 0; i < capacidadeE; i++)
        headsEquipa[i] = NULL;
}

/* 
* A funcao inserirInicioListaE insere um novo item na lista ligada cuja head e um ponteiro,
* que e uma lista pertencente ao encadeamento externo da HashTable de Equipas.
* head:ponteiro para posicao no array da HT da lista de encadeamento externo a que o item pertence.
* nome: nome do item.
* retorna a nova head da lista de encadeamento externo a que o item pertence.
*/
ItemSecondHT * inserirInicioListaE(ItemSecondHT * head, char * nome){
    ItemSecondHT *temporario = malloc(sizeof(ItemSecondHT));
    elementHT(temporario) = malloc(sizeof(equipa));
    keyHT(temporario) = (char *)malloc(sizeof(char) * (strlen(nome) + 1));
    strcpy(keyHT(temporario), nome);
    descHT(temporario) = 0;
    temporario->next = head;
    return temporario;
}

/* 
* A funcao HTprocurarEquipa procura uma equipa de nome key na HashTable de equipas e 
* retorna o link da HashTable com essa equipa caso ela exista. Se nao existir, retorna nulo.
* head:ponteiro para posicao no array da HT da lista de encadeamento externo a que o item pertence.
* key: nome do item.
*/
linkEquipa * procuraElemento(ItemSecondHT * head, char * key){
    while(head != NULL){
        if(strcmp(keyHT(head), key) == 0){
            return head;
        }
        head = head->next;
    }
    return NULL;
}

/* 
* Esta funcao procura uma equipa na HashTable de equipas. Caso a equipa exista, retorna a equipa.
* Se a equipa nao existir, retorna nulo.
* nome: nome do item.
* headsEquipa: variavel que armazena as heads da HT de Encademento Externo das Equipas
* capacidadeE: tamanho total do array da HashTable de Encademento Externo das Equipas
*/
equipa * HTProcurarElementoS(char * nome, ItemSecondHT ** headsEquipa, int capacidadeE){
    linkEquipa * elemento;
    int i;
    i = hash(nome, capacidadeE);
    elemento = procuraElemento(headsEquipa[i], nome);
    if(elemento == NULL) return NULL;
    return elementHT(elemento);
}

/* 
* A funcao compararEquipas compara equipas que pela ordem lexicografica. E a funcao chamada 
* na ordenacao das equipas com mais vitorias.
* recebe duas equipas.
*/
int compararElemento(const void *a, const void *b) {
	equipa ** e1, **e2;
	e1 = (equipa **) a;
    e2 = (equipa **) b;
	return strcmp((*e1)->nome, (*e2)->nome);
}

/* 
* A funcao imprimirEquipas ordena as equipas com mais vitorias por ordem lexicografica e imprime
* as proprias equipas.
* arrayV: array com ponteiros para as equipas com o maximo de vitorias
* elementos: variavel que armazena a quantidade de elementos no arrayV
* linha: variavel que armazena a linha do input que originou este comando.
*/
void imprimirEquipas(equipa **arrayV, int elementos, int linha){
    int i;
    qsort(arrayV, elementos, sizeof(equipa *), compararElemento);
    for (i = 0; i < elementos; i++){
        printf("%d * %s\n", linha, arrayV[i]->nome);
    }
    free(arrayV);
}

/* 
* A funcao HTEncontraEquipasVencedoras encontra as equipas com mais vitorias de todas as 
* equipas e chama a funcao que as ordena por ordem lexicografica e as imprime.
* headsEquipa: variavel que armazena as heads da HT de Encademento Externo das Equipas
* capacidadeE: tamanho total do array da HashTable de Encademento Externo das Equipas
* linha: variavel que armazena a linha do input que originou este comando.
*/
void HTencontraEquipasVencedoras(ItemSecondHT **headsEquipa, int capacidadeE, int linha){
    int max = 0, elementos = 0, i;
    linkEquipa * tempHead;
    equipa **arrayV = NULL, ** temporario;
    for(i = 0; i < capacidadeE; i++){
        tempHead = headsEquipa[i];
        while (headsEquipa[i] != NULL){
            /* Ou seja, encontramos um novo maximo de vitorias e damos reset ao vetor*/
            if(descHT(headsEquipa[i]) > max){
                elementos = 0;
                temporario = arrayV;
                free(temporario);
                arrayV = NULL;
                max = descHT(headsEquipa[i]);
            }
            /*Se tiver o max de vitorias entao sera adicionado ao vetor*/
            if (descHT(headsEquipa[i]) == max){
                elementos++;
                arrayV = (equipa **)realloc(arrayV, sizeof(equipa *) * elementos);
                arrayV[elementos-1] = elementHT(headsEquipa[i]);
            }
            headsEquipa[i] = headsEquipa[i]->next;
        }
        headsEquipa[i] = tempHead;
    }
    if(elementos>0){
        printf("%d Melhores %d\n", linha, max);
        imprimirEquipas(arrayV, elementos, linha);
    }
}

/* 
* Esta funcao verifica se ja existe um elemento com nome "nome", e se nao existir adiciona um 
* elemento com esse nome. Se ja existir, retorna FALSE, se conseguir adicionar a equipa retorna 
* TRUE.
* nome: nome do item
* headsEquipa: variavel que armazena as heads da HT de Encademento Externo das Equipas
* capacidadeE: tamanho total do array da HashTable de Encademento Externo das Equipas
*/
int HTInserirElementoS(char * nome, ItemSecondHT ** headsEquipa, int capacidadeE){
    int i;
    if (HTProcurarElementoS(nome, headsEquipa, capacidadeE) != NULL) return FALSE;
    i = hash(nome, capacidadeE);
    headsEquipa[i] = inserirInicioListaE(headsEquipa[i], nome);
    return TRUE;
}


/* A funcao freeEquipa da free aos elementos da equipa recebida e da propria equipa*/
void freeEquipa(equipa * e){
    free(e->nome);
    free(e);
}

/* 
* A funcao freeAllEquipa da free aos elementos da HashTable de equipas e das proprias equipas
* nessa HashTable.
* headsEquipa: variavel que armazena as heads da HT de Encademento Externo das Equipas
* capacidadeE: tamanho total do array da HashTable de Encademento Externo das Equipas
*/
void freeAllEquipa(ItemSecondHT **headsEquipa, int capacidadeE){
    linkEquipa *temp;
    int i;
    for(i= 0; i < capacidadeE; i++){
        while (headsEquipa[i]!= NULL){
            temp = headsEquipa[i];
            freeEquipa(elementHT(temp));
            headsEquipa[i] = headsEquipa[i]->next;
            free(temp);
        }
    }
    free(headsEquipa);
}