// vector.c
#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

void vector_init(Vector *vector) {
  // initialize size and capacity
  vector->size = 0;
  vector->capacity = VECTOR_INITIAL_CAPACITY;

  // allocate memory for vector->data
  vector->data = malloc(sizeof(long) * vector->capacity);
}

void vector_append(Vector *vector, long value) {
  // make sure there's room to expand into
  vector_double_capacity_if_full(vector);

  // append the value and increment vector->size
  vector->data[vector->size++] = value;
}

long vector_get(Vector *vector, int index) {
  if (index >= vector->size || index < 0) {
    printf("Index %d out of bounds for vector of size %d\n", index, vector->size);
    exit(1);
  }
  return vector->data[index];
}

void vector_set(Vector *vector, int index, long value) {
  // zero fill the vector up to the desired index
  while (index >= vector->size) {
    vector_append(vector, 0);
  }

  // set the value at the desired index
  vector->data[index] = value;
}

void vector_double_capacity_if_full(Vector *vector) {
  if (vector->size >= vector->capacity) {
    // double vector->capacity and resize the allocated memory accordingly
    vector->capacity *= 2;
    vector->data = realloc(vector->data, sizeof(int) * vector->capacity);
  }
}

void vector_free(Vector *vector) {
  free(vector->data);
}

// for troubleshooting purposes
void vector_print(Vector *vector){
	unsigned int i = 0;
	for(i; i < vector->size; i++){
		printf("%d: %ld\n",i,vector_get(vector, i)); 
	}
}

long vector_min(Vector *vector){
	unsigned int i = 0; 
	long min = vector_get(vector,0); // set min to first number in vector
	for(i; i < vector->size; i++){
		if( min > vector_get(vector,i) ){
			min = vector_get(vector,i);
		}
	}
	return min;
}

long vector_max(Vector *vector){
	unsigned int i = 0;
	long max = 0;
	for(i; i < vector->size; i++){
		if( max < vector_get(vector,i) ){
			max = vector_get(vector,i);
		} 
	}
	return max;
}

long vector_sum(Vector *vector){
	unsigned int i = 0;
	long sum = 0;
	for(i; i < vector->size; i++){
		sum = sum + vector->data[i];
	}
	return sum;
}

long vector_sos(Vector *vector){
	unsigned int i = 0;
	long sos = 0;
	for(i; i < vector->size; i++){
		sos = sos + vector->data[i] * vector->data[i];
	}
	return sos;
} 

void vector_load(Vector *vector,long * buf,int len){		
	int index = 0;
	while(index < len ){
		vector_append(vector, buf[index++]);
	}
}






