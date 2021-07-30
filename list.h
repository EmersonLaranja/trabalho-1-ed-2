#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include "uf.h"

typedef struct list List;

List *initList();
void createGroupList(List **groupList, Subset **subsets, Point **pointsArray, int qtdGroups, int qtdPoints);
void printGroupList(List **list, int k, FILE *f);
void insertList(List *list, Point *point);
Point *returnFirst(List *list);
void printList(List *list, FILE *f);
void destroyGroupList(List **groupsList, int qtdGroups);
void sortLists(List **groupsList, int qtdGruops);
int compareLists(const void *a, const void *b);
void destroyList(List *list);

#endif /* LIST_H */