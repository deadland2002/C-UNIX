#include <stdio.h>

// Structure to represent a process
struct Process {
    int pid;
    int burst_time;
    int arrival_time;
};

// Function to calculate average waiting time and turn around time
void calculateWaitingTurnaroundTime(struct Process processes[], int n) {
    int waiting_time[n], turnaround_time[n], completion_time[n];
    float total_waiting_time = 0, total_turnaround_time = 0;

    // Sort processes based on their arrival time (earliest first)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    // Calculate completion time for each process
    completion_time[0] = processes[0].arrival_time + processes[0].burst_time;
    for (int i = 1; i < n; i++) {
        int min_burst_time = processes[i].burst_time;
        int min_burst_index = i;
        for (int j = i + 1; j < n; j++) {
            if (processes[j].arrival_time <= completion_time[i - 1] && processes[j].burst_time < min_burst_time) {
                min_burst_time = processes[j].burst_time;
                min_burst_index = j;
            }
        }
        struct Process temp = processes[i];
        processes[i] = processes[min_burst_index];
        processes[min_burst_index] = temp;
        completion_time[i] = completion_time[i - 1] + processes[i].burst_time;
    }

    // Calculate waiting time and turnaround time for each process
    for (int i = 0; i < n; i++) {
        waiting_time[i] = completion_time[i] - processes[i].arrival_time - processes[i].burst_time;
        turnaround_time[i] = completion_time[i] - processes[i].arrival_time;
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }

    // Display Gantt chart
    printf("Gantt Chart:\n");
    for (int i = 0; i < n; i++) {
        printf("| P%d ", processes[i].pid);
    }
    printf("|\n");

    // Display process details
    printf("\nProcess\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].burst_time, processes[i].arrival_time, waiting_time[i], turnaround_time[i]);
    }

    // Calculate average waiting time and turn around time
    float avg_waiting_time = total_waiting_time / n;
    float avg_turnaround_time = total_turnaround_time / n;

    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        printf("Enter details for Process %d\n", i + 1);
        processes[i].pid = i + 1;
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
    }

    calculateWaitingTurnaroundTime(processes, n);

    return 0;
}
