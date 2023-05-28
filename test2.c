#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include <stdlib.h>

void swap(int *a, int *b){
   int temp = *a;
   *a = *b;
   *b = temp;
}

void insert(int arr[], int *last_index, int key){
   int i= *last_index;
   arr[i] = key;

   while(i>0 && arr[(i-1)/2] < arr[i]){
      swap(&arr[i], &arr[(i-1)/2]);
      i=(i-1)/2;
   }
   (*last_index)++;
}

void print(int arr[]){
   for(int i=0;i<100; i++){
      printf("%d ", arr[i]);
   }
   system("pause");
}

void resort(int arr[], int index){
   int left = 2*(index) + 1;
   int right =  2*(index) + 2;
   if(arr[left]>arr[index] && arr[right]>arr[index]){
      if(arr[left]>arr[right]){
         swap(&arr[index], &arr[left]);
         resort(arr, left);
      }else{
         swap(&arr[index], &arr[right]);
         resort(arr, right);
      }
   }else if(arr[left] > arr[index] && arr[right]<arr[index]){
      swap(&arr[index], &arr[left]);
      resort(arr, left);
   }else if(arr[left] < arr[index] && arr[right]>arr[index]){
      swap(&arr[index], &arr[right]);
      resort(arr, right);
   }else{
      return;
   }
}

void pop(int arr[], int *last_inserted_index, int delete_index){
   int left = 2*(delete_index) + 1;
   int right =  2*(delete_index) + 2;
   arr[0] = arr[(*last_inserted_index) - 1];
   arr[(*last_inserted_index-1)] = 0;
   (*last_inserted_index)--;
   resort(arr, 0);
}

int main() {
   int max_heap_arr[100] = {0};
   int data_count = 0;
   insert(max_heap_arr,&data_count, 95);
   insert(max_heap_arr,&data_count, 90);
   insert(max_heap_arr,&data_count, 76);
   insert(max_heap_arr,&data_count, 60);
   insert(max_heap_arr,&data_count, 32);
   while(true){
      system("cls");
      puts("MAX HEAP TREE\n=============\n1. Insert\n2. View\n3. Pop\n4. Exit");
      int ch;printf("Choose: ");scanf("%d", &ch);  getchar();
      if(ch==1){
         if(data_count == 100){
            printf("Array Overload !\n");
            continue;
         }
         int inp; printf("Input your data [1-100]: "); scanf("%d",&inp); getchar();
         insert(max_heap_arr, &data_count,inp);
         continue;
      }else if(ch==2){
         print(max_heap_arr);
         continue;
      }else if(ch==3){
         pop(max_heap_arr, &data_count, 0);
         system("pause");
         continue;
      }else if(ch==4){
         exit(0);
      }else{
         printf("Invalid menu\n");
      }
   }
   return 0;
}