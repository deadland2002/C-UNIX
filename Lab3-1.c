#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int processId;
    int arrivalTime;
    int burstTime;
    int endTime;
    int turnaroundTime;
    int waitingTime;
} Process;

void getProcess(Process *process) {
    printf("Enter Process Id: ");
    scanf("%d", &(process->processId));
    printf("Enter Arrival Time: ");
    scanf("%d", &(process->arrivalTime));
    printf("Enter Burst Time: ");
    scanf("%d", &(process->burstTime));
}

int cmpfunc(const void *a, const void *b) {
    const Process *arr1 = (const Process *)a;
    const Process *arr2 = (const Process *)b;
    return arr1->arrivalTime - arr2->arrivalTime;
}

int main() {
    int numProcesses;

    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    Process *processes = (Process *)malloc(sizeof(Process) * numProcesses);

    for (int i = 0; i < numProcesses; i++) {
        printf("Process %d:\n", i + 1);
        getProcess(&processes[i]);
        processes[i].endTime = 0;
        processes[i].turnaroundTime = 0;
        processes[i].waitingTime = 0;
    }

    printf("\n%10s %10s %10s %10s %10s %10s\n", "PId", "AT", "BT", "ET", "TAT", "WT");

    qsort(processes, numProcesses, sizeof(Process), cmpfunc);

    for (int i = 0; i < numProcesses; i++) {
        printf("%10d %10d %10d %10d %10d %10d\n", processes[i].processId, processes[i].arrivalTime,
               processes[i].burstTime, processes[i].endTime, processes[i].turnaroundTime,
               processes[i].waitingTime);
    }

    free(processes);
    
    return 0;
}
