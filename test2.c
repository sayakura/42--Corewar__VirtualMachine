#define FOR_EACH(item, array) typeof(*array) *start = array;\
                            typeof(*array) *end = (start + (sizeof(array) / sizeof*(array)) + 1);\
                            typeof(*array) item;\
                            while ((item = *start) && start++ != end )

#include <stdio.h>
int main(int ac, char **av)
{
	int arr[] = {123, 1, 123, 324};
	FOR_EACH(i, arr)
	{
		printf("%d\n", i);
	}
	return (0);
}
