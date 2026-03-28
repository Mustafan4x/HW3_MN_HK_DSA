/*
 * CSE 3318 - Homework 3
 * Name: Mustafa Nazeer
 * UTA ID: 1002332338
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
* Date:         2-24-2026
* E-Signature:  Mustafa Nazeer
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

// Function creates a file, based off of the passed in size, then populates that file
// with a random number in the range [0, 20,000], with 1 number per line in the file
void populateArray(int arrSize){

    FILE *filePtr;
    char* name;

    
    if(arrSize == 30)
        name = "nodes30.txt";

    else if(arrSize == 1000)
        name = "nodes1000.txt";
    
    else if(arrSize == 6000)
        name = "nodes6000.txt";

    else if(arrSize == 10000)
        name = "nodes10000.txt";
    else{
        printf("Invalid array size, must be 30, 1000, 6000, or 10000.\n");
        return;
    }

    filePtr = fopen(name, "w");

    if(filePtr == NULL){
        printf("Error opening file.\n");
        return;
    }

    // Populate Array, go to 20,001 to have a range of [0, 20,000]
    for(int i = 0; i < arrSize; ++i){
        fprintf(filePtr, "%d\n", rand() % 20001);
    }

    fclose(filePtr);
}

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

// Fills in arrays with data from a passed in filename
void fillArrays(char* name, int size, int arr[]){

    FILE* filePtr = fopen(name, "r");

    if(filePtr == NULL){
        printf("Error opening file.\n");
        return;
    }

    for(int i = 0; i < size; ++i){
        if(fscanf(filePtr, "%d", &arr[i]) != 1){
            printf("Error reading data at index %d.\n", i);
            break;
        }
    }

    fclose(filePtr);
}

// Resets array states, so that they're in random order before every sorting test
void setArrayState(int arr30[], int arr1000[], int arr6000[], int arr10000[]){

    // Seed RNG
    srand(time(NULL));

    populateArray(30);
    populateArray(1000);
    populateArray(6000);
    populateArray(10000);

    fillArrays("nodes30.txt", 30, arr30);
    fillArrays("nodes1000.txt", 1000, arr1000);
    fillArrays("nodes6000.txt", 6000, arr6000);
    fillArrays("nodes10000.txt", 10000, arr10000);
}

// Function creates a file, based off of the passed in size, then populates that file
// with the sorted version of the randomized file
void populateArray_Sorted(int arr[], int arrSize){

    FILE *filePtr;
    char* name;

    
    if(arrSize == 30)
        name = "snodes30.txt";

    else if(arrSize == 1000)
        name = "snodes1000.txt";
    
    else if(arrSize == 6000)
        name = "snodes6000.txt";

    else if(arrSize == 10000)
        name = "snodes10000.txt";
    else{
        printf("Invalid array size, must be 30, 1000, 6000, or 10000.\n");
        return;
    }

    filePtr = fopen(name, "w");

    if(filePtr == NULL){
        printf("Error opening file.\n");
        return;
    }

    // Populate array with sorted data
    for(int i = 0; i < arrSize; ++i){
        fprintf(filePtr, "%d\n", arr[i]);
    }

    fclose(filePtr);
}

double getTimeToSortArray(int arr[], int size){

    clock_t start = clock();
    quickSort(arr, 0, size - 1);
    clock_t end = clock();

    // Write to File before returning
    populateArray_Sorted(arr, size);

    return (double)(end - start) / CLOCKS_PER_SEC;
}

int getRandomIndex(int arrSize){
    return rand() % arrSize;
}

double getTimeToSearchArray(void (*search_function)(int[], int, int), int arr[], int size){

    clock_t start = clock();
    search_function(arr, size, getRandomIndex(size));
    clock_t end = clock();

    return (double)(end - start) / CLOCKS_PER_SEC;
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

int main(){

    int arr30[30];
    int arr1000[1000];
    int arr6000[6000];
    int arr10000[10000];

    setArrayState(arr30, arr1000, arr6000, arr10000);


    // Timing sorting time on each array
    printf("Time to sort 30 elements (with quicksort):      %f seconds.\n", getTimeToSortArray(arr30, 30));
    printf("Time to sort 1000 elements (with quicksort):    %f seconds.\n", getTimeToSortArray(arr1000, 1000));
    printf("Time to sort 6000 elements (with quicksort):    %f seconds.\n", getTimeToSortArray(arr6000, 6000));
    printf("Time to sort 10000 elements (with quicksort):   %f seconds.\n", getTimeToSortArray(arr10000, 10000));





    return 0;
}
/*
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

    // PART 1: Generation of Data
    printf("--- Part 1: Generating Data ---\n");
    for (int i = 0; i < num_files; i++) {
    // TODO: generate data for each size and filename
    // Ensure the generated integers are UNIQUE and between 0 and 20000
    // Save the data in nodes<x>.txt file
    // Sort the data
    // Example of how to measure time (Use this pattern for all measurements)

    start_time = clock();
    // TODO: Sort the array
    end_time = clock();

    time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Time to sort array of size %d: %f seconds\n", sizes[i], time_taken);
    // Save the sorted data in snode<x>.txt file
    }
    printf("Data generation complete.\n\n");


    // PART 2 & 3 Loop: Process each dataset size
    for (int i = 0; i < num_files; i++) {
    printf("=== Processing Dataset Size: %d ===\n", sizes[i]);
    // --- PART 2: Search on Sorted Array ---
    // TODO: Read data from sfilenames[i] into an array
    // TODO: Select 10 random elements from the array
    // TODO: Measure time for Linear Search of the 10 elements
    // TODO: Measure time for Binary Search of the 10 elements


    // --- PART 3: Search and Insertion on Binary Search Tree ---
    // 1. Random BST (Insert keys in the exact order they appear in the file)
    Node* randomBST = NULL;
    // TODO: Read from file again or use an unsorted copy of the array to insert elements

    // 2. Sorted BST (Insert keys from the sorted array)
    Node* sortedBST = NULL;
    // TODO: Measure time to Search for those 10 elements in BOTH trees
    // TODO: Insert elements from the sorted array into sortedBST
    // TODO: Generate 10 NEW random elements (between 0 and 20000)
    // TODO: Measure time for Iterative Insertion of these 10 elements into BOTH trees
    // TODO: Measure time for Recursive Insertion of these 10 elements into BOTH trees

    // Cleanup memory for this iteration
    // TODO: Free arrays
    // TODO: Free BSTs (randomBST and sortedBST) using freeTree()
    printf("\n");

    }

    return 0;
}
*/