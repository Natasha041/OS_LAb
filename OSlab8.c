#include <stdio.h>
#include <stdlib.h>

int main() {
    int processCount, resourceCount;
    
    // Input number of processes and resources
    printf("Enter the number of processes: ");
    scanf("%d", &processCount);
    printf("Enter the number of resources: ");
    scanf("%d", &resourceCount);

    // Matrix for allocated resources
    int allocated[processCount][resourceCount];
    // Matrix for maximum resources required by each process
    int maxRequired[processCount][resourceCount];
    // Array for available resources
    int available[resourceCount];
    // Matrix for resources still needed by each process
    int need[processCount][resourceCount];
    // Flag array to mark if process is part of a safe sequence
    int finished[processCount];

    // Initialize all processes as unfinished
    for (int i = 0; i < processCount; i++) {
        finished[i] = 0;
    }

    // Input allocated resources
    printf("\nEnter the allocation table:\n");
    for (int i = 0; i < processCount; i++) {
        printf("Resources allocated to process %d: ", i + 1);
        for (int j = 0; j < resourceCount; j++) {
            scanf("%d", &allocated[i][j]);
        }
    }

    // Input maximum resources required
    printf("\nEnter the maximum resource requirements table:\n");
    for (int i = 0; i < processCount; i++) {
        printf("Maximum resources for process %d: ", i + 1);
        for (int j = 0; j < resourceCount; j++) {
            scanf("%d", &maxRequired[i][j]);
        }
    }

    // Input available resources
    printf("\nEnter the available resources:\n");
    for (int j = 0; j < resourceCount; j++) {
        scanf("%d", &available[j]);
    }

    // Calculate the need matrix
    printf("\nNeed Table:\n");
    for (int i = 0; i < processCount; i++) {
        for (int j = 0; j < resourceCount; j++) {
            need[i][j] = maxRequired[i][j] - allocated[i][j];
            printf("%d\t", need[i][j]);
        }
        printf("\n");
    }

    // Request handling
    int requestProcess;
    int request[resourceCount];

    printf("\nEnter the process number for the resource request (1 to %d): ", processCount);
    scanf("%d", &requestProcess);
    
    printf("Enter the resource request for process %d:\n", requestProcess);
    for (int j = 0; j < resourceCount; j++) {
        scanf("%d", &request[j]);
    }

    // Check if the request can be granted
    int requestValid = 1;
    for (int j = 0; j < resourceCount; j++) {
        if (request[j] > need[requestProcess - 1][j]) {
            requestValid = 0;
            break;
        }
    }

    if (requestValid) {
        int availableSufficient = 1;
        for (int j = 0; j < resourceCount; j++) {
            if (request[j] > available[j]) {
                availableSufficient = 0;
                break;
            }
        }
        
        if (availableSufficient) {
            for (int j = 0; j < resourceCount; j++) {
                available[j] -= request[j];
                allocated[requestProcess - 1][j] += request[j];
                need[requestProcess - 1][j] -= request[j];
            }
            printf("\nRequest granted.\n");
        } else {
            printf("\nRequest denied due to insufficient available resources.\n");
        }
    } else {
        printf("\nRequest denied as it exceeds the need.\n");
    }

    // Print updated tables
    printf("\nUpdated Need Table:\n");
    for (int i = 0; i < processCount; i++) {
        for (int j = 0; j < resourceCount; j++) {
            need[i][j] = maxRequired[i][j] - allocated[i][j];
            printf("%d\t", need[i][j]);
        }
        printf("\n");
    }

    printf("\nUpdated Allocation Table:\n");
    for (int i = 0; i < processCount; i++) {
        for (int j = 0; j < resourceCount; j++) {
            printf("%d\t", allocated[i][j]);
        }
        printf("\n");
    }

    printf("\nUpdated Available Table:\n");
    for (int j = 0; j < resourceCount; j++) {
        printf("%d\t", available[j]);
    }
    printf("\n");

    // Determine if a safe sequence exists
    printf("\nSafe Sequence Determination:\n");
    for (int i = 0; i < processCount; i++) {
        if (finished[i] == 0) {
            int canFinish = 1;
            for (int j = 0; j < resourceCount; j++) {
                if (need[i][j] > available[j]) {
                    canFinish = 0;
                    break;
                }
            }
            if (canFinish) {
                finished[i] = 1;
                for (int j = 0; j < resourceCount; j++) {
                    available[j] += allocated[i][j];
                }
                printf("Process %d can safely finish.\n", i + 1);
            }else{
                printf("Process %d can not safely finish.\n", i + 1);
            }
        }
    }

    return 0;
}
