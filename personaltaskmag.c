#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct task {
    int recno;
    char name[100];
    char category[20];
    char status[20];
    char date[10];
}task;

void add() {
    task *t;
    FILE *fp;
    int n,i;
    printf("\nHow many task you want to add: ");
    scanf("%d",&n);
    t = (task*)malloc(n*sizeof(task));
    fp = fopen("personaltask.txt","a");
    for(i=0;i<n;i++) {
        printf("\nEnter Task Number: ");
        scanf("%d",&t[i]);
        fflush(stdin);
        printf("\nEnter name: ");
        scanf("%[^\n]s",t[i].name);
        fflush(stdin);
        printf("\nEnter Category: ");
        scanf("%[^\n]s",t[i].category);
        fflush(stdin);
        printf("\nEnter Status: ");
        scanf("%[^\n]s",t[i].status);
        fflush(stdin);
        printf("\nEnter Due Date (yymmdd): ");
        scanf("%[^\n]s",t[i].date);
        fwrite(&t[i],sizeof(task),1,fp);
        }
    printf("\n");
    fclose(fp);
    }

void view() {
    task t1;
    FILE *fp;
    int j;
    fp = fopen("personaltask.txt","r");
    printf("\n%-5s%-20s%-20s%-13s%-10s","No.","Name","Category","Status","Date");
    printf("\n---------------------------------------------------------------");
    while(fread(&t1,sizeof(task),1,fp)) {
        printf("\n%-5d%-20s%-20s%-13s%-10s",t1.recno,t1.name,t1.category,t1.status,t1.date);
    }
    printf("\n\n");
    fclose(fp);
}  

void search() {
    task t1;
    FILE *fp;
    int j, ans;
    int found = 0;
    fp = fopen("personaltask.txt","r");
    printf("\nEnter task no. you want to search: ");
    scanf("%d",&ans);
    while(fread(&t1,sizeof(task),1,fp)) {
        if(t1.recno == ans) {
            found = 1;
            printf("\n%-5s%-20s%-20s%-13s%-10s","No.","Name","Category","Status","Date");
            printf("\n---------------------------------------------------------------");
            printf("\n%-5d%-20s%-20s%-13s%-10s",t1.recno,t1.name,t1.category,t1.status,t1.date);
            printf("\n\n");
        }
    }
    if(found == 0) 
        printf("\n\tTask Not Found");
    printf("\n\n");
    fclose(fp);
}

void status() { //used to update status ONLY
    task t1;
    FILE *fp, *temp;
    int ans;
    int found=0;
    fp = fopen("personaltask.txt","r");
    temp = fopen("temporaty.txt","w");
    printf("\nEnter record no. you want to update: ");
    scanf("%d",&ans);
    while(fread(&t1,sizeof(task),1,fp)) {
        if(t1.recno == ans) {
            found = 1;
            fflush(stdin);
            printf("\nEnter Status: ");
            scanf("%[^\n]s",t1.status);}
        fwrite(&t1,sizeof(task),1,temp);}
    fclose(fp);
    fclose(temp);
        if(found == 1) {
        fp = fopen("personaltask.txt","w");
        temp = fopen("temporaty.txt","r");
        while(fread(&t1,sizeof(task),1,temp))
             fwrite(&t1,sizeof(task),1,fp);
        printf("\n\tStatus changed\n\n");
        fclose(fp);
        fclose(temp);
    }
    else
        printf("\n\tTask Not Found\n\n");
}

void update(int *a) {
    task t1;
    FILE *fp, *temp;
    int ans;
    int found=0;
    fp = fopen("personaltask.txt","r");
    temp = fopen("temporaty.txt","w");
    printf("\nEnter task no. you want to update: ");
    scanf("%d",&ans);
    while(fread(&t1,sizeof(task),1,fp)) {
        if(t1.recno == ans) {
            found = 1;
            if(*a == 1) {
                fflush(stdin);
                printf("\nEnter name: ");
                scanf("%[^\n]s",t1.name); }
            else if(*a == 2) {
                fflush(stdin);
                printf("\nEnter Category: ");
                scanf("%[^\n]s",t1.category);}
            else if(*a == 3) {
                fflush(stdin);
                printf("\nEnter Due Date (yymmdd): ");
                scanf("%[^\n]s",t1.date);}}
    fwrite(&t1,sizeof(task),1,temp); 
    }
    fclose(fp);
    fclose(temp);
    if(found == 1) {
        fp = fopen("personaltask.txt","w");
        temp = fopen("temporaty.txt","r");
        while(fread(&t1,sizeof(task),1,temp))
            fwrite(&t1,sizeof(task),1,fp);
        fclose(fp);
        fclose(temp);
    }
    else
        printf("\tTask Not Found\n\n");
}

void delete() {
    task t1;
    FILE *fp;
    FILE *temp;
    int ans, found=0;
    printf("Enter task no. you want to delete: ");
    scanf("%d",&ans);
    fp = fopen("personaltask.txt","r");
    temp = fopen("temporaty.txt","w");
    while(fread(&t1,sizeof(task),1,fp)) {
        if(t1.recno == ans)
            found = 1;
        else 
            fwrite(&t1,sizeof(task),1,temp);
    }
    fclose(fp);
    fclose(temp);
    if(found == 1) {
        fp = fopen("personaltask.txt","w");
        temp = fopen("temporaty.txt","r");
        while(fread(&t1,sizeof(task),1,temp)) {
            fwrite(&t1,sizeof(task),1,fp);
        }
        printf("\n\tTask Deleted\n");
        fclose(fp);
        fclose(temp);}
    else
        printf("\n\tTask Not Found");
    printf("\n\n");
} 

void sort() {
    task *t, temp;
    FILE *fp;
    int n,i,j,ans;
    int fail = 0;
    fp = fopen("personaltask.txt","r");
    fseek(fp,0,SEEK_END);
    n = ftell(fp)/sizeof(task);
    t = (task*)calloc(n,sizeof(task));
    rewind(fp);
    for(i=0;i<n;i++)
        fread(&t[i],sizeof(task),1,fp);
    printf("\n\nSort By: ");
    printf("\n1. Task No.");
    printf("\n2. Name");
    printf("\n3. Categories");
    printf("\n4. Status");
    printf("\n5. Date");
    printf("\nEnter you choice: ");
    scanf("%d",&ans);
    switch(ans) {
        case 1:
            for(i=0;i<n;i++) {
                for(j=i+1;j<n;j++) {
                    if(t[i].recno > t[j].recno) {
                        temp = t[i];
                        t[i] = t[j];
                        t[j] = temp;
                        }
                    }
                }
            break;
        case 2:
            for(i=0;i<n;i++) {
                for(j=i+1;j<n;j++) {
                    if(strcmp(t[i].name , t[j].name) >0) {
                        temp = t[i];
                        t[i] = t[j];
                        t[j] = temp;
                        }
                    }
                }
            break;
        case 3:
            for(i=0;i<n;i++) {
                for(j=i+1;j<n;j++) {
                    if(strcmp(t[i].category , t[j].category) >0) {
                        temp = t[i];
                        t[i] = t[j];
                        t[j] = temp;
                        }
                    }
                }
            break;
        case 4:
            for(i=0;i<n;i++) {
                for(j=i+1;j<n;j++) {
                    if(strcmp(t[i].status , t[j].status) >0) {
                        temp = t[i];
                        t[i] = t[j];
                        t[j] = temp;
                        }
                    }
                }
            break;
        case 5:
            for(i=0;i<n;i++) {
                for(j=i+1;j<n;j++) {
                    if(strcmp(t[i].date , t[j].date) >0) {
                        temp = t[i];
                        t[i] = t[j];
                        t[j] = temp;
                        }
                    }
                }
            break;
        default:
            printf("\n\tInvalid Value");
            fail = 1;
            break;
    }
    if(fail ==0) {
        printf("\n%-5s%-20s%-20s%-13s%-10s","No.","Name","Category","Status","Date");
        printf("\n---------------------------------------------------------------");
        for(i=0;i<n;i++)
            printf("\n%-5d%-20s%-20s%-13s%-10s",t[i].recno,t[i].name,t[i].category,t[i].status,t[i].date);
    }
    printf("\n\n");
    fclose(fp);
}

void empty() { 
    task *t;
    FILE *fp;
    int i,n;
    fp = fopen("personaltask.txt","w");
    fseek(fp,0,SEEK_END);
    n = ftell(fp)/sizeof(task);
    for(i=0;i<n;i++)
        fwrite(&t[i],sizeof(task),1,fp);
    fclose(fp);
    printf("\t\nAll Tasks Deleted\n\n");
}



 int main() {
     int ano,slc;
     char ans; 
     do {
         printf("Personal Task Management");
         printf("\n1) Add New Task");
         printf("\n2) View All Task");
         printf("\n3) Search for Task");
         printf("\n4) Update Status");
         printf("\n5) Update Other Details");
         printf("\n6) Delete Task");
         printf("\n7) Sort Task");
         printf("\n8) Empty all Task");
         printf("\n9) Exit Program");
         printf("\nEnter Your Choice: ");
         scanf("%d",&ano);
         switch(ano) {
            case 1:
                add();
                break;
            case 2:
                view();
                break;
            case 3:
                search();
                break;
            case 4:
                status();
                break;
            case 5:
                printf("\nUpdate: ");
                printf("\n1. Name");
                printf("\n2. Category");
                printf("\n3. Due Date");
                printf("\n4. Exit update");
                printf("\nEnter your choice: ");
                scanf("%d",&slc);
                if(slc == 4) {
                    printf("\n");
                    break;}
                else if(slc == 1 || slc == 2 || slc == 3)
                    update(&slc);
                else 
                    printf("\n\tInvalid Value\n\n");
                    break;
                break;
            case 6:
                delete();
                break; 
            case 7:
                sort();
                break; 
            case 8:
                printf("\nThis will delete all tasks PERMANENTLY, are you sure? (y/n): ");
                scanf(" %c",&ans);
                if(ans == 'y')
                    empty();
                else{
                    printf("\n");
                    break;}
            case 9:
                break; 
            default: {
                printf("\n\tInvalid value\n\n");
                break;}
         }
     }while(ano != 9);
 }
 