#include <stdio.h>
#include <stdlib.h>

typedef struct test_structure{

  int a;
  char name[100];
  float f;

} daves_structure;

int main()
{
	daves_structure item = { 5, "hello world", 3.14 };

	daves_structure *p = &item;
	p[0].a = 5;

	printf( "p->a equals %d.\n", (*p).a );

	return 0;
	
}
