// arquivo :    digraph.c
// descricao :  apenas para fins de aprendizado implementacao de um grafo direcionado por listas de adjacencia para implementacao de algoritmos basicos
// autor :      Augusto Guerra de Lima - augustoguerra@dcc.ufmg.br
// historico :  2024101030 arquivo criado

#include<stdio.h>
#include<stdlib.h>

// registro : edge
// descricao : implementa uma aresta direcionada para a lista de adjacencia
typedef
struct edge
{
    int vertex;
    struct edge* next;
}edge_t;

// registro :   adj_list
// decricao :   lista de cada vertice contem informacoes extras que podem ser utilizadas em alguns algorimos ex DFS
typedef
struct adj_list
{
    int color;
    int parent;
    int dtime;
    int ftime;
    edge_t* head;
}adj_list_t;

// registro :  digraph
// descricao : grafo direcionado representado por listas de adjacencia
typedef
struct digraph
{
    int V;
    int E;
    adj_list_t* adj;
}digraph_t;

typedef digraph_t* ptr_digraph;

// funcao : digraph_init
// descricao : dinamicamente aloca espaco para um grafo a ser utilizado 
// dominio : cardinalidade do conjunto de vertices
// imagem : apontador para um digrafo dinamicamente alocado
ptr_digraph digraph_init(int V)
{
    ptr_digraph G = (ptr_digraph)malloc(sizeof(digraph_t));
    G->V=V;
    G->E=0;

    G->adj=(adj_list_t*)malloc(V*sizeof(adj_list_t));
    for(int i=0;i<V;i++)
    {
        G->adj[i].color=0;
        G->adj[i].parent=-1;
        G->adj[i].dtime=-1;
        G->adj[i].ftime=-1;
        G->adj[i].head=NULL;
    }
    return(G);
}//end digraph_init

// metodo : digraph_free
// descricao : libera memoria de um digrafo alocado dinamicamente e de todos os registros secundarios
void digraph_free(ptr_digraph G)
{
    for(int i=0;i<G->V;i++)
    {
        edge_t* j=G->adj[i].head;
        while(j!=NULL)
        {
            edge_t* p=j;
            j=j->next;
            free(p);
        }
    }
    free(G->adj);
    free(G);
}

// metodo : add_edge
// descricao : adiciona um arco ao grafo
void add_edge(ptr_digraph G, int u, int v)
{
    edge_t* e=(edge_t*)malloc(sizeof(edge_t));
    e->vertex=v;
    e->next=G->adj[u].head;
    G->adj[u].head=e;
    G->E++;
}

// funcao : digraph_transpose
// descricao : computa o digrafo transposto em O(v+e)
// dominio : um digrafo
// imagem : o digrafo de entrada transposto i.e. direcao dos arcos invertida para todos os arcos do digrafo de entrada
ptr_digraph digraph_transpose(ptr_digraph G)
{
    ptr_digraph Gt = digraph_init(G->V);
    for(int i=0; i<G->V; i++)
    {
        edge_t* j=G->adj[i].head;
        while(j!=NULL)
        {
            add_edge(Gt,j->vertex,i);
            j=j->next;
        }
    }
    return(Gt);
}

// metodo : digraph_print
// descricao : funcao auxiliar que imprime visualmente a representacao das listas de adjacencia no console
void digraph_print(ptr_digraph G)
{
    for(int i=0;i<G->V;i++)
    {
        printf("%d:\t",i);
        edge_t* j=G->adj[i].head;
        while(j!=NULL)
        {
            printf("%d\t",j->vertex);
            j=j->next;
        }
        printf("\n");
    }
}