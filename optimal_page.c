#include <stdio.h>

struct frame
{
    int pno;
} frames[10];

int ref_str[] = {8, 5, 7, 8, 5, 7, 2, 3, 7, 3, 5, 9, 4, 6, 2};
int size = 15;
int n, i, j;

int page_found(int pno)
{
    int fno;
    for (fno = 0; fno < n; fno++)
        if (frames[fno].pno == pno)
            return fno;

    return -1;
}

int get_optimal(int current)
{
    int future = -1, j, i, index = -1;

    for (i = 0; i < n; i++)
    {
        for (j = current + 1; j < size; j++)
        {
            if (frames[i].pno == ref_str[j])
            {
                break;
            }
        }
        if (j == size)
        {
            return i;
        }
        if (j > future)
        {
            future = j;
            index = i;
        }
    }
    return index;
}

int main()
{
    int i, j, pno, p, page_fault = 0, flag;
    printf("\nHow many frames: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        frames[i].pno = -1;
    }

    printf("\nPage No. \tFrames\t\tPage Fault");
    printf("\n========================================");

    for (p = 0; p < size; p++)
    {
        flag = 0;
        pno = ref_str[p];
        j = page_found(pno);

        if (j == -1)
        {
            page_fault++;
            j = get_optimal(p);

            frames[j].pno = pno;
            flag = 1;
        }

        printf("\n%5d\t     ", pno);
        for (i = 0; i < n; i++)
            printf("%2d  ", frames[i].pno);

        if (flag == 1)
            printf("\t:YES");
        else
            printf("\t:NO");
    }

    printf("\n==================================================");
    printf("\nNo. of page faults: %d\n", page_fault);
}
