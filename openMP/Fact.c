#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#define N 5
#define I 15

struct node {
   int data;
   int factdata;
   struct node* next;
};


int fact(int n) {
   if(n>=1)
      return n*fact(n-1);
    else
      return 1;
}

void processwork(struct node* p)
{
   int n;
   n = p->data;
   p->factdata = fact(n);
}


struct node* init_list(struct node* p) {
    int i;
    struct node* head = NULL;
    struct node* temp = NULL;

    head = (struct node*)malloc(sizeof(struct node));
    p = head;
    p->data = I;
    p->factdata = 0;
    for (i=0; i< N; i++) {
       temp  =  (struct node*)malloc(sizeof(struct node));
       p->next = temp;
       p = temp;
       p->data = I+1;
       p->factdata = 0;
    }
    p->next = NULL;
    return head;
}


int main(int argc, char *argv[]) {
     double start, end;
     struct node *p=NULL;
     struct node *temp=NULL;
     struct node *head=NULL;

	 printf("Process linked list\n");
     printf("  Each linked list node will be processed by function 'processwork()'\n");
     printf("  Each ll node will compute factorial of randomly generated numbers\n");

     p = init_list(p);
     head = p;
     start = omp_get_wtime();
     {
        while (p != NULL) {
		   processwork(p);
		   p = p->next;
        }
     }
     end = omp_get_wtime();
     p = head;
	 while (p != NULL) {
        printf("%d : %d\n",p->data, p->factdata);
        temp = p->next;
        free (p);
        p = temp;
     }
	 free (p);
     printf("Compute Time: %f seconds\n", end - start);
     return 0;
}
