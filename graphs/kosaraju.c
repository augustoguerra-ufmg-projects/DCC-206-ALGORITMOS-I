// arquivo :    kosaraju.c
// descricao :  implementacao do algoritmo kosaraju utilizando dfs para identificar componentes fortemente
// conexas de um digrafo e uma aplicacao interessante do algoritmo dfs de caminhamento consegue identificar
// quais sao todas as componentes fortemente conexas se baseando no fato de que os vertices mutualmente alcancaveis
// sao identicos no grafo transposto e realiza a chamada na ordem decrescente ao tempo de finalizacao de dois vertices
// basicamente o Kosaraju Algorithm consiste na chamada de duas dfss entao a complexidade esta em O(m+n)
// autor :      Augusto Guerra de Lima - augustoguerra@dcc.ufmg.br
// historico :  2024101101 arquivo criado

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"digraph.c"

// registro :   stack_t
// descricao :  estrutura auxiliar para empilhar vertices para o algoritmo de Kosaraju
typedef
struct stack
{
    int top;
    int* stack;
}stack_t;

typedef stack_t* ptr_stack;

ptr_stack stack_init(int size)
{
    ptr_stack S = (ptr_stack)malloc(sizeof(stack_t));
    S->stack = (int*)malloc(size*sizeof(int));
    S->top = -1;

    return(S);
}

void stack_free(ptr_stack S)
{
    free(S->stack);
    free(S);
}

void add_stack(ptr_stack S, int x)
{
    S->stack[++S->top] = x;
}

int pop_stack(ptr_stack S)
{
    return(S->stack[S->top--]);
}

bool is_empty(ptr_stack S)
{
    return(S->top==-1);
}


// metodo : dfs_visit
// descricao :  caminha pela profundidade do digrafo G e ao finalizar um vertice coloca na pilha
void dfs_visit(ptr_digraph G, ptr_stack S, int s)
{
    G->adj[s].color=1;
    edge_t* i = G->adj[s].head;
    while(i!=NULL)
    {
        if(G->adj[i->vertex].color==0)
            dfs_visit(G,S,i->vertex);
        
        i=i->next;
    }
    G->adj[s].color=2;
    add_stack(S,s);
}

// metodo :  dfs_SCC
// descricao :  caminha pelo grafo transposto onde as chamadas sao feitas em Kosaraju na ordem descrescente
// da finalizacao dos vertices i.e. no comportamento de pilha LIFO
void dfs_SCC(ptr_digraph Gt, int s)
{
    Gt->adj[s].color=1;
    printf("%d ",s);

    edge_t* i= Gt->adj[s].head;
    while(i!=NULL)
    {
        if(Gt->adj[i->vertex].color==0)
            dfs_SCC(Gt, i->vertex);
        
        i=i->next;
    }
}

// metodo : Kosaraju
// descricao : computa com duas dfss quais sao as componentes fortemente conexas de um digrafo
// imprimindo-as no console
void Kosaraju(ptr_digraph G)
{
    ptr_stack S = stack_init(G->V);
    ptr_digraph Gt = digraph_transpose(G);

    for(int i=0; i<G->V; i++)
    {
        if(G->adj[i].color==0)
        {
            dfs_visit(G,S,i);
        }
    }

    while(!is_empty(S))
    {
        int i=pop_stack(S);
        if(Gt->adj[i].color==0)
        {
            dfs_SCC(Gt,i);
            printf("\n");
        }
    }
    stack_free(S);
    digraph_free(Gt);
}