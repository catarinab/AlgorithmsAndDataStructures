/*
 * Ficheiro:  p1.c
 * Autor: Catarina Soares da Costa Bento
 * Numero: 93230
 * Curso: LEIC-A
 * Descricao: solucao do primeiro projecto de IAED1920: implementacao de um sistema
 *                     de logística de encomendas em C
 */

#include <stdio.h>
#include <string.h>

/** Numero maximo de produtos no sistema**/
#define MAXPRODUTOS 10000
/** Numero maximo de encomendas no sistema**/
#define MAXENCOMENDAS 500
/** Numero maximo do peso de encomenda**/
#define MAXPESOENCOMENDAS 200
/** Tamanho maximo da descricao de um produto**/
#define MAXDESCRICAO 64
/** Valor retornado caso um produto nao seja encontrado numa encomenda**/
#define NAO_ENCONTRADO -1
/**ERRO e retornado se uma das condicoes nao se verificar, SUCESSO e retornado caso contrario**/
#define ERRO 0
#define SUCESSO 1
/** Flags utilizadas para definir se a ordenacao de produtos e por preco ou descricao**/
#define FLAGPRECO 1
#define FLAGDESC 0

/**______________________________________Abstracoes Sort________________________________________**/

#define keyD(A) (A.descricao)
#define keyP(A) (A.preco)
#define keyID(A) (A.idp)
#define lessP(A, B) ((keyP(A) - keyP(B)) == 0 ? keyID(A) < keyID(B) : keyP(A) < keyP(B))
#define less(A, B, C) (C == 0 ? strcmp(keyD(A), keyD(B)) < 0 : lessP(A, B))

/**______________________________________Estruturas_______________________________________________**/

/**Tipo que descreve um Produto
 * idp: identificador do produto **/
typedef struct{
    int idp;
    char descricao[MAXDESCRICAO];
    int preco;
    int peso;
    int quantidade;
} produto;

/** Estrutura que contem as informacoes essenciais de um produto numa encomenda**/
typedef struct{
    int identificador;
    int quantidade;
} produtosEncomenda;

/**Tipo que descreve uma Encomenda
 * indiceVetor: indice em que o produtosEncomenda sera inserido no vetor produtosEncomenda**/
typedef struct{
    produtosEncomenda produtosEncomenda[MAXPESOENCOMENDAS];
    int pesoTotal;
    int indiceVetor;
} encomenda;

/**______________________________________Variaveis________________________________________________**/

/** numProdutos e numEncomendas sao contadores de que definem o identificador dos Produtos e 
 * o identificador das Encomendas respetivamente**/
int numProdutos = 0, numEncomendas = 0;

/**Variaveis auxiliares ao funcionamento de todas as funcoes**/
int arg1, arg2, arg3;
int idpEncomenda;

/** Os seguintes vetores sao globais, pois usados por quase todas as funcoes do programa**/
/** Vetor de Produtos, cujo indice e o identificador de cada produto**/
produto produtos[MAXPRODUTOS];

/**Vetor de encomendas cujo indice e o identificador de cada encomenda**/
encomenda encomendas[MAXENCOMENDAS];

/**______________________________________Funcoes_________________________________________________**/

/** Funcao que troca duas posicoes (a e b) num vetor de inteiros.**/
void exch(int produtos[], int a, int b){
    int temp = produtos[a];
    produtos[a] = produtos[b];
    produtos[b] = temp;
}

/** Algoritmo de Quick Sort, que ordena um vetor de inteiros(que contem identificadores de produtos)
 * e que, dependendo da flag, compara as descricoes ou compara o preco do produtos com os IDs.
 * 
 * tab: array de inteiros que contem os IDs dos produtos que queremos ordernar
 * l: indice mais a esquerda do vetor a ser ordenado
 * r: indice mais a direita do vetor a ser ordenado
 * o pivo encontra-se no meio do vetor, pois a ordenacao assim e mais rapida
 * flag: = 0 se quiseremos ordenar por descricao e = 1 se quiseremos ordenar por preco**/
void sort(int tab[], int l, int r, int flag){
    int left = l, right = r;
    int pivot = tab[(left + right) / 2];
    if (r <= l)
        return;
    while (left <= right){
        for (; less(produtos[tab[left]], produtos[pivot], flag); left++);
        for(;less(produtos[pivot], produtos[tab[right]], flag); right--);
        if (right >= left){
            exch(tab, left, right);
            right--;
            left++;
        }
    }
    sort(tab, left, r, flag);
    sort(tab, l, right, flag);
}

/**______________________________________Produtos________________________________________________**/

/**Esta funcao adiciona um produto ao Sistema**/
void adicionarProduto(){
    scanf(" %[^:]:%d:%d:%d", produtos[numProdutos].descricao, &produtos[numProdutos].preco,
                &produtos[numProdutos].peso, &produtos[numProdutos].quantidade);
    produtos[numProdutos].idp = numProdutos;
    printf("Novo produto %d.\n", numProdutos++);
}

/**Esta funcao adiciona stock a um produto do Sistema
 * idp: identificador do produto
 * qtd: quantidade a ser adicionada do stock do produto**/
void adicionarStock(int idp, int qtd){
    if (idp < numProdutos){
        produtos[idp].quantidade += qtd;
    }
    else{
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", arg1);
    }
}

/**Esta funcao remove stock a um produto do Sistema
 * idp: identificador do produto
 * qtd: quantidade a ser removida do stock do produto**/
void removerStock(int idp, int qtd){
    if (idp >= numProdutos){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", arg1);
    }
    else if (qtd > produtos[idp].quantidade){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", arg2, arg1);
    }
    else{
        produtos[idp].quantidade -= qtd;
    }
}

/**Esta funcao muda o preco de um produto do Sistema **/
void alterarPreco(){
    scanf(" %d:%d", &arg1, &arg2);
    if (arg1 >= numProdutos){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", arg1);
    }
    else{
        produtos[arg1].preco = arg2;
    }
}

/**Funcao que lista os produtos ja ordenados
 * recebe um vetor de inteiros que contem o identificador de cada produto ordenado**/
void listarProdutos(int produtosSorted[]){
    int i;
    printf("Produtos\n");
    for(i = 0; i < numProdutos; i++){
        printf("* %s %d %d\n", produtos[produtosSorted[i]].descricao, produtos[produtosSorted[i]].preco,
               produtos[produtosSorted[i]].quantidade);
    }
}

/**Funcao que poe os IDs de cada produto num vetor e chama a funcao que da sort ao vetor e tambem
 * a que lista os produtos.
 * O vetor produtosSorted mantem os IDs dos produtos depois da funcao retornar, de forma a que na 
 * proxima ordenacao o vetor esteja ordenado ate certo indice.
 * So sao colocados IDs no vetor que ja nao tenham sido colocados antes
 * retorna o proximo valor de indiceProdutoSort**/
int ordenarProdutos(int produtosSorted[], int indiceProdutoSort){
    int i;
    for (i = indiceProdutoSort; i < numProdutos; i++){
        produtosSorted[i] = i;
    }
    sort(produtosSorted, 0, numProdutos - 1, FLAGPRECO);
    listarProdutos(produtosSorted);
    return numProdutos;
}

int listarKProdutos(){
    int i;
    int produtosSorted[MAXPRODUTOS];
    for (i = 0; i < numProdutos; i++){
        produtosSorted[i] = i;
    }
    listarProdutos(produtosSorted);
    return numProdutos;
}

/**______________________________________Encomendas____________________________________________**/

/**Esta funcao adiciona uma Encomenda ao Sistema**/
void adicionarEncomenda(){
    printf("Nova encomenda %d.\n", numEncomendas++);
}

/**Esta funcao procura o indice em que o produtosEncomenda com o identificador = idp se encontra
 * no vetor produtosEncomenda da encomenda com identificador de valor ide.
 * Se encontrar o idp, retorna o indice em que ele se encontra
 * Se nao encontrar o produtosEncomenda, retorna NAO_ENCONTRADO
*/
int encontrarprodutosEncomenda(int ide, int idp){
    int i;
    for (i = 0; i < encomendas[ide].indiceVetor; i++){
        if (idp == encomendas[ide].produtosEncomenda[i].identificador)
            return i;
    }
    return NAO_ENCONTRADO;
}

/** Esta funcao verifica as condicoes necessarias para adicionar um produto com identificador = idp
 * com quantidade = qtd, a encomenda com identificador = ide
 * se nao se verificar uma das condicoes retorna ERRO
 * se se verificarem todas as condicoes, retorna o novo peso da encomenda**/
int verificaAdicaoEncomenda(int ide, int idp, int qtd){
    int peso;
    if (ide >= numEncomendas){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", idp, ide);
        return ERRO;
    }
    if (idp >= numProdutos){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", idp, ide);
        return ERRO;
    }
    if (qtd > produtos[idp].quantidade){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",
               idp, ide);
        return ERRO;
    }
    peso = encomendas[arg1].pesoTotal + arg3 * produtos[arg2].peso;
    if (peso > MAXPESOENCOMENDAS){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",
               arg2, arg1);
        return ERRO;
    }
    return peso;
}

/**Esta funcao adiciona um produto a uma Encomenda
 * Apenas adiciona um produto caso todas as condicoes necessarias se verifiquem
 * A funcao encontra o indice do vetor do produto no produtosEncomenda e altera as 
 * informacoes desse. Caso o produto nao se encontre na encomenda, atribui-lhe um indice no vetor
 * Retira tambem o stock ao produto e altera o peso da encomenda**/
void adicionarprodutosEncomenda(){
    /**Variavel local em que e armazenado o novo peso da encomenda caso o produto seja adicionado**/
    int peso;
    scanf(" %d:%d:%d", &arg1, &arg2, &arg3);
    if((peso = verificaAdicaoEncomenda(arg1, arg2, arg3)) != ERRO){
        if ((idpEncomenda = encontrarprodutosEncomenda(arg1, arg2)) == NAO_ENCONTRADO){
            idpEncomenda = encomendas[arg1].indiceVetor;
            encomendas[arg1].indiceVetor++;
        }
            removerStock(arg2, arg3);
            encomendas[arg1].pesoTotal = peso;
            encomendas[arg1].produtosEncomenda[idpEncomenda].quantidade += arg3;
            encomendas[arg1].produtosEncomenda[idpEncomenda].identificador = arg2;
    }
}

/** Esta funcao verifica as condicoes necessarias para remover um produto com identificador = idp
 * a encomenda com identificador = ide
 * se nao se verificar uma das condicoes retorna ERRO
 * se se verificarem todas as condicoes, retorna SUCESSO**/
int verificaRemocaoEncomenda(int ide, int idp){
    if (ide >= numEncomendas){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", arg2, arg1);
        return ERRO;
    }
    else if (idp >= numProdutos){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", arg2, arg1);
        return ERRO;
    }
    return SUCESSO;
}

/**Esta funcao remove um produto a uma Encomenda
 * Apenas remove o produto caso todas as condicoes necessarias se verifiquem
 * A funcao encontra o indice do vetor do produtosEncomenda e altera as informacoes desse
 * adiciona tambem o stock ao produto e diminui o peso da encomenda
 * Se o produto nao se encontrar na encomenda, nao faz nada
 * Modifica o vetor tambem o vetor dos produtos de modo a nao ficar um indice vazio**/
void removerprodutosEncomenda(int arg1, int arg2){
    /** Variavel local em que e armazenada a quantidade do produto na encomenda**/
    int quantidade;
    if(verificaRemocaoEncomenda(arg1, arg2)){
        idpEncomenda = encontrarprodutosEncomenda(arg1, arg2); 
        quantidade = encomendas[arg1].produtosEncomenda[idpEncomenda].quantidade;
        if (idpEncomenda != NAO_ENCONTRADO){
            adicionarStock(arg2, quantidade);

            encomendas[arg1].pesoTotal -= quantidade * produtos[arg2].peso;
            encomendas[arg1].produtosEncomenda[idpEncomenda] = encomendas[arg1].produtosEncomenda[--encomendas[arg1].indiceVetor];
            encomendas[arg1].produtosEncomenda[encomendas[arg1].indiceVetor].quantidade = 0;
        }
    }
}

/**Esta funcao calcula o preco de uma Encomenda no sistema caso ela exista**/
void custoEncomenda(){
    /**Custo: Variavel local em que e armazenado o custo da encomenda**/
    int i, custo;
    scanf(" %d", &arg1);
    if (arg1 >= numEncomendas){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", arg1);
    }
    else{
        for (i = 0, custo = 0; i <= numProdutos; i++){
            idpEncomenda = encontrarprodutosEncomenda(arg1, i);
            if(idpEncomenda != NAO_ENCONTRADO){
                custo += encomendas[arg1].produtosEncomenda[idpEncomenda].quantidade * produtos[i].preco;
            }
        }
        printf("Custo da encomenda %d %d.\n", arg1, custo);
    }
}

/**Esta funcao lista a descrição e a quantidade de um produto numa encomenda caso se 
 * verifiquem todas as condicoes necessarias.
 * Se o produto nao se encontrar na encomenda, a quantidade impressa e 0**/
void listarprodutosEncomenda(){
    /** Variavel local em que armazenada a quantidade do produto na encomenda, ou 0 caso o produto 
     * nao se encontre na encomenda**/
    int quantidade;
    scanf(" %d:%d", &arg1, &arg2);
    idpEncomenda = encontrarprodutosEncomenda(arg1, arg2);
    if (arg2 >= numProdutos){
        printf("Impossivel listar produto %d. Produto inexistente.\n", arg2);
    }
    else if (arg1 >= numEncomendas){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", arg1);
    }
    else{
        if(idpEncomenda == NAO_ENCONTRADO)
            quantidade = 0;
        else
            quantidade = encomendas[arg1].produtosEncomenda[idpEncomenda].quantidade;
        printf("%s %d.\n", produtos[arg2].descricao, quantidade);
    }
}

/** Esta funcao lista o identificador da encomenda em que o produto dado ocorre mais vezes.
 * Nao lista nada caso o produto nao esteja em nenhuma encomenda 
 * e/ou nao exisitirem encomendas.**/
void maxprodutosEncomenda(){
    /**encomendaM: identificador da encomenda em que o produto ocorre mais vezes
     * maxOcorrencias: a quantidade do produto nessa dada encomenda**/
    int encomendaM, idp, maxOcorrencias, i;
    scanf(" %d", &arg1);
    if (arg1 >= numProdutos){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", arg1);
    }
    else{
        encomendaM = -1, maxOcorrencias = 0;
        for (i = 0; i < numEncomendas; i++){
            idp = encontrarprodutosEncomenda(i, arg1);
            if (encomendas[i].produtosEncomenda[idp].quantidade > maxOcorrencias && idp != NAO_ENCONTRADO){
                encomendaM = i;
                maxOcorrencias = encomendas[i].produtosEncomenda[idp].quantidade;
            }    
        }
        if (encomendaM != NAO_ENCONTRADO)
            printf("Maximo produto %d %d %d.\n", arg1, encomendaM, maxOcorrencias);
    }
}

 /** Esta funcao lista os produtos de uma encomenda ja devidamente ordenados**/
void listarProdutosEncomendas(int produtosSorted[], int len, int ide){
    /** IDProduto: identificador de cada produto a ser listado
     * quantidade: quantidade de cada produto na encomenda**/
    int i, quantidade, IDProduto;
    for (i = 0; i < len; i++){
        IDProduto = produtosSorted[i];
        idpEncomenda = encontrarprodutosEncomenda(ide, IDProduto);
        if ((quantidade = encomendas[ide].produtosEncomenda[idpEncomenda].quantidade) != 0)
            printf("* %s %d %d\n", produtos[IDProduto].descricao, produtos[IDProduto].preco, quantidade);
    }
}

/**Esta funcao poe os Identificadores dos produtos da encomenda num vetor para ser ordenado, 
 * caso as condicoes necessarias (a encomenda existir) se cumpram.
 * De seguida, chama a funcao que o ordena e a funcao que imprime o valor dos produtos**/
void ordenarProdutosEncomendas(){
    /**indiceVetor: tamanho do vetor de produtosEncomenda**/
    int i, indiceVetor;
    int produtosSortedEncomenda[MAXPESOENCOMENDAS];
    scanf(" %d", &arg1);
    indiceVetor = encomendas[arg1].indiceVetor;

    if(arg1 >= numEncomendas)
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", arg1);
    else{
        for (i = 0; i < indiceVetor; i++){
            produtosSortedEncomenda[i] = encomendas[arg1].produtosEncomenda[i].identificador;
        }
        sort(produtosSortedEncomenda, 0, indiceVetor - 1, 0);
        printf("Encomenda %d\n", arg1);
        listarProdutosEncomendas(produtosSortedEncomenda, indiceVetor, arg1);
    }
}



/**A funcao main le o comando dado no input e chama a funcao correta em funcao disso.
 * indiceProdutoSort: o primeiro indice utilizado na proxima vez que os produtos forem ordenados
 * produtosSorted: vetor que contem todos os produtos do sistema (na altura da ordenacao)
 *                              ordenados por preco e id**/
int main(){
    char c;
    int indiceProdutoSort = 0, produtosSorted[MAXPRODUTOS];
    while ((c = getchar()) != 'x'){
        switch (c){
        case 'a':
            adicionarProduto();
            break;
        case 'q':
            scanf(" %d:%d", &arg1, &arg2);
            adicionarStock(arg1, arg2);
            break;
        case 'k':
            listarKProdutos();
            break;
        case 'N':
            adicionarEncomenda();
            break;
        case 'A':
            adicionarprodutosEncomenda();
            break;
        case 'r':
            scanf(" %d:%d", &arg1, &arg2);
            removerStock(arg1, arg2);
            break;
        case 'R':
            scanf(" %d:%d", &arg1, &arg2);
            removerprodutosEncomenda(arg1, arg2);
            break;
        case 'C':
            custoEncomenda();
            break;
        case 'p':
            alterarPreco();
            break;
        case 'E':
            listarprodutosEncomenda();
            break;
        case 'm':
            maxprodutosEncomenda();
            break;
        case 'l':
            indiceProdutoSort = ordenarProdutos(produtosSorted, indiceProdutoSort);
            break;
        case 'L':
            ordenarProdutosEncomendas();
            break;
        }
    }
    return 0;
}