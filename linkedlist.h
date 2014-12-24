typedef struct list_Node
{
int value;
struct list_Node *next;
} list_Node;

void list_add(list_Node **head, int data);
void list_del(list_Node **head);
void list_del_first(list_Node **head);
void list_print(list_Node **head);
int list_size(list_Node **head);
void list_reverse(list_Node **head);
