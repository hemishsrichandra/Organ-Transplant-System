#include<stdio.h>
#include <string.h>
#include<stdlib.h>

struct recipient{
    char name[20];
    char blood_grp[4];
    int age;
    char entry_date[11];
    char hospital[20];
    char super_urgency[4];
};

struct donor{
    char name[20];
    char blood_grp[4];
    int age;
    char death_date[11];
};

struct Node_rec{
   struct recipient data;
   struct Node_rec* next; 
};

struct Node_dnr{
    struct donor data;
    struct Node_dnr* next;
};

// int len_ll(struct Node_rec* ptr){ (to find the length of the recipient linked list)
//     int i=0;
//     while(ptr!=NULL){
//         i++;
//         ptr=ptr->next;
//     }
//     return i;
// }

struct Node_dnr* add_dnr(struct Node_dnr* head,struct donor new){//to add a new donor to the end of the list
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

struct Node_rec* add_rec(struct Node_rec* head,struct recipient new){//to add a new recipient to the end of the list
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

struct Node_rec* del_begin(struct Node_rec* head){//to delete a node at the beginning of the recipients' linked list
    struct Node_rec* ptr=head;
    head=head->next;
    free(ptr);
    return head;
}

struct Node_rec* del_end(struct Node_rec* head){//to delete a node at the end of the recipients' linked list
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

struct Node_rec* del_index(struct Node_rec* head,int index){//to delete a node in the middle of the recipients' linked list
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

struct Node_rec* delete_rec(struct Node_rec* head,struct recipient* info){//to delete the recipient from the list if he dies before the organ is available
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

void print_recipients(struct Node_rec* head){// print the list of recipients
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

void print_donors(struct Node_dnr* head){//print the list of donors
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

int blood_match(char* bld_grp_dnr, char* bld_grp_rec) {//check if a particular donor with a specific blood group can donate to the recipient with the given blood group
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


struct Node_rec* match_recipient(struct Node_rec* head,char* bld_grp_dnr){//matching the recipient based on blood group matching and super urgency
    struct Node_rec* ptr=head;
    int i=0;
    while(ptr!=NULL){
        if(strcmp(ptr->data.super_urgency,"YES")==0 && blood_match(bld_grp_dnr,ptr->data.blood_grp)){//check if there is a super urgency case whose blood group matches
            printf("Allocate organ to %s in %s Hospital\n\n",ptr->data.name,ptr->data.hospital);
            if(i==0) head=del_begin(head);
            else if(ptr->next==NULL) head=del_end(head);
            else head=del_index(head,i);
            return head;
        }
        ptr=ptr->next;
        i++;
    }
    i=0;
    ptr=head;
    while(ptr!=NULL){
        if(blood_match(bld_grp_dnr,ptr->data.blood_grp)){//if there is no super urgency then we allocate organ to the first person whose blood group matches
            printf("Allocate organ to %s in %s Hospital\n",ptr->data.name,ptr->data.hospital);
            if(i==0) head=del_begin(head);
            else if(ptr->next==NULL) head=del_end(head);
            else head=del_index(head,i);
            return head;
        }
        ptr=ptr->next;
        i++;
    }
    printf("No compatible recipient found.\n");
    return head;
}

// int main(){
//fgets use karo for taking string inputs
//     return 0;
// }
//use multiple linked lists for donor and recipients for each organ.