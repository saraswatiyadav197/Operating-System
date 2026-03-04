#include <stdio.h>
#include <limits.h>

int main() {
    int n, at[20], bt[20], rt[20];
    int wt[20], tat[20], ct[20];
    int i, time = 0, remain = 0, shortest;
    float awt = 0, att = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("Enter Arrival Time for P%d: ", i+1);
        scanf("%d", &at[i]);

        printf("Enter Burst Time for P%d: ", i+1);
        scanf("%d", &bt[i]);

        rt[i] = bt[i];
    }

    while(remain != n) {
        shortest = -1;
        int min = INT_MAX;

        for(i = 0; i < n; i++) {
            if(at[i] <= time && rt[i] > 0 && rt[i] < min) {
                min = rt[i];
                shortest = i;
            }
        }

        if(shortest == -1) {
            time++;
            continue;
        }

        rt[shortest]--;
        time++;

        if(rt[shortest] == 0) {
            remain++;
            ct[shortest] = time;

            tat[shortest] = ct[shortest] - at[shortest];
            wt[shortest] = tat[shortest] - bt[shortest];

            awt += wt[shortest];
            att += tat[shortest];
        }
    }

    awt /= n;
    att /= n;

    printf("\nPROCESS\tAT\tBT\tWT\tTAT");

    for(i = 0; i < n; i++) {
        printf("\nP%d\t%d\t%d\t%d\t%d", i+1, at[i], bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f", awt);
    printf("\nAverage Turnaround Time = %.2f", att);

    return 0;
}
