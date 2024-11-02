// arquivo :    dfs_edge_classifier.c
// descricao :  um algoritmo que pensei recentemente para classificar as arestas de uma chamada DFS
// essencialmente ha quatro tipos de arestas que podem ser classificadas como
// tree - fazem parte da arvore/floresta DFSF
// back - denunciam um ciclo no digrafo
// foward - uma aresta (u,v) onde v e descendente de u mas nao faz parte da arvore
// cross - uma aresta (u,v) mas v nao e descendente de u ou outras aresta do digrafo btw
// autor :      Augusto Guerra de Lima - augustoguerra@dcc.ufmg.br
// historico :  2024101101 arquivo criado

#include<stdio.h>
#include<stdlib.h>
#include"digraph.c"

int time = -1;
// essencialmente pensei em como traduzir essas classificoes em termos de atributos de vertices e arestas
// se uma aresta cinza liga numa branca entao e tree
// se uma aresta cinza liga numa cinza entao e back
// se uma aresta cinza liga numa preta e necessario verificar os intervalos de finalizacao
// se os intervalos sao contidos e uma aresta foward
// se os intervalos sao disjunto e uma aresta cross
// existe um teorema para os intervalos serem contidos ou disjuntos presentes em CLRS

// importante dizer que explora os vertices na ordem da lista de adjacencia de um vertice 
void dfs_visit(ptr_digraph G, int s)
{
    time++;
    G->adj[s].color=1;
    G->adj[s].dtime=time;

    edge_t* e=G->adj[s].head;
    while(e!=NULL)
    {
    
        if(G->adj[e->vertex].color==0)
        {
            printf("%d -> %d TREE\n", s, e->vertex);
            G->adj[e->vertex].color=1;
            dfs_visit(G,e->vertex);
        }
        else if(G->adj[e->vertex].color==1)
        {
            printf("%d -> %d BACK\n", s, e->vertex);
        }
        else if(G->adj[e->vertex].color==2)
        {
            if(G->adj[s].dtime<G->adj[e->vertex].dtime)
            {
                printf("%d -> %d FOWARD\n", s, e->vertex);
            }
            else
            {
                printf("%d -> %d CROSS\n", s, e->vertex);
            }
        }
        e=e->next;
    }
    time++;
    G->adj[s].ftime=time;
    G->adj[s].color=2;
}

void dfs(ptr_digraph G)
{
    for(int i=0; i<G->V; i++)
        if(G->adj[i].color==0)
            dfs_visit(G,i);
}