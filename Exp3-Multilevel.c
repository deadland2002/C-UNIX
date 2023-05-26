#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int processId;
    int arrivalTime;
    int burstTime;
    int priority;
    int remainingTime;
    int endTime;
    int turnaroundTime;
    int waitingTime;
    int responseTime;
} Process;

void getProcess(Process *process) {
    printf("Enter Process ID: ");
    scanf("%d", &process->processId);
    printf("Enter Arrival Time: ");
    scanf("%d", &process->arrivalTime);
    printf("Enter Burst Time: ");
    scanf("%d", &process->burstTime);
    printf("Enter Priority (1 for Level 1, 2 for Level 2, 3 for Level 3): ");
    scanf("%d", &process->priority);
    process->remainingTime = process->burstTime;
}

void calculateScheduling(Process *processes, int numProcesses) {
    int timeQuantum[] = {2, 4};
    int currentTime = 0;
    int completedProcesses = 0;

    printf("\nGantt Chart:\n");
    while (completedProcesses < numProcesses) {
        int currentProcess = -1;

        for (int i = 0; i < numProcesses; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                if (currentProcess == -1) {
                    currentProcess = i;
                } else if (processes[i].priority < processes[currentProcess].priority) {
                    currentProcess = i;
                } else if (processes[i].priority == processes[currentProcess].priority &&
                           processes[i].arrivalTime < processes[currentProcess].arrivalTime) {
                    currentProcess = i;
                }
            }
        }

        if (currentProcess == -1) {
            printf(" Idle ");
            currentTime++;
        } else {
            printf("  P%d  ", processes[currentProcess].processId);

            if (processes[currentProcess].remainingTime <= timeQuantum[processes[currentProcess].priority - 1]) {
                currentTime += processes[currentProcess].remainingTime;
                processes[currentProcess].remainingTime = 0;
            } else {
                currentTime += timeQuantum[processes[currentProcess].priority - 1];
                processes[currentProcess].remainingTime -= timeQuantum[processes[currentProcess].priority - 1];
            }

            if (processes[currentProcess].remainingTime == 0) {
                processes[currentProcess].endTime = currentTime;
                processes[currentProcess].turnaroundTime = processes[currentProcess].endTime - processes[currentProcess].arrivalTime;
                processes[currentProcess].waitingTime = processes[currentProcess].turnaroundTime - processes[currentProcess].burstTime;
                completedProcesses++;
            }
        }
    }
    printf("\n");
}

void printProcesses(Process *processes, int numProcesses) {
    printf("%10s %10s %10s %10s %10s %10s %10s %10s\n", "PId", "AT", "BT", "Priority", "ET", "TAT", "WT", "RT");
    for (int i = 0; i < numProcesses; i++) {
        printf("%10d %10d %10d %10d %10d %10d %10d %10d\n", processes[i].processId, processes[i].arrivalTime,
               processes[i].burstTime, processes[i].priority, processes[i].endTime, processes[i].turnaroundTime,
               processes[i].waitingTime, processes[i].responseTime);
    }
}

int main() {
    int numProcesses;

    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    Process *processes = (Process *)malloc(sizeof(Process) * numProcesses);

    for (int i = 0; i < numProcesses; i++) {
        printf("Process %d:\n", i + 1);
        getProcess(&processes[i]);
    }

    calculateScheduling(processes, numProcesses);
    printProcesses(processes, numProcesses);

    free(processes);

    return 0;
}
