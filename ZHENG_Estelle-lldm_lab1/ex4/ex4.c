#include <stdio.h>
#include <string.h>     // to use strlen
#include <unistd.h>     // I/O syscall
#include <sys/types.h>  // I/O syscall
#include <sys/stat.h>   // I/O syscall
#include <fcntl.h>      // I/O syscall
#include <sys/mman.h>   // MMAP syscall

int main(){
    int fd;                                         // fd is the file descriptor
    char buff1[10] = "Hello!";                      // buff is the message that is written
    char buff2[10];                                 // buff that is read
    int size;                                       // size of what is read

    int *map_ptr;                                   // pointer of the mapping
    int unmap;                                      // boolean to know if unmap

    /* open the "hello.txt" file if it exists, if not, creates it in this directory.
    We want to read and write on it.
    Return the fd of this file, usually 3. */
    fd = open("hello.txt", O_CREAT | O_RDWR); 

    /* write the buff1 message in the fd. 
    strlen is the size of the buff1 (= number of bytes). */ 
    write(fd, buff1, strlen(buff1));                

    /* read the content of the file (= fd of the file) with an empty buff2 of exactly the same size as buff1. */
    size = read(fd, buff2, strlen(buff2));

    /* must not forget the '\0' at the end. */
    buff2[size] = 0;                                

    /* used to prinf the content of the file. 
    fd = 1 because it is the standard ouput.
    buff2 of what we want to read (which is in fact the opened file).
    size is the size of what is read. */
    write(1, buff2, size);

    /* must not forget to close the opened file to free the fd. */
    close(fd);

    /* mapping a region of the memory, which is just allocating a memory space.
    NULL means the kernel will choose itself an adress to allocate the memory.
    5*sizeof(int) is number of bytes needed to be mapped, the 5 also represents the number of array.
    PROT_READ | PROT_WRITE to permet the access as reading and writing.
    MAP_PRIVATE | MAP_ANONYMOUS to not share the mapping region with others and to not connect any file to this region.
    fd = 0, because it is the standard input.
    offset = 0, the start of the file mapping.
    */
    map_ptr = mmap ( NULL, 5*sizeof(int), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0 );

    /* This is just to have a visual representation of whether the mapping region has been allocated or not. */
    printf("The elements of the array: ");
    for(int i=0; i<5; i++){
        map_ptr[i] = i;
        printf("[%d] ",map_ptr[i]);
    }
    printf("\n");

    /* unmapping the mapping region.
    map_ptr represents the allocate memory region.
    5*sizeof(int) is still the lenght of this allocate memory region. */
    unmap = munmap(map_ptr, 5*sizeof(int));

    /* To check if the unmapping was a success or not. */
    if(unmap == 0)
        printf("Unmapping sucessfully!\n");
    else
        printf("Error: unmapping failed.\n");

    return 0;
}