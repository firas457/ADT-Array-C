#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "AdptArray.h"
#include "book.h"
#include "Person.h"


#define INITIAL_SIZE 2

// struct contains capicity to check array capicity
//PElement* adpt_array: the array that well implement the adaptive dynamic array
struct AdptArray_ {

    int capicity;
    PElement* adpt_array;
    COPY_FUNC copy_element;
    DEL_FUNC free_element;
    PRINT_FUNC print_element;

};

//constructor for creating new adaptive array
PAdptArray CreateAdptArray(COPY_FUNC copy_element, DEL_FUNC free_element, PRINT_FUNC print_element) {

    PAdptArray arr = malloc(sizeof(struct AdptArray_));

    if (arr == NULL) {
        return NULL;
    }

    arr->capicity=INITIAL_SIZE;
  
    arr->adpt_array=malloc(arr->capicity * sizeof(PElement));
   
    for(int i=0;i<arr->capicity;i++){
        arr->adpt_array[i]=NULL;
    }

    arr->copy_element = copy_element;
    arr->free_element = free_element;
    arr->print_element = print_element;

    return arr;
}


//free all the new copies that have been added to adaptive array
//free previously allocated memories for arr(input array), and the adaptive array inside arr.
void DeleteAdptArray(PAdptArray arr) {
    if (arr == NULL) {
        return;
    }

      for (int i = 0; i < arr->capicity; i++) {
        if (arr->adpt_array[i] != NULL) {
            arr->free_element(arr->adpt_array[i]);
        }
      }
  
    
    free(arr->adpt_array);
     
    free(arr);
  
    
 
}

//set a new element at specific index inside the adaptive array
// a new copy of the new elemnt well be added to the array
Result SetAdptArrayAt(PAdptArray arr, int index, PElement element) {
    
    if (index < 0) {
        return FAIL;
    }
   
    if (index >= arr->capicity) {
        
        int newSize = index + 1;
          
       PElement *newArray = malloc(sizeof(PElement) * newSize);
       
        if (!newArray) {
            return FAIL;
        }

        for (int i = 0; i < arr->capicity; i++) {
            newArray[i] = arr->adpt_array[i];
        }
      
         for (int i = arr->capicity; i < newSize; i++) {
            if(i==index){
        
            newArray[i] =arr->copy_element(element);
         
        
            }
            else{
                newArray[i]=NULL;
            }

        }

        free(arr->adpt_array);
        
        arr->adpt_array = newArray;
        arr->capicity=newSize;
       
        return SUCCESS;

        }
  
    else if (index < arr->capicity) {

        if( arr->adpt_array[index] != NULL){
        arr->free_element(arr->adpt_array[index]);
        arr->adpt_array[index] =arr->copy_element(element);
        free(element);

        return SUCCESS;

        }

        arr->adpt_array[index] =element;
        return SUCCESS;
    }

    
     return FAIL;
   
}

//get element at specific index
PElement GetAdptArrayAt(PAdptArray arr, int index) {
    
    if (index < 0 || index >= arr->capicity || arr->adpt_array[index] ==NULL) {
        return NULL;
    }
    
    PElement b1=arr->copy_element(arr->adpt_array[index]);
  
    return b1;

    }

//get the size of the addaptive array
int GetAdptArraySize(PAdptArray arr) {
    
     if(arr==NULL){
        return -1;
    }
    
    return arr->capicity;

}


//print all the elments inside the adaptive array
void PrintDB(PAdptArray arr) {
  
    for (int i = 0; i < arr->capicity; i++) {

        if(arr->adpt_array[i]!=NULL){

        arr->print_element(arr->adpt_array[i]);
        }

    }

}
