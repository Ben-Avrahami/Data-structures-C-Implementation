#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/*
 *
 * This Method  swaps the values between a and b
 *
 */

void Swap(int *a, int *b) {
    int temp = *b;
    *b = *a;
    *a = temp;
}

/*
 *
 * This Method genrates a random number between 0 to 999*
 *
 */

int randomNumber(int high, int low) {
    int upper = high;
    int lower = low;

    int number = (rand() % (upper - lower + 1)) + lower; //makes a random number

    return number;//returs the number

}

/*
 *
 * This method is doing MinHeapify action on the heap
 *
 */

void minHeapify(int *arr, int heapSize, int i, int *comparisons) {

    /*p1 and p2 are pointer for arr[i] and arr[smallest]*/
    int *p1;
    int *p2;
    int smallest = i;
    int leftChild = (i * 2) + 1;
    int rightChild = (i * 2) + 2;


    if (leftChild < heapSize && arr[leftChild] < arr[smallest]) {
        smallest = leftChild;
        (*comparisons)++;
    }


    if (rightChild < heapSize && arr[rightChild] < arr[smallest]) {
        smallest = rightChild;
        (*comparisons)++;
    }

    if (smallest != i) {
        p1 = &arr[i];
        p2 = &arr[smallest];

        Swap(p1, p2);//calls the swap method

        minHeapify(arr, heapSize, smallest,comparisons);//recursive call to the method
    }
}

/*
 *
 * This Method build a min Heap
 *
 */
void buildMinHeap(int *arr, int arrSize, int *comparisons) {
    int i;
    int size = (arrSize / 2) - 1;

    for (i = size; i >= 0; i--) {
        minHeapify(arr, arrSize, i,comparisons); //calls the MinHeapify Method
    }
}


/*
 *
 * This Method recieves a char array, a pointer and the size of the array
 *  then prints the array and the message that the char array has in it
 *
 */
void printArray(char message[], int *arr, int arrSize) {
    int i;

    printf("%s ", message);//prints the message array

    printf("\n");

    for (i = 0; i < arrSize; i++) {
        printf("%d ", arr[i]); //prints the arr array
    }

    printf("\n"); //goes down a line

}


/*
 *
 * This method Extracts the min value from the heap
 *
 */

int heapExtractMin(int *arr, int *arrSize,int *comparisons) {

    int min;
    int size = *arrSize;
    if (size < 1)
        printf("Heap underflow");

    min = arr[0];

    arr[0] = arr[size - 1];

    *arrSize = size - 1;


    minHeapify(arr, *arrSize, 0, comparisons);//calls the min heapify Method

    return min;


}


int partition(int *arr, int low, int high,int* comparisons2) 
{
    int pivot = arr[high];

    int i = low - 1;

    int j;

    for (j = low; j < high; j++) {
        if (arr[j] <= pivot) 
        {
            (*comparisons2)++;
            i++;
            Swap(&arr[i], &arr[j]);
        }
    }

    Swap(&arr[i + 1], &arr[high]);

    return i + 1;
}

int randomizedPartition(int *arr, int low, int high,int* comparisons2) {

    int i = randomNumber(high, low);

    Swap(&arr[i], &arr[high]);

    return partition(arr, low, high,comparisons2);
}

void quickSort(int *arr, int low, int high,int* comparisons2) {

    int q;

    if (low < high) 
    {
        
        q = partition(arr, low, high,comparisons2);
        quickSort(arr, low, q - 1, comparisons2);
        quickSort(arr, q + 1, high, comparisons2);
    }
}

int randomizedSelect(int *arr, int low, int high, int location, int* comparisons2) {
    int q, k;

    if (low == high)
    {
        
        return arr[low];
    }

    q = randomizedPartition(arr, low, high,comparisons2);
    k = q - low + 1;

    if (location == k)
    {
        
        return arr[q];
    }

    else if (location < k)
    {
        
        return randomizedSelect(arr, low, q - 1, location,comparisons2);
    }
    else
        return randomizedSelect(arr, q + 1, high, location - k,comparisons2);
}


int main() {

    /*Variable declaration:

    N=n(the amount of numbers that the user want to have in the array).

    K=k(the amount of smallest numbers in the array that the user wants to be printed.

    ksmallest is a varibale that has the K smallest value in the array.

    time_t is a varibale for the random number.*/


    int *ptr = (int *) malloc(1);
    int min;
    int N, K, ksmallest;
    int i = 0;
    int option;
    int heapComparisons=0;
    int comparisons=0;
    time_t randomNum = time(NULL);


    printf("Please enter the amount of numbers you want to enter \n");

    scanf("%d", &N);

    printf("Please enter K \n");

    scanf("%d", &K);

    ptr = (int *) realloc(ptr, N * sizeof(int));

    printf("\nHey do you want to choose the numbers yourself or I will choose them for you?\n");
    printf("\nIf you want to choose the numbers yourself enter 1.\n\nIf you want me to choose them for you enter 2.\n\n");

    scanf("%d", &option);
    switch (option) {
        case 1:

            printf("Enter the numbers\n");

            while (i != N) {
                printf("\nNumber No%d.", i + 1);
                scanf("%d", ptr + i);
                i++;
            }

            printArray("The Array :\n", ptr, N);

            buildMinHeap(ptr, N,&heapComparisons);

            printArray("The array after min heap: \n", ptr, N);


            ksmallest = randomizedSelect(ptr, 0, N-1, K,&comparisons);

            printf("\nThe %d smallest number is:%d", K, ksmallest);

            

            quickSort(ptr, 0, K,&comparisons);

            printArray("", ptr, K);

            printf("\nThe %d smallest numbers using heapExtractMin are:\n", K);

            for (i = 0; i < K; i++) {
                min = heapExtractMin(ptr, &N, &heapComparisons);
                printf("%d ", min);
            }
            printf("\nThe number of comparisons using heapExtractMin :%d\n", heapComparisons);
            printf("\nThe number of comparisons using quicksort :%d\n", comparisons);
            break;

        case 2:

            srand(randomNum);

            while (i != N) {
                printf("\nNumber No%d.", i + 1);
                ptr[i] = randomNumber(999, 0);//generates a random number
                printf("\n%d", ptr[i]);
                i++;
            }
            printArray("\nThe Array :", ptr, N);

            buildMinHeap(ptr, N, &heapComparisons);//build a min heap

            printArray("The array after min heap: \n", ptr, N);

           // quickSort(ptr, 0, N - 1,&comparisons);//calls quicksort

            printArray("The array after quicksort: \n", ptr, N);


            ksmallest = randomizedSelect(ptr, 0, N - 1, K,&comparisons);

            

            printf("\nThe %d smallest number is:%d\n", K, ksmallest);

            printf("The %d smallest numbers using randomizedSelect are:", K);

            quickSort(ptr, 0, K,&comparisons);//calls quicksort

            printArray("", ptr, K);//prints the array

            printf("\nThe %d smallest numbers using heapExtractMin are:\n", K);


            for (i = 0; i < K; i++) {
                min = heapExtractMin(ptr, &N, &heapComparisons);
                printf("%d ", min);
            }
            printf("\nThe number of comparisons using heapExtractMin :%d\n", heapComparisons);
            printf("\nThe number of comparisons using quicksort :%d\n", comparisons);

            break;

            free(ptr);
    }


    return 0;
}












