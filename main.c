#include <stdio.h>

#define INPUT_FILENAME "input.txt"

typedef struct node
{
    int value;
    struct node *left;
    struct node *right;   
} node;

node originalArr[5005];
node* workingArr[5005];
int lenArr;


void swapThisAndRight(node *oldLeft)
{
    node* oldRight = oldLeft->right;

    oldLeft->right = oldRight->right;
    oldLeft->right->left = oldLeft;
    oldRight->right = oldLeft;
    oldRight->left = oldLeft->left;
    oldRight->left->right = oldRight;
    oldLeft->left = oldRight;
}



int main()
{
    FILE *pf = fopen(INPUT_FILENAME, "r");
    if (!pf)
    {
        fprintf(stderr, "Can't open input file: %s.\n", INPUT_FILENAME);
        return 1;
    }

    int value;
    fscanf(pf, "%d", &value); //First 
    originalArr[lenArr].value = value;
    lenArr++;
    while (fscanf(pf, "%d", &value) == 1)
    {
        originalArr[lenArr].value = value;
        originalArr[lenArr].left = &originalArr[lenArr-1];
        originalArr[lenArr-1].right = &originalArr[lenArr];
        lenArr++;
    }
    fclose(pf);

    originalArr[lenArr-1].right = &originalArr[0];
    originalArr[0].left = &originalArr[lenArr-1];

    for(node *curr = originalArr, *endArr = originalArr + lenArr; curr != endArr; curr++)
    {
        if(curr->value < 0){
            for(int i = curr->value; i < 0; i++)
                swapThisAndRight(curr->left);
        }else{
            for(int i = 0; i < curr->value; i++)
                swapThisAndRight(curr);
        }
    }

    node *pnode = &originalArr[0];
    while (pnode->value != 0)
    {
        pnode = pnode->right;
    }
    
    for(int i = 0; i < lenArr; i++){
        workingArr[i] = pnode;
        //printf("%4d ", pnode->value);
        pnode = pnode->right;
    }

    int position = 0;
    int sum = 0;
    for(int i = 0; i < 3; i++)
    {
        position = (position+1000)%lenArr;
        sum+=workingArr[position]->value;
    }

    printf("%d\n", sum);
}
