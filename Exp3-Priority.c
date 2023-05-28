#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int PID;
    int AT;
    int BT;
    int priority;
    int ET;
    int TAT;
    int WT;
} Process;

void getProcess(Process *process) {
    printf("Enter Arrival Time: ");
    scanf("%d", &(process->AT));
    printf("Enter Burst Time: ");
    scanf("%d", &(process->BT));
    printf("Enter Priority: ");
    scanf("%d", &(process->priority));
}

void calculatePriority(Process *p_arr, int n) {
    int *completionTime = (int *)malloc(sizeof(int) * n);
    int *isCompleted = (int *)malloc(sizeof(int) * n);
    int currentTime = 0;
    int completed = 0;

    for (int i = 0; i < n; i++) {
        isCompleted[i] = 0;
    }

    printf("\nGantt Chart:\n");
    while (completed < n) {
        int HP = -1;
        int HPIndex = -1;

        for (int i = 0; i < n; i++) {
            if (isCompleted[i] == 0 && p_arr[i].AT <= currentTime) {
                if (HP == -1 || p_arr[i].priority < HP) {
                    HP = p_arr[i].priority;
                    HPIndex = i;
                }
            }
        }

        if (HPIndex == -1) {
            printf("| Idle ");
            currentTime++;
            continue;
        }

        int CPIndex = HPIndex;
        isCompleted[CPIndex] = 1;
        completionTime[CPIndex] = currentTime + p_arr[CPIndex].BT;
        p_arr[CPIndex].ET = completionTime[CPIndex];
        p_arr[CPIndex].TAT = p_arr[CPIndex].ET - p_arr[CPIndex].AT;
        p_arr[CPIndex].WT = p_arr[CPIndex].TAT - p_arr[CPIndex].BT;
        completed++;
        currentTime = completionTime[CPIndex];

        printf("|  P%d  ", p_arr[CPIndex].PID);
    }
    printf("|\n");

    free(completionTime);
    free(isCompleted);
}

void printp_arr(Process *p_arr, int n) {
    printf("\n%10s %10s %10s %10s %10s %10s %10s\n", "PId", "AT", "BT", "Priority", "ET", "TAT", "WT");

    int totalTAT = 0;
    int totalWT = 0;

    for (int i = 0; i < n; i++) {
        printf("%10d %10d %10d %10d %10d %10d %10d\n", p_arr[i].PID, p_arr[i].AT,
               p_arr[i].BT, p_arr[i].priority, p_arr[i].ET, p_arr[i].TAT,
               p_arr[i].WT);

        totalTAT += p_arr[i].TAT;
        totalWT += p_arr[i].WT;
    }

    double avgTAT = (double)totalTAT / n;
    double avgWT = (double)totalWT / n;

    printf("\nAverage Turnaround Time: %.2f\n", avgTAT);
    printf("Average Waiting Time: %.2f\n", avgWT);
}

int main() {
    int n;

    printf("Enter the number of processess: ");
    scanf("%d", &n);

    Process *p_arr = (Process *)malloc(sizeof(Process) * n);

    for (int i = 0; i < n; i++) {
        printf("Process %d:\n", i + 1);
        getProcess(&p_arr[i]);
        p_arr[i].PID = i+1;
        p_arr[i].ET = 0;
        p_arr[i].TAT = 0;
        p_arr[i].WT = 0;
    }

    calculatePriority(p_arr, n);
    printp_arr(p_arr, n);

    free(p_arr);

    return 0;
}
