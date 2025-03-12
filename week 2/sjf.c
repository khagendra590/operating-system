#include<stdio.h>
void main(){

    int bt[20], wt[20], tat[20], i, j, n, temp;
    float avgwt, avgtat;

    printf("Enter the no. of process: ");
    scanf("%d",&n);

    for(i=0;i<n;i++){
        printf("Enter the burst time for process %d: ",i+1);
        scanf("%d",&bt[i]);
    }

    for(i=0;i<n;i++){
        for(j=i+1;j<n;j++){
            if(bt[j]<bt[i]){
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;
            }
        }
    }

    wt[0]=avgwt=0;
    tat[0]=avgtat=bt[0];

    for(i=1;i<n;i++){
        wt[i] = wt[i-1] + bt[i-1];
        tat[i] = wt[i] + bt[i];
        avgwt += wt[i];
        avgtat += tat[i];
    }

    printf("\nProcess-ID\tBurst Time\tWaiting Time\tTurn-around Time\n");
    for(i=0;i<n;i++){
        printf("%d\t\t%d\t\t%d\t\t%d\n",i+1,bt[i],wt[i],tat[i]);
    }
    printf("\nAverage waiting time = %f\n",avgwt/n);
    printf("Average turn-around time = %f",avgtat/n);

}
