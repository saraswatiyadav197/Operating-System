#include <stdio.h>

#define MAX 10

typedef struct {
    int id;
    int C;   // capacity (execution time)
    int T;   // period
    int D;   // deadline
    int remaining;
    int next_arrival;
    int abs_deadline;
} Task;

int main() {
    int n, i, t, hyper = 1;

    Task task[MAX];

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    // Input
    for (i = 0; i < n; i++) {
        task[i].id = i + 1;

        printf("\nTask %d\n", i + 1);
        printf("Capacity (Ci): ");
        scanf("%d", &task[i].C);

        printf("Period (Ti): ");
        scanf("%d", &task[i].T);

        printf("Deadline (Di): ");
        scanf("%d", &task[i].D);

        task[i].remaining = 0;
        task[i].next_arrival = 0;
        task[i].abs_deadline = task[i].D;
    }

    // CPU Utilization
    float U = 0;
    for (i = 0; i < n; i++) {
        U += (float)task[i].C / task[i].D;
    }

    printf("\nCPU Utilization = %.3f\n", U);
    if (U <= 1)
        printf("Scheduling feasible\n");
    else
        printf("Not guaranteed\n");

    // Find LCM (hyperperiod)
    int gcd(int a, int b) {
        if (b == 0) return a;
        return gcd(b, a % b);
    }

    int lcm(int a, int b) {
        return (a * b) / gcd(a, b);
    }

    hyper = task[0].T;
    for (i = 1; i < n; i++) {
        hyper = lcm(hyper, task[i].T);
    }

    printf("LCM (Hyperperiod) = %d\n", hyper);

    // Time row
    printf("\nTime:     ");
    for (t = 0; t < hyper; t++) {
        printf("%2d ", t);
    }

    printf("\nProcess:  ");

    // Scheduling loop
    for (t = 0; t < hyper; t++) {

        // Check arrivals
        for (i = 0; i < n; i++) {
            if (t == task[i].next_arrival) {
                task[i].remaining = task[i].C;
                task[i].next_arrival += task[i].T;
                task[i].abs_deadline = t + task[i].D;
            }
        }

        // Select earliest deadline
        int chosen = -1;
        int min_deadline = 9999;

        for (i = 0; i < n; i++) {
            if (task[i].remaining > 0) {
                if (task[i].abs_deadline < min_deadline) {
                    min_deadline = task[i].abs_deadline;
                    chosen = i;
                }
            }
        }

        if (chosen == -1) {
            printf(" - ");
        } else {
            printf("P%d ", task[chosen].id);
            task[chosen].remaining--;
        }
    }

    printf("\n");

    return 0;
}
