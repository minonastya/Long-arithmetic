#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

void list_del(list_Node **head)
{ 
  list_Node *tmp = *head;
  while (tmp != NULL)
  {
    *head = (*head)->next;
    free(tmp);
    tmp = *head;
  }
  return;
}


void list_add(list_Node **head, int data)
{
  list_Node *tmp = (list_Node*)malloc(sizeof(list_Node));
  tmp->value = data;
  tmp->next = *head;
  *head = tmp;
  return;
} 


int list_size(list_Node **head)
{
  list_Node *tmp = *head;
  int count = 0;
  while (tmp != NULL)
  {
    tmp = tmp->next;
    count++;
  }
  return count;
}


void list_print(list_Node **head)
{
  list_Node *tmp = *head;
  while (tmp != NULL)
  {
    printf("%d", tmp->value);
    tmp = tmp->next;
  }
  printf("\n");
  return;
}



void list_reverse(list_Node **head)
{
  list_Node *prev = NULL;
  list_Node *next = NULL;
  list_Node *curr = *head;
  while (curr) 
  {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }
  *head = prev;
  return;
}

void list_del_first(list_Node **head)
{
    list_Node *tmp = *head;
  if (tmp != NULL)
  {
    *head = (*head)->next;
    free(tmp);
  }
  return;
}
