#include <stdio.h>
#include <stdlib.h>

#include <sys/mman.h>   // for mmap
#include <string.h>     // for string
#include <unistd.h>
#include <fcntl.h>
#include <time.h>       // for the time


/* Create a shared memory in given a size*/
void* createSharedMem(int size) {
    /* 

    The memory buffer is going to be readable and writable.
    The memory is going to be shared with other processes, but only with its own process and its children. 
    fd = 0, because it is the standard input.
    offset = 0, the start of the file mapping..

    */
    int access = PROT_READ | PROT_WRITE;
    int share = MAP_SHARED | MAP_ANONYMOUS;

    return mmap(NULL, size, access, share, 0, 0);
}

int main() {
	/* initialising the pid by doing a fork of a child process*/
	pid_t pid;
	pid = fork();

    /* the MAX size (in bytes) of shared memory object */
    const int SIZE = 4096;

    /* the memory itself, also the pointer to shared memory obect. */
    void *shm_ptr = createSharedMem(SIZE);

    /* message sent by Parent and Child of a maximun size of 4096 */
	char messageParent[SIZE];
    char messageChild[SIZE];


    /* Error occured */
    if(pid < 0){
        printf("Fork failed\n");
        return 1;
    }
    while(1){
        /* Child process */
        if(pid == 0){
            printf("Child wrote: ");
            /* Input the actual message written by Child process */
            fgets(messageChild, 100, stdin);
            /* Write to the (allocated) shared memory object */
            sprintf(shm_ptr, "%s", messageChild);
            
            sleep(1);

            /* Print what was written by Parent process, in other means, what is read by Child process */
            printf("Child read: %s\n", shm_ptr);
        } 
        /* Parent process */
        else {
            printf("Parent wrote: ");
            /* Input the actual message written by Parent process */
            fgets(messageParent, SIZE, stdin);
            /* Write to the (allocated) shared memory object */
            sprintf(shm_ptr, "%s", messageParent);

            sleep(1);

            /* Print what was written by Child process, in other means, what is read by Parent process */
            printf("Parent read: %s\n", shm_ptr);   
        }
    }
    return 0;
}