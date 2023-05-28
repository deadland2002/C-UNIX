#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int PID;
    int AT;
    int BT;
    int priority;
    int RemT;
    int ET;
    int TAT;
    int WT;
    int ResT;
} Process;

void getProcess(Process *process , int i) {
    process->PID = i+1;
    printf("Enter Arrival Time: ");
    scanf("%d", &process->AT);
    printf("Enter Burst Time: ");
    scanf("%d", &process->BT);
    printf("Enter Priority (1 for Level 1, 2 for Level 2, 3 for Level 3): ");
    scanf("%d", &process->priority);
    process->RemT = process->BT;
}

void calculateScheduling(Process *p_arr, int n) {
    int TQ[] = {2, 4};
    int CurrT = 0;
    int ComP = 0;

    printf("\nGantt Chart:\n");
    while (ComP < n) {
        int CurrP = -1;

        for (int i = 0; i < n; i++) {
            if (p_arr[i].AT <= CurrT && p_arr[i].RemT > 0) {
                if (CurrP == -1) {
                    CurrP = i;
                } else if (p_arr[i].priority < p_arr[CurrP].priority) {
                    CurrP = i;
                } else if (p_arr[i].priority == p_arr[CurrP].priority &&
                           p_arr[i].AT < p_arr[CurrP].AT) {
                    CurrP = i;
                }
            }
        }

        if (CurrP == -1) {
            printf(" Idle ");
            CurrT++;
        } else {
            printf("  P%d  ", p_arr[CurrP].PID);

            if (p_arr[CurrP].RemT <= TQ[p_arr[CurrP].priority - 1]) {
                CurrT += p_arr[CurrP].RemT;
                p_arr[CurrP].RemT = 0;
            } else {
                CurrT += TQ[p_arr[CurrP].priority - 1];
                p_arr[CurrP].RemT -= TQ[p_arr[CurrP].priority - 1];
            }

            if (p_arr[CurrP].RemT == 0) {
                p_arr[CurrP].ET = CurrT;
                p_arr[CurrP].TAT = p_arr[CurrP].ET - p_arr[CurrP].AT;
                p_arr[CurrP].WT = p_arr[CurrP].TAT - p_arr[CurrP].BT;
                ComP++;
            }
        }
    }
    printf("\n");
}

void printTable(Process *p_arr, int n) {
    printf("%10s %10s %10s %10s %10s %10s %10s %10s\n", "PId", "AT", "BT", "Priority", "ET", "TAT", "WT", "ResT");
    for (int i = 0; i < n; i++) {
        printf("%10d %10d %10d %10d %10d %10d %10d %10d\n", p_arr[i].PID, p_arr[i].AT,
               p_arr[i].BT, p_arr[i].priority, p_arr[i].ET, p_arr[i].TAT,
               p_arr[i].WT, p_arr[i].ResT);
    }
}

int main() {
    int n;

    printf("Enter the number of processess: ");
    scanf("%d", &n);

    Process *p_arr = (Process *)malloc(sizeof(Process) * n);

    for (int i = 0; i < n; i++) {
        printf("Process %d:\n", i + 1);
        getProcess(&p_arr[i],i);
    }

    calculateScheduling(p_arr, n);
    printTable(p_arr, n);

    free(p_arr);

    return 0;
}
