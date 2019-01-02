//
// Created by Mahan on 1/2/2019.
//

#include "MyFile.h"
#include "MyLinkedList.h"


#define DEBUG

struct Node *Add_Node(struct Problem_Unit info) {
    struct Node *tmp = malloc(sizeof(struct Node));

    tmp->data = info;
    tmp->next = NULL;
    return tmp;
}

void Remove_Node(struct Node **list, struct Node *target) {
    if (*list == target) {
        *list = target->next;
        free(target);
        return;
    }
    struct Node *current = *list;
    while (current->next != target)
        current = current->next;
    current->next = target->next;
    free(target);
}

struct Node *Random_Node_Finder(int *chance_sum, struct Node *list) {
    srand(time(NULL));
    int random_counter = rand() % (*chance_sum);

    struct Node *current = list;
    while (1) {
        random_counter -= (current->data).chance;
        if (random_counter <= 0) {
            ((current->data).chance)--;
            (*chance_sum)--;
            return current;
        }
        current = current->next;
    }
}

void Check_List(struct Node **list) {
    struct Node *current = *list;
    while (current != NULL) {
        if (((current->data).chance) == 0) {
            struct Node *tmp = current;
            current = current->next;
            Remove_Node(list, tmp);
        } else
            current = current->next;
    }
}

void Print_List(struct Node *list){
    for(struct Node * current = list; current != NULL; current = current->next){
        struct Problem_Unit tmp = current->data;
        puts(tmp.problem);
        puts(tmp.choice1);
        printf("Peaple: %d Court: %d Trasury: %d\n", tmp.people1, tmp.court1, tmp.treasury1);
        puts(tmp.choice2);
        printf("Peaple: %d Court: %d Trasury: %d\n", tmp.people2, tmp.court2, tmp.treasury2);
        printf("Chance: %d\n",tmp.chance);
    }

}


struct Node *Create_List() {
    struct Node *list = NULL, *current = NULL;
    int n = 1;
    while (1) {
        FILE *fp = Open_In_File(n);
        if (fp == NULL)
            break;
        struct Problem_Unit tmp;
        tmp = Scan_In_Problem(fp);
        if (list == NULL) {
            list = Add_Node(tmp);
            current = list;
        } else {
            current->next = Add_Node(tmp);
            current = current->next;
        }
        n++;
    }
    return list;
}