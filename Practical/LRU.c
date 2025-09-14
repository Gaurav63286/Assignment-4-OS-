#include <stdio.h>

struct frame
{
    int pno;
    int counter;
} frames[10];

int ref_str[] = {3, 5, 7, 2, 5, 1, 2, 3, 1, 3, 5, 3, 1, 6, 2};
int size = 15;
int n, i, j, currtime;

int page_found(int pno)
{
    int fno;
    for (fno = 0; fno < n; fno++)
        if (frames[fno].pno == pno)
            return fno;
    return -1;
}
int get_lru()
{
    int min = 0, fno;
    for (fno = 0; fno < n; fno++)
        if (frames[fno].counter < frames[min].counter)
            min = fno;
    return min;
}
int main()
{
    int i, j, pno, p, page_fault = 0, flag;
    printf("\nHow many frames: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        frames[i].pno = -1;
        frames[i].counter = -1;
    }
    printf("\nPage No. \tFrames\t\tPage Fault");
    printf("\n========================================");
    currtime = 0;
    for (p = 0; p < size; p++)
    {
        flag = 0;
        pno = ref_str[p];
        j = page_found(pno);
        if (j == -1)
        {
            page_fault++;
            j = get_lru();
            frames[j].pno = pno;
            flag = 1;
        }
        frames[j].counter = currtime;
        currtime++;
        printf("\n%5d\t", pno);
        for (i = 0; i < n; i++)
            printf("%2d:%2d  ", frames[i].pno, frames[i].counter);
        if (flag == 1)
            printf("\t:YES");
        else
            printf("\t:NO");
    }
    printf("\n==================================================");
    printf("\nNo. of page fault: %d", page_fault);
}