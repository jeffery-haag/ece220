#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* This code performs operations on matrices. It loads in matrices from a text file into a linked list, orders them, 
 * removesduplicates, and zeros. It can also perform multiplication and addition on the matrices. It then
 * writes the matrices to a text file, and frees associated memory
 * Partners: briants2, jrhaag2
*/

void swap(sp_tuples_node *a, sp_tuples_node *b);
void sortMat(sp_tuples * matS);

sp_tuples * load_tuples(char* input_file)
{
    char matrix[1000000];
    int i=0, count=0;
    char garb;
    int row, col;
    double value;
    int swapped, adata, bdata;
    int place1, place2;
   
    sp_tuples_node *ptr1;
    sp_tuples_node *ptr2;
    sp_tuples_node *temp = NULL;
    sp_tuples_node *lptr = NULL;
    sp_tuples_node *prev = NULL;
  
    FILE* file = fopen(input_file, "r");
    while(fgets(&matrix[i++], sizeof(char)+1, file) != NULL); //Get matrix file
    fclose(file);
   
    char more[strlen(matrix)];
   
    sp_tuples * mat_t = (sp_tuples*)malloc(sizeof(sp_tuples)); //Allocate memory for main struct
   
    (*mat_t).tuples_head=NULL; //Initialize pointer
   
    sscanf(matrix, "%d%d%c%[^,]s", &(*mat_t).m, &(*mat_t).n, &garb, more); //Get dimensions of matrix
   
    for(i=0; i<sizeof(more); i++)
    {
      if (more[i] == '\n') count++; //Count number of non-zero cells
      if (more[i-1] == '\n' && more[i-2] == '\n') count--;
    }
    (*mat_t).nz = count;
   
    //BUILD LINKED LIST (Done)
    for(i=0; i<count; i++)
    {
      //INSERT NEW NODE HERE
      sp_tuples_node * new_node = (sp_tuples_node*)malloc(sizeof(sp_tuples_node)); //Create new node
      sp_tuples_node * last = (*mat_t).tuples_head; //Create a node for head
     
      sscanf(more, "%d%d%lf%c%[^,]s", &row, &col, &value, &garb, more); //Get data
     
      new_node->row = row; //Fill in data in new node
      new_node->col = col; //Fill in data in new node
      new_node->value = value; //Fill in data in new node
      new_node->next = NULL;
      if((*mat_t).tuples_head == NULL)
      {
        (*mat_t).tuples_head = new_node; //Set current node to head if list is empty
      }
      else
      {
        while(last->next != NULL)
        {
          last = last->next; //Step through list until the end
        }
        last->next = new_node; //Change pointer of last node
      }
    }
   
    //REMOVE DUPLICATES (Done)
    ptr1 = (*mat_t).tuples_head;
    while (ptr1->next != NULL)
    {
      place1 = (((*ptr1).row * (*mat_t).n) + (*ptr1).col);
      ptr2 = ptr1->next;
      while (ptr2->next != NULL)
      {
        place2 = (((*ptr2).row * (*mat_t).n) + (*ptr2).col);
        if (place1 == place2 && ptr1 == (*mat_t).tuples_head) //Delete first node
        {
          temp = (*mat_t).tuples_head;
          (*mat_t).tuples_head = (*ptr1).next;
          free(temp);
          (*mat_t).nz--;
        }
        else if (place1 == place2) //Delete regular
        {
          temp = ptr1;
          (*prev).next = (*ptr1).next;
          free(temp);
          (*mat_t).nz--;
        }
        ptr2 = ptr2->next;
      }
      prev = ptr1;
      ptr1 = ptr1->next;
    }
   
    //REMOVE ZEROS (Done)
    ptr1 = (*mat_t).tuples_head;
    while(ptr1->next != NULL)
    {
      if(ptr1->value == 0.0 && ptr1 == (*mat_t).tuples_head) //Delete first node
      {
        temp = (*mat_t).tuples_head;
        (*mat_t).tuples_head = (*ptr1).next;
        free(temp);
        (*mat_t).nz--;
      }
      else if (ptr1->value == 0.0 && ptr1->next->value == 0.0) //Remove 2 zeros in a row
      {
        temp = (*ptr1).next;
        (*prev).next = (*(*ptr1).next).next;
        free(temp);
        (*mat_t).nz--;
      }
      else if (ptr1->value == 0.0) //remove regular zero
      {
        temp = ptr1;
        (*prev).next = (*ptr1).next;
        free(temp);
        (*mat_t).nz--;
      }
      prev = ptr1;
      ptr1 = ptr1->next;
    }
    if((*ptr1).value == 0.0 && (*ptr1).next == NULL) //Delete last node
    {
      (*prev).next = NULL;
      free(ptr1);
      (*mat_t).nz--;
    }
   
    //SORT LINKED LIST (gucci bubble sort) (Done)
    while (swapped)
    {
      swapped=0;
      ptr1 = (*mat_t).tuples_head;
     
      while(ptr1->next != lptr)
      {
        adata = (((*ptr1).row * (*mat_t).n) + (*ptr1).col);
        bdata = (((*(ptr1->next)).row * (*mat_t).n) + (*(ptr1->next)).col);
        if (adata > bdata)
        {
          swap(ptr1, ptr1->next); //Swap nodes
          swapped=1;
        }
        prev = ptr1;
        ptr1 = ptr1->next;
      }
      lptr = ptr1;
    }
   
    ptr1 = (*mat_t).tuples_head;
    (*mat_t).nz = 0;
    while (ptr1->next != NULL) //Make sure nz is correct
    {
      (*mat_t).nz++;
      ptr1 = ptr1->next;
    }
    (*mat_t).nz++;
//    (*mat_t).nz
   
    return mat_t;
}





void sortMat(sp_tuples * matS)
{	
	sp_tuples_node * ptr1 = (*matS).tuples_head;
	sp_tuples_node * temp = NULL;
	sp_tuples_node * prev = (*matS).tuples_head;
	int nzcount=0;
	while(ptr1->next)//find m and n
	{
		ptr1=ptr1->next;
		nzcount++;
	}
		//matS->m=ptr1->row;
 		//matS->n=ptr1->col;
		matS->nz=nzcount;


    ptr1 = (*matS).tuples_head;
    while(ptr1->next != NULL)
    {
      if(ptr1->value == 0.0 && ptr1 == (*matS).tuples_head  && ptr1->next != NULL) //Delete first node
      {
        temp = (*matS).tuples_head;
        (*matS).tuples_head = (*ptr1).next;
        free(temp);
        (*matS).nz--;
      }
      if(ptr1->value == 0.0 && ptr1 == (*matS).tuples_head  && ptr1->next->value == 0.0) //Delete first node
      {
        temp = (*matS).tuples_head;
        (*matS).tuples_head = (*(*ptr1).next).next;
        free(temp);
        (*matS).nz--;
      }
      if (ptr1->value == 0.0 && ptr1->next != NULL )  // && ptr1->next->value == 0.0) //Remove 2 zeros in a row
      {
	  temp = prev;
	  while (ptr1->value == 0.0 && ptr1->next->next != NULL)
	  {
            prev = ptr1;
	    ptr1 = ptr1->next;
            free(prev);
            (*matS).nz--;
	  }
	  temp->next = ptr1;
      }
      else if (ptr1->value == 0.0 && ptr1->next->next == NULL)
      {
	temp = ptr1;
	prev->next = ptr1->next;
	free(temp);
	(*matS).nz--;
      }
      prev = ptr1;
      ptr1 = ptr1->next;
    }
    if((*ptr1).value == 0.0 && (*ptr1).next == NULL) //Delete last node
    {
      (*prev).next = NULL;
      free(ptr1);
      (*matS).nz--;
    }
    


int swapped, adata, bdata;
    //SORT LINKED LIST (gucci bubble sort) (Done)
    while (swapped)
    {
      swapped=0;
      sp_tuples_node *lptr = NULL;
      ptr1 = (*matS).tuples_head;
     
      while(ptr1->next != lptr)
      {
        adata = (((*ptr1).row * (*matS).n) + (*ptr1).col);
        bdata = (((*(ptr1->next)).row * (*matS).n) + (*(ptr1->next)).col);
        if (adata > bdata)
        {
          swap(ptr1, ptr1->next); //Swap nodes
          swapped=1;
        }
       // prev = ptr1;
        ptr1 = ptr1->next;
      }
      lptr = ptr1;
    }
   
    ptr1 = (*matS).tuples_head;
    (*matS).nz = 0;
    while (ptr1->next != NULL) //Make sure nz is correct
    {
      (*matS).nz++;
      ptr1 = ptr1->next;
    }
    (*matS).nz++;

    ptr1 = (*matS).tuples_head;
    while(ptr1->next != NULL)
    {
      if(ptr1->value == 0.0 && ptr1 == (*matS).tuples_head  && ptr1->next != NULL) //Delete first node
      {
        temp = (*matS).tuples_head;
        (*matS).tuples_head = (*ptr1).next;
        free(temp);
        (*matS).nz--;
      }
      if(ptr1->value == 0.0 && ptr1 == (*matS).tuples_head  && ptr1->next->value == 0.0) //Delete first node
      {
        temp = (*matS).tuples_head;
        (*matS).tuples_head = (*(*ptr1).next).next;
        free(temp);
        (*matS).nz--;
      }
      if (ptr1->value == 0.0 && ptr1->next != NULL )  // && ptr1->next->value == 0.0) //Remove 2 zeros in a row
      {
	  temp = prev;
	  while (ptr1->value == 0.0 && ptr1->next->next != NULL)
	  {
            prev = ptr1;
	    ptr1 = ptr1->next;
            free(prev);
            (*matS).nz--;
	  }
	  temp->next = ptr1;
      }
      else if (ptr1->value == 0.0 && ptr1->next->next == NULL)
      {
	temp = ptr1;
	prev->next = ptr1->next;
	free(temp);
	(*matS).nz--;
      }
      prev = ptr1;
      ptr1 = ptr1->next;
    }
    if((*ptr1).value == 0.0 && (*ptr1).next == NULL) //Delete last node
    {
      (*prev).next = NULL;
      free(ptr1);
      (*matS).nz--;
    }

return;
}  

double gv_tuples(sp_tuples * mat_t,int row,int col)

{
    //Should be done. hard to test
    sp_tuples_node * ptr;
    ptr = (*mat_t).tuples_head;
    while (ptr->next != NULL)
    {
      if (ptr->row == row && ptr->col == col)
	{
		return (ptr->value);
	}
      ptr = ptr->next;
    }
    if(ptr->next == NULL && ptr->row == row && ptr->col == col)return (ptr->value);
    return 0;
}



void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
    int place1, place2;
    sp_tuples_node * ptr;
    sp_tuples_node * temp=NULL;
    sp_tuples_node * prev=NULL;
    ptr = (*mat_t).tuples_head;
   
    //Delete node if val = 0
    if (value == 0)
    {
      while(ptr->next != NULL)
      {
        if(ptr->row == row && ptr->col == col && ptr == (*mat_t).tuples_head) //Delete first node
        {
          temp = (*mat_t).tuples_head;
          (*mat_t).tuples_head = (*ptr).next;
          free(temp);
          (*mat_t).nz--;
          return;
        }
        else if (ptr->col == col && ptr->row == row) //remove regular zero
        {
          temp = ptr;
          (*prev).next = (*ptr).next;
          free(temp);
          (*mat_t).nz--;
          return;
        }
        prev = ptr;
        ptr = ptr->next;
      }
      if((*ptr).row == row && ptr->col == col && (*ptr).next == NULL) //Delete last node
      {
        (*prev).next = NULL;
        free(ptr);
        (*mat_t).nz--;
        return;
      }
    }
   
    //Replace node value
    ptr = (*mat_t).tuples_head;
    while (ptr->next != NULL)
    {
      if (ptr->row == row && ptr->col == col && ptr == (*mat_t).tuples_head) //Delete first node
      {
        ptr->value = value;
        return;
      }
      else if (ptr->row == row && ptr->col == col) //Delete regular
      {
        ptr->value = value;
        return;
      }
      ptr = ptr->next;
    }
    if (ptr->row == row && ptr->col == col && ptr->next == NULL) //Delete final node
    {
      ptr->value = value;
      return;
    }
   
    //Add a new node
    ptr = (*mat_t).tuples_head;
    prev = NULL;
    place2 = ((row * (*mat_t).n) + col);
    while (ptr->next != NULL)
    {
      place1 = (((*ptr).row * (*mat_t).n) + (*ptr).col);
      if (place2 < place1 && ptr == (*mat_t).tuples_head) //Add new value at head
      {
        sp_tuples_node * new_node = (sp_tuples_node*)malloc(sizeof(sp_tuples_node));
        new_node->row = row;
        new_node->col = col;
        new_node->value = value;
        new_node->next = (*mat_t).tuples_head;
        (*mat_t).tuples_head  = new_node;
        (*mat_t).nz++;
        return;
      }
      if (place1 > place2) //Add node in interior of list
      {
        sp_tuples_node * new_node = (sp_tuples_node*)malloc(sizeof(sp_tuples_node));
        new_node->row = row;
        new_node->col = col;
        new_node->value = value;
        new_node->next = prev->next;
        prev->next  = new_node;
        (*mat_t).nz++;
        return;
      }
      prev = ptr;
      ptr = ptr->next;
    }
    //Add node at end of linked list
    sp_tuples_node * new_node = (sp_tuples_node*)malloc(sizeof(sp_tuples_node));
    new_node->row = row;
    new_node->col = col;
    new_node->value = value;
    new_node->next = NULL;
    prev->next  = new_node;
    (*mat_t).nz++;
    return;
}



void save_tuples(char * file_name, sp_tuples * mat_t)
{
  //seg faults
  FILE* file = fopen(file_name, "w+"); //Open new file
  sp_tuples_node * ptr;
  ptr = (*mat_t).tuples_head;
  fprintf (file, "%d %d\n", (*mat_t).m, (*mat_t).n);
  while (ptr->next != NULL)
  {
    fprintf (file, "%d %d %lf\n", ptr->row, ptr->col, ptr->value); //Print to file
    ptr = ptr->next;
  }
  if (ptr->next == NULL)
    fprintf (file, "%d %d %lf", ptr->row, ptr->col, ptr->value); //Print final line to file

  
  fclose(file); //Close file
    return;
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB)
{
	///sp_tuples_node * ptr1 = (*sp_tuples_node)malloc(sizeof(sp_tuples_node)) ;
	sp_tuples * matC = (sp_tuples*)malloc(sizeof(sp_tuples)); //Allocate memory for C struct
   
	if (matA->n >= matB->n) matC->n = matA->n;
	else matC->n = matB->n;
	if (matA->m >= matB->m) matC->m = matA->m;
	else matC->m = matB->m;

        (*matC).tuples_head=NULL; //Initialize pointer
	(*matC).nz=(*matA).nz;
	
	sp_tuples_node * ptrToa=matA->tuples_head;
	sp_tuples_node * ptrTob=matB->tuples_head;
	
	while(ptrToa->next !=NULL )   //this hsould go through a only stopping for nonzeros
    	{
	if (ptrToa->value !=0)
	{
      //INSERT NEW NODE HERE
      sp_tuples_node * new_node = (sp_tuples_node*)malloc(sizeof(sp_tuples_node)); //Create new node
      sp_tuples_node * last = (*matC).tuples_head; //Create a node for head
      new_node->row = ptrToa->row; //Fill in data in new node
      new_node->col = ptrToa->col; //Fill in data in new node
      new_node->value = ptrToa->value; //Fill in data in new node
      new_node->next = NULL;
  
      if((*matC).tuples_head == NULL)
      {
        (*matC).tuples_head = new_node; //Set current node to head if list is empty
      }
      else
      {
        while(last->next != NULL)
        {
          last = last->next; //Step through list until the end
        }
	last->next = new_node;
      	}
	ptrToa=(*ptrToa).next;
   	}
	}

	if(ptrToa->value !=0)//just covers last one
	{
		sp_tuples_node * new_node = (sp_tuples_node*)malloc(sizeof(sp_tuples_node)); //Create new node
      sp_tuples_node * last = (*matC).tuples_head; //Create a node for head
     
      new_node->row = ptrToa->row; //Fill in data in new node
      new_node->col = ptrToa->col; //Fill in data in new node
      new_node->value = ptrToa->value; //Fill in data in new node
      new_node->next = NULL;
      if((*matC).tuples_head == NULL)
      {
        (*matC).tuples_head = new_node; //Set current node to head if list is empty
      }
      else
      {
        while(last->next != NULL)
        {
          last = last->next; //Step through list until the end
        }
	last->next = new_node;
      }
	ptrToa=(*ptrToa).next;
	}
	
///////////////////FINSIHED WITH ADDNG A HERE//////////////
	int breaker=0;
	double cval=0;
	//sp_tuples_node * ptrTocPrev=matC->tuples_head;
	//sp_tuples_node * ptrToc=ptrTocPrev->next;
	sp_tuples_node * ptrToc=matC->tuples_head;
	ptrTob=matB->tuples_head;
	while(ptrTob->next !=NULL)
	{
	breaker=0;
	    if(ptrTob->value !=0)
	    {	
		//ptrTocPrev=matC->tuples_head;
		ptrToc=matC->tuples_head;
		while(ptrToc->next !=NULL)//checking if that row col is in c already
		{
			if((ptrToc->row == ptrTob->row) && (ptrToc->col == ptrTob->col))
			{
				cval=(gv_tuples(matC,(ptrToc->row),(ptrToc->col)));
				ptrToc->value=(cval+(ptrTob->value));
				//ptrToc->value=(6969);
				breaker=1;
				
			}
			ptrToc=ptrToc->next;
		}
		if(ptrToc->row==ptrTob->row && ptrToc->col==ptrTob->col)//just last value of matC
		{
			int cval=gv_tuples(matC,ptrTob->row,ptrTob->col);
			ptrToc->value=(cval+(ptrTob->value));
			breaker=1;
			
		}
	
		//if(breaker!=0)break;    //becuase shouldnt add to c if already added
		
		//ptrTocPrev=matC->tuples_head;
		//ptrToc=ptrToc->next;//resetting pounters

		//if(breaker==1)printf("FFFFFFFFFFFFF");
		if(breaker==0)set_tuples(matC, ptrTob->row, ptrTob->col, ptrToc->value); //its not in C so justa add new node.
	    }
	ptrTob=ptrTob->next;
	}
	if(ptrTob->value != 0.0)//this is just for last value of matB
	{
		ptrToc=matC->tuples_head;
		while(ptrToc->next !=NULL)//checking if that row col is in c already
		{
			if(ptrToc->row==ptrTob->row && ptrToc->col==ptrTob->col)
			{
				int cval=gv_tuples(matC,ptrTob->row,ptrTob->col);
				ptrToc->value=(cval+(ptrTob->value));
				breaker=1;
				
			}
			ptrToc=ptrToc->next;
		}
		if(ptrToc->row==ptrTob->row && ptrToc->col==ptrTob->col)//just last value of matC
		{
			int cval=gv_tuples(matC,ptrTob->row,ptrTob->col);
			ptrToc->value=(cval+(ptrTob->value));
			breaker=1;
		}
	
		
		//sp_tuples_node * ptrTocPrev=matC->tuples_head;
		//ptrToc=ptrTocPrev->next;//resetting pounter
		
		if (breaker==0)set_tuples(matC, ptrTob->row, ptrTob->col, ptrToc->value); //this just takes last value in B into C if doesnt match
	}
//after this there should be nothing in C that has row col of B


//fors last in B

		
	//sortMat(matC);//to sort it
    return matC;//retmat;
}



sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB)
{
	sp_tuples * matC = (sp_tuples*)malloc(sizeof(sp_tuples)); //Allocate memory for C struct
   
        (*matC).tuples_head=NULL; //Initialize pointer
	(*matC).nz=0;

	matC->n = matB->n;
	matC->m = matA->m;

	int count=((*matA).m * (*matB).n);//should be rowA times colB;
	for(int i=0; i<count; i++)//create c to werid size and empty
	{	
		
      		sp_tuples_node * new_node = (sp_tuples_node*)malloc(sizeof(sp_tuples_node)); //Create new node
      		sp_tuples_node * last = (*matC).tuples_head; //Create a node for head
     
      		new_node->row = -1; //Fill in data in new node
      		new_node->col = -1; //Fill in data in new node
      		new_node->value = 0; //Fill in data in new node
      		new_node->next = NULL;
      		if((*matC).tuples_head == NULL)
      		{
        		(*matC).tuples_head = new_node; //Set current node to head if list is empty
      		}
     		 else
     	        {
       			 while(last->next != NULL)
        		{
          		last = last->next; //Step through list until the end
        		}
        		last->next = new_node; //Change pointer of last node
      		}
    	}
	(*matC).nz=0;
///////////////////C should be right size ///////////
	sp_tuples_node * ptrToa=matA->tuples_head;
	sp_tuples_node * ptrTob=matB->tuples_head;
	sp_tuples_node * ptrToc=matC->tuples_head;
	while(ptrToa->next !=NULL)
	{
	    if(ptrToa->value !=0)
	    {
		int ia=ptrToa->row;
		int ja=ptrToa->col;
		ptrTob=matB->tuples_head;
		while(ptrTob->next !=NULL)
		{
		    if(ptrTob->value !=0 && ptrTob->row==ja)
		    {
			int breaker=0;
			ptrToc=matC->tuples_head;
            		while(ptrToc->next !=NULL && breaker==0)
            		{
                		if(ptrToc->value==0 && breaker==0 && ptrToc->row==-1) //im looking for empty value of c to feed into
                		{
                    			ptrToc->row=ia;
                    			ptrToc->col=ptrTob->col;
					double cValue=gv_tuples(matC,ia,ptrTob->col);
					double aValue=gv_tuples(matA,ia,ja);
					double bValue=gv_tuples(matB,ptrTob->row,ptrTob->col);

					ptrToc->value=(cValue+(aValue*bValue));

                   			breaker=1;
                		}
               
               			ptrToc=ptrToc->next;
            			}
				if(breaker==0)
				{
				    
            				ptrToc->row=ia;
                    			ptrToc->col=((ptrTob->col));
					double cValue=gv_tuples(matC,ia,((ptrTob->col)));
					double aValue=gv_tuples(matA,ia,ja);
					double bValue=gv_tuples(matB,ptrTob->row,((ptrTob->col)));
					ptrToc->value=(cValue+(aValue*bValue));
				    
				}
				
	

                	
			//sortMat(matC);
			
			//set_tuples(matC, ia, ptrTob->col, (cValue+(aValue*bValue)));
			(*matC).nz++;
			//matC->row=ia;
			//matC->col=(ptrTob->col);
			//this only works if that row col exists in all three
		    }
		    ptrTob=ptrTob->next;
		}
	    }
	    ptrToa=ptrToa->next;
	}
		//////////start////
if(ptrToa->value !=0)
	    {
		int ia=ptrToa->row;
		int ja=ptrToa->col;
		ptrTob=matB->tuples_head;
		while(ptrTob->next !=NULL)
		{
		    if(ptrTob->value !=0 && ptrTob->row==ja)
		    {
			int breaker=0;
			ptrToc=matC->tuples_head;
            		while(ptrToc->next !=NULL && breaker==0)
            		{
                		if(ptrToc->value==0 && breaker==0 && ptrToc->row==-1) //im looking for empty value of c to feed into
                		{
                    			ptrToc->row=ia;
                    			ptrToc->col=ptrTob->col;
					double cValue=gv_tuples(matC,ia,ptrTob->col);
					double aValue=gv_tuples(matA,ia,ja);
					double bValue=gv_tuples(matB,ptrTob->row,ptrTob->col);

					ptrToc->value=(cValue+(aValue*bValue));

                   			breaker=1;
                		}
               
               			ptrToc=ptrToc->next;
            			}
				if(breaker==0)
				{
				    
            				ptrToc->row=ia;
                    			ptrToc->col=((ptrTob->col));
					double cValue=gv_tuples(matC,ia,((ptrTob->col)));
					double aValue=gv_tuples(matA,ia,ja);
					double bValue=gv_tuples(matB,ptrTob->row,((ptrTob->col)));
					ptrToc->value=(cValue+(aValue*bValue));
				    
				}
				
	

                	
			//sortMat(matC);
			
			//set_tuples(matC, ia, ptrTob->col, (cValue+(aValue*bValue)));
			(*matC).nz++;
			//matC->row=ia;
			//matC->col=(ptrTob->col);
			//this only works if that row col exists in all three
		    }
		    ptrTob=ptrTob->next;
		}
	    }



		//////////end////////
	
	sortMat(matC);
    return matC;//matC;

}


   
void destroy_tuples(sp_tuples * mat_t){
      //seg faults
      sp_tuples_node * temp;
    sp_tuples_node * ptr;
    ptr = mat_t->tuples_head;
    while (ptr != NULL)
    {
      temp = ptr;
      ptr = ptr->next;
      free(temp);
    }
    free(mat_t);
    mat_t = NULL;
     
    return;
} 

void swap(sp_tuples_node *a, sp_tuples_node *b) //Works
{
  //works
  int row, col;
  double val;
 
  row = a->row;
  col = a->col;
  val = a->value;
  a->row = b->row;
  a->col = b->col;
  a->value = b->value;
  b->row = row;
  b->col = col;
  b->value = val;
  return;
}
