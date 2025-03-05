#include "gerenciador.h"


//metodo de alocacao do no de uma lista
lista_espera* aloca_lista(int num,char cliente[50] ,char itens[100]){
    //criando espaco na memoria
    lista_espera* novo_no = (lista_espera*) malloc(sizeof(lista_espera));

    // colocando atribudos
    novo_no->prox = NULL;
    novo_no->numero = num;
    strcpy(novo_no->cliente, cliente);
    strcpy(novo_no->itens, itens);
    strcpy(novo_no->status,"pendente");
    return novo_no;
}

//metodo de alocacao de no de uma fila
fila_preparo* aloca_fila(lista_espera** lista_es){
    //criando espaco na memoria 
    fila_preparo* novo_no = (fila_preparo*)malloc(sizeof(fila_preparo));
    //colocando os atribudos
    novo_no->pedido = (*lista_es);
    novo_no->prox = NULL;
    return novo_no;
}
// metodo de alocacao de no de um pilha
pilha_entrega* aloca_pilha(lista_espera** lista_es){
    //criando espaco na memoria
    pilha_entrega* novo_no = (pilha_entrega*)malloc(sizeof(pilha_entrega));
    //colocando os atributos
    novo_no->pedido = (*lista_es);
    novo_no->prox = NULL;
    return novo_no;
}

//metodo de criacao do pedido de restaurante
void criar_pedido(lista_espera** lista_es,int num,char cliente[50],char itens[100]){
    //verificando c a lista esta vazia
    if ((*lista_es)==NULL)
    {
        (*lista_es) = aloca_lista(num,cliente,itens);
    }else{
        //gerenciando com um aux (para n perder o ponto inicial)
        lista_espera *aux=(*lista_es);
        //enquanto o no atual nao for o ultimo, percorremos para o proximo(verificando se o atribudo aux->prox == NULL)
        while (aux->prox != NULL)
        {
            aux = aux->prox;
        }
        //criando pedido
        aux->prox = aloca_lista(num,cliente,itens);
    }
}
//metodo de atualizacao do status do pedido
void pedido_preparo(fila_preparo**fila_p,lista_espera**lista_es){
    //verificando c a lista de pedidos esta vazia
    if ((*lista_es)== NULL)
    {
        printf("ha nenhum pedido em espera\n");
    }else{
        //criando variavel auxiliar
        lista_espera*aux_lista = (*lista_es);

        //verificando status do pedido (so ira para preparo se estiver pendente)
        while (strcmp(aux_lista->status, "pendente")!= 0)
        {
            aux_lista = aux_lista->prox;
            if (aux_lista == NULL)
            {
                printf("todos os pedidos ja estao em preparo\n");
                return;
            }
        }
        // verificando c a fila esta vazia
        if ((*fila_p)==NULL)
        {
            (*fila_p) = aloca_fila(&aux_lista);
            strcpy(aux_lista->status,"em preparo");
        }else{
            //outra variavel de auxilio 
            fila_preparo *aux_fila = (*fila_p);
            //percorrendo para o ultimo no 
            while (aux_fila->prox != NULL)
            {
                aux_fila = aux_fila->prox;
            }
            //armazenando pedido para preparo
            strcpy(aux_lista->status,"em preparo");
            //alocando novo no
            aux_fila->prox = aloca_fila(&aux_lista);
        }
        printf("pedido numero [%d] de [%s] %s!!\n",aux_lista->numero,aux_lista->cliente,aux_lista->status);
    }
}
//metodo para atualizar pedido como "pronto"
void pedido_pronto(pilha_entrega**pilha_en,fila_preparo**fila_p){
    //verificando c a fila esta vazia
    if ((*fila_p)==NULL)
    {
        printf("Ha nenhum pedido em preparo\n");
    }else{
        //variavel auxiliar
        fila_preparo* aux_fila = (*fila_p);
        //alocar pilha c a mesma estiver vazia
        if ((*pilha_en) == NULL)
        {
            //alocamos a pilha, atualizamos a fila e os status do pedido
            (*pilha_en) = aloca_pilha(&aux_fila->pedido);
            strcpy(aux_fila->pedido->status,"pronto");
            (*fila_p) = (*fila_p)->prox;
        }else{
            //ponteiro auxiliar
            pilha_entrega* aux_pilha = (*pilha_en);
            //percorremos ate o final da pilha para alocarmos um novo no
            while (aux_pilha->prox != NULL)
            {
                aux_pilha = aux_pilha->prox;
            }
            //processo de alocacao e atualizacao dos pedidos
            aux_pilha->prox = aloca_pilha(&aux_fila->pedido);
            strcpy(aux_fila->pedido->status,"pronto");
            (*fila_p) = (*fila_p)->prox;
        }   
        //print como aviso 
        printf("pedido numero [%d] de [%s] %s!!\n",aux_fila->pedido->numero,aux_fila->pedido->cliente,aux_fila->pedido->status);
        //como atualizamos a fila para o prox, o primeiro sai(processo de fila = numa fila o primeiro entra, o primeiro sai)
        free(aux_fila); 
    }
}

void pedido_entregue(pilha_entrega** pilha_en){
    if ((*pilha_en)==NULL)
    {
        printf("nao ha nenhum pedido pronto\n");
        return;
    }
    pilha_entrega* aux_pilha1 = NULL;
    pilha_entrega* aux_pilha2 = (*pilha_en); 

    while (aux_pilha2->prox != NULL)
    {
        aux_pilha1 = aux_pilha2;
        aux_pilha2 = aux_pilha2->prox;
    }
    
    strcpy(aux_pilha2->pedido->status,"entregue");
    if (aux_pilha1==NULL)
    {
        (*pilha_en) = NULL;
        free(aux_pilha2);
        printf("pedido entregue, todos os pedidos ja foram entregue\n");
        return;
    }
    printf("pedido entregue\n");
    aux_pilha1->prox = NULL;
    free(aux_pilha2);
}
