#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

typedef struct node Node;

struct node
{
  Point *point;
  Node *next;
};

struct list
{
  Node *first;
  Node *last;
};

List *initList(void)
{
  List *list = (List *)malloc(sizeof(List));
  list->first = NULL;
  list->last = NULL;

  return list;
}

void printList(List *list, FILE *f)
{
  Node *aux;

  for (aux = list->first; aux != NULL; aux = aux->next)
  {
    fprintf(f, "%s", returnId(aux->point));
    if (aux->next != NULL)
    {
      fprintf(f, ",");
    }
  }
  fprintf(f, "\n");
}

void printGroupList(List **list, int k, FILE *f)
{

  for (int i = 0; i < k; i++)
  {
    printList(list[i], f);
  }
};

void insertList(List *list, Point *point)
{

  Node *new = (Node *)malloc(sizeof(Node));
  new->point = point;

  //se for vazia
  if (list->first == NULL)
  {
    list->first = new;
    list->last = new;
  }
  list->last->next = new;
  list->last = new;
  new->next = NULL;
}

void destroyList(List *list)
{
  Node *p = list->first;
  Node *t = NULL;

  while (p != NULL)
  {
    t = p->next;
    free(p);
    p = t;
  }
  //liberando a sentinela
  free(list);
}

Point *returnFirst(List *list)
{
  return list->first->point;
}

void createGroupList(List **groupsList, Subset **subsetsArray, Point **pointsArray, int qtdGroups, int qtdPoints)
{
  int lengGroup = 0, posi;
  for (int i = 0; i < qtdGroups; i++)
  {
    groupsList[i] = initList();
  }
  int flag;

  for (int i = 0, posi = 0; i < qtdPoints; i++)
  {
    flag = 0;
    for (int j = 0; j < qtdPoints; j++)
    {
      if (returnParent(subsetsArray[j]) == i)
      {
        insertList(groupsList[posi], pointsArray[j]);

        flag = 1;
      }
    }
    if (flag)
    {
      posi++;
    }
  }
}

void sortLists(List **groupsList, int qtdGruops)
{
  qsort(groupsList, qtdGruops, sizeof(List *), compareLists);
}

int compareLists(const void *a, const void *b)
{
  List *x = *(List **)a;
  List *y = *(List **)b;
  return strcmp(returnId(returnFirst(x)), returnId(returnFirst(y)));
}

void destroyGroupList(List **groupsList, int qtdGroups)
{
  for (unsigned int i = 0; i < qtdGroups; i++)
  {
    destroyList(groupsList[i]);
  }
}