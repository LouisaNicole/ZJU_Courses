#include <stdio.h>

#define ElementType int
#define MAXN 100

void merge_pass( ElementType list[], ElementType sorted[], int N, int length );

void output( ElementType list[], int N )
{
    int i;
    for (i=0; i<N; i++) printf("%d ", list[i]);
    printf("\n");
}

void  merge_sort( ElementType list[],  int N )
{
    ElementType extra[MAXN];  /* the extra space required */
    int  length = 1;  /* current length of sublist being merged */
    while( length < N ) { 
        merge_pass( list, extra, N, length ); /* merge list into extra */
        output( extra, N );
        length *= 2;
        merge_pass( extra, list, N, length ); /* merge extra back to list */
        output( list, N );
        length *= 2;
    }
} 


int main()
{
    int N, i;
    ElementType A[MAXN];

    scanf("%d", &N);
    for (i=0; i<N; i++) scanf("%d", &A[i]);
    merge_sort(A, N);
    output(A, N);

    return 0;
}

/* Your function will be put here */
void merge_pass( ElementType list[], ElementType sorted[], int N, int length ){
    int left = 0, right = length;
    int left_end = right -1;
    int right_end = (right + length - 1) < N ? (right + length - 1) : (N - 1);
    int i, j, index = 0;
    for(i=0; i<N; i+=length*2){
        while(left <= left_end && right <= right_end && right < N && left < N){
            if(list[left] < list[right]){
                sorted[index++] = list[left++];
            }
            else{
                sorted[index++] = list[right++];
            }
        }
        while(left <= left_end){
            sorted[index++] = list[left++];
        }
        while(right <= right_end){
            sorted[index++] = list[right++];
        }
        left = right;
        right += length;
        left_end = right - 1;
        right_end = (right + length - 1) < N ? (right + length - 1) : (N - 1);
    }
}