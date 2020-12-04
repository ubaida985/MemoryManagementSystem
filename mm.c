#include <stdio.h>
#include <memory.h>
#include <unistd.h>
#include <D:\Projects\MemoryManagementSystem\mman-win32\trunk\mman.h>
//#include <sys/mman.h> //linux system

static size_t SYSTEM_PAGE_SIZE = 0;

void mm_init(){
    SYSTEM_PAGE_SIZE = getpagesize();//inbuilt function in unistd.h to return the size of one vm page
}

static void* mm_get_new_vm_page_from_kernel(int units){//it is an API and request unit number of VM
    //in order to allocate a page from mmap system call
    char *vm_page=mmap(0,units * SYSTEM_PAGE_SIZE,PROT_READ|PROT_WRITE|PROT_EXEC,MAP_ANON|MAP_PRIVATE,0,0);
    //first arguement can always be null, second is obvios, then you need the permisions so you take read write and execute permissions
    // | is or then you also have to specify the map as map anonymous or map private, and the last two arguements can always be null 


    if(vm_page==MAP_FAILED){
        printf("Error : VM Page allocation Failed\n");
        return NULL;
    }
    memset(vm_page,0,units*SYSTEM_PAGE_SIZE);
    //initializing the memory that has been assigned
    return (void *)vm_page;
    //returning the address of the virtual memory page that has been assigned
}


//api to release the vm pages back to the kernel
static void mm_return_vm_page_to_kernel(void *vm_page, int units){

    if(munmap(vm_page, units*SYSTEM_PAGE_SIZE)){
        //if this api succeeds in returning the page it returns 0
        printf("Error: Could not munmap the vm page");
    }
}

//main function
int main(int argc, char **argv){
    mm_init();
    //intializing our virtual memory page manager
    printf("VM Page size = %lu\n", SYSTEM_PAGE_SIZE);
    //print the global variable
    void *addr1 = mm_get_new_vm_page_from_kernel(1);
    //request a vm page 
    void *addr2 = mm_get_new_vm_page_from_kernel(1);
    //request another page.
    printf("Page 1 = %p, page 2 = %p\n", addr1, addr2);
    //you can subtract the address and check if the page were continous, they may or may not be continous
}