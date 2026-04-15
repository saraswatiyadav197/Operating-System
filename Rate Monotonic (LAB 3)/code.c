#include <stdio.h>

#define MAX 10

typedef struct {
    int id;
    int C;   // execution time
    int T;   // period
    int remaining;
    int next_arrival;
} Task;

// GCD
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// LCM
int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

int main() {
    int n, i, t, hyper;

    Task task[MAX];

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    // Input
    for (i = 0; i < n; i++) {
        task[i].id = i + 1;

        printf("\nTask %d\n", i + 1);
        printf("Execution Time (Ci): ");
        scanf("%d", &task[i].C);

        printf("Period (Ti): ");
        scanf("%d", &task[i].T);

        task[i].remaining = 0;
        task[i].next_arrival = 0;
    }

    // Step 1: CPU Utilization
    float U = 0;
    for (i = 0; i < n; i++) {
        U += (float)task[i].C / task[i].T;
    }

    // Step 2: Hyperperiod (LCM)
    hyper = task[0].T;
    for (i = 1; i < n; i++) {
        hyper = lcm(hyper, task[i].T);
    }

    // Step 3: Sort by period (priority)
    for (i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (task[i].T > task[j].T) {
                Task temp = task[i];
                task[i] = task[j];
                task[j] = temp;
            }
        }
    }

    // Output basic info
    printf("\nPriority Order (Higher → Lower): ");
    for (i = 0; i < n; i++) {
        printf("P%d ", task[i].id);
    }

    printf("\nLCM (Hyperperiod) = %d\n", hyper);
    printf("CPU Utilization = %.3f\n", U);

    // Timeline
    printf("\nTime:     ");
    for (t = 0; t < hyper; t++) {
        printf("%2d ", t);
    }

    printf("\nProcess:  ");

    for (t = 0; t < hyper; t++) {

        // Check arrivals
        for (i = 0; i < n; i++) {
            if (t == task[i].next_arrival) {
                task[i].remaining = task[i].C;
                task[i].next_arrival += task[i].T;
            }
        }

        // Pick highest priority task
        int chosen = -1;
        for (i = 0; i < n; i++) {
            if (task[i].remaining > 0) {
                chosen = i;
                break;
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
