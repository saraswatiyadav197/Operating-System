#include <stdio.h>

int main() {
    int n,i,j,at[10],bt[10],pr[10],ct[10],tat[10],wt[10];
    float avgtat=0, avgwt=0;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(i=0;i<n;i++){
        printf("AT BT Priority for P%d: ",i+1);
        scanf("%d%d%d",&at[i],&bt[i],&pr[i]);
    }

    for(i=0;i<n-1;i++){
        for(j=i+1;j<n;j++){
            if(pr[i] > pr[j]){
                int t;
                t=pr[i]; pr[i]=pr[j]; pr[j]=t;
                t=bt[i]; bt[i]=bt[j]; bt[j]=t;
                t=at[i]; at[i]=at[j]; at[j]=t;
            }
        }
    }

    ct[0]=at[0]+bt[0];

    for(i=1;i<n;i++)
        ct[i]=ct[i-1]+bt[i];

    for(i=0;i<n;i++){
        tat[i]=ct[i]-at[i];
        wt[i]=tat[i]-bt[i];

        avgtat += tat[i];
        avgwt += wt[i];
    }

    printf("\nP\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for(i=0;i<n;i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",i+1,at[i],bt[i],pr[i],ct[i],tat[i],wt[i]);

    printf("\nAverage Turnaround Time = %.2f", avgtat/n);
    printf("\nAverage Waiting Time = %.2f", avgwt/n);

    return 0;
}
