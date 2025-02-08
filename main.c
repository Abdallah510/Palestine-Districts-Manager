#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#define size 30
//definitions
typedef struct node* list;
typedef struct node* node;
//struct
struct node{
    char name[20];
    int population;
    struct node* next;
    struct node* previous;
     char data;
     struct node* r;
};
//global variables
struct node* radix[27];
struct node* districts[size];
int numOfDistrict =0;
//flags
int isSorted =0;
//functions
list makeEmpty(list l);
void insert(char town_name[50],int population,list l);
void load(int* numOfDistrict);
void printInputFile();
void init_radix();
int find_max_length_of_districts();
void extend_String();
void Delete_radix();
void radix_sort();
void print();
void Sum();
void add_town();
void delete_town();
void delete_district();
void calc();
void print_no_detail();
void change_population();
void save();
void reExtendString();
void insert_radix();
void sort_towns();
void add_district();
//==========================
int main()
{
    init_radix();
    int op;
do{
    printf("\nmenu\n");
    printf("1.load the input file\n");
    printf("2.print loaded information from the input file\n");
    printf("3.sort the districts alphabetically\n");
    printf("4.Sort the towns for each district based on population in ascending order\n");
    printf("5.Print the sorted information\n");
    printf("6.Add a new district to the list of sorted districts\n");
    printf("7.Add a new town to a certain district\n");
    printf("8.Delete a town from a specific district\n");
    printf("9.Delete a complete district\n");
    printf("10.Calculate the population of Palestine and min and max town\n");
    printf("11.Print the districts and their total population\n");
    printf("12Change the population of a town\n");
    printf("13.Save to output file\n");
    printf("14.exit\n");
    printf("please enter an operation:");
    scanf("%d",&op);
    switch(op){
   case 1:
       load(&numOfDistrict);
        break;
   case 2:
       printInputFile();
        break;
   case 3:
     radix_sort();
        break;
    case 4:
        sort_towns();
        break;
    case 5:
        print();
        break;
    case 6:
        add_district();
        break;
    case 7:
        add_town();
        break;
    case 8:
        delete_town();
        break;
    case 9:
        delete_district();
        break;
    case 10:
        calc();
        break;
    case 11:
        print_no_detail();
        break;
    case 12:
        change_population();
        break;
    case 13:
        save();
        break;
    case 14:printf("exiting system.....");
        break;
    default:printf("not a correct operation!!...please enter a valid operation\n");
        break;

   }

  }while(op != 14);
}

list makeEmpty(list l){
    l=(list)malloc(sizeof(struct node));
    if(l==NULL)
        printf("memory is full");
    else
    l->next= NULL;
    l->previous = NULL;
    l->r =NULL;
    return l;
}
void insert(char town_name[50],int population,list l){
    node temp;
    temp =(node)malloc(sizeof(struct node));
    if(temp == NULL)
        printf("memory is full");
    else{
   strcpy(temp->name,town_name);
    temp->population = population;
    temp->next = l->next;
    l->next = temp;
    temp->previous = l ;
    if(temp->next !=NULL)
        temp->next->previous =temp;
    }
}
void load (int* numOfDistrict){
    char line[50];
    int population;
    char town[20],district[20];
    int i =0;

    FILE *input_file;
    input_file = fopen("districts.txt","r");
    if(input_file == NULL){
        printf("error opening file");
    }
    else{
    while(fgets(line,50,input_file)!=NULL){
        int reapeat = 0;
        char *ptr = strtok(line,"|");
        strcpy(district,ptr);
        ptr = strtok(NULL,"|");
        strcpy(town,ptr);
        ptr = strtok(NULL,"|");
        population = atoi(ptr);
        for(int g =0;g< *numOfDistrict;g++){
            if(strcasecmp(districts[g]->name,district)==0){
                insert(town,population,districts[g]);
                 Sum();
                reapeat =1;
                break;
        }
    }
    if(reapeat !=1){
    districts[i] = makeEmpty(NULL);
    strcpy(districts[i]->name,district);
    insert(town,population,districts[i]);
    (*numOfDistrict)++;
    Sum();
    i++;
    }
  }
   printf("\nfile was loaded successfully\n");
  fclose(input_file);
  }
}
void Sum(){
    node p;
    for(int i =0;i<numOfDistrict;i++){
        int sum = 0;
        p= districts[i]->next;
        while(p!=NULL){
            sum+=p->population;
            p=p->next;
        }
        districts[i]->population = sum;
    }
}
void printInputFile(){
    printf("\n");
    if(numOfDistrict==0){
        printf("there are no districts\n");
    }
    else{
    char line[50];
    FILE *input_file;
    input_file = fopen("districts.txt","r");
    if(input_file == NULL){
    printf("error opening file");
    }
    printf("\n");
    while(fgets(line,50,input_file)!=NULL){
        printf("%s\n",line);
    }

    }

}
void init_radix(){
    radix[0]=makeEmpty(NULL);
    radix[0]->data ='$';
    char dig='A';

    for(int i=1; i<27; i++){
          radix[i]=makeEmpty(NULL);
          radix[i]->data=dig;
        dig+=1;

    }

}

int find_max_length_of_districts(){
    int max = strlen(districts[0]->name);
    for(int i=1;i<numOfDistrict;i++){
        if(strlen(districts[i]->name)>max)
         max=strlen(districts[i]->name);
    }
    return max;
}
void extend_String(){
    int diff=0;
    int length = find_max_length_of_districts();
    for(int i = 0;i<numOfDistrict;i++){
            if(strlen(districts[i]->name)!= length){
                    diff = length - strlen(districts[i]->name);
                    for(int j=0;j<diff;j++){
                        strcat(districts[i]->name,"$");
                    }
            }
    }

}
void Delete_radix(){
    node p;
    node temp;

    for(int i=0;i<27;i++){
        if(radix[i]->r !=NULL){
                p=radix[i]->r;
                radix[i]->r = NULL;
                while(p!=NULL){
                    temp =p->r;
                    free(p);
                    p=temp;
                }

    }
}
}
void reExtendString(){
    for(int i=0;i<numOfDistrict;i++){
        char *ptr = strtok(districts[i]->name,"$");
        strcpy(districts[i]->name,ptr);
    }
}
void insert_radix(char dis_name[20],int population,node l,node town){
      node temp;
    temp =(node)malloc(sizeof(struct node));
    if(temp == NULL)
        printf("memory is full");
    else{
   strcpy(temp->name,dis_name);
    temp->population = population;
    temp->next= town;
    if(town!=NULL)
   town->previous=temp;
    temp->r = l->r;
    l->r = temp;
}
}
void radix_sort(){
    printf("\n");
    if(numOfDistrict==0){
        printf("there are no districts\n");
    }

    else{
    extend_String();
    int max_length = find_max_length_of_districts();
    char ch;
    int a;
    for(int i=max_length-1;i>=0;i--){
        for(int j=0;j<numOfDistrict;j++){
            ch=districts[j]->name[i];
            for(int k=0;k<27;k++){
                if(toupper(ch)==toupper(radix[k]->data)){
                        node p =radix[k];
                        while(p->r!= NULL)
                            p=p->r;
                        insert_radix(districts[j]->name,districts[j]->population,p,districts[j]->next);
                }

            }
        }

         a=0;
        for(int h=0;h<27;h++){
            if(radix[h]->r!=NULL){
                node q=radix[h]->r;
                    while(q!=NULL){
                    strcpy(districts[a]->name,q->name);
                    districts[a]->population = q->population;
                    districts[a]->next = q->next;
                    a++;
                    q = q->r;
                    }
            }
        }
       Delete_radix();
    }
    reExtendString();
    isSorted =1;
    printf("sort was successful\n");

    }

}
void sort_towns(){
    printf("\n");
    if(numOfDistrict == 0 ){
        printf("there are no districts\n");
    }
    for(int i=0;i<numOfDistrict;i++){
        node p = districts[i]->next;
        if(p==NULL)
            continue;
        int swapped;
        node current;
        node null=NULL;
        do{
            swapped=0;
            current=districts[i]->next;
            while(current->next!=null){
                if(current->population > current->next->population){
                    int temp_pop = current->population;
                    current->population=current->next->population;
                    current->next->population=temp_pop;
                    char temp_name[20];
                    strcpy(temp_name,current->name);
                    strcpy(current->name,current->next->name);
                    strcpy(current->next->name,temp_name);
                    swapped = 1;
                }
               current=current->next;
            }
            null = current;
        }while(swapped);
    }
    printf(" town sort was successful\n");

}
void print(){
     printf("\n");
    if(numOfDistrict == 0 ){
        printf("there are no districts\n");
    }
    else if(isSorted ==0){
        printf("districts are not sorted\n");
    }
    else{
        for(int i =0;i<numOfDistrict;i++){
        printf("%s district,population = %d \n",districts[i]->name,districts[i]->population);
        node p= districts[i]->next;
        while(p!=NULL){
            printf("%s,%d\n",p->name,p->population);
            p=p->next;
        }

       }

    }
}
void add_district(){
    char name[20];
    int flag = 0;
     printf("\n");
    printf("enter name of district\n");
    scanf("%s",name);
    for(int i =0;i<numOfDistrict;i++){
        if(strcasecmp(name,districts[i]->name)==0){
        printf("district already exists\n");
        flag = 1;
        break;
        }
    }
    if(flag != 1){
    districts[numOfDistrict]=makeEmpty(NULL);
    strcpy(districts[numOfDistrict]->name,name);
    districts[numOfDistrict]->population=0;
    numOfDistrict++;
    printf("district was added successfully\n");
    radix_sort();
    }
}
void add_town(){
     printf("\n");
    if(numOfDistrict == 0 ){
        printf("there are no districts\n");
    }
    else{
        char dis_name[20];
     char town_name[30];
     int population;
     int flag =0;
     printf("enter the district you which to enter the town in\n");
    scanf("%s",dis_name);
     for(int i=0 ;i<numOfDistrict;i++){
            if(strcasecmp(districts[i]->name,dis_name)==0){
                printf("enter town name\n");
                while(getchar() != '\n');
                scanf("%99[^\n]",town_name);
                node p = districts[i]->next;
                while(p!=NULL){
                        if(strcasecmp(p->name,town_name)==0){
                            printf("town already exist\n");
                            flag =1;
                            break;
                        }
                        p = p->next;
                }
                if(flag != 1){
                printf("enter town population\n");
                scanf("%d",&population);
                insert(town_name,population,districts[i]);
                Sum();
                printf("town was added successfully\n");
                flag = 1;
                }

            }

     }
     if(flag !=1)
      printf("district does not exis\n");

    }

}
void delete_town(){
     printf("\n");
    if(numOfDistrict == 0 ){
        printf("there are no districts\n");
    }
    else{
    char dis_name[20];
    char town_name[20];
    int flag =0;
    printf("enter district you wish to delete the town from\n");
    scanf("%s",dis_name);
    for(int i =0;i<numOfDistrict;i++){
            if(strcasecmp(districts[i]->name,dis_name)==0){
                printf("enter town to delete\n");
                while(getchar() != '\n');
                scanf("%99[^\n]",town_name);
               node p = districts[i]->next;
                while(p!=NULL){
                        if(strcasecmp(p->name,town_name)==0){
                            node temp;
                            temp = p->previous;
                            temp->next=p->next;
                            if(temp->next!=NULL){
                                p->next->previous = temp;
                            }
                            free(p);
                            flag =1;
                            Sum();
                            printf("town deleted successfully\n");
                        }
                        p=p->next;
                }
                if(flag!=1){
                     printf("town does not exis\n");
                     flag =1;
                }
            }
    }
    if(flag !=1)
      printf("district does not exist\n");

    }


}
void delete_district(){
     printf("\n");
    if(numOfDistrict == 0 ){
        printf("there are no districts\n");
    }
    else{
        char dis_name[20];
        int flag =0;
        printf("enter district you wish to delete\n");
        scanf("%s",dis_name);
        for(int i = 0;i<numOfDistrict;i++){
             if(strcasecmp(districts[i]->name,dis_name)==0){
                    node p,temp;
                    p=districts[i]->next;
                    districts[i]->next=NULL;
                    while(p!=NULL){
                            temp = p->next;
                            free(p);
                            p = temp;
                    }
                    free(districts[i]);
                    for(int j=i;j<numOfDistrict-1;j++)
                        districts[j]=districts[j+1];
                    numOfDistrict--;
                    flag = 1;
                    printf("district was successfully deleted\n");
             }


        }
        if(flag!=1)
            printf("district not found\n");
    }
}
void calc(){
     printf("\n");
    if(numOfDistrict == 0 ){
        printf("there are no districts\n");
    }
    else{
        int sum =0;
        int min=INT_MAX;
        int max=INT_MIN;
        for(int i=0;i<numOfDistrict;i++){
                sum+=districts[i]->population;
                node p =districts[i]->next;
                while(p!=NULL){
                    if(p->population<min)
                    min=p->population;
                    if(p->population>max)
                    max=p->population;
                    p=p->next;

                }

        }
        printf("the population of palestine is = %d\n",sum);
        printf("the max town population is =%d\n",max);
        printf("the min town population is =%d\n",min);


    }
}
void print_no_detail(){
     printf("\n");
    if(numOfDistrict == 0 ){
        printf("there are no districts\n");
    }
    else{
            for(int i=0;i<numOfDistrict;i++){
                printf("%s district, population = %d\n",districts[i]->name,districts[i]->population);
            }

    }
}
void change_population(){
     printf("\n");
    if(numOfDistrict == 0 ){
        printf("there are no districts\n");
    }
    else{
    char dis_name[20];
     char town_name[20];
     int population;
     int flag =0;
     printf("enter the district you which to change the town in\n");
    scanf("%s",dis_name);
     for(int i=0 ;i<numOfDistrict;i++){
            if(strcasecmp(districts[i]->name,dis_name)==0){
                node p = districts[i]->next;
                if(p==NULL){
                    flag=6;
                    printf("there are no towns\n");
                    break;
                }
                printf("enter town name\n");
                while(getchar() != '\n');
                 scanf("%99[^\n]",town_name);
                while(p!=NULL){
                        if(strcasecmp(p->name,town_name)==0){
                            printf("enter new town population\n");
                            scanf("%d",&population);
                             p->population=population;
                             flag =1;
                             Sum();
                             printf("population changed successfully\n");
                        }
                        p = p->next;
                }
                if(flag ==0){
                    printf("town does not exist\n");
                    flag =1;
                }

            }

     }
     if(flag ==0)
      printf("district does not exist\n");

    }

}
void save(){
    printf("\n");
     FILE *out_file;
    out_file = fopen("sorted_districts.txt","w");
    if(out_file == NULL){
        printf("error opening file");
    }
    else{
        for(int i =0;i<numOfDistrict;i++){
        fprintf(out_file,"%s district,population = %d \n",districts[i]->name,districts[i]->population);
        node p= districts[i]->next;
        while(p!=NULL){
        fprintf(out_file,"%s,%d\n",p->name,p->population);
        p=p->next;
        }

       }
       printf("save was successfull\n");

       fclose(out_file);

    }

}


