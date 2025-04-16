#include <stdio.h>
#include <stdbool.h>

int main() {
    int n, m, i, j, k;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], need[n][m], avail[m];
    int finish[n], safeSeq[n];

    for (i = 0; i < n; i++) {
        printf("Enter details for P%d\n", i);
        printf("Enter allocation: ");
        for (j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

        printf("Enter Max: ");
        for (j = 0; j < m; j++)
            scanf("%d", &max[i][j]);
    }

    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    printf("Enter Available Resources -- ");
    for (i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    char choice;
    printf("Enter New Request Details -- (y/n)? ");
    scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y') {
        int pid, req[m];
        printf("Enter pid -- ");
        scanf("%d", &pid);

        printf("Enter Request for Resources -- ");
        for (i = 0; i < m; i++)
            scanf("%d", &req[i]);

        bool canGrant = true;

        for (i = 0; i < m; i++) {
            if (req[i] > need[pid][i]) {
                canGrant = false;
                break;
            }
        }

        if (canGrant) {
            for (i = 0; i < m; i++) {
                if (req[i] > avail[i]) {
                    canGrant = false;
                    break;
                }
            }
        }

        if (canGrant) {
            for (i = 0; i < m; i++) {
                avail[i] -= req[i];
                alloc[pid][i] += req[i];
                need[pid][i] -= req[i];
            }
        } else {
            printf("Request cannot be granted.\n");
            return 1;
        }
    }

    for (i = 0; i < n; i++)
        finish[i] = 0;

    int count = 0;
    while (count < n) {
        bool found = false;
        for (i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                    printf("P%d is visited( ", i);
                    for (j = 0; j < m; j++) {
                        avail[j] += alloc[i][j];
                        printf("%d ", avail[j]);
                    }
                    printf(")\n");

                    finish[i] = 1;
                    safeSeq[count++] = i;
                    found = true;
                }
            }
        }

        if (!found) {
            printf("SYSTEM IS NOT IN SAFE STATE\n");
            return 1;
        }
    }

    printf("SYSTEM IS IN SAFE STATE\n");
    printf("The Safe Sequence is -- (");
    for (i = 0; i < n; i++) {
        printf("P%d", safeSeq[i]);
        if (i != n - 1) printf(" ");
    }
    printf(")\n");

    printf("\n%-10s %-20s %-20s %-20s\n", "Process", "Allocation", "Max", "Need");
    for (i = 0; i < n; i++) {
        printf("P%-9d", i);
        for (j = 0; j < m; j++)
            printf("%d ", alloc[i][j]);
        printf("        ");
        for (j = 0; j < m; j++)
            printf("%d ", max[i][j]);
        printf("        ");
        for (j = 0; j < m; j++)
            printf("%d ", need[i][j]);
        printf("\n");
    }

    return 0;
}
