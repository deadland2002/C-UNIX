#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    int ID;
    int *allocated;
    int *required;
    bool visited;
} Process;

bool deadlock = true;

void getVals(Process processes[], int nR, int nP)
{
    for (int i = 0; i < nP; i++){
        int *temp = (int *)malloc(sizeof(int) * nR);
        printf("\nEnter allocated resource value : ");
        for (int j = 0; j < nR; j++){
            scanf("%d", &temp[j]);
        }
        processes[i].allocated = temp;
        processes[i].visited = false;
    }
    for (int i = 0; i < nP; i++){
        int *temp = (int *)malloc(sizeof(int) * nR);
        printf("\nEnter required resource value : ");
        for (int j = 0; j < nR; j++){
            scanf("%d", &temp[j]);
        }
        processes[i].required = temp;
    }
}

bool checkRes(Process processess[], int *available, int nR, int i)
{
    for (int j = 0; j < nR; j++){
        int val = processess[i].allocated[j] + available[j];
        if (val < processess[i].required[j])
        {
            return false;
        }
    }
    for (int j = 0; j < nR; j++){
        int val = processess[i].allocated[j] + available[j];
        available[j] = val;
    }
    return true;
}

void printSeries(int *series, int n)
{
    for (int j = 0; j < n; j++){
        printf("%d ", series[j]);
    }
}

int isCycle(Process processess[], int nR, int nP, int i, int *available, int *series, int ind)
{
    if (processess[i].visited)
        return -1;

    if (ind + 1 == nP){
        if (checkRes(processess, available, nR, i)){
            deadlock = false;
            series[ind] = i;
            printSeries(series, nP);
            return ind;
        }
        return -1;
    }
    else{
        if (!checkRes(processess, available, nR, i))
            return -1;

        processess[i].visited = true;
        series[ind] = i;

        bool flag = true;
        for (int j = 0; j < nP; j++){
            if (!processess[j].visited){
                int cycle = isCycle(processess, nR, nP, j, available, series, ind + 1);
                if (cycle == -1)
                    flag = false;
                else
                    flag = true;
            }
        }
        processess[i].visited = false;
        if (flag)
            return ind;
        return -1;
    }
}

int main()
{
    int nP, nR;

    printf("Enter number of processes: ");
    scanf("%d", &nP);
    printf("Enter number of resources: ");
    scanf("%d", &nR);

    Process processes[nP];
    int *available = (int *)malloc(sizeof(int) * nR);
    int *series = (int *)malloc(sizeof(int) * nP);

    getVals(processes, nR, nP);

    printf("Enter available resources: ");
    for (int j = 0; j < nR; j++)
        scanf("%d", &available[j]);

    for (int i = 0; i < nP; i++){
        int index = 0;
        int cycle = isCycle(processes, nR, nP, i, available, series, index);
    }

    if (deadlock){
        printf("Deadlock present");
    }
    printf("\n");
    return 0;
}
