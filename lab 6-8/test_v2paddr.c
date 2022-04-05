#include "types.h"
#include "user.h"
#include "syscall.h"

int
main(int argc, char *argv[])
{
	uint pa = 0x0;
	uint va = 0x0;
	int exist;
	exist = v2paddr(&va,&pa);
	printf(1, "VA: %x\n", va);
	if(exist!=-1)
		printf(1, "PA: %x\n\n", pa);
	else
		printf(1, "VA is invalid\n\n");
	va = 0x2999;
	exist =v2paddr(&va,&pa);
	printf(1, "VA: %x\n", va);
	if(exist!=-1)
		printf(1, "PA: %x\n\n", pa);
	else
		printf(1, "VA is invalid\n\n");
	va = 0x400A;
	exist =v2paddr(&va,&pa);
	printf(1, "VA: %x\n", va);
	if(exist!=-1)
		printf(1, "PA: %x\n\n", pa);
	else
		printf(1, "VA is invalid\n\n");
	va = 0x80000123;
	exist =v2paddr(&va,&pa);
	printf(1, "VA: %x\n", va);
	if(exist!=-1)
		printf(1, "PA: %x\n\n", pa);
	else
		printf(1, "VA is invalid\n\n");
	exit();
}