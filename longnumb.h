#include "linkedlist.h"
typedef struct number
{
  int sign;
  list_Node *head;
} number;


number* longNum_init();
int longNum_read(number **num, char first_el);
void longNum_delete(number **num);
