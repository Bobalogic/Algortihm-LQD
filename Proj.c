#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

int numSquares = 0;
long numSolutions = 0;


typedef struct{
    int line;
    int col;
    int size;
} Quadrado;

int getMax(int v1, int v2) {
    if(v1>=v2)
        return v1;
    return v2;
}

int getMin(int v1, int v2) {
    if(v1<=v2)
        return v1;
    return v2;
}

int getMaxComb(int value) {
    return (value * (value + 1) * (2*value + 1))/6;
}


Quadrado createSquare(int line, int col, int size) {
    Quadrado novo;
    novo.line = line;
    novo.col = col;
    novo.size = size;
    return novo;
}


void createSquares(Quadrado *sqrLst, int size, int col, int line) {
    int i;
    for(i=size; i>1; i--) {
        sqrLst[numSquares++] = createSquare(col, line, i);
    }
}


int *buildMatrix(int lines) {
    int *cList = malloc(sizeof(int)*(lines+1));
    int coef, i;

    for (i = 0; i<lines-1; i++) {
        scanf("%d\n", &coef);
        if(coef!=1) {
            cList[i] = coef;
        }
        else
            cList[i] = 0;
    }
    scanf("%d", &coef);
    if(coef== 0)
        return NULL;
    cList[i] = cList[i-1];
    return cList;
}


Quadrado *getAllSquares(int *cList, int lines, int cols) {
    int l, c;

    Quadrado *squareList = malloc(sizeof(Quadrado)*(getMaxComb(getMax(lines, cols))));

    for(l=0; l<lines-1; l++) {
        for(c=0; c<cList[l]-1; c++) {
            createSquares(squareList, getMin(cList[l]-c, lines-l), l, c);
        }
    }
    return squareList;
}


int isCompatible(Quadrado Q1, Quadrado Q2) {
    if(Q1.line+Q1.size<=Q2.line || Q1.line>=Q2.line+Q2.size || Q1.col+Q1.size<=Q2.col || Q1.col>=Q2.col+Q2.size)
        return TRUE;
    return FALSE;
}


int isCompatibleWithSolution(Quadrado *auxLst, Quadrado Q1, int usedSqrNum) {
    int i;

    for (i=usedSqrNum-1; i>=0; i--) {
        if(!isCompatible(Q1, auxLst[i]))
            return FALSE;
    }
    return TRUE;
}


void computeSolutions(Quadrado *sqrLst, Quadrado *auxLst, int counter, int usedSqrNum) {
    if(counter == numSquares) {
        numSolutions+=1;
        return;
    }
    /*Caminho: Usa este Quadrado*/
    if(isCompatibleWithSolution(auxLst, sqrLst[counter++], usedSqrNum)){
        auxLst[usedSqrNum++] = sqrLst[counter-1];
        computeSolutions(sqrLst, auxLst, counter, usedSqrNum);
        usedSqrNum-=1;
    }
    /*Caminho: Nao usa este quadrado*/
    computeSolutions(sqrLst, auxLst,counter, usedSqrNum);
}


int main() {
    int lines, cols;
    int *cList;
    Quadrado *squareList;
    Quadrado *auxLst;

    scanf("%d\n", &lines);
    scanf("%d", &cols);
    if(lines==0 || cols==0) {
        printf("0\n");
        return 0;
    }

    cList = buildMatrix(lines);
    if(cList==NULL) {
        printf("0\n");
        return 0;
    }
    
    squareList = getAllSquares(cList, lines, cols);
    if(numSquares==0) {
        printf("1\n");
        return 0;
    }

    auxLst = malloc(sizeof(Quadrado)*(numSquares+1));
    computeSolutions(squareList, auxLst, 0, 0);
    printf("%ld\n", numSolutions);

    return 0;
}