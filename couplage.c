#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct graphe_biparti_s{
    int* parti ;
    int** adj ;
    int n ;
} ;
typedef struct graphe_biparti_s graphe_biparti ;

struct a_s{int s1; int s2 ;} ;
typedef struct a_s arete ;

struct resultat_s{
    arete* aretes ;
    int len_a ;
} ;
typedef struct resultat_s resultat ;

resultat adjacence_to_arete(graphe_biparti gp){
    bool** est_ajoute = malloc(gp.n * sizeof(bool*)) ;
    for(int i = 0; i < gp.n; i++){
        est_ajoute[i] = malloc(gp.n * sizeof(bool)) ;
        for(int j = 0; j < gp.n ; j++){ est_ajoute[i][j] = false ;}
    }
    arete* res = malloc(sizeof(arete)) ;
    arete new; new.s1 = 0; new.s2 = gp.adj[0][1] ;
    res[0] = new ;
    est_ajoute[0][3] = true ; est_ajoute[3][0] = true ;
    int indice_ajout = 1 ;
    for(int i = 0; i < gp.n; i++){
        for(int j = 1; j <= gp.adj[i][0]; j++){
            if (!est_ajoute[i][gp.adj[i][j]]){
                est_ajoute[i][gp.adj[i][j]] = true ;
                est_ajoute[gp.adj[i][j]][i] = true ;
                arete new; new.s1 = i; new.s2 = gp.adj[i][j] ;
                res = realloc(res, (indice_ajout+1) * sizeof(arete)) ;
                res[indice_ajout] = new ;
                indice_ajout++ ;
                
            }
        }
    }
    for(int i = 0; i < gp.n; i++){free(est_ajoute[i]) ;}
    free(est_ajoute) ;
    resultat final; final.aretes = res ; final.len_a = indice_ajout ;
    return final ;
}

bool ajouter_arete(arete* gp_aretes, int len, arete* couplage, int len_c){
    for(int i = 0; i < len; i++){
        arete new = gp_aretes[i] ;
        bool possible = true ;
        for(int j = 0; j < len_c; j++){
            if (new.s1 == couplage[j].s1 || new.s1 == couplage[j].s2 || new.s2 == couplage[j].s1 || new.s2 == couplage[j].s2){
                possible = false ;
            }
        }
        if(possible){
            couplage = realloc(couplage, sizeof(arete) * (len_c + 1)) ;
            couplage[len_c] = new ;
            return true ;
        }
    }
    return false ;
}

resultat init_couplage(graphe_biparti gp){
    resultat r =  adjacence_to_arete(gp) ;
    arete* gp_aretes = r.aretes ;
    int len = r.len_a ;
    arete* couplage = malloc(sizeof(arete)) ;
    int len_c = 0 ;
    while (ajouter_arete(gp_aretes, len, couplage, len_c)){ len_c++ ;}
    resultat res; res.aretes = couplage; res.len_a = len_c ;
    return res ;
}

int main(void){
    int vois0[] = {1,3};
    int vois1[] = {2,3,4};
    int vois2[] = {1,4};
    int vois3[] = {2,0,1};
    int vois4[] = {2,1,2};
    int* list[5] = {vois0, vois1, vois2, vois3, vois4};
    graphe_biparti gp ;
    int parti[] = {1,1,1,2,2};
    gp.parti = parti; gp.adj = list; gp.n = 5;
    resultat res = init_couplage(gp) ;
    printf("%d", res.len_a) ;
    printf("(%d, %d) (%d, %d)", res.aretes[0].s1, res.aretes[0].s2, res.aretes[1].s1, res.aretes[1].s2) ;
    return 0 ;
}
