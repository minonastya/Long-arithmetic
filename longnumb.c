#include <stdio.h>
#include <stdlib.h>
#include "longnumb.h"


number* longNum_init()
{
  number *tmp = (number*) malloc(sizeof(number));
  tmp->sign = 1;
  tmp->head = NULL;
  return tmp;
}

int longNum_read(number **num, char first_el)
{
  int check = 0; 
  if (first_el == '-') ((*num)->sign = -1);
  else if (first_el < '0' && first_el > '9' && first_el != '-') (check = 1);
  else list_add(&(*num)->head, (int)first_el - (int)'0');
    
  while (1)
  { 
    char digit; 
    scanf("%c", &digit);
    if (digit >= '0' && digit <= '9') (list_add(&(*num)->head, (int)digit - (int)('0')));
    else if ((int)digit == 10 || digit == ' ')
    {
      if ((int)digit == 10) break;
      else 
      { 
        scanf("%c", &digit);
        while ((int)digit != 10)
        { 
          if (digit == ' ') scanf("%c", &digit);
          else 
          check = 1;
            
        }
      }
     return check; 
    }
  }
  return check;
}



void longNum_delete(number **num) 
{
  list_del(&(*num)->head);
  (*num)->sign = 1;
  return;
}
