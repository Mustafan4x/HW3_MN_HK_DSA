/*
 * CSE 3318 - Homework 3
 * Name: Mustafa Nazeer
 * UTA ID: 1002332338
 * 
 * Name: Hassan Asif Khan
 * UTA ID: 1002217908
*/


/*
* --- HONOR CODE STATEMENT AGREEMENT ---
* 
* I pledge, on my honor, to uphold UT Arlington's tradition of academic integrity, a tradition that values hard
* work and honest effort in the pursuit of academic excellence.
* I promise that I will submit only work that I personally create or that I contribute to group collaborations, and I
* will appropriately reference any work from other sources. I will follow the highest standards of integrity and
* uphold the spirit of the Honor Code. I will not participate in any form of cheating/sharing the
* questions/solutions.
* 
*
* Name:         Mustafa Nazeer
* Date:         3-28-2026
* E-Signature:  Mustafa Nazeer
*
* Name:         Hassan Asif Khan
* Date:         3-28-2026
* E-Signature:  Hassan Asif Khan
*
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
} Node;



void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int A[], int p, int r){

    int x = A[r];
    int i = p - 1;

    for(int j = p; j <= r - 1; ++j){
        if(A[j] <= x){
            ++i;
            swap(&A[i], &A[j]);
        }
    }
    swap(&A[i + 1], &A[r]);

    return i + 1;
}

void quickSort(int A[], int p, int r){

    if(r > p){
        int q = partition(A, p, r);
        quickSort(A, p, q - 1);
        quickSort(A, q + 1, r);
    }
}

int getRandomIndex(int arrSize){
    return rand() % arrSize;
}

int linearSearch(int arr[], int size, int target){

    for(int i = 0; i < size; ++i){
        if(arr[i] == target)
            return i;
    }
    // Target not found
    return -1;
}

int binarySearch(int arr[], int size, int target){

    int start = 0;
    int end = size - 1;

    while(end <= start){
        int middle = start + (end - start) / 2;

        if(arr[middle] == target)
            return middle;
        else if (arr[middle] < target)
            start = middle + 1;
        else
            end = middle - 1;
    }
    // Target not found
    return -1;
}

Node* BST_Search(Node* root, int target){

    Node* curr = root;

    while(curr != NULL){

        if(curr->key == target)
            return curr;
        else if(target < curr->key)
            curr = curr->left;
        else
            curr = curr->right;
    }
    // Target not found
    return NULL;
}

Node* BST_Insert_Recursive(Node* root, int new_key){

    if(root == NULL)
        return malloc(sizeof(Node));

    if(new_key < root->key)
        root->left = BST_Insert_Recursive(root->left, new_key);
    else if(new_key > root->key)
        root->right = BST_Insert_Recursive(root->right, new_key);

    return root;
}

Node* BST_Insert_Iterative(Node* root, int new_key){

    Node* newNode = malloc(sizeof(Node));

    if(root == NULL)
        return newNode;

    Node* parent = NULL;
    Node* curr = root;

    while(curr != NULL){

        parent = curr;

        if(new_key < curr->key)
            curr = curr->left;
        else if(new_key > curr->key)
            curr = curr->right;
        else
            return root;
    }

    if(new_key < parent->key)
        parent->left = newNode;
    else
        parent->right = newNode;

    return root;
}

void freeTree(Node* root){

    if(root == NULL)
        return;
    
    freeTree(root->left);
    freeTree(root->right);

    free(root);
}

int main() {

    // Seed the random number generator
    srand(time(NULL));

    // Variables for timing
    clock_t start_time, end_time;
    double time_taken;

    int sizes[] = {30, 1000, 6000, 10000};
    const char* filenames[] = {"nodes30.txt", "nodes1000.txt", "nodes6000.txt", "nodes10000.txt"};

    const char* sfilenames[] = {"snodes30.txt", "snodes1000.txt", "snodes6000.txt", "snodes10000.txt"};
    int num_files = 4;

    // Arrays for unsorted data
    int arr30[sizes[0]];
    int arr1000[sizes[1]];
    int arr6000[sizes[2]];
    int arr10000[sizes[3]];

    // Arrays for sorted data
    int s_arr30[sizes[0]];
    int s_arr1000[sizes[1]];
    int s_arr6000[sizes[2]];
    int s_arr10000[sizes[3]];


    int* arrays[] = {arr30, arr1000, arr6000, arr10000};
    int* s_arrays[] = {s_arr30, s_arr1000, s_arr6000, s_arr10000};

    int totalRandomElements = 10;
    int randomElements[totalRandomElements];

    // PART 1: Generation of Data
    printf("--- Part 1: Generating Data ---\n");
    for (int i = 0; i < num_files; i++) {

        FILE *filePtr;
      
        filePtr = fopen(filenames[i], "w");

        if(filePtr == NULL){
            printf("Error opening file.\n");
            return 1;
        }

        // Populate Array, go to 20,001 to have a range of [0, 20,000]
        for(int j = 0; j < sizes[i]; ++j){
            fprintf(filePtr, "%d\n", rand() % 20001);
        }
        fclose(filePtr);

        filePtr = fopen(filenames[i], "r");

        if(filePtr == NULL){
            printf("Error opening file.\n");
            return 1;
        }

        for(int j = 0; j < sizes[i]; ++j){
            if(fscanf(filePtr, "%d", &arrays[i][j]) != 1){
                printf("Error reading data at index %d.\n", j);
                break;
            }
        }
        fclose(filePtr);

        start_time = clock();
        quickSort(arrays[i], 0, sizes[i] - 1);
        end_time = clock();

        time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;



        printf("Time to sort array of size %d: %f seconds\n", sizes[i], time_taken);

        filePtr = fopen(sfilenames[i], "w");

        if(filePtr == NULL){
            printf("Error opening file.\n");
            return 1;
        }

        // Populate array with sorted data
        for(int j = 0; j < sizes[i]; ++j){
            fprintf(filePtr, "%d\n", arrays[i][j]);
        }
        fclose(filePtr);
    }
    printf("Data generation complete.\n\n");


    // PART 2 & 3 Loop: Process each dataset size
    for (int i = 0; i < num_files; i++) {
    printf("=== Processing Dataset Size: %d ===\n", sizes[i]);
    // --- PART 2: Search on Sorted Array ---

        FILE* filePtr;

        filePtr = fopen(sfilenames[i], "r");

        if(filePtr == NULL){
            printf("Error opening file.\n");
            return 1;
        }

        for(int j = 0; j < sizes[i]; ++j){
            if(fscanf(filePtr, "%d", &s_arrays[i][j]) != 1){
                printf("Error reading data at index %d.\n", j);
                break;
            }
        }
        fclose(filePtr);

        for(int j = 0; j < totalRandomElements; ++j)
            randomElements[j] = getRandomIndex(sizes[i]);

        double linearSearchTimes[totalRandomElements];
        double binarySearchTimes[totalRandomElements];

        for(int j = 0; j < totalRandomElements; ++j){

            start_time = clock();
            linearSearch(s_arrays[i], sizes[i], randomElements[j]);
            end_time = clock();

            linearSearchTimes[j] = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

            start_time = clock();
            binarySearch(s_arrays[i], sizes[i], randomElements[j]);
            end_time = clock();

            binarySearchTimes[j] = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        }


        // --- PART 3: Search and Insertion on Binary Search Tree ---
        // 1. Random BST (Insert keys in the exact order they appear in the file)
        Node* randomBST = NULL;

        for(int j = 0; j < sizes[i]; ++j){
            BST_Insert_Iterative(randomBST, arrays[i][j]);
        }

        // 2. Sorted BST (Insert keys from the sorted array)
        Node* sortedBST = NULL;

        for(int j = 0; j < sizes[i]; ++j){
            BST_Insert_Iterative(sortedBST, s_arrays[i][j]);
        }

        double randomBST_SearchTimes[totalRandomElements];
        double sortedBST_SearchTime[totalRandomElements];

        for(int j = 0; j < totalRandomElements; ++j){

            start_time = clock();
            BST_Search(randomBST, randomElements[j]);
            end_time = clock();

            randomBST_SearchTimes[j] = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

            start_time = clock();
            BST_Search(sortedBST, randomElements[j]);
            end_time = clock();

            sortedBST_SearchTime[j] = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        }

        int newRandomElements[totalRandomElements];

        for(int j = 0; j < totalRandomElements; ++j)
            newRandomElements[j] = getRandomIndex(sizes[i]);

        double randomBST_InsertTimes_Iterative[totalRandomElements];
        double randomBST_InsertTimes_Recursive[totalRandomElements];

        double sortedBST_InsertTimes_Iterative[totalRandomElements];
        double sortedBST_InsertTimes_Recursive[totalRandomElements];

        for(int j = 0; j < totalRandomElements; ++j){

            start_time = clock();
            BST_Insert_Iterative(randomBST, newRandomElements[j]);
            end_time = clock();

            randomBST_InsertTimes_Iterative[j] = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

            start_time = clock();
            BST_Insert_Recursive(randomBST, newRandomElements[j]);
            end_time = clock();

            randomBST_InsertTimes_Recursive[j] = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;




            start_time = clock();
            BST_Insert_Iterative(sortedBST, newRandomElements[j]);
            end_time = clock();

            sortedBST_InsertTimes_Iterative[j] = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

            start_time = clock();
            BST_Insert_Recursive(sortedBST, newRandomElements[j]);
            end_time = clock();

            sortedBST_InsertTimes_Recursive[j] = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        }

        // Cleanup memory for this iteration
        freeTree(randomBST);
        freeTree(sortedBST);
        printf("\n");
    }

    return 0;
}