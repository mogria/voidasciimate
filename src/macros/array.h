#ifndef _ARRAY_H
#define _ARRAY_H


#define ALLOC1(type, varname, size)  do { \
  varname = calloc((size), sizeof(type)); \
} while(0)

#define ALLOC2(type, varname, size1, size2)  do { \
  varname = malloc(size1 * sizeof(type*));\
  int y; \
  for(y = 0; y < size1; y++) { \
    ALLOC1(type, varname[y], size2); \
  } \
} while(0)

#define FREE1(varname)  do { \
  free(varname); \
} while(0)

#define FREE2(varname, size) do { \
  int y = 0; \
  for(y = 0; y < size; y++) { \
    FREE1(varname[y]); \
  } \
  FREE1(varname); \
} while(0)
 
#endif /* _ARRAY_H */
