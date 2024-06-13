#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE_OF_TITLE 100
#define MAX_SIZE_OF_AUTHOR 50
#define MAX_SIZE_OF_NARRATOR 50
#define MAX_SIZE_OF_GENRE 50
#define MAX_SIZE_OF_NAME 50
#define MAX_SIZE_OF_EMAIL 100
#define MAX_PREFERENCE_TYPE_LENGTH 50

typedef struct audiobook_avl_node
{
    int AudiobookId;
    char title[MAX_SIZE_OF_TITLE];
    char Author[MAX_SIZE_OF_AUTHOR];
    char narrator[MAX_SIZE_OF_NARRATOR];
    char duration[6];
    char genre[MAX_SIZE_OF_GENRE];
    float sum_rating;
    int count_rating;
    struct audiobook_avl_node *right;
    struct audiobook_avl_node *left;
    int height; 
}audiobook_avl_node;

typedef struct preferenceNode {
    char preferenceType[MAX_PREFERENCE_TYPE_LENGTH];
    char preferenceValue[50];
    struct preferenceNode* next;
}preferenceNode;

typedef struct audiobooklog_avl_node
{
    int ID; 
    audiobook_avl_node* book;
    char timestamp[5];
    float rating ;
    struct audiobooklog_avl_node *left;
    struct audiobooklog_avl_node *right;
    int height;
}audiobooklog_avl_node;

typedef struct user_avl_node
{
    int userid;
    char name[MAX_SIZE_OF_NAME];
    char email[MAX_SIZE_OF_EMAIL];
    preferenceNode* preferences;
    audiobooklog_avl_node *ptr;
    struct user_avl_node *right;
    struct user_avl_node *left;
    int height; 
}user_avl_node;

int height(audiobook_avl_node *root)
{
    if (root == NULL)
        return -1;
    return root->height;
}

int height_user(user_avl_node *root)
{
    if (root == NULL)
        return -1;
    return root->height;
}

int height_audiobooklog(audiobooklog_avl_node *root)
{
    if (root == NULL)
        return -1;
    return root->height;
}

int max(int a,int b)
{
    if(a>b)
    {
        return a;
    }
    return b;
}

int balance_factor(audiobook_avl_node *root)
{
    return height(root->left) - height(root->right);
}

int balance_factor_user(user_avl_node *root)
{
    return height_user(root->left) - height_user(root->right);
}

int balance_factor_audiobooklog(audiobooklog_avl_node *root)
{
    return height_audiobooklog(root->left) - height_audiobooklog(root->right);
}

void initialise_Audiobook(audiobook_avl_node* AB){
    AB -> AudiobookId = 0;
    AB -> title[0] = '\0';
    AB -> Author[0] = '\0';
    AB -> narrator[0] = '\0';
    AB -> duration[0] = '\0';
    AB -> genre[0] = '\0';
    AB -> count_rating = 0;
    AB -> sum_rating = 0;
    AB -> height = 0;
    AB -> left = NULL;
    AB -> right = NULL;
}

void initialise_user(user_avl_node* UL){
    UL -> userid = 0;
    UL -> email[0] = '\0';
    UL -> name[0] = '\0';
    UL -> preferences = NULL;
    UL -> right = NULL;
    UL -> left = NULL;
    UL -> ptr = NULL;
    UL -> height = 0;
}

audiobook_avl_node* match_AB_IB(audiobook_avl_node* AB , int AB_ID){
    audiobook_avl_node* ret = NULL;
    if(AB){
        if(AB -> AudiobookId == AB_ID){
            ret = AB;
        }
        else{
            ret = match_AB_IB(AB -> left , AB_ID);
            if(ret == NULL){
            ret = match_AB_IB(AB -> right , AB_ID);
         }
        }
    }
    return ret;
}

user_avl_node* createusernode() {
    user_avl_node *newUser = (user_avl_node*)malloc(sizeof(user_avl_node));
    printf("Enter user ID: ");
    scanf("%d", &newUser->userid);
    printf("Enter name of the user: ");
    scanf("%49s", newUser->name);
    printf("Enter email of the user: ");
    scanf("%99s", newUser->email);
    newUser->preferences = NULL;
    newUser->ptr = NULL;
    newUser->left = NULL;
    newUser->right = NULL;
    newUser->height = 0;
    return newUser;
}

audiobook_avl_node *createAudiobook() {
    audiobook_avl_node *newAudiobook = (audiobook_avl_node*)malloc(sizeof(audiobook_avl_node));
    printf("Enter Audiobook ID: ");
    scanf("%d", &newAudiobook->AudiobookId);

    printf("Enter title of the audiobook: ");
    scanf("%99s", newAudiobook->title);

    printf("Enter author of the audiobook: ");
    scanf("%99s", newAudiobook->Author);

    printf("Enter narrator of the audiobook: ");
    scanf("%99s", newAudiobook->narrator);

    printf("Enter duration of the audiobook (in HH:MM format): ");
    scanf("%5s", newAudiobook->duration);

    printf("Enter genre of the audiobook: ");
    scanf("%49s", newAudiobook->genre);

    newAudiobook->sum_rating = 0;
    newAudiobook->count_rating = 0;
    newAudiobook->left = NULL;
    newAudiobook->right = NULL;
    newAudiobook->height = 0;

    return newAudiobook;
}

audiobooklog_avl_node* createAudiobookLogNode(int id) {
    audiobooklog_avl_node* newNode = (audiobooklog_avl_node*)malloc(sizeof(audiobooklog_avl_node));

    newNode->ID=id;

    printf("Enter timestamp (in HH:MM format): ");
    scanf("%s", newNode->timestamp);
    strcat( newNode->timestamp,"\n");
    newNode->rating=0.0;
    newNode->book = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 0;

    return newNode;
}

void printNodeDetails_audiobook(audiobook_avl_node *node) {
    if (node == NULL) {
        printf("Node is NULL\n");
        return;
    }

    printf("AudiobookId: %d\n", node->AudiobookId);
    printf("Title: %s\n", node->title);
    printf("Author: %s\n", node->Author);
    printf("Narrator: %s\n", node->narrator);
    printf("Duration: %s\n", node->duration);
    printf("Genre: %s\n", node->genre);
    printf("Sum Rating: %.2f\n", node->sum_rating);
    printf("Count Rating: %d\n", node->count_rating);
}


void printLevelWithSpaces(audiobook_avl_node *root, int level) {
    if (root == NULL) {
        if (level == 1)
            printf("  "); // Print two spaces for empty node at level 1
        return;
    }
    if (level == 1)
        printf("%d ", root->AudiobookId);
    else if (level > 1) {
        if (root->left == NULL && root->right == NULL) 
        {
            printf("x x ");
        } 
        else 
        {
            printLevelWithSpaces(root->left, level - 1);
            printLevelWithSpaces(root->right, level - 1);
        }
    }
}

void printLevelOrderWithSpaces(audiobook_avl_node *root) {
    if (root == NULL)
        return;
    int h = root->height;
    int i;
    for (i = 1; i <= h + 1; i++) {
        printLevelWithSpaces(root, i);
        printf("\n");
    }
}


void printLevelWithSpaces_user(user_avl_node *root, int level) {
    if (root == NULL) {
        if (level == 1)
            printf("  "); // Print two spaces for empty node at level 1
        return;
    }
    if (level == 1)
        printf("%d ", root->userid);
    else if (level > 1) {
        if (root->left == NULL && root->right == NULL) 
        {
            printf("x x");
        } 
        else 
        {
            printLevelWithSpaces_user(root->left, level - 1);
            printLevelWithSpaces_user(root->right, level - 1);
        }
    }
}

void printLevelOrderWithSpaces_user(user_avl_node *root) {
    if (root == NULL)
        return;
    int h = root->height;
    int i;
    for (i = 1; i <= h + 1; i++) {
        printLevelWithSpaces_user(root, i);
        printf("\n");
    }
}

void printLevelWithSpaces_audiobooklog(audiobooklog_avl_node *root, int level) {
    if (root == NULL) {
        if (level == 1)
            printf("  "); // Print two spaces for empty node at level 1
        return;
    }
    if (level == 1)
        printf("%d ", root->ID);
    else if (level > 1) {
        if (root->left == NULL && root->right == NULL) 
        {
            printf("x x ");
        } 
        else 
        {
            printLevelWithSpaces_audiobooklog(root->left, level - 1);
            printLevelWithSpaces_audiobooklog(root->right, level - 1);
        }
    }
}

void printLevelOrderWithSpaces_audiobooklog(audiobooklog_avl_node *root){
    if (root == NULL)
        return;
    int h = root->height;
    int i;
    for (i = 1; i <= h + 1; i++) {
        printLevelWithSpaces_audiobooklog(root, i);
        printf("\n");
    }
}



void printUserAVLNode(user_avl_node *node) {
    if (node == NULL) {
        printf("Node is NULL\n");
        return;
    }
    printf("User ID: %d\n", node->userid);
    printf("Name: %s\n", node->name);
    printf("Email: %s\n", node->email);
    // Print preferences
    printf("Preferences:\n");
    preferenceNode* currentPref = node->preferences;
    while (currentPref != NULL) {
        printf("  Type: %s, Value: %s\n", currentPref->preferenceType, currentPref->preferenceValue);
        currentPref = currentPref->next;
    }
    //printLevelOrderWithSpaces_audiobooklog(node->ptr);
  
}

void display_AB(audiobook_avl_node* AB){
    if(AB){
        display_AB(AB -> left);
        printNodeDetails_audiobook(AB);
        printf("\n");
        display_AB(AB -> right);
    }
}

void print_abl(audiobooklog_avl_node* abl){
    printf("audiobook ID   :  %d\n" , abl -> ID);
    printf("timestamp   :  %s" , abl -> timestamp);
    printf("rating   :  %f\n\n" , abl -> rating);
}

void display_abl(audiobooklog_avl_node* abl){
    if(abl){
        display_abl(abl -> left);
        print_abl(abl);
        display_abl(abl -> right);
    }
}

void print_UL(user_avl_node* node){
    if(node){
         printf("User ID: %d\n", node->userid);
        printf("Name: %s\n", node->name);
        printf("Email: %s\n", node->email);
        // Print preferences
        printf("Preferences:\n");
        preferenceNode* currentPref = node->preferences;
        while (currentPref != NULL) {
            printf("  Type: %s, Value: %s", currentPref->preferenceType, currentPref->preferenceValue);
            currentPref = currentPref->next;
        }
        printf("user library   :\n");
        display_abl(node -> ptr);
    }
}

void display_UL(user_avl_node* UL){
    if(UL){
        display_UL(UL -> left);
        print_UL(UL);
        printf("\n");
        display_UL(UL -> right);
    }
}

audiobook_avl_node *rotate_left(audiobook_avl_node *root)
{
    audiobook_avl_node *temp = root->right;
    root->right = temp->left;
    temp->left = root;
    root->height = max(height(root->left), height(root->right)) + 1;
    temp->height = max(height(temp->left), height(temp->right)) + 1;
    return temp;
}

audiobook_avl_node *rotate_right(audiobook_avl_node *root)
{
    audiobook_avl_node *temp = root->left;
    root->left = temp->right;
    temp->right = root;
    root->height = max(height(root->left), height(root->right)) + 1;
    temp->height = max(height(temp->left), height(temp->right)) + 1;
    return temp;
}


user_avl_node *rotate_left_user(user_avl_node *root)
{
    user_avl_node *temp = root->right;
    root->right = temp->left;
    temp->left = root;
    root->height = max(height_user(root->left), height_user(root->right)) + 1;
    temp->height = max(height_user(temp->left), height_user(temp->right)) + 1;
    return temp;
}

user_avl_node *rotate_right_user(user_avl_node *root)
{
    user_avl_node *temp = root->left;
    root->left = temp->right;
    temp->right = root;
    root->height = max(height_user(root->left), height_user(root->right)) + 1;
    temp->height = max(height_user(temp->left), height_user(temp->right)) + 1;
    return temp;
}

audiobooklog_avl_node *rotate_left_audiobooklog(audiobooklog_avl_node *root)
{
    audiobooklog_avl_node *temp = root->right;
    root->right = temp->left;
    temp->left = root;
    root->height = max(height_audiobooklog(root->left), height_audiobooklog(root->right)) + 1;
    temp->height = max(height_audiobooklog(temp->left), height_audiobooklog(temp->right)) + 1;
    return temp;
}

audiobooklog_avl_node *rotate_right_audiobooklog(audiobooklog_avl_node *root)
{
    audiobooklog_avl_node *temp = root->left;
    root->left = temp->right;
    temp->right = root;
    root->height = max(height_audiobooklog(root->left), height_audiobooklog(root->right)) + 1;
    temp->height = max(height_audiobooklog(temp->left), height_audiobooklog(temp->right)) + 1;
    return temp;
}

audiobook_avl_node *balance_audiobook(audiobook_avl_node *root)
{
    if(root==NULL)
    {
        return NULL;
    }
    else
    {
        root->height = 1 + max(height(root->left), height(root->right));
        if(balance_factor(root)>1)
        {
            if(balance_factor(root->left)==1)
            {
                root=rotate_right(root);
            }
            else if(balance_factor(root->left)==-1)
            {
                root->left=rotate_left(root->left);
                root=rotate_right(root);
            }
        }
        else if(balance_factor(root)<-1)
        {
            if(balance_factor(root->right)==-1)
            {
                root=rotate_left(root);
            }
            else if(balance_factor(root->right)==1)
            {
                root->right=rotate_right(root->right);
                root=rotate_left(root);
            }
        }
        return root;
    }
}

audiobook_avl_node *minValueNode(audiobook_avl_node *node) 
{
    audiobook_avl_node *current = node;
    while (current->left != NULL)
        {
            current = current->left;
        }
    return current;
}


audiobook_avl_node *insert_audiobook(audiobook_avl_node *root,audiobook_avl_node *new_audiobook)
{
    if (root == NULL)
    {
        return new_audiobook;
    }
    else
    {
        if(strcmp(new_audiobook->title,root->title)<0)
        {
             root->left = insert_audiobook(root->left,new_audiobook);
        }
        else if(strcmp(new_audiobook->title,root->title)>0)
        {
             root->right = insert_audiobook(root->right,new_audiobook);
        }
        else
        {
            if(strcmp(new_audiobook->Author,root->Author)<0)
            {
                root->left = insert_audiobook(root->left,new_audiobook);
            }
            // else if(strcmp(new_audiobook->Author,root->Author)>0)
            else
            {
                root->right = insert_audiobook(root->right,new_audiobook);
            }
        }
    }
    return balance_audiobook(root);
}


user_avl_node *balance_usernode(user_avl_node *root)
{
    if(root==NULL)
    {
        return NULL;
    }
    else
    {
        root->height = 1 + max(height_user(root->left), height_user(root->right));
        if(balance_factor_user(root)>1)
        {
            if(balance_factor_user(root->left)==1)
            {
                root=rotate_right_user(root);
            }
            else if(balance_factor_user(root->left)==-1)
            {
                root->left=rotate_left_user(root->left);
                root=rotate_right_user(root);
            }
        }
        else if(balance_factor_user(root)<-1)
        {
            if(balance_factor_user(root->right)==-1)
            {
                root=rotate_left_user(root);
            }
            else if(balance_factor_user(root->right)==1)
            {
                root->right=rotate_right_user(root->right);
                root=rotate_left_user(root);
            }
        }
        return root;
    }
}

user_avl_node *insert_usernode(user_avl_node *root,user_avl_node *new_user)
{
    if (root == NULL)
        return new_user;
    if (new_user->userid < root->userid)
        root->left = insert_usernode(root->left, new_user);
    else if (new_user->userid > root->userid)
        root->right = insert_usernode(root->right, new_user);
    else
    {
        printf("this user alresdy exist ");
    }
    return balance_usernode(root);
}

audiobooklog_avl_node *balance_audiobooklog(audiobooklog_avl_node *root)
{
    if(root==NULL)
    {
        return NULL;
    }
    else
    {
        root->height = 1 + max(height_audiobooklog(root->left), height_audiobooklog(root->right));
        if(balance_factor_audiobooklog(root)>1)
        {
            if(balance_factor_audiobooklog(root->left)==1)
            {
                root=rotate_right_audiobooklog(root);
            }
            else if(balance_factor_audiobooklog(root->left)==-1)
            {
                root->left=rotate_left_audiobooklog(root->left);
                root=rotate_right_audiobooklog(root);
            }
        }
        else if(balance_factor_audiobooklog(root)<-1)
        {
            if(balance_factor_audiobooklog(root->right)==-1)
            {
                root=rotate_left_audiobooklog(root);
            }
            else if(balance_factor_audiobooklog(root->right)==1)
            {
                root->right=rotate_right_audiobooklog(root->right);
                root=rotate_left_audiobooklog(root);
            }
        }
        return root;
    }
}


audiobooklog_avl_node *insert_audiobooklog(audiobooklog_avl_node *root,audiobooklog_avl_node *new_user)
{
    if (root == NULL)
        return new_user;
    if (new_user->ID < root->ID)
        root->left = insert_audiobooklog(root->left, new_user);
    else if (new_user->ID > root->ID)
        root->right = insert_audiobooklog(root->right, new_user);
    else
    {
        printf("this user alresdy exist ");
    }
    return balance_audiobooklog(root);
}

audiobook_avl_node *search_for_audiobook(audiobook_avl_node *root,int id)
{
    if(root==NULL)
    {
        return NULL;
    }
    else
    {
        if(root->AudiobookId==id)
        {
            return root;
        }
        else
        {
            audiobook_avl_node *temp1=search_for_audiobook(root->left,id);
            audiobook_avl_node *temp2=search_for_audiobook(root->right,id);
            if(temp1!=NULL)
            {
                return temp1;
            }
            else if(temp2!=NULL)
            {
                return temp2;
            }
            else
            {
                return NULL;
            }
        }
    }
}

audiobook_avl_node *search_for_audiobook_based_on_title(audiobook_avl_node *root,char title[])
{
    if(root==NULL)
    {
        return NULL;
    }
    else
    {
        if(strcmp(root->title,title)==0)
        {
            return root;
        }
        else
        {
            audiobook_avl_node *temp1=search_for_audiobook_based_on_title(root->left,title);
            audiobook_avl_node *temp2=search_for_audiobook_based_on_title(root->right,title);
            if(temp1!=NULL)
            {
                return temp1;
            }
            else if(temp2!=NULL)
            {
                return temp2;
            }
            else
            {
                return NULL;
            }
        }
    }
}

audiobook_avl_node *search_for_audiobook_based_on_author(audiobook_avl_node *root,char author[])
{
    if(root==NULL)
    {
        return NULL;
    }
    else
    {
        if(strcmp(root->Author,author)==0)
        {
            return root;
        }
        else
        {
            audiobook_avl_node *temp1=search_for_audiobook_based_on_author(root->left,author);
            audiobook_avl_node *temp2=search_for_audiobook_based_on_author(root->right,author);
            if(temp1!=NULL)
            {
                return temp1;
            }
            else if(temp2!=NULL)
            {
                return temp2;
            }
            else
            {
                return NULL;
            }
        }
    }
}



user_avl_node* search_user_on_id(user_avl_node* root, int key)
{
    if (root == NULL || root->userid == key)
        return root;

    if (root->userid < key)
    {
        return search_user_on_id(root->right, key);
    }
    else
    {
         search_user_on_id(root->left, key);
    }
}

audiobooklog_avl_node *search_audiobook_in_user(audiobooklog_avl_node* root, int key)
{
    if (root == NULL || root->ID== key)
        return root;

    if (root->ID < key)
    {
        return search_audiobook_in_user(root->right, key);
    }
    else
    {
         search_audiobook_in_user(root->left, key);
    }
}

user_avl_node *search_for_user_based_on_email(user_avl_node *root,char mail[])
{
    if(root==NULL)
    {
        return NULL;
    }
    else
    {
        if(strcmp(root->email,mail)==0)
        {
            return root;
        }
        else
        {
            user_avl_node *temp1=search_for_user_based_on_email(root->left,mail);
            user_avl_node *temp2=search_for_user_based_on_email(root->right,mail);
            if(temp1!=NULL)
            {
                return temp1;
            }
            else if(temp2!=NULL)
            {
                return temp2;
            }
            else
            {
                return NULL;
            }
        }
    }
}

audiobooklog_avl_node* search_user_audiobook_on_id(audiobooklog_avl_node* root, int key)
{
    if (root == NULL || root->ID == key)
        return root;

    if (root->ID < key)
    {
        return search_user_audiobook_on_id(root->right, key);
    }
    else
    {
         search_user_audiobook_on_id(root->left, key);
    }
}


audiobook_avl_node *minValueNode_audiobook(audiobook_avl_node *node) {
    audiobook_avl_node *current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

audiobook_avl_node *deleteNode_audiobook(audiobook_avl_node *root,audiobook_avl_node *del) {
    if (root == NULL)
        return root;
    if (strcmp(del->title,root->title)<0)
        root->left = deleteNode_audiobook(root->left,del);
    else if (strcmp(del->title,root->title)>0)
        root->right = deleteNode_audiobook(root->right,del);
    else {
        if (root->left == NULL) {
            audiobook_avl_node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            audiobook_avl_node *temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children: Get the inorder successor (smallest in the right subtree)
        audiobook_avl_node *temp = minValueNode_audiobook(root->right);

        // Copy the inorder successor's data to this node
       
       strcpy(root->Author,temp->Author);
       strcpy(root->genre,temp->genre);
       strcpy(root->duration,temp->duration);
       strcpy(root->narrator,temp->narrator);
       strcpy(root->title,temp->title);
       root->count_rating=temp->count_rating;
       root->sum_rating=temp->sum_rating;
       root->AudiobookId=temp->AudiobookId;
     
        // Delete the inorder successor
        root->right = deleteNode_audiobook(root->right,temp);
    }

    // If the tree had only one node, then return
    if (root == NULL)
        return root;

    // Update height of the current node
    root->height = 1 + max(height(root->left), height(root->right));

    // Rebalance the tree starting from the root
    return balance_audiobook(root);
}

audiobooklog_avl_node *minValueNode_audiobooklog(audiobooklog_avl_node *node) {
    audiobooklog_avl_node *current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

audiobooklog_avl_node *deleteNode_audiobooklog(audiobooklog_avl_node *root, int key) {
    if (root == NULL)
        return root;

    if (key < root->ID)
        root->left = deleteNode_audiobooklog(root->left, key);

    else if (key > root->ID)
        root->right = deleteNode_audiobooklog(root->right, key);

    // If the key is the same as the root's key, then this is the node to be deleted
    else {
        // Node with only one child or no child
        if (root->left == NULL) {
            audiobooklog_avl_node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            audiobooklog_avl_node *temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children: Get the inorder successor (smallest in the right subtree)
        audiobooklog_avl_node *temp = minValueNode_audiobooklog(root->right);

        // Copy the inorder successor's data to this node
        root->ID = temp->ID;

        // Delete the inorder successor
        root->right = deleteNode_audiobooklog(root->right, temp->ID);
    }

    // If the tree had only one node, then return
    if (root == NULL)
        return root;

    // Update height of the current node
    root->height = 1 + max(height_audiobooklog(root->left), height_audiobooklog(root->right));

    // Rebalance the tree starting from the root
    return balance_audiobooklog(root);
}


// 1 --- a  -> add audiobook 
void add_Audiobook(audiobook_avl_node **root)
{
    audiobook_avl_node *new_node = createAudiobook();
    if(*root==NULL)
    {
        *root=new_node;
        printf("Insertion Successful \n");
    }
    else
    {   
        if(search_for_audiobook(*root,new_node->AudiobookId)!=NULL)
        {
            printf("There already exists an audiobook with this Id \n");
        }
        else
        {
          *root=insert_audiobook(*root,new_node);
          printf("Insertion Successful \n");

        }
    }
}

// 1--b edit audiobook
void edit_audiobook(audiobook_avl_node **root)
{
    int i_d;
    printf("Enter Id of Audiobook you would like to edit \n");
    scanf("%d",&i_d);
    if(search_for_audiobook(*root,i_d)==NULL)
    {
        printf("No such audiobook exists \n");
    }
    else
    {
        audiobook_avl_node *id_node =search_for_audiobook(*root,i_d);
        int f=0;
        int flag;
        char s[MAX_SIZE_OF_TITLE];
        while(f==0)
        {
            printf("Enter  1  if you wish to modify the Title of Audiobook      \n");
            printf("Enter  2  if you wish to modify the  Author of Audiobook \n");
            printf("Enter  3  if you wish to modify the duration of Audiobook \n");

            scanf("%d",&flag);
            if(flag<1||flag>3)
            {
                printf("plese enter a valid number ::\n");
            }
            else
            {
               f=1;
            }
        }
        if(flag==1)
        {
            printf("Enter the Title of Audiobook  : ");
            scanf("%s",s);
            strcpy(id_node->title,s);
            printf("Data successfully modified \n");
        }
         else if(flag==2)
         {  
            printf("Enter the Author of Audiobook  :");
            scanf("%s",s);
            strcpy(id_node->Author,s);
            printf("Data successfully modified \n");
                 
         }
         else if(flag==3)
         {
             printf("Enter the Duration of Audiobook in HH:MM format : ");
             scanf("%s",s);
             strcpy(id_node->duration,s);
             printf("Data successfully modified \n");
         }
    }
}

// 2 --- delete an audiobook 
void delete_audiobook(audiobook_avl_node **root)
{
    char s[MAX_SIZE_OF_EMAIL];
    int flag_;
    int f=0;
    audiobook_avl_node *ptr;
    printf("enter the following details to delete a Audiobook :: \n");
    while(f==0)
    {
        printf("enter  1  if you wish to delete  based on Authors name      \n");
        printf("Enter  0  if you wish to delete  base on Title of Audiobook \n");
        scanf("%d",&flag_);
        if(flag_<0||flag_>1)
        {
            printf("plese enter a valid number ::\n");
                         
        }
        else
        {
            f=1;
        }
    }
    if(flag_==1)
    {
        printf("Enter the Authors name :\n");
        scanf("%s",s);
        ptr=search_for_audiobook_based_on_author(*root,s);
        if(ptr==NULL)
        {
            printf("NO such audiobook exists \n");
        }
        else
        {
           *root =deleteNode_audiobook(*root,ptr);
           printf("audiobook deleted successfully \n");
        }
    }
    else
    {
        printf("Enter the Title of Audiobook :\n");
        scanf("%s",s);
        ptr=search_for_audiobook_based_on_title(*root,s);
        if(ptr==NULL)
        {
            printf("NO such audiobook exists \n");
        }
        else
        {
            *root =deleteNode_audiobook(*root,ptr);
            printf("audiobook deleted successfully \n");
        }
    }
}

// 3 -- add user to userlist
void Add_user_profile(user_avl_node **root)
{
    printf("Enter the details of the User  : \n");
    int iD;
    printf("Enter the userID  : ");
    scanf("%d",&iD);
    if(search_user_on_id(*root,iD)!=NULL)
    {
        printf("User with provided id already exists \n");
    }
    else
    {
        user_avl_node *newUser = (user_avl_node*)malloc(sizeof(user_avl_node));
        newUser->userid=iD;
        printf("Enter email of the user : ");
        char mail[MAX_SIZE_OF_EMAIL];
        scanf("%s", mail);
        if(search_for_user_based_on_email(*root,mail)!=NULL)
        {   
            printf("This email Already Exists  \n");
        }
        else
        {
            strcpy(newUser->email,mail);
            printf("Enter name of the user: ");
            scanf("%s", newUser->name);
            newUser->ptr = NULL;
            newUser->left = NULL;
            newUser->right = NULL;
            newUser->height = 0; 
            char f[MAX_PREFERENCE_TYPE_LENGTH];
            printf("Do you have any preffered genre ? ");
            printf("if yes ! then enter the genre ,  else  enter No    :  ");
            scanf("%s",f);
            strcat(f,"\n");

            if(strcmp(f,"No")!=0)
            {   
                preferenceNode *p=(preferenceNode*)malloc(sizeof(preferenceNode));
                strcpy( p->preferenceType,"genre");
                strcpy(p->preferenceValue,f);
                p->next=newUser->preferences;
                newUser->preferences=p;
            }
            printf("Do you have any preffered author ? ");
            printf("if yes ! then enter the name of author  ,  else  enter No    :  ");
            scanf("%s",f);
            strcat(f,"\n");
            if(strcmp(f,"No")!=0)
            {   
                preferenceNode *q=(preferenceNode*)malloc(sizeof(preferenceNode));
                strcpy( q->preferenceType,"author");
                strcpy(q->preferenceValue,f);
                q->next=newUser->preferences;
                newUser->preferences=q;
            }
             printf("Do you have any preffered narrator ? ");
            printf("if yes ! then enter the name of narrator  ,  else  enter No     :  ");
            scanf("%s",f);
            strcat(f,"\n");
            if(strcmp(f,"No")!=0)
            {   
                preferenceNode *r=(preferenceNode*)malloc(sizeof(preferenceNode));
                strcpy( r->preferenceType,"narrator");
                strcpy(r->preferenceValue,f);
                r->next=newUser->preferences;
                newUser->preferences=r;
            }
            *root = insert_usernode(*root,newUser);
            printf("new user created successfully \n");

        }
    }
}

// 4 -- add audiobook to user 



void add_to_user_library(audiobook_avl_node **list,user_avl_node **root)
{
    int id;
    char ch;
    printf("Enter the following Details to update the user library  :\n");
    printf("Enter the user ID  :  ");
    scanf("%d",&id);
    getchar();
    if(search_user_on_id(*root,id)==NULL)
    {
        printf("This user does not exist \n");
    }
    else
    {
        printf("enter y  if you wish to add an Audiobook to user log  \n");
        printf("enter n  if you wish to delete an Audiobook from user log \n ");
        printf("enter  :  ");
        scanf("%c",&ch);
        user_avl_node *user = search_user_on_id(*root,id);
        if(ch=='y')
        {
            printf("Enter the Details of Audiobook : \n");
            int iD;
            printf("Enter the id of Audiobook   :"  );
            scanf("%d",&iD);
            if(search_user_audiobook_on_id(user->ptr,iD)!=NULL)
            {
                printf("This Audiobook Already Exists in Audiobooklog of User \n");
            }
            else
            {
               audiobooklog_avl_node *new_node=createAudiobookLogNode(iD);
               if(search_for_audiobook(*list,iD)==NULL)
               {
                  printf("This audiobook is not Available on Audiobook list \n");
               }
               else
               {  
                  new_node->book=search_for_audiobook(*list,iD);
                  user->ptr=insert_audiobooklog(user->ptr,new_node);
                  printf("new audiobook added successfully  \n");
               }
            }
        }
        else if(ch=='n')
        {  
            printf("Enter the Details of Audiobook : \n");
            int iD;
            printf("Enter the id of Audiobook you wish to delete   :"  );
            scanf("%d",&iD);
            audiobooklog_avl_node *ttemp=search_user_audiobook_on_id(user->ptr,iD);
            if(ttemp==NULL)
            {
                printf("This Audiobook is not part of audiobooklog of user  \n");
            }
            else
            {   
                if(ttemp->rating!=0)
                {
                    ttemp->book->sum_rating-=ttemp->rating;
                    ttemp->book->count_rating--;
                }
                user->ptr=deleteNode_audiobooklog(user->ptr,iD);

                printf("Audiobook successfully delted \n");
            }
        }
    }
}

// 5 -- search for audiobook


void find_audiobook_title(audiobook_avl_node *root,char t[])
{   
    if(root==NULL)
    {
        return ;
    }
    else
    {
        if(strcmp(root->title,t)==0)
        {
           printf("Id of Audiobook  : %d\n",root->AudiobookId);
        }
        find_audiobook_title(root->left,t);
        find_audiobook_title(root->right,t);
        return;
    }
}

void find_audiobook_author(audiobook_avl_node *root,char a[])
{
    if(root==NULL)
    {
        return ;
    }
    else
    {
        if(strcmp(root->Author,a)==0)
        {
           printf("Id of Audiobook  : %d\n",root->AudiobookId);
        }
        find_audiobook_author(root->left,a);
        find_audiobook_author(root->right,a);
        return;
    }
}

void find_audiobook_genre(audiobook_avl_node *root,char g[])
{
    if(root==NULL)
    {
        return;
    }
    else
    {
        if(strcmp(root->genre,g)==0)
        {
           printf("Id of Audiobook  : %d\n",root->AudiobookId);
        }
        find_audiobook_genre(root->left,g);
        find_audiobook_genre(root->right,g);
        return;
    }
}

void search_audiobook(audiobook_avl_node *root)
{
    char st[MAX_SIZE_OF_TITLE];
    int flag1;
    int f1=0;
    printf("enter the following details to search for an Audiobook :: \n");
    while(f1==0)
    {
        printf("Enter  1  if you wish to search based on Title of Audiobook      \n");
        printf("Enter  2  if you wish to search  based on Genre of Audiobook \n");
        printf("Enter  3  if you wish to search  based on Author of Audiobook \n");
        scanf("%d",&flag1);
        if(flag1<1||flag1>3)
        {
            printf("plese enter a valid number ::\n");
        }
        else
        {
            f1=1;
        }
    }
    if(flag1==1)
    {
    
        printf("Enter the Title of Audiobook :\n");
        scanf("%s",st);
        find_audiobook_title(root,st);

    }
    else if(flag1==2)
    {
        printf("Enter the genre of Audiobook :\n");
        scanf("%s",st);
        find_audiobook_genre(root,st);
    }
    else
    {
        printf("Enter the Author of Audiobook :\n");
         scanf("%s",st);
        find_audiobook_author(root,st);
    }
}

// 6 --- listening progress

/*Adds two timestamps to give a new timestamp */
 /*eg ,,  05:30 + 00:35 = 06:05 */
char *addstrings(char old[], char new[]) {
    int old_hours = (old[0] - '0') * 10 + (old[1] - '0');
    int old_minutes = (old[3] - '0') * 10 + (old[4] - '0');
    int new_hours = (new[0] - '0') * 10 + (new[1] - '0');
    int new_minutes = (new[3] - '0') * 10 + (new[4] - '0');
    int total_hours = old_hours + new_hours;
    int total_minutes = old_minutes + new_minutes;
    if (total_minutes > 59) {
        total_hours += total_minutes / 60;
        total_minutes %= 60;
    }
    char *result = (char *)malloc(6 * sizeof(char)); 
     result[0] = total_hours / 10 + '0';
    result[1] = total_hours % 10 + '0';
    result[2] = ':';
    result[3] = total_minutes / 10 + '0';
    result[4] = total_minutes % 10 + '0';
    result[5] = '\0';
    return result;
}

void listening_progress(user_avl_node **root)
{   
    int id;
    printf("Enter Details of user you would like to update  :\n");
    printf("Enter user Id  : ");
    scanf("%d",&id);
    if(search_user_on_id(*root,id)==NULL)
    {
        printf("No user exists with given id  \n");
    }
    else
    {
        user_avl_node *user=search_user_on_id(*root,id);
        printf("Enter Id of Audiobook you would like to update  : ");
        scanf("%d",&id);
        if(search_audiobook_in_user(user->ptr,id)==NULL)
        {
            printf("This Audiobook do not exist in Auiobooklog \n");
        }
        else
        {
            audiobooklog_avl_node *userlog=search_audiobook_in_user(user->ptr,id);
            char ts[6];
            printf("Enter the new Timestamp  :  ");
            scanf("%s",ts);
            strcpy(userlog->timestamp,strcat(addstrings(userlog->timestamp,ts) , "\n")); /*updating timestamp of Audiobook log of user */
            printf("timestamp updated successfully  \n"); 
        }
    }
}


// 7 DISPLAY USER LIBRARY
// CREATE DUPLICATE AudioBook
audiobooklog_avl_node* create_duplicate(audiobooklog_avl_node* abl){
    audiobooklog_avl_node* ret = (audiobooklog_avl_node*)malloc(sizeof(audiobooklog_avl_node));
    ret -> ID = abl -> ID;
    ret -> book = abl -> book;
    ret -> height = 0;
    ret -> right = NULL;
    ret -> left = NULL;
    ret -> rating = abl -> rating;
    strcpy(ret -> timestamp , abl -> timestamp);
    return ret;
}
// INSERT AUDIOBOOK LOG BASED ON TIMESTAMP
audiobooklog_avl_node *insert_audiobooklog_timestamp(audiobooklog_avl_node *root,audiobooklog_avl_node *new_user)
{
    if (root == NULL)
        return new_user;
    if (strcmp(new_user -> timestamp , root -> timestamp) < 0)
        root->left = insert_audiobooklog(root->left, new_user);
    else if (strcmp(new_user -> timestamp , root -> timestamp) > 0)
        root->right = insert_audiobooklog(root->right, new_user);
    else
    {
        printf("this user alresdy exist ");
    }
    return balance_audiobooklog(root);
}
//PRINT IN DESCENDING ORDER OF TIME STAMP
void print_highest_timestamp(audiobooklog_avl_node* abl){
    if(abl){
        print_highest_timestamp(abl -> right);
        printf("AB ID   :  %d\n" , abl -> ID);
        printf("timestamp   :  %s\n" , abl -> timestamp);
        print_highest_timestamp(abl -> left);
    }
}
// all AB
void all_audiobook(audiobooklog_avl_node* abl , audiobooklog_avl_node** new_root){
    if(abl){
        audiobooklog_avl_node* temp = create_duplicate(abl);
        *new_root = insert_audiobooklog_timestamp(*new_root , temp);
        all_audiobook(abl -> left , new_root);
        all_audiobook(abl -> right , new_root);
    }
}
// by genre
void by_genre(audiobooklog_avl_node* abl , char genre[MAX_SIZE_OF_GENRE] , audiobooklog_avl_node** new_root){
    if(abl){
        if(strcmp(abl -> book -> genre , genre) == 0){
            audiobooklog_avl_node* temp = create_duplicate(abl);
            *new_root = insert_audiobooklog_timestamp(*new_root , temp);
        }
        by_genre(abl -> left , genre , new_root);
        by_genre(abl -> right , genre , new_root);
    }
}


// 8 -- rate an audiobook
void Rate_audiobook(user_avl_node **ul, audiobook_avl_node **ab) {   
    int userId, audiobookId, rating;
    
    printf("Enter ID of user: ");
    scanf("%d", &userId);
    
    // Check if the user exists
    user_avl_node *userNode = search_user_on_id(*ul, userId);
    if (userNode == NULL) {
        printf("This user does not exist.\n");
    } else {
        printf("Enter ID of the audiobook you would like to rate: ");
        scanf("%d", &audiobookId);
        
        // Check if the audiobook exists in the user's playlist
        audiobooklog_avl_node *logNode = search_audiobook_in_user(userNode->ptr, audiobookId);
        if (logNode == NULL) {
            printf("This audiobook does not exist in the user's playlist.\n");
        } else {
            printf("Enter new rating (1-5): ");
            scanf("%d", &rating);
            
                if(logNode->rating== 0)
                {
                    logNode->book->count_rating++;
                    logNode->book->sum_rating += rating;
                }
                else
                {
                    logNode->book->sum_rating=logNode->book->sum_rating-logNode->rating + rating;
                    
                }
                logNode->rating=rating;
                printf("Audiobook successfully rated.\n");
            
        }
    }
}



//  9 MOST POPULR AUDIO BOOK
void most_popular(audiobook_avl_node* AB , float* max_rat){
    if(AB){
        float rating = (AB -> sum_rating * 1.0)/AB -> count_rating;
        if(rating > *max_rat){
            *max_rat = rating;
        }
        most_popular(AB -> left , max_rat);
        most_popular(AB -> right , max_rat);
    }
}

void print_9(audiobook_avl_node* AB , float rating){
    if(AB){
        int curr_rating = (AB -> sum_rating * 1.0)/AB -> count_rating;
        if(curr_rating == rating){
            printNodeDetails_audiobook(AB);
        }
        print_9(AB -> left , rating);
        print_9(AB -> right , rating);
    }
}


//convert time into minutes
int convert(char timestamp[]){
    int retval = (int)(timestamp[0] - '0');
    retval = (retval * 10) + (int)(timestamp[1] - '0');
    retval = retval * 60;
    int min = (int)(timestamp[3] - '0');
    min = (10 * min) + (int)(timestamp[4] - '0');
    retval += min;
    return retval; 
}

// 10 LISTENING HISTORY REPORT USER
int display_10(audiobooklog_avl_node* abl){
    int ret_val = 0;
    if(abl){
        ret_val += display_10(abl -> left);
        printf("AB ID   :  %d\n" , abl -> ID);
        printf("title   :  %s\n" , abl -> book -> title);
        printf("author  :  %s\n" , abl -> book -> Author);
        printf("timestamp   :  %s\n" , abl -> timestamp);
        ret_val += convert(abl -> timestamp);
        ret_val += display_10(abl -> right);
    }
    return ret_val;
}

user_avl_node* listening_10(user_avl_node* UL , int userID){
    user_avl_node* ret = NULL;
    if(UL){
        if(UL -> userid == userID){
            ret = UL;
            printf("user ID   :  %d\n" , UL -> userid);
            printf("user name   :  %s\n" , UL -> name);
            printf("user library   :\n");
            int listening_time = display_10(ret -> ptr);
            printf("total listening time  :  %d hr  %d min\n" , listening_time/60 , listening_time%60);
        }
        else{
            if(UL -> userid > userID){
                ret = listening_10(UL -> left , userID);
            }
            else{
                ret = listening_10(UL -> right , userID);
            }
        }
    }
    return ret;
}


// 12 LISTENING HISTORY REPORT AUDIOBOOK

audiobooklog_avl_node* match_abl_ID(audiobooklog_avl_node* abl , int ID){
    audiobooklog_avl_node* ret = NULL;
    if(abl){
        if(abl -> ID == ID){
            ret = abl;
        }
        else{
            if(abl -> ID > ID){
                ret = match_abl_ID(abl -> left , ID);
            }
            else{
                ret = match_abl_ID(abl -> right , ID);
            }
        }
        return ret;
    }
}

int listening_history_report_AB(user_avl_node* UL , int AB_ID , int* flag){
    int ret_val = 0;
    if(UL){
        audiobooklog_avl_node* temp = match_abl_ID(UL -> ptr , AB_ID);
        if(temp){
            if(*flag == 0){
                printf("ID   :  %d\n" , AB_ID);
                printf("title   :  %s\n" , temp -> book -> title);
                printf("author   :  %s\n\n" , temp -> book -> Author);
                *flag = 1;
            }
            printf("user ID   :  %d\n" , UL -> userid);
            printf("user timestamp   :  %s\n" , temp -> timestamp);
            ret_val += convert(temp -> timestamp);
        }
        ret_val += listening_history_report_AB(UL -> left , AB_ID , flag);
        ret_val += listening_history_report_AB(UL -> right , AB_ID , flag);
    }
    return ret_val;
}

//  13 RANGE _ SEARCH _ AUDIOBOOK
void range_search(audiobook_avl_node* AB , int id1 , int id2){
    if(AB){
        if(AB -> AudiobookId >= id1 && AB -> AudiobookId <= id2){
            printf("ID   :  %d\n" , AB -> AudiobookId);
            printf("title   :  %s\n\n" , AB -> title);
        }
        range_search(AB -> left , id1 , id2);
        range_search(AB -> right , id1 , id2);
    }
}

void update_abl(audiobooklog_avl_node* abl , FILE* file)
{
    if(abl)
    {
        update_abl(abl -> left , file);
        char line[50];
        sprintf(line, "%d", abl->ID);      /*converting int to char array */
        fprintf(file, "%s\n", line);
        fprintf(file, "%s", abl->timestamp);
        sprintf(line, "%f", abl->rating);      /*converting float to char array */
        fprintf(file, "%s\n", line);
        update_abl(abl -> right , file);
    }
}

void update_UL(user_avl_node* UL , FILE* file)
{
    if(UL)
    {
        char line[50];
        update_UL(UL -> left , file);
        fprintf(file, "#\n");        /*Every user starts with '#' */
        sprintf(line, "%d", UL->userid);           /*converting int to char array */
        fprintf(file, "%s\n\n", line);

        fprintf(file, "%s\n\n", UL->name);
        fprintf(file, "%s\n\n", UL->email);

        preferenceNode* trav_pn = UL->preferences;
        while (trav_pn) {
            fprintf(file, "%s\n", trav_pn->preferenceType);
            fprintf(file, "%s", trav_pn->preferenceValue);
            trav_pn = trav_pn->next;
        }
        fprintf(file, "\n");

        update_abl(UL -> ptr , file);
        fprintf(file, "\n");
        update_UL(UL -> right , file);
    }
}

void update_AB(audiobook_avl_node* AB , FILE* file)
{
    if(AB)
    {
        char line[50];
        update_AB(AB -> left , file);
        fprintf(file, "@\n");         /*every Audiobook starts with '@' */
        sprintf(line, "%d", AB->AudiobookId);    /*converting int to char array */
        fprintf(file, "%s\n\n", line);

        fprintf(file, "%s\n\n", AB->title);

        fprintf(file, "%s\n", AB->Author);
        fprintf(file, "\n");

        fprintf(file, "%s\n\n", AB->narrator);
        fprintf(file, "%s\n\n", AB->duration);
        fprintf(file, "%s\n\n", AB->genre);

        sprintf(line, "%f", AB->sum_rating);     /*converting float into char array */
        fprintf(file, "%s\n\n", line);

        sprintf(line, "%d", AB->count_rating);       /*converting int to char array */
        fprintf(file, "%s\n\n", line);
        update_AB(AB -> right , file);
    }
}

int main() {
    
    audiobook_avl_node* AB = NULL;
    user_avl_node* UL = NULL;

    FILE* file;
    file = fopen("dspd2new.txt" , "r");
    if(file == NULL){
        printf("error in opening file\n");
        return 1;
    }

    char line[1024];
    int flag = 0;
    int mode = 1;
    user_avl_node* temp_UL = (user_avl_node*)malloc(sizeof(user_avl_node));
    audiobook_avl_node* temp_AB = (audiobook_avl_node*)malloc(sizeof(audiobook_avl_node));
    int i = 0;

    while(fgets(line , sizeof(line) , file) != NULL){          /*loop runs till file is empty */
        line[strlen(line) - 1] = '\0';
        if(line[0] == '@'){                             /*if line[0]==@ the its an Audiobook */
            initialise_Audiobook(temp_AB);
            flag = 0;
            mode = 1;
        }

        else if(line[0] == '#'){                     /*if line[0]==# the its a uselist  */
            initialise_user(temp_UL);
            flag = 1;
            mode = 1;
        }
        
        else{
            if(line[0] == '\0'){             /*Every mode corresponds to new type of information */
                mode++;
                if(flag == 0 && mode == 9){
                    AB = insert_audiobook(AB , temp_AB);
                    temp_AB = (audiobook_avl_node*)malloc(sizeof(audiobook_avl_node));
                }
                else if(flag == 1 && mode == 6){
                    UL = insert_usernode(UL , temp_UL);
                    temp_UL = (user_avl_node*)malloc(sizeof(user_avl_node));
                }
            }

            else{
                if(flag == 0){      /*flag==0    -->  audiobook info is being updated */
                    switch(mode){
                        case 1:
                             temp_AB -> AudiobookId = atoi(line);
                             break;
                        case 2:
                             strcpy(temp_AB -> title , line);
                             break;
                        case 3:
                        {
                             strcpy(temp_AB -> Author , line);    
                             break;
                        }
                        case 4:
                             strcpy(temp_AB -> narrator , line);
                             break;
                        case 5:
                             strcpy(temp_AB -> duration , line);
                             break;
                        case 6:
                             strcpy(temp_AB -> genre , line);
                             break;
                        case 7:
                             temp_AB -> sum_rating = atof(line);
                             break;
                        case 8:
                             temp_AB -> count_rating = atoi(line);
                        default:
                             break;
                    }
                }
                else{               /*flag==1    -->  user info is being updated */
                    switch(mode){
                        case 1:
                             temp_UL -> userid = atoi(line);
                             break;
                        case 2:
                             strcpy(temp_UL -> name , line);
                             break;
                        case 3:
                             strcpy(temp_UL -> email , line);
                             break;
                        case 4:
                        {
                             preferenceNode* temp_pn = temp_UL -> preferences;
                             while(temp_pn && temp_pn -> next){
                                temp_pn = temp_pn -> next;
                             }
                             preferenceNode* pfrn = (preferenceNode*)malloc(sizeof(preferenceNode));
                             strcpy(pfrn -> preferenceType , line);
                             fgets(line , sizeof(line) , file);
                             strcpy(pfrn -> preferenceValue , line);
                             pfrn -> next = NULL;
                             if(temp_pn == NULL){
                                temp_UL -> preferences = pfrn;
                             }
                             else{
                                temp_pn -> next = pfrn;
                             }
                             break;
                        }
                        case 5:
                        {
                             audiobooklog_avl_node* abl = (audiobooklog_avl_node*)malloc(sizeof(audiobooklog_avl_node));
                             abl -> ID = atoi(line);
                             fgets(line , sizeof(line) , file);
                             strcpy(abl -> timestamp , line);
                             fgets(line , sizeof(line) , file);
                             abl -> rating = atof(line);
                             abl -> height = 0;
                             abl -> left = NULL;
                             abl -> right = NULL;
                             abl -> book = match_AB_IB(AB , abl -> ID);
                             temp_UL -> ptr = insert_audiobooklog(temp_UL -> ptr , abl);
                             break;
                        }
                        default:
                             break;
                    }
                }
            }
        }
    }
    // int flag_12 = 0;
    // int lis = listening_history_report_AB(UL , 5, &flag_12);
    // printf("hours : %d\nmin  : %d\n" , lis/60 , lis%60);
    // user_avl_node* temp_10 = listening_10(UL , 1);
    // if(temp_10 == NULL){
    //     printf("no\n");
    // }
    // printf("end of switch\n");
    // display_AB(AB);
    // display_UL(UL);
    // int flag_que = 0;
    // while(flag_que == 0){
    //     int que_no;
    //     printf("enter the ques num  : ");
    //     scanf("%d" , &que_no);
    //     switch(que_no){
    //         case 9:
    //         {
    //             float temp_9 = 0.0;
    //             most_popular(AB , &temp_9);
    //             if(temp_9 == 0.0){
    //                 printf("no audiobooks are not rated yet\n");
    //             }
    //             else{
    //                 print_9(AB , temp_9);
    //             }
    //             break;
    //         }
    //         default:
    //             break;
    //     }
    //     printf("to continue enter 0 , to exit enter 1  : ");
    //     scanf("%d" , &que_no);
    //     if(que_no == 1){
    //         flag_que = 1;
    //     }
    // }
 
  int t_flag=0;
  while(t_flag==0)
  {
        system("cls");
        printf("Enter  1  if  you wish to Add or Edit an AudioBook  \n");
        printf("Enter  2  if  you wish to  delete an AudioBook  \n");
        printf("Enter  3  if  you wish to Add a User to UserList \n");
        printf("Enter  4  if  you wish  to add an Audiobook to Audiobook log of an User \n");
        printf("Enter  5  if  you wish  to  search an AudioBook  \n");
        printf("Enter  6  if  you wish  to  update the Timestamp of AudioBook  \n");
        printf("Enter  7  if  you wish to Display User Libraries \n");
        printf("Enter  8  if  you wish to Rate an AudioBook \n");
        printf("Enter  9  if  you wish to find out the Most Popular AudioBook \n");
        printf("Enter  10  if  you wish to display Listening Progress Report of user \n");
        printf("Enter  12  if  you wish to display Listening History report of an Audiobook \n");
        printf("Enter  13  if  you wish to search audiobooks providing ranges \n\n");
       
        int n,flag_=0;
       while(flag_==0)
       {
          printf("Enter a Valid Number (1-13)  :   "); 
          scanf("%d",&n);
          if(n<1||n>13)
         {
            printf(" Please  Enter  a  Valid  Number ! ! ! \n");
         }
         else
        {
          flag_=1; 
        }
       }

        switch(n){

            case 1:
            {
                int s;
                int g=0;
                while(g==0)
                {
                    printf("Enter 1 if you wish to add an AudioBook   \n");
                    printf("Enter 2 if you wish to edit an AudioBook   \n");
                    printf("enter  :  ");
                    scanf("%d",&s);
                    if(s==1||s==2)
                    {
                        g=1;
                    }
                    else
                    {
                        printf("Please Enter a valid number :  \n");
                    }
                }
                if(s==1)
                {
                    add_Audiobook(&AB);
                }
                else if(s==2)
                {
                    edit_audiobook(&AB);
                    printf("\n");
                }
                break;
            }
            case 2:
            {
                  delete_audiobook(&AB);
                  printf("\n");
                  break;

            }
            case 3:
            {
                 Add_user_profile(&UL);
                 printf("\n");
                 break;
            }
            case 4:
            {
                add_to_user_library(&AB,&UL);
                break;

            }
            case 5:
            {
                search_audiobook(AB);
                break;
            }
            case 6:
            {
                listening_progress(&UL);
                break;
            }
            case 7:
            {
                 int id_7;
                printf("enter the user ID   : ");
                scanf("%d" , &id_7);
                printf("enter 1 to get filtered by genre :\n");
                printf("enter 2 to get all audiobooks  : ");
                int filter_7;
                scanf("%d" , &filter_7);
                if(filter_7 == 1){
                    char genre_7[MAX_SIZE_OF_GENRE];
                    printf("enter the preffered genre  :  ");
                    scanf("%s" , genre_7);
                    user_avl_node* temp_7 = search_user_on_id(UL , id_7);
                    if(temp_7 == NULL){
                        printf("user with given ID doen not exist\n");
                    }
                    else{
                        audiobooklog_avl_node* new_root = NULL;
                        by_genre(temp_7 -> ptr , genre_7 , &new_root);
                        if(new_root == NULL){
                            printf("no audibook exist with given genre\n");
                        }
                        else{
                            print_highest_timestamp(new_root);
                        }
                    }
                }
                else if(filter_7 == 2){
                    user_avl_node* temp_7 = search_user_on_id(UL , id_7);
                    if(temp_7 == NULL){
                        printf("user with given ID doen not exist\n");
                    }
                    else{
                        audiobooklog_avl_node* new_root = NULL;
                        all_audiobook(temp_7 -> ptr , &new_root);
                        if(new_root == NULL){
                            printf("no audibook are prsent\n");
                        }
                        else{
                            print_highest_timestamp(new_root);
                        }
                    }
                }
                else{
                    printf("enter valid number\n");
                }

                break;
            }
            case 8:
            {
                Rate_audiobook(&UL,&AB);
                break;
            }
            case 9:
            {
                float temp_9 = 0.0;
                most_popular(AB , &temp_9);
                if(temp_9 == 0.0){
                    printf("no audiobooks are not rated yet\n");
                }
                else{
                    print_9(AB , temp_9);
                }
                break;
            }
            case 10:
            {
                int id_10;
                printf("enter the user ID   :  ");
                scanf("%d" , &id_10);
                user_avl_node* temp_10 = listening_10(UL , id_10);
                if(temp_10 == NULL){
                    printf("no such user exist with given ID\n");
                }
                break;
            }
            case 11:
            {
                break;
            }
            case 12:
            {
                int flag_12 = 0;
                printf("enter the audiobook ID   :  ");
                int id_12;
                scanf("%d" , &id_12);
                int lis = listening_history_report_AB(UL , id_12, &flag_12);
                printf("hours : %d\nmin  : %d\n" , lis/60 , lis%60);
                break;
            }
            case 13:
            {
                printf("enter the 2 audiobook ID's  :\n");
                int id1,id2;
                scanf("%d" , &id1);
                scanf("%d",&id2);
                range_search(AB  , id1 , id2);
                break;
            }
            
        }
       printf("\n\n");
       printf("Enter y if you wish to continue the operation  \n");
       printf("Enter n  to  terminate the operation  \n");
       printf("Enter     :   ");
       char ch;
       fflush(stdin);
       scanf("%c",&ch);
       if(ch=='n')
       {
           t_flag=1;
       }
  }
     system("cls");
    display_AB(AB);
    printLevelOrderWithSpaces(AB);

    display_UL(UL);
    printLevelOrderWithSpaces_user(UL);
    FILE* file_AB = fopen("new_AudioBook.txt" , "w");
    update_AB(AB , file_AB);
    fclose(file_AB);
    FILE* file_UL = fopen("new_UL.txt" , "w");
    update_UL(UL , file_UL);
    fclose(file_UL);
    printf("Thank you\n");
    
    return 0;
}