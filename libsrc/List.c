#include <stdio.h>
#include <stdlib.h>
#include "List.h"

struct list * createList(int (*equals)(const void *,const void *),
                         char * (*toString)(const void *),
                         void (*freeObject)(void *))
{
    struct list *list;
    list = (struct list *) malloc(sizeof(struct list));
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    list->equals = equals;
    list->toString = toString;
    list->freeObject = freeObject;
    return list;
}

void freeList(struct list *list)
{
    if(list->head == NULL){
        free(list);
        return;
    }
    
    struct node *nextNode = list->head;
    void * temp;
    while(nextNode != NULL){
        temp = nextNode->next;
        freeNode(nextNode, list->freeObject);
        nextNode = temp;
    } 
    //free(list->head);
    free(list);
}

/*Return the size of the list
 *
 *
 */
int getSize(const struct list *list)
{
   return list->size;	//the list points to its size variable
}

int isEmpty(const struct list *list)
{
    
    return list->size == 0;
}

void addAtFront(struct list *list, struct node *node)
{
    if (list == NULL) return;
    if (node == NULL) return;
    list->size++;
    node->next = list->head;
    node->prev = NULL;
    if (list->head == NULL) {
        list->head = node;
        list->tail = node;
    } else {
        list->head->prev = node;
        list->head = node;
    }
}

void addAtRear(struct list *list, struct node *node)
{	
	if (list == NULL) return;
        if (node == NULL) return;

	node->prev = list->tail;
	node->next = NULL;
	if(list->head == NULL){
		list->head = node;
		list->tail = node;			
	}
	else{
		list->tail->next = node;
                node->prev = list->tail;
		list->tail = node;
		
	}
	list->size++;
	
}

struct node* removeFront(struct list *list)
{
    if(list == NULL) return NULL;
    if(list->head == NULL){ 
        return NULL;
    }
    if(list->head == list->tail){
        struct node *retVal = list->head;

        list->head = NULL;
        list->tail = NULL;
        list->size--;

        retVal->next = NULL;
        retVal->prev = NULL;
        return retVal;
    }
    else{
        struct node *retVal = list->head;
        struct node *nextNode = list->head->next;

        list->head = nextNode;
        list->head->prev = NULL;
        
        list->size--;

        retVal->next = NULL;
        retVal->prev = NULL;
        return retVal;
        
        
    }
    
    return NULL;
}

struct node* removeRear(struct list *list)
{
    if(list == NULL) return NULL;
    if(list->head == NULL){
        return NULL;
    }
    if(list->head == list->tail){
        struct node *retVal = list->head;

        list->head = NULL;
        list->tail = NULL;
        list->size--;

        retVal->next = NULL;
        retVal->prev = NULL;
        return retVal;
    }
    else{
        struct node *retVal = list->tail;
        struct node *prevNode = list->tail->prev;

        list->tail = prevNode;
    
        list->tail->next = NULL;
        
        list->size--;

        retVal->next = NULL;
        retVal->prev = NULL;
        return retVal;
        
    }
    return NULL;
}    

struct node* removeNode(struct list *list, struct node *node)
{
    if (list == NULL) return NULL;
    if (node == NULL) return NULL;
    
    if(list->head == NULL){
        return NULL;
    }

    if(list->head == node){
        return removeFront(list);
    }
    if(list->tail == node){
       return removeRear(list);
    }
    
    struct node *current = list->head;
    int found = 0;
    struct node *retVal;
    while (found != 1 && current != NULL){
        current = current->next;
        if(current == node){
            retVal = current;
            current->prev->next = current->next;
            current->next->prev = current->prev;

            list->size--;
            found = 1;
        }
        
    }
    if(found == 1){
        retVal->next = NULL;
        retVal->prev = NULL;
        return retVal;
    }
    return NULL;
}


struct node* search(const struct list *list, const void *obj)
{
 if(list == NULL) return NULL;
    if(obj == NULL) return NULL;
    
    if(list->head == NULL){
        return NULL;
    }
    
    struct node *current = list->head;
    int found = 0;
    struct node *retVal;
    while(found != 1 && current != NULL){
        if(list->equals(current, obj)){
            retVal = current;
            found = 1;
            
        }
        else{
            current = current->next;
        }
    }
    
    if(found == 1){
       
        return retVal;
    }
    return NULL; 
}

void reverseList(struct list *list)
{
    if(list == NULL) return;
    if(list->head == NULL) return;
    if(list->head == list->tail) return;
    
    struct node *pivot = list->tail;
    while(pivot->prev != NULL){
        addAtRear(list, removeNode(list, pivot->prev));
        
    }
}

void printList(const struct list *list)
{
    if (!list) return; //list was null!!
    int count = 0;
    char *output;
    struct node *temp = list->head;
    while (temp) {
        output = list->toString(temp->obj);
        printf(" %s -->",output);
        free(output);
        temp = temp->next;
        count++;
        if ((count % 6) == 0)
            printf("\n");
    }
    printf(" NULL \n");
}
