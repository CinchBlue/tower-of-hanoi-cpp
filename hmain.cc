
/* File:  hmain.cc
 * By:    
 * Date:  
 *
 */

#include "hanoi.h"

// Test driver for Towers of Hanoi
//     DO NOT TRY 64 DISKS!!!

int main()
{  
	int num;

	std::cout << "Enter number of disks: " << std::flush;

	while(std::cin >> num)
	{
		hanoi(num,1,3,2);
		std::cout << "Enter number of disks: " << std::flush;
	}
	
	return 0;
}



