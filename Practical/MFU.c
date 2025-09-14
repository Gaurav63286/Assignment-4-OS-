#include <stdio.h>

struct frame {
    int pno;
    int freq;  
} frames[10];

int ref_str[] = {3, 5, 7, 2, 5, 1, 2, 3, 1, 3, 5, 3, 1, 6, 2};
int size = 15;
int n;

int page_found(int pno) {
    int fno;
    for (fno = 0; fno < n; fno++)
        if (frames[fno].pno == pno)
            return fno;
    return -1;
}

int get_mfu() {
    int max = 0, fno;
    for (fno = 1; fno < n; fno++)
        if (frames[fno].freq > frames[max].freq)
            max = fno;
    return max;
}

int main() {
    int i, j, pno, p, page_fault = 0, flag;

    printf("How many frames: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        frames[i].pno = -1;
        frames[i].freq = 0;
    }

    printf("\nPage No.\tFrames\t\tPage Fault");
    printf("\n========================================\n");

    for (p = 0; p < size; p++) {
        flag = 0;
        pno = ref_str[p];
        j = page_found(pno);

        if (j == -1) {

            page_fault++;
    
            int empty_index = -1;
            for (i = 0; i < n; i++) {
                if (frames[i].pno == -1) {
                    empty_index = i;
                    break;
                }
            }

            if (empty_index != -1) {
               
                frames[empty_index].pno = pno;
                frames[empty_index].freq = 1;
            } else {
                
                j = get_mfu();
                frames[j].pno = pno;
                frames[j].freq = 1; 
            }
            flag = 1;
        } else {
         
            frames[j].freq++;
        }

        printf("%5d\t\t", pno);
        for (i = 0; i < n; i++)
            printf("%2d:%d  ", frames[i].pno, frames[i].freq);
        printf("\t%s\n", flag ? "YES" : "NO");
    }

    printf("==================================================\n");
    printf("Total Page Faults: %d\n", page_fault);

    return 0;
}