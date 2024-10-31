// arquivo :    digraph.c
// descricao :  apenas para fins de aprendizado implementacao de um grafo direcionado por listas de adjacencia para implementacao de algoritmos basicos
// implementacao similar ao de CRLS (computa floresta)
// autor :      Augusto Guerra de Lima - augustoguerra@dcc.ufmg.br
// historico :  2024101030 arquivo criado

#include<stdio.h>
#include<stdlib.h>
#include"digraph.c"

int time = -1;

// metodo :  dfs_visit
// descricao :  visita a partir de um vertice fonte todos os alcancaveis 
void dfs_visit(ptr_digraph G, ptr_digraph DFSF, int s)
{
    time++;
    DFSF->adj[s].dtime=time;
    DFSF->adj[s].color=1;

    edge_t* v=G->adj[s].head;
    while(v!=NULL) // grau de saida de s
    {
        if(DFSF->adj[v->vertex].color==0)
        {
            add_edge(DFSF,s,v->vertex);
            DFSF->adj[v->vertex].parent=s;
            dfs_visit(G, DFSF, v->vertex);
        }
        v=v->next;
    }

    time++;
    DFSF->adj[s].ftime=time;
    DFSF->adj[s].color=2;
}

// funcao : dfs
// descricao : funcao de caminhamento (busca) em profundidade
// dominio  : um grafo G e um vertice (nao coloquei vertice source por que estou preocupado com a floresta)
// imagem :   a arvore dfs resultante ao explorar o grafo 
ptr_digraph dfs(ptr_digraph G)
{   
    ptr_digraph DFSF = digraph_init(G->V);
    
    time=-1;
    for(int s=0; s<G->V; s++)
        {
            dfs_visit(G, DFSF, s);
        }
    
    return(DFSF);
}//end dfs()