#include <stdio.h>
#include <unistd.h>  
#include "pt.h"      

struct pt pt1, pt2, pt3;

int thread1(struct pt *pt) {
    PT_BEGIN(pt); 

    while (1) {
        printf("[Thread 1] Running every 1 second\n");
        PT_YIELD(pt); 
    }

    PT_END(pt); 
}

int thread2(struct pt *pt) {
    static int counter = 0; //why is it static??
    PT_BEGIN(pt);

    while (1) {
        PT_WAIT_UNTIL(pt, counter >= 3); 
        printf("[Thread 2] Running every 3 seconds\n");
        counter = 0;
    }

    PT_END(pt);
}

int thread3(struct pt *pt) {
    static int user_input;
    PT_BEGIN(pt);

    while (1) {
        printf("[Thread 3] Enter a number (0 to stop): ");
        scanf("%d", &user_input);
        
        if (user_input == 0) {
            printf("[Thread 3] Stopping protothreads...\n");
            exit(0);
        }

        printf("[Thread 3] You entered: %d\n", user_input);
        PT_YIELD(pt);
    }

    PT_END(pt);
}


int main() {
    PT_INIT(&pt1);
    PT_INIT(&pt2);
    PT_INIT(&pt3);

    int counter = 0;

    while (1) {
        thread1(&pt1);
        thread2(&pt2);
        thread3(&pt3);

        sleep(1); 
        counter++; 
    }

    return 0;
}
