//defining all the data structures our linux memory manager is going to use

//first is the virtual memory page family
typedef struct vm_page_family{
    
    //the first is going to define the which application is registering with the linux memory page manager
    char struct_name[MM_MAX_STRUCT_NAME];
    
    //will contain the size of the structure
    uint32_t struct_size;

}vm_page_family_t;


//virtual memory page for families
//this structure is going to be used to save the first structure ie the array of vm pages
typedef struct vm_page_for_families_ {

    //a pointer to the next memory page for the families ds
    struct vm_page_for_families *next;

    //a pointer to the array of objects of type vm page family
    vm_page_family_t vm_page_family[0];

};typedef struct vm_page_for_families_t;

#define MAX_FAMILIES_PER_VM_PAGE    \
    (SYSTEM_PAGE_SIZE - sizeof(vm_page_for_families *))/sizeof(vm_page_family_t);

//looping macro to iterate over the page family object of the virtual memory page
//count tracks the nunmber of page family objects that are present in the vm page
//in order to ensure that we don't overshoot the max limit of the vm page we woll have to check the condition 
//count<MAX_FAMILIES_PER_VM_PAGE
#define ITERATE_PAGE_FAMILIES_BEGIN(vm_page_for_families_ptr, curr)           \
{                                                                              \
    uint32_t count = 0;                                                         \
    for(curr=(vm_page_family_t *)&vm_page_for_families_ptr->vm_page_family[0];   \
    curr->struct_size && count< MAX_FAMILIES_PER_VM_PAGE;                         \
    curr++,count++){
        
#define ITERATE_PAGE_FAMILY_ENDS(vm_page_for_families_ptr, curr) }}