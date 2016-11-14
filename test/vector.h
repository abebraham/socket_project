// vector.h

#define VECTOR_INITIAL_CAPACITY 1000

// Define a vector type
typedef struct {
  int size;      // slots used so far
  int capacity;  // total available slots
  long *data;     // array of integers we're storing
} Vector;

void vector_init(Vector *vector);

void vector_append(Vector *vector, long value);

long vector_get(Vector *vector, int index);

void vector_set(Vector *vector, int index, long value);

void vector_double_capacity_if_full(Vector *vector);

void vector_free(Vector *vector);

void vector_print(Vector *vector);

long vector_min(Vector *vector);

long vector_max(Vector *vector);

long vector_sum(Vector *vector);

long vector_sos(Vector *vector); 


