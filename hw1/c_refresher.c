#include <stdio.h>
#include <stdlib.h>

struct s2 {
  float a;
  int b;
  };

struct s1 {
  int c;
  struct s2 **d;
};

void question_1 () {
  int a = 20;
  int* stack_ptr = &a;

  int *heap_ptr = malloc(sizeof(int));
  int *heap_ptr2 = malloc(3*sizeof(int));

  heap_ptr[0] = 50;

  heap_ptr2[0] = 5;
  heap_ptr2[1] = 6;
  heap_ptr2[2] = 7;

  printf("Stack\n");
  printf("address: %p value: %d\n", &a, a);
  printf("address: %p value: %p\n", &stack_ptr, stack_ptr);
  printf("address: %p value: %p\n", &heap_ptr, heap_ptr);
  printf("address: %p value: %p\n", &heap_ptr2, heap_ptr2);

  printf("Heap\n");
  printf("address: %p value: %d\n", &heap_ptr2[2], heap_ptr2[2]);
  printf("address: %p value: %d\n", &heap_ptr2[1], heap_ptr2[1]);
  printf("address: %p value: %d\n", &heap_ptr2[0], heap_ptr2[0]);
  printf("address: %p value: %d\n", &heap_ptr[0], heap_ptr[0]);
  
}

void question_2a() {
  int a[2][4] = {{10, 20, 30, 40}, {50, 60, 70, 80}};
  int* b[2] = {&a[0][0], &a[1][0]};

  for(int i = 1; i >= 0; i --){
    for(int j = 3; j >= 0; j--){
      printf("address: %p value: %d\n", b[i] + j, *(b[i] + j));
    }
  }

  printf("address: %p value: %p\n", &b[1], b[1]);
  printf("address: %p value: %p\n", &b[0], b[0]);

}

void question_2b() {
  int a[2][4] = {{10, 20, 30, 40}, {50, 60, 70, 80}};
  int* b[2] = {&a[0][0], &a[1][0]};
  int** c  = &b[0];

  for(int i = 1; i >= 0; i --){
    for(int j = 3; j >= 0; j--){
      printf("address: %p value: %d\n", *(c + i) + j, *(*(c + i) + j));
    }
  }

  printf("address: %p value: %p\n", c + 1, *(c + 1));
  printf("address: %p value: %p\n", c + 0, *(c + 0));
  printf("address: %p value: %p\n", &c, c);

}

void question_3() {
  struct s1 x[5];

  struct s2 struct_s2_0 = {0.0, 0};
  struct s2 struct_s2_1 = {1.0, 1};
  struct s2 struct_s2_2 = {2.0, 2};
  struct s2 struct_s2_3 = {3.0, 3};
  struct s2 struct_s2_4 = {4.0, 4};

  struct s2* struct_s2_0_ptr = &struct_s2_0;
  struct s2* struct_s2_1_ptr = &struct_s2_1;
  struct s2* struct_s2_2_ptr = &struct_s2_2;
  struct s2* struct_s2_3_ptr = &struct_s2_3;
  struct s2* struct_s2_4_ptr = &struct_s2_4;

  x[0] = (struct s1){0, &struct_s2_0_ptr};
  x[1] = (struct s1){1, &struct_s2_1_ptr};
  x[2] = (struct s1){2, &struct_s2_2_ptr};
  x[3] = (struct s1){3, &struct_s2_3_ptr};
  x[4] = (struct s1){4, &struct_s2_4_ptr};
  
  int b = (*(x[2].d))->b;

  printf("b = %d\n", b);
}

void question_4() {
  double a[] = {3.14, 2.71};

  for(int i = 0; i < 2; i++){
    printf("a[%d]: ", i);
    unsigned char *bytes = (unsigned char *)&a[i];
    for(int j = 0; j < 8; j++){
      printf("0x%02X ", bytes[j]);
    }
    printf("\n");
  }
}

void question_5(int i) {
  int a[2];
  int b[3];
  int *c;
  int *d;
  c = (int *)malloc(sizeof(int) * 4);
  d = (int *)malloc(sizeof(int) * 5);

  printf("address for a: %p\n", &a[0]);
  printf("address for b: %p\n", &b[0]);
  printf("address for c: %p\n", c);
  printf("address for d: %p\n", d);

  return;
}

int main () {
  question_5();
}
