#ifndef DEFS_H_
#define DEFS_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum e_bool {false, true} bool;
typedef enum e_status { success, failure} status;
typedef void * Element;
typedef Element(*copyFunction) (Element);
typedef status(*freeFunction) (Element);
typedef status(*printFunction) (Element);
typedef int(*transformIntoNumberFunction) (Element); 
typedef bool(*equalFunction) (Element, Element);
#endif /* DEFS_H_ */
