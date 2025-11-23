#include<stdio.h>
#include <string.h>
#include<stdlib.h>
#include<strings.h>

//recipient information
struct recipient{
    char name[20];
    char blood_grp[4];
    int age;
    char entry_date[11];
    char hospital[20];
    char super_urgency[4];
};

//donor information
struct donor{
    char name[20];
    char blood_grp[4];
    int age;
    char death_date[11];
};

//node for recipients' linked list
struct Node_rec{
   struct recipient data;
   struct Node_rec* next; 
};

//node for donors' linked list
struct Node_dnr{
    struct donor data;
    struct Node_dnr* next;
};

//to add a new donor to the end of the list
struct Node_dnr* add_dnr(struct Node_dnr* head,struct donor new){
    struct Node_dnr* p=(struct Node_dnr*)malloc(sizeof(struct Node_dnr));
    if(head==NULL){
        p->data=new;
        p->next=NULL;
        return p;
    }
    struct Node_dnr* ptr=head;
    p->data=new;
    while(ptr->next!=NULL){
        ptr=ptr->next;
    }
    ptr->next=p;
    p->next=NULL;
    return head;
}

//to add a new recipient to the end of the list
struct Node_rec* add_rec(struct Node_rec* head,struct recipient new){
    struct Node_rec* p=(struct Node_rec*)malloc(sizeof(struct Node_rec));
    if(head==NULL){
        p->data=new;
        p->next=NULL;
        return p;
    }
    struct Node_rec* ptr=head;
    p->data=new;
    while(ptr->next!=NULL){
        ptr=ptr->next;
    }
    ptr->next=p;
    p->next=NULL;
    return head;
}

//to delete a node at the beginning of the recipients' linked list
struct Node_rec* del_begin(struct Node_rec* head){
    struct Node_rec* ptr=head;
    head=head->next;
    free(ptr);
    return head;
}

//to delete a node at the end of the recipients' linked list
struct Node_rec* del_end(struct Node_rec* head){
    if (head == NULL) return NULL;
    if (head->next == NULL) {
        free(head);
        return NULL;
    }
    struct Node_rec* p=head;
    struct Node_rec* q=head->next;
    while(q->next!=NULL){
        p=p->next;
        q=q->next;
    }
    p->next=NULL;
    free(q);
    return head;
}

//to delete a node in the middle of the recipients' linked list
struct Node_rec* del_index(struct Node_rec* head,int index){
    struct Node_rec* p=head;
    struct Node_rec* q=head->next;
    for(int i=0;i<index-1;i++){
        p=p->next;
        q=q->next;
    }
    p->next=q->next;
    free(q);
    return head;
}

//to delete the recipient from the list if he dies before the organ is available
struct Node_rec* delete_rec(struct Node_rec* head,struct recipient* info){
    if (head == NULL || info == NULL) {
    printf("List is empty or invalid recipient pointer.\n");
    return head;
    }
    if(info==&(head->data)){
        head=del_begin(head);
        return head;
    }
    int i=0;
    struct Node_rec* ptr=head;
    while(ptr->next!=NULL){
        if((&(ptr->data))==info){
            head=del_index(head,i);
            return head;
        }
        ptr=ptr->next;
        i++;
    }
    if((&(ptr->data))==info){
        head=del_end(head);
        return head;
    }
    printf("Recipient not found.\n\n");
    return head;
}

// print the list of recipients
void print_recipients(struct Node_rec* head){
    struct Node_rec* ptr=head;
    int i=1;
    printf("---- Recipient List ----\n\n");
    while(ptr!=NULL){
        printf("%d. Name: %s\n",i,(ptr->data).name);
        printf("   Blood Group: %s\n",(ptr->data).blood_grp);
        printf("   Age: %d\n",(ptr->data).age);
        printf("   Date of Entry: %s\n",(ptr->data).entry_date);
        printf("   Hospital Name: %s\n",(ptr->data).hospital);
        printf("   Super Urgency: %s\n",(ptr->data).super_urgency);
        printf("--------------------------\n\n");
        ptr=ptr->next;
        i++;
    }
}

//print the list of donors
void print_donors(struct Node_dnr* head){
    if(head==NULL){
        printf("No donors available\n");
        return;
    }
    struct Node_dnr* ptr=head;
    int i=1;
    printf("---- Donor List ----\n\n");
    while(ptr!=NULL){
        printf("%d. Name: %s\n",i,(ptr->data).name);
        printf("   Blood Group: %s\n",(ptr->data).blood_grp);
        printf("   Age: %d\n",(ptr->data).age);
        printf("   Date of Death: %s\n",(ptr->data).death_date);
        printf("----------------------\n\n");
        ptr=ptr->next;
        i++;
    }
}

//check if a particular donor with a specific blood group can donate to the recipient with the given blood group
int blood_match(char* bld_grp_dnr, char* bld_grp_rec) {
    if (strcmp(bld_grp_dnr, "O-") == 0)
        return 1;
    if (strcmp(bld_grp_dnr, "O+") == 0 && (strcmp(bld_grp_rec, "O+") == 0 || strcmp(bld_grp_rec, "A+") == 0 || strcmp(bld_grp_rec, "B+") == 0 || strcmp(bld_grp_rec, "AB+") == 0))
        return 1;
    if (strcmp(bld_grp_dnr, "A-") == 0 && (strcmp(bld_grp_rec, "A+") == 0 || strcmp(bld_grp_rec, "A-") == 0 || strcmp(bld_grp_rec, "AB+") == 0 || strcmp(bld_grp_rec, "AB-") == 0))
        return 1;
    if (strcmp(bld_grp_dnr, "A+") == 0 && (strcmp(bld_grp_rec, "AB+") == 0 || strcmp(bld_grp_rec, "A+") == 0))
        return 1;
    if (strcmp(bld_grp_dnr, "B-") == 0 && (strcmp(bld_grp_rec, "B+") == 0 || strcmp(bld_grp_rec, "B-") == 0 || strcmp(bld_grp_rec, "AB+") == 0 || strcmp(bld_grp_rec, "AB-") == 0))
        return 1;
    if (strcmp(bld_grp_dnr, "B+") == 0 && (strcmp(bld_grp_rec, "AB+") == 0 || strcmp(bld_grp_rec, "B+") == 0))
        return 1;
    if (strcmp(bld_grp_dnr, "AB-") == 0 && (strcmp(bld_grp_rec, "AB+") == 0 || strcmp(bld_grp_rec, "AB-") == 0))
        return 1;
    if (strcmp(bld_grp_dnr, "AB+") == 0 && strcmp(bld_grp_rec, "AB+") == 0)
        return 1;

    return 0;
}

//matching the recipient based on blood group matching and super urgency
struct Node_rec* match_recipient(struct Node_rec* head,char* bld_grp_dnr,int* matched){
    struct Node_rec* ptr=head;
    int i=0;
    while(ptr!=NULL){
        //check if there is a super urgency case whose blood group matches
        if(strcmp(ptr->data.super_urgency,"YES")==0 && blood_match(bld_grp_dnr,ptr->data.blood_grp)){
            printf("Allocate organ to %s in %s Hospital\n\n",ptr->data.name,ptr->data.hospital);
            if(i==0) head=del_begin(head);
            else if(ptr->next==NULL) head=del_end(head);
            else head=del_index(head,i);
            *matched=1;
            return head;
        }
        ptr=ptr->next;
        i++;
    }
    i=0;
    ptr=head;
    while(ptr!=NULL){
        //if there is no super urgency then we allocate organ to the first person whose blood group matches
        if(blood_match(bld_grp_dnr,ptr->data.blood_grp)){
            printf("Allocate organ to %s in %s Hospital\n",ptr->data.name,ptr->data.hospital);
            if(i==0) head=del_begin(head);
            else if(ptr->next==NULL) head=del_end(head);
            else head=del_index(head,i);
            *matched=1;
            return head;
        }
        ptr=ptr->next;
        i++;
    }
    printf("No compatible recipient found.\n");
    return head;
}

/*---File I/O---*/
//used to save the recipients
void save_rec(struct Node_rec* head,const char* fname) {
    FILE *fptr = fopen(fname, "w");
    if (fptr == NULL) {
        printf("Error opening file for writing..\n");
        return;
    }
    struct Node_rec* ptr = head;
    while (ptr != NULL) {
        fprintf(fptr, "%s,%s,%d,%s,%s,%s\n",ptr->data.name,ptr->data.blood_grp,ptr->data.age,ptr->data.entry_date,ptr->data.hospital,ptr->data.super_urgency);
        ptr = ptr->next;
    }
    fclose(fptr);
    printf("Recipient list saved successfully..\n");
}

//used to retrieve the recipients
struct Node_rec* load_rec(struct Node_rec* head,const char* fname){
    FILE *fptr=fopen(fname,"r");
    if (fptr == NULL) {
        printf("File not found..\n");
        return NULL;
    }
    struct recipient temp;
    while(fscanf(fptr,"%[^,],%[^,],%d,%[^,],%[^,],%s\n",temp.name,temp.blood_grp,&temp.age,temp.entry_date,temp.hospital,temp.super_urgency)==6){
        head=add_rec(head,temp);
    }
    fclose(fptr);
    printf("Recipients loaded successfully..\n");
    return head;
}

//used to save the donors
void save_dnr(struct Node_dnr* head,const char* fname) {
    FILE *fptr = fopen(fname, "w");
    if (fptr == NULL) {
        printf("Error opening file for writing..\n");
        return;
    }
    struct Node_dnr* ptr = head;
    while (ptr != NULL) {
        fprintf(fptr, "%s,%s,%d,%s\n",ptr->data.name,ptr->data.blood_grp,ptr->data.age,ptr->data.death_date);
        ptr = ptr->next;
    }
    fclose(fptr);
    printf("Donor list saved successfully..\n");
}

//used to load the donors
struct Node_dnr* load_dnr(struct Node_dnr* head,const char* fname) {
    FILE *fptr = fopen(fname, "r");
    if (fptr == NULL) {
        printf("File not found..\n");
        return NULL;
    }
    struct donor temp;
    while (fscanf(fptr, "%[^,],%[^,],%d,%s\n",temp.name,temp.blood_grp,&temp.age,temp.death_date) == 4) {
        head = add_dnr(head, temp);
    }
    fclose(fptr);
    printf("Donors loaded successfully..\n");
    return head;
}

//used for replacing the \n with \0 while using fgets for input
void trim_newline(char *str) {
    int len = strlen(str);
    if (len > 0 && str[len-1] == '\n') str[len-1] = '\0';
}

int main(){
    //declaring the linked list heads for all the organs' recipients
    struct Node_rec* heart_rec=NULL;
    struct Node_rec* kidney_rec=NULL;
    struct Node_rec* liver_rec=NULL;
    struct Node_rec* lungs_rec=NULL;

    // loading all the recipient linked lists for organs before starting the program
    heart_rec=load_rec(heart_rec,"Heart Recipients.txt");
    kidney_rec=load_rec(kidney_rec,"Kidney Recipients.txt");
    liver_rec=load_rec(liver_rec,"Liver Recipients.txt");
    lungs_rec=load_rec(lungs_rec,"Lungs Recipients.txt");
    
    //declaring the donor linked list heads
    struct Node_dnr* heart_dnr=NULL;
    struct Node_dnr* kidney_dnr=NULL;
    struct Node_dnr* liver_dnr=NULL;
    struct Node_dnr* lungs_dnr=NULL;

    // loading all the donor linked lists for organs before starting the program
    heart_dnr=load_dnr(heart_dnr,"Heart Donors.txt");
    kidney_dnr=load_dnr(kidney_dnr,"Kidney Donors.txt");
    liver_dnr=load_dnr(liver_dnr,"Liver Donors.txt");
    lungs_dnr=load_dnr(lungs_dnr,"Lungs Donors.txt");

    //Main menu printing and while loop initialisation
    printf("\n~Organ Transplant System~\n");
    //an infinite loop to keep taking and executing instructions from the user until they save and exit the program
    while(1){
        int option;//used to store the choice of the user
        printf("\n ---------Menu---------\n");
        printf("1. Enter new donor\n");
        printf("2. Add recipient\n");
        printf("3. Get donors list\n");
        printf("4. Get recipients list\n");
        printf("5. Delete Recipient\n");
        printf("6. Save and Exit\n");
        printf("Enter choice: ");
        scanf("%d",&option);getchar();
        char organ[20];

        switch(option){
            //case 1 for checking if the organs of new donors are compatible with any of the recipients and allocating them
            //if no compatible recipient is found then the organ expires a there is a time limit for the transplant to happen after the organ is extracted
            case 1: 
            struct donor new_dnr;
            printf("\nEnter organ(Heart/Kidney/Liver/Lungs): ");
            fgets(organ,20,stdin);trim_newline(organ);
            if(strcasecmp(organ,"Heart")!=0 && strcasecmp(organ,"Kidney")!=0 && strcasecmp(organ,"Lungs")!=0 && strcasecmp(organ,"Liver")!=0){
                printf("\nInvalid choice of organ! Please try again.");
                break;
            }
            printf("\nEnter name: ");
            fgets(new_dnr.name,20,stdin);trim_newline(new_dnr.name);
            printf("\nEnter blood group: ");
            fgets(new_dnr.blood_grp,5,stdin);trim_newline(new_dnr.blood_grp);
            printf("\nEnter age(in integer): ");
            scanf("%d",&new_dnr.age);getchar();//using getchar() to prevent the next fgets from absorbing the nextline character
            printf("\nEnter date of demise(dd-mm-yyyy): ");
            fgets(new_dnr.death_date,15,stdin);trim_newline(new_dnr.death_date);

            int matched=0;
            int* mptr=&matched;
            
            if(strcasecmp(organ,"Heart")==0){
                heart_rec=match_recipient(heart_rec,new_dnr.blood_grp,mptr);
            }
            else if(strcasecmp(organ,"Kidney")==0){
                kidney_rec=match_recipient(kidney_rec,new_dnr.blood_grp,mptr);
            }
            else if(strcasecmp(organ,"Liver")==0){
                liver_rec=match_recipient(liver_rec,new_dnr.blood_grp,mptr);
            }
            else if(strcasecmp(organ,"Lungs")==0){
                lungs_rec=match_recipient(lungs_rec,new_dnr.blood_grp,mptr);
            }

            if(matched){
            if(strcasecmp(organ,"Heart")==0){
                heart_dnr=add_dnr(heart_dnr,new_dnr);
            }
            else if(strcasecmp(organ,"Kidney")==0){
                kidney_dnr=add_dnr(kidney_dnr,new_dnr);
            }
            else if(strcasecmp(organ,"Liver")==0){
                liver_dnr=add_dnr(liver_dnr,new_dnr);
            }
            else if(strcasecmp(organ,"Lungs")==0){
                lungs_dnr=add_dnr(lungs_dnr,new_dnr);
            }
            }
            else{
                printf("Organ Allocation failed. Organ expired.\n");
            }
            break;

            //case 2 for adding a new recipient to any of the organ recipient lists
            case 2:
            struct recipient new_rec;
            printf("\nEnter organ(Heart/Kidney/Liver/Lungs): ");
            fgets(organ,20,stdin);trim_newline(organ);
            if(strcasecmp(organ,"Heart")!=0 && strcasecmp(organ,"Kidney")!=0 && strcasecmp(organ,"Lungs")!=0 && strcasecmp(organ,"Liver")!=0){
                printf("\nInvalid choice of organ! Please try again.");
                break;
            }

            printf("\nEnter name: ");
            fgets(new_rec.name,20,stdin);trim_newline(new_rec.name);
            printf("\nEnter blood group: ");
            fgets(new_rec.blood_grp,5,stdin);trim_newline(new_rec.blood_grp);
            printf("\nEnter age(in integer): ");
            scanf("%d",&new_rec.age);getchar();
            printf("\nEnter date of entry(dd-mm-yyyy): ");
            fgets(new_rec.entry_date,15,stdin);trim_newline(new_rec.entry_date);
            printf("\nEnter hospital name: ");
            fgets(new_rec.hospital,20,stdin);trim_newline(new_rec.hospital);
            printf("\nSuper-Urgency?(Yes/No): ");
            fgets(new_rec.super_urgency,5,stdin);trim_newline(new_rec.super_urgency);

            if(strcasecmp(organ,"Heart")==0){
                heart_rec=add_rec(heart_rec,new_rec);
            }
            else if(strcasecmp(organ,"Kidney")==0){
                kidney_rec=add_rec(kidney_rec,new_rec);
            }
            else if(strcasecmp(organ,"Liver")==0){
                liver_rec=add_rec(liver_rec,new_rec);
            }
            else if(strcasecmp(organ,"Lungs")==0){
                lungs_rec=add_rec(lungs_rec,new_rec);
            }
            break;

            //case 3 to print the donor lists for a particular organ
            case 3:
            printf("\nEnter organ(Heart/Kidney/Liver/Lungs): ");
            fgets(organ,20,stdin);trim_newline(organ);
            if(strcasecmp(organ,"Heart")!=0 && strcasecmp(organ,"Kidney")!=0 && strcasecmp(organ,"Lungs")!=0 && strcasecmp(organ,"Liver")!=0){
                printf("\nInvalid choice of organ! Please try again.");
                break;
            }
            if(strcasecmp(organ,"Heart")==0){
                print_donors(heart_dnr);
            }
            else if(strcasecmp(organ,"Kidney")==0){
                print_donors(kidney_dnr);
            }
            else if(strcasecmp(organ,"Liver")==0){
                print_donors(liver_dnr);
            }
            else if(strcasecmp(organ,"Lungs")==0){
                print_donors(lungs_dnr);
            }
            break;

            //case 4 for printing the recipient lists for a specific organ
            case 4:
            printf("\nEnter organ(Heart/Kidney/Liver/Lungs): ");
            fgets(organ,20,stdin);trim_newline(organ);
            if(strcasecmp(organ,"Heart")!=0 && strcasecmp(organ,"Kidney")!=0 && strcasecmp(organ,"Lungs")!=0 && strcasecmp(organ,"Liver")!=0){
                printf("\nInvalid choice of organ! Please try again.");
                break;
            }
            if(strcasecmp(organ,"Heart")==0){
                print_recipients(heart_rec);
            }
            else if(strcasecmp(organ,"Kidney")==0){
                print_recipients(kidney_rec);
            }
            else if(strcasecmp(organ,"Liver")==0){
                print_recipients(liver_rec);
            }
            else if(strcasecmp(organ,"Lungs")==0){
                print_recipients(lungs_rec);
            }
            break;

            //case 5 to delete a recipient from the lists incase he expires before the allotment of the organ
            case 5:
            printf("\nEnter organ(Heart/Kidney/Liver/Lungs): ");
            fgets(organ, 20, stdin);trim_newline(organ);
            if(strcasecmp(organ,"Heart")!=0 && strcasecmp(organ,"Kidney")!=0 && strcasecmp(organ,"Lungs")!=0 && strcasecmp(organ,"Liver")!=0) {
                printf("\nInvalid choice of organ! Please try again.");
                break;
            }
            char name[20];
            printf("\nEnter recipient name: ");
            fgets(name, 20, stdin);trim_newline(name);

            struct Node_rec** list_ptr = NULL;
            if(strcasecmp(organ,"Heart")==0) list_ptr = &heart_rec;
            else if(strcasecmp(organ,"Kidney")==0) list_ptr = &kidney_rec;
            else if(strcasecmp(organ,"Liver")==0) list_ptr = &liver_rec;
            else if(strcasecmp(organ,"Lungs")==0) list_ptr = &lungs_rec;

            struct Node_rec* ptr=(*(list_ptr));
            while(ptr!=NULL && strcasecmp(ptr->data.name,name)!=0){
                ptr=ptr->next;
            }
            if(ptr==NULL){
                printf("\nRecipient not found..");
            }
            else{
                (*(list_ptr))=delete_rec(*list_ptr,ptr);
                printf("\nRecipient successfully removed..");
            }
            break;

            //case 6 to update and save all the donor and recipient linked lists before exiting the program
            case 6:
            save_rec(heart_rec, "Heart Recipients.txt");
            save_rec(kidney_rec, "Kidney Recipients.txt");
            save_rec(liver_rec, "Liver Recipients.txt");
            save_rec(lungs_rec, "Lungs Recipients.txt");

            save_dnr(heart_dnr, "Heart Donors.txt");
            save_dnr(kidney_dnr, "Kidney Donors.txt");
            save_dnr(liver_dnr, "Liver Donors.txt");
            save_dnr(lungs_dnr, "Lungs Donors.txt");

            printf("\nAll data saved. Exiting system safely...\n");
            exit(0);

            //default case to handle incorrect menu option inputs
            default:printf("Invalid Option! Please try again.\n");break;
        }
    }
    return 0;
}