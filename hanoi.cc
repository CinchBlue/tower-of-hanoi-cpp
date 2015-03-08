#include "hanoi.h"

void hanoi(int num, int from, int to, int temp)
{
	if (num == 1)
		std::cout << "Move Plate #" << num << " from #" << from << " to #" << to << std::endl;
	else
	{
		hanoi(num-1, from, temp, to);
		std::cout << "Move Plate #" << num << " from #" << from << " to #" << to << std::endl;
		hanoi(num-1, temp, to, from);
	}
}

