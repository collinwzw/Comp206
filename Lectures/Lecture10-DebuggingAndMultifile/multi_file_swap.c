// This file implements the swap. You must compile 
// it together with main to make it useful

void swap( int *a, int *b )
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
