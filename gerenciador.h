/***
 * Sistema de Gerenciamento de Pedidos de um Restaurante
 */

#ifndef __GERENCIADOR_H__
#define __GERENCIADOR_H__

//bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// estrutura de lista
struct est_lista
{
    int numero;
    char cliente[50];
    char itens[100];
    char status[20];
    struct est_lista *prox;
};
typedef struct est_lista lista_espera;
// estrutura de fila 
struct est_fila
{
    struct est_lista *pedido;
    struct est_fila *prox;
};
typedef struct est_fila fila_preparo;
// estrutura de pilha
struct est_pilha
{
    struct est_lista *pedido;
    struct est_pilha *prox;
};
typedef struct est_pilha pilha_entrega;


//metodos de alocacao 
lista_espera* aloca_lista(int,char[50],char[100]);
fila_preparo* aloca_fila(lista_espera**);
pilha_entrega* aloca_pilha(lista_espera**);

//metodo de edicao
void criar_pedido(lista_espera**,int,char[50],char[100]);
void pedido_preparo(fila_preparo**,lista_espera**);
void pedido_pronto(pilha_entrega**,fila_preparo**);
void pedido_entregue(pilha_entrega**);




#endif //__GERENCIADOR_H__