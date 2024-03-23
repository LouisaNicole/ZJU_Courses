#include <stdio.h>
#include <stdlib.h>

#define MAX_RUNS 1000
#define MAX_ELEMENTS 100001

typedef struct {
    int size;
    int* elements;
}Multiruns;

void insert(Multiruns* run, int element) {
    int i = 0, j;
    if(run->size == 0){
        run->elements[run->size] = element;
        run->size++;
    }else{
        while(element > run->elements[i] && i < run->size) i++;
        for (j = run->size; j > i; j--) {
            run->elements[j] = run->elements[j - 1];
        }
        run->elements[j] = element;
        run->size++;
    }
}

void erase(Multiruns* run, int element) {
    int i, j;
    for (i = 0; i < run->size; i++) {
        if (run->elements[i] == element) {
            for (j = i; j < run->size - 1; j++) {
                run->elements[j] = run->elements[j + 1];
            }
            run->size--;
            break;
        }
    }
}

int main() {
    int n, m, index = 0, cnt = 0, i;
    int num[MAX_ELEMENTS];
    scanf("%d%d", &n, &m);
    Multiruns m1, m2;
    Multiruns result[MAX_RUNS]; 
    m1.elements = (int*)malloc(sizeof(int) * MAX_ELEMENTS);
    m2.elements = (int*)malloc(sizeof(int) * MAX_ELEMENTS);
    for(i=0; i<MAX_RUNS; i++){
        result[i].elements = (int*)malloc(sizeof(int) * MAX_ELEMENTS);
    }
    m1.size = m2.size = result[0].size = 0;
    for(i=0; i<n; i++) {
        scanf("%d", &num[i]);
        if(i < m) {
            insert(&m1, num[i]);
            insert(&result[0], num[i]);
        }
    }
    for(i=m; i<n; i++) {
        if(num[i] > m1.elements[0]) {
            insert(&result[index], num[i]);
            erase(&m1, m1.elements[0]);
            insert(&m1, num[i]);
        }else {
            insert(&m2, num[i]);
            erase(&m1, m1.elements[0]);
            insert(&result[index + 1], num[i]);
        }
        if(m1.size == 0) {
            index++;
            int k;
            for(k=0; k<m; k++) {
                m1.elements[k] = m2.elements[k];
                m1.size++;
                m2.elements[k] = 0;
            }
            m2.size = 0;
        }
    }
    while(result[cnt].size != 0) cnt++;
    for(i=0; i<cnt; i++) {
        int flag = 0, j;
        for(j=0; j<result[i].size; j++) {
            if(flag != 0) printf(" ");
            printf("%d", result[i].elements[j]);
            flag++;
        }
        printf("\n");
    }
    free(m1.elements);
    free(m2.elements);
    for(i=0; i<MAX_RUNS; i++){
        free(result[i].elements);
    }
    return 0;
}