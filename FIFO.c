#include <stdio.h>
#include <stdlib.h>

struct fnode
{
    int pno;
} frame[15];
int ref_str[] = {3, 4, 5, 6, 3, 4, 7, 3, 4, 5, 6, 7, 2, 4, 6};
int page_fault = 0, n, i, pno, p, flag = 0;
int len = 15;

int page_found(int pno)
{
    for (i = 0; i < n; i++)
        if (frame[i].pno == pno)
            return i;
    return -1;
}

int main()
{
    printf("enter how many frame:");
    scanf("%d", &n);
    printf("len:%d", len);
    for (i = 0; i < n; i++)
        frame[i].pno = -1;

    printf("\n page_no  page_frame  page_fault");
    printf("\n*******************************************");
    for (p = 0; p < len; p++)
    {
        pno = ref_str[p];
        flag = 0;
        if (page_found(pno) == -1)
        {
            frame[page_fault % n].pno = pno;
            page_fault++;
            flag = 1;
        }
        printf("\n%4d\t", pno);
        for (i = 0; i < n; i++)
            printf("%4d", frame[i].pno);
        if (flag == 1)
            printf("   : YES");
        else
            printf("    :NO");
    }
    printf("\n================================================");
    printf("\nTotal no of page fault: %d", page_fault);
}