//
// Created by Administrateur on 12/09/2022.
//
#include "function.h"

void test (float a, float b, float c){
    float d = (b*b) - (4*a* c);
    double r1, r2;
    if (d < 0) {
        /*double complex r3 = (-b+ (float)sqrt(d*I))/(2*a);
        double complex r4 = (-b- (float)sqrt(d*I))/(2*a);
        printf("il existe deux racines complexes: %.2f et %.2f", r3, r4);*/
        printf("les racines ne sont pas reels");
    }
    if (d == 0) {
        float r = (-b/2*a);
        printf("il existe une racine: %f", r);
    }
    if (d > 0){
        r1 = (float)((-b+ sqrtf(d))/(2*a));
        r2 = (float)(-b- sqrtf(d))/(2*a);
        printf("il existe deux racine: %f et %f", r1, r2);
    }
}

int minuscule (char t){
    return tolower(t);
}

int fact_for(int f){
    int fa = 1;
    for(int i = 1; i<=f; i++){
        fa *= i;
    }
    return fa;
}

int fact_while(int f){
    int fa = 1;
    int i = 1;
    while(i <= f){
        fa *= i;
        i++;
    }
    return fa;
}

int fact_rec(int f){
    if (f == 1) return 1;
    return f * fact_rec(f-1);
}

void pendu(char mot[]){
    int ok = 0;
    int nb = (int)strlen(mot);
    int t = 0; //lettres trouvés
    char l; //letter
    char v[nb];
    for (int i = 0; i <nb; i++){
        v[i] = '_';
    }

    while(!ok){
        printf("\n");
        for (int k = 0; k <nb; k++){
            printf("%c", v[k]);
        }
        printf("\nEnter a letter: ");
        scanf(" h%c", &l);
        for (int j = 0; j <nb; j++){
            if (l == mot[j]){
                v[j] = l;
                t++;
            }
        }

        if (nb == t) ok = 1;
    }
}

void tab_alea (int n){
    int tab[n];
    for (int i = 0; i < n; i++){
        tab[i] = (int)rand() % 100;
    }
    int temp;
    for(int k=0;k<n;k++){
        for(int j=1;j<n;j++){
            if(tab[j-1]>tab[j]){
                temp=tab[j-1];
                tab[j-1]=tab[j];
                tab[j]=temp;
            }
        }
    }
    for (int i = 0; i < n; i++){
        printf("\n%d", tab[i]);
    }
}

void tab2_alea(int n){
    int tab[n][n];
    for (int i = 0; i < n; i++){
        for(int j=0; j < n; j++){
            tab[i][j] = (int)rand() % 100;
        }
    }
    int temp;
    for(int i=0;i<n;++i ){
        for(int k=0;k<n;k++){
            for(int j=1;j<n;j++){
                if(tab[j-1][i]>tab[j][i]){
                    temp=tab[j-1][i];
                    tab[j-1][i]=tab[j][i];
                    tab[j][i]=temp;
                }
            }
        }
    }
    for (int i = 0; i < n; i++){
        for(int j=0; j < n; j++){
            printf("%d ", tab[i][j]);
        }
        printf("\n");
    }
}