/*************************************************************************
        Copyright © 2021 Konstantinidis Konstantinos
	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at
        http://www.apache.org/licenses/LICENSE-2.0
	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*************************************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef int BinTreeElementType;

typedef struct BinTreeNode *BinTreePointer;

 struct BinTreeNode {
    BinTreeElementType Data;    //Data of the nodes
    BinTreePointer LChild, RChild;  //Pointers to the 2 children of the tree nodes
};

typedef enum {
    FALSE, TRUE
}boolean;

void CreateBST(BinTreePointer *Root);
boolean BSTEmpty(BinTreePointer Root);
void RecBSTInsert(BinTreePointer *Root, BinTreeElementType Item, boolean *flag);
int Ceil(BinTreePointer Root, BinTreeElementType Item);
int Floor(BinTreePointer Root, BinTreeElementType Item);

main(){
    BinTreeElementType Item, floor, ceil;
    BinTreePointer Root;
    int amount, i=0;
    boolean flag;

    CreateBST(&Root);

    printf("Enter the amount of numbers you want to insert: ");
    scanf("%d", &amount);

    while(amount<2){
        printf("You cannot have less than 2 numbers\n");
        printf("Enter the amount of numbers you want to insert: ");
        scanf("%d", &amount);
    }

    while(i<amount){
        flag = TRUE;
        printf("Enter number to insert in the BST: ");
        scanf("%d", &Item);

        while(Item<0){
            printf("You cannot have a negative number\n");
            printf("Enter number to insert in the BST:");
            scanf("%d", &Item);
        }

        RecBSTInsert(&Root, Item, &flag); //Try to insert the number in the tree
        if(flag)    //If the flag became false then the number is already in the tree
            i++;
    }

    while(TRUE){
        printf("Enter a number to search (If you want to terminate the search enter a negative number): ");
        scanf("%d", &Item);

        if(Item<0){
            printf("Terminating program..\n");
            break;
        }
        else{
            ceil = Ceil(Root, Item);
            printf("Ceiling: %d \n", ceil);

            floor = Floor(Root, Item);
            printf("Floor: %d \n", floor);
        }
    }
    system("PAUSE");
}

//Function that creates a BST
void CreateBST(BinTreePointer *Root){
    *Root = NULL;
}

//Function to see if the BST is empty
boolean BSTEmpty(BinTreePointer Root){
    return (Root==NULL);
}

//Function that insert a number in the BST in the correct place
//If the number is already in the BST then the flag becomes false
void RecBSTInsert(BinTreePointer *Root, BinTreeElementType Item, boolean *flag){
    if(BSTEmpty(*Root)){
        (*Root) = (BinTreePointer)malloc(sizeof (struct BinTreeNode));
        (*Root)->Data = Item;
        (*Root)->LChild =  NULL;
        (*Root)->RChild = NULL;
    }
    else
        if(Item < (*Root)->Data){
            RecBSTInsert(&(*Root)->LChild, Item, flag);
        }
        else if(Item > (*Root)->Data){
            RecBSTInsert(&(*Root)->RChild, Item, flag);
        }
        else{
            printf("%d Is already in the BST\n", Item);
            *flag = FALSE;
        }
}

//Function that finds the ceiling of the number the user asked to search for
//Ceiling is the next biggest number in the BST, in
//comparison to the one the user asked to search for
int Ceil(BinTreePointer Root, BinTreeElementType Item){
    BinTreeElementType ceil;

    if(BSTEmpty(Root))
        return -1;
    else if(Root->Data == Item)
        return Root->Data;
    else if(Root->Data < Item)
        return Ceil(Root->RChild, Item);
    else
        ceil = Ceil(Root->LChild, Item);

    if(ceil == -1)
        return Root->Data;

    return ceil;
}

//Function that finds the floor of the number the user asked to search for
//Floor is the next smallest number in the BST, in
//comparison to the one the user asked to search for
int Floor(BinTreePointer Root, BinTreeElementType Item){
    BinTreeElementType floor;

    if(BSTEmpty(Root))
        return -1;
    else if(Root->Data == Item)
        return Root->Data;
    else if(Root->Data > Item)
        return Floor(Root->LChild, Item);
    else
        floor = Floor(Root->RChild, Item);

    if(floor == -1)
        return Root->Data;

    return floor;
}
