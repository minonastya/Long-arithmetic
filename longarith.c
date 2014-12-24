#include <stdio.h>
#include "longarith.h"

void longNum_addition(number **num1, number **num2, number **res)
{
  list_Node *tmp1 = (*num1)->head;
  list_Node *tmp2 = (*num2)->head;
  int curr = 0;
  while(tmp1 != NULL || tmp2 != NULL)
  {
    if (tmp1 != NULL)
    {
      curr += tmp1->value;
      tmp1 = tmp1->next;
    }
    if (tmp2 != NULL)
    {
      curr += tmp2->value;
      tmp2 = tmp2->next;
    }
  list_add(&(*res)->head, curr % 10);
  curr /= 10;
  }
  if (curr) list_add(&(*res)->head, curr);
  return;
}



void longNum_substraction(number **num1, number **num2, number **res)
{
  list_Node *tmp = NULL;
  list_Node *tmp1 = (*num1)->head;
  list_Node *tmp2 = (*num2)->head;
  number *tmp3 = longNum_init();
  int curr = 0, less = 0, first = 1, digit = 0;
  (*res)->sign = 1;
  while(tmp1 != NULL || tmp2 != NULL)
  {
    if (tmp1 == NULL && curr) (less = 1);
    if (tmp1 != NULL)
    {
      curr += tmp1->value;
      tmp1 = tmp1->next;
    }
    if (tmp2 != NULL)
    {                                            
      curr -= tmp2->value;                          
      tmp2 = tmp2->next;                          
    }                                            
    if (curr < 0)
    {
      list_add(&tmp3->head, curr + 10); 
      curr = -1;
    }
    else
    {                                                 
      list_add(&tmp3->head, curr);                    
      curr = 0;                                       
    }                                                                     
  } 
  list_reverse(&tmp3->head);
  if (curr) (less = 1);
  if (less)
  {
    curr = 0;
    tmp = tmp3->head;
    while(tmp != NULL)
    {
      digit = 9 - (int)*(&tmp->value) + curr;
      if (first)
      {
        digit++;
        if (digit == 10)
        {
          digit = 0;
          curr = 1;
        }
        else (curr = 0);
        list_add(&(*res)->head, digit);
        first = 0;
      }
      else
      {
        if (digit == 10)
        {
          digit = 0;
          curr = 1;
        }
        else (curr = 0);
        list_add(&(*res)->head, digit);
      }
      tmp = tmp->next;
    }
    (*res)->sign = -1;
  }
  else
  {
    tmp = tmp3->head;
    while(tmp != NULL)
    {
      digit = (int)*(&tmp->value);
      list_add(&(*res)->head, digit);
      tmp = tmp->next;
    }
  }
  longNum_delete(&tmp3);
  return;
}


void longNum_multiplication(number **num1, number **num2, number **res)
{
  list_Node *tmp = NULL;
  list_Node *tmp1Mult = (*num1)->head;
  list_Node *tmp2Mult = (*num2)->head;
  number *tmp1Sum = longNum_init();
  number *tmp2Sum = longNum_init();
  number *tmpResSum = longNum_init();
  int digit = 0, less = 0, curr = 0, i = 0, count = 0;

  if (list_size(&(*num1)->head) < list_size(&(*num2)->head))
  {
    tmp1Mult = (*num2)->head;
    tmp2Mult = (*num1)->head;
    less = 1;
  }
  while(tmp2Mult != NULL)
  {
    digit = tmp2Mult->value;
    if (!less)
    tmp1Mult = (*num1)->head;
    else
    tmp1Mult = (*num2)->head;
    curr = 0;
    list_del(&tmp1Sum->head);
    while(tmp1Mult != NULL)
    {
      curr += digit * tmp1Mult->value;
      list_add(&tmp1Sum->head, curr % 10);
      curr /= 10;
      tmp1Mult = tmp1Mult->next;
    }
    if (curr)
    list_add(&tmp1Sum->head, curr);
    list_reverse(&tmp1Sum->head);
    for (i = 0; i < count; ++i)
    list_add(&tmp1Sum->head, 0);
    list_del(&tmpResSum->head);
    longNum_addition(&tmp1Sum, &tmp2Sum, &tmpResSum);
    list_del(&tmp2Sum->head);
    tmp = tmpResSum->head;
    while(tmp != NULL)
    {
      digit = (int)*(&tmp->value);
      list_add(&tmp2Sum->head, digit);
      tmp = tmp->next;
    }
    count++;
    tmp2Mult = tmp2Mult->next;
  }
  tmp = tmp2Sum->head;
  while(tmp != NULL)
  {
    digit = (int)*(&tmp->value);
    list_add(&(*res)->head, digit);
    tmp = tmp->next;
  }
  longNum_delete(&tmp1Sum);
  longNum_delete(&tmp2Sum);
  longNum_delete(&tmpResSum);
  return;
}


int input(number **num1, number **num2, number **res)
{
  char op, first_el, enter;
  int k = 0; 
  scanf("%c", &first_el);
  if (longNum_read(num1, first_el)) k++;
  scanf("%c", &op);
  scanf("%c", &enter);
  scanf("%c", &first_el);
  if (longNum_read(num2, first_el)) k++;
   if (k)
  {
    printf("Unknown command\n");
    return 1;
  }

  if (op == '+' || op == '-')
  {
    if ((*num1)->sign == (*num2)->sign)
    {
      if (op == '+') 
      longNum_addition(num1, num2, res);
      else 
      longNum_substraction(num1, num2, res);
    }
    else
    {
      if (op == '-') longNum_addition(num1, num2, res);
      else longNum_substraction(num1, num2, res);
    }
    (*res)->sign *= (*num1)->sign;
  }
  else
  {
    if (op == '*')
    longNum_multiplication(num1, num2, res);
  else
  {
    printf("Unknown command\n");
    return 1;
  }
    if ((*num1)->sign != (*num2)->sign)
    (*res)->sign *= (-1);
    else (*res)->sign = 1;
}
  
if ((*res)->sign == -1)
  printf("-");
  list_print(&(*res)->head);
  return 0;
}

int main(void)
{
  number *num1 = longNum_init();
  number *num2 = longNum_init();
  number *res = longNum_init();
  input(&num1, &num2, &res);
  longNum_delete(&num1);
  longNum_delete(&num2);
  longNum_delete(&res);
  return 0;
}
