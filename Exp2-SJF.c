#include <stdio.h>

// Structure to represent a process
struct Process {
    int pid;
    int BT;
    int AT;
};

// Function to calculate average waiting time and turn around time
void calculateTime(struct Process p_arr[], int n) {
    int WT[n], TAT[n], CT[n];
    float total_WT = 0, total_TAT = 0;

    // Sort p_arr based on their arrival time (earliest first)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p_arr[j].AT > p_arr[j + 1].AT) {
                struct Process temp = p_arr[j];
                p_arr[j] = p_arr[j + 1];
                p_arr[j + 1] = temp;
            }
        }
    }

    // Calculate completion time for each process
    CT[0] = p_arr[0].AT + p_arr[0].BT;
    for (int i = 1; i < n; i++) {
        int min_BT = p_arr[i].BT;
        int min_burst_index = i;
        for (int j = i + 1; j < n; j++) {
            if (p_arr[j].AT <= CT[i - 1] && p_arr[j].BT < min_BT) {
                min_BT = p_arr[j].BT;
                min_burst_index = j;
            }
        }
        struct Process temp = p_arr[i];
        p_arr[i] = p_arr[min_burst_index];
        p_arr[min_burst_index] = temp;
        CT[i] = CT[i - 1] + p_arr[i].BT;
    }

    // Calculate waiting time and turnaround time for each process
    for (int i = 0; i < n; i++) {
        WT[i] = CT[i] - p_arr[i].AT - p_arr[i].BT;
        TAT[i] = CT[i] - p_arr[i].AT;
        total_WT += WT[i];
        total_TAT += TAT[i];
    }

    // Display Gantt chart
    printf("Gantt Chart:\n");
    for (int i = 0; i < n; i++) {
        printf("| P%d ", p_arr[i].pid);
    }
    printf("|\n");

    // Display process details
    printf("\nProcess\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", p_arr[i].pid, p_arr[i].BT, p_arr[i].AT, WT[i], TAT[i]);
    }

    // Calculate average waiting time and turn around time
    float avg_WT = total_WT / n;
    float avg_TAT = total_TAT / n;

    printf("\nAverage Waiting Time: %.2f\n", avg_WT);
    printf("Average Turnaround Time: %.2f\n", avg_TAT);
}

int main() {
    int n;
    printf("Enter the number of processess: ");
    scanf("%d", &n);

    struct Process p_arr[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        printf("Enter details for Process %d\n", i + 1);
        p_arr[i].pid = i + 1;
        printf("Burst Time: ");
        scanf("%d", &p_arr[i].BT);
        printf("Arrival Time: ");
        scanf("%d", &p_arr[i].AT);
    }

    calculateTime(p_arr, n);

    return 0;
}
