#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int processId;
    int arrivalTime;
    int burstTime;
    int priority;
    int endTime;
    int turnaroundTime;
    int waitingTime;
} Process;

void getProcess(Process *process) {
    printf("Enter Process ID: ");
    scanf("%d", &(process->processId));
    printf("Enter Arrival Time: ");
    scanf("%d", &(process->arrivalTime));
    printf("Enter Burst Time: ");
    scanf("%d", &(process->burstTime));
    printf("Enter Priority: ");
    scanf("%d", &(process->priority));
}

void calculatePriority(Process *processes, int numProcesses) {
    int *completionTime = (int *)malloc(sizeof(int) * numProcesses);
    int *isCompleted = (int *)malloc(sizeof(int) * numProcesses);
    int currentTime = 0;
    int completed = 0;

    for (int i = 0; i < numProcesses; i++) {
        isCompleted[i] = 0;
    }

    printf("\nGantt Chart:\n");
    while (completed < numProcesses) {
        int highestPriority = -1;
        int highestPriorityIndex = -1;

        for (int i = 0; i < numProcesses; i++) {
            if (isCompleted[i] == 0 && processes[i].arrivalTime <= currentTime) {
                if (highestPriority == -1 || processes[i].priority < highestPriority) {
                    highestPriority = processes[i].priority;
                    highestPriorityIndex = i;
                }
            }
        }

        if (highestPriorityIndex == -1) {
            printf("| Idle ");
            currentTime++;
            continue;
        }

        int currentProcessIndex = highestPriorityIndex;
        isCompleted[currentProcessIndex] = 1;
        completionTime[currentProcessIndex] = currentTime + processes[currentProcessIndex].burstTime;
        processes[currentProcessIndex].endTime = completionTime[currentProcessIndex];
        processes[currentProcessIndex].turnaroundTime = processes[currentProcessIndex].endTime - processes[currentProcessIndex].arrivalTime;
        processes[currentProcessIndex].waitingTime = processes[currentProcessIndex].turnaroundTime - processes[currentProcessIndex].burstTime;
        completed++;
        currentTime = completionTime[currentProcessIndex];

        printf("|  P%d  ", processes[currentProcessIndex].processId);
    }
    printf("|\n");

    free(completionTime);
    free(isCompleted);
}

void printProcesses(Process *processes, int numProcesses) {
    printf("\n%10s %10s %10s %10s %10s %10s %10s\n", "PId", "AT", "BT", "Priority", "ET", "TAT", "WT");

    int totalTurnaroundTime = 0;
    int totalWaitingTime = 0;

    for (int i = 0; i < numProcesses; i++) {
        printf("%10d %10d %10d %10d %10d %10d %10d\n", processes[i].processId, processes[i].arrivalTime,
               processes[i].burstTime, processes[i].priority, processes[i].endTime, processes[i].turnaroundTime,
               processes[i].waitingTime);

        totalTurnaroundTime += processes[i].turnaroundTime;
        totalWaitingTime += processes[i].waitingTime;
    }

    double avgTurnaroundTime = (double)totalTurnaroundTime / numProcesses;
    double avgWaitingTime = (double)totalWaitingTime / numProcesses;

    printf("\nAverage Turnaround Time: %.2f\n", avgTurnaroundTime);
    printf("Average Waiting Time: %.2f\n", avgWaitingTime);
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

    calculatePriority(processes, numProcesses);
    printProcesses(processes, numProcesses);

    free(processes);

    return 0;
}
