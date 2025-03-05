#include "gerenciador.c"

int main(int argc, char const *argv[])
{
    lista_espera *lista_pedidos = NULL;
    fila_preparo *fila_pedidos = NULL;
    pilha_entrega *pilha_pedidos = NULL;
    int num = 0;

    criar_pedido(&lista_pedidos,++num,"maria","batata,pizza");
    criar_pedido(&lista_pedidos,++num,"jao","batata,arroz");
    criar_pedido(&lista_pedidos,++num,"pedro","mandioca");

    pedido_preparo(&fila_pedidos,&lista_pedidos);
    pedido_preparo(&fila_pedidos,&lista_pedidos);
    pedido_preparo(&fila_pedidos,&lista_pedidos);

    pedido_pronto(&pilha_pedidos,&fila_pedidos);
    pedido_pronto(&pilha_pedidos,&fila_pedidos);
    pedido_pronto(&pilha_pedidos,&fila_pedidos);

    pedido_entregue(&pilha_pedidos);
    pedido_entregue(&pilha_pedidos);
    pedido_entregue(&pilha_pedidos);

    return 0;
}
