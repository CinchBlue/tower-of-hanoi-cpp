#include "hanoi.h"
#include <stack>

//Helper functions
int check_disc_larger(int from_i, std::stack<int>* pegs[3]);
int display_peg(std::stack<int> peg); 
int power(int base, int exp)
{
	int result = 1;
	
	while (exp > 0)
	{
		result = result * base;
		exp--;
	}
	
	return result;
}

/*
 * This is the iterative version. I make use of std::stack for the pegs.
 *
 * The iterative version is based on a picture I found on Wikipedia. Using
 * the picture, a pattern can be derived:
 * 
 * 1. A larger peg cannot be put onto a smaller peg.
 * 2. Assuming the top-most peg is 1 and the bottom-most is 0,
 * 		Odd-numbered discs will always move right.
 * 		Even-numbered discs will always move left.
 * 3. Odd moves will move the smallest-disc (1).
 * 4. Even moves will move the next smallest-disc.
 * 
 * Following these patterns, the most efficient solution will always be
 * figured out. I tested this up to 10 disks and it works.
 */
void hanoi(int num, int from, int to, int temp)
{ 
	//I use std::stack as the tower abstraction
	std::stack<int> A;
	std::stack<int> B;
	std::stack<int> C;
	
	//Create array of pegs
	std::stack<int>* pegs[3] = {&A,&B,&C};
	
	//I care about the smallest disc (#1) which begins with A
	//The smallest disc will also be at the top of a stack at any time
	//Therefore, I can just an index to the correct stack
	int first_disc = 0;
	
	int even_move_disc = 0;
	
	int discs = num;
	
	//Auto-fill the stack from num to 1
	while (discs > 0)
	{
		pegs[first_disc]->push(discs);
		discs--;
	}
	
	/*
	 * Here's how it works:
	 * 
	 * Odds move right (A -> C)
	 * Evens move left (C -> A)
	 * The array wraps around at the ends
	 * 
	 * Moves alternate between the 1 and next smallest disc
	 * 1 is at the top, num is at the bottom
	 * */
	 
	 //START PROCESS
	 
	 int i = 1;
	 
	 //While max moves has still not been obtained
	 while (i <= power(2,num) - 1)
	 {
		 //ODD-MOVE
		 //If odd-move, move smallest disc right
		 if (i % 2 == 1)
		 {
			//If next peg is larger, go to next next peg (increase offset, j)
			int j = check_disc_larger(first_disc, pegs);
			
			std::cout << "ODD-move: Moved (1) from " << first_disc << " to " << (3 + first_disc + j) % 3 << std::endl;
			
			//Move smallest disc onto the correct stack
			pegs[(3+ first_disc + j) % 3]->push(pegs[first_disc]->top());
			pegs[first_disc]->pop();
			first_disc = (3 + first_disc + j) % 3;
		 }
		 
		 //EVEN-MOVE
		 //If even-move, move the next smallest disc left/right
		 else
		 {
			 //If next disc is not empty, set even to that.
			 if (!pegs[(first_disc + 1) % 3]->empty())
			 {
				 std::cout << "HIIII!" << std::endl;
				 even_move_disc = (first_disc + 1) % 3;
				 std::cout << "Next-smallest peg: " << pegs[even_move_disc]->top() << std::endl;
				 
				 
			 }
			 //If next next disc is not empty, set even to that.
			 else if (!pegs[(first_disc + 2) % 3]->empty())
			 {
				 std::cout << "HIIII2222" << std::endl;
				 even_move_disc = (first_disc + 2) % 3;
				  std::cout << "Next-smallest peg: " << pegs[even_move_disc]->top() << std::endl;
			 }
			 
			 //If both are now empty, find the lesser of the two
			 if ((!pegs[(first_disc + 2) % 3]->empty()) && (!pegs[(first_disc + 1) % 3]->empty()))
			 {
				//Find next smallest disc between the non first disc pegs
				even_move_disc = (pegs[(first_disc + 1) % 3]->top() < pegs[(first_disc + 2) % 3]->top()) ?
								((first_disc + 1) % 3) : ((first_disc + 2) % 3);
								
				std::cout << "BYEEE!!!" << std::endl;
			 }
					
			
			//ODD DISC
			//If next smallest disc is odd, move next smallest disc up
			if (pegs[even_move_disc]->top() % 2 == 1)
			{
				//If next peg is larger, go to next next peg (increase offset, j)
				int j = check_disc_larger(even_move_disc, pegs);
				
				std::cout << "EVEN-move, ODD-disc: Moved (" << pegs[even_move_disc]->top() << ") from " << even_move_disc << " to " << (3 + even_move_disc + j) % 3  << std::endl;
				std::cout << "Moved " << j << std::endl;
				
				//Move smallest disc onto the correct stack
				pegs[(3 + even_move_disc + j) % 3]->push(pegs[even_move_disc]->top());
				pegs[even_move_disc]->pop();
				

		 
			}
			
			//EVEN DISC
			//If next smallest disc is even, move next smallest disc down
			else if (pegs[even_move_disc]->top() % 2 == 0)
			{
				
				//If next peg is larger, go to next next peg (increase offset, j)
				int j = check_disc_larger(even_move_disc, pegs);
				
				std::cout << "EVEN-move, EVEN-disc: Moved (" << pegs[even_move_disc]->top() << ") from " << even_move_disc << " to " << (3 + even_move_disc + j) % 3 << std::endl;
				std::cout << "Moved " << j << std::endl;
				
				//Move smallest disc onto the correct stack
				pegs[(3 + even_move_disc + j) % 3]->push(pegs[even_move_disc]->top());
				pegs[even_move_disc]->pop();
				

		 
			}
		 }
		 
		//Print out the data.
		std::cout << "MOVE #: " << i << std::endl;
		std::cout << "TOP -> BOTTOM" << std::endl;
	
		std::cout << "A: ";
		display_peg(A);
	
		std::cout << "B: ";
		display_peg(B);
	
		std::cout << "C: ";
		display_peg(C);
		 
		if (i==1)
			std::getchar();
		 
		std::getchar();
		
		system("clear");
		
		i++;
	 }

	//END PROCESS
}









int check_disc_larger(int from_i, std::stack<int>* pegs[3])
{
	int j = 0;
	
	//If EVEN, check to the left and find the next valid peg
	if (pegs[from_i]->top() % 2 == 0)
	{
		j = -1;
		
		//Checking empty() is necessary due to SEGFAULT if you don't check before accessing
		if (!pegs[(3 + from_i + j) % 3]->empty())
		{

			
			if(pegs[from_i]->top() > pegs[(3 + from_i + j) % 3]->top())
				j--;
		}
	}
		
	//If ODD, check right and find the next valid peg
	else if (pegs[from_i]->top() % 2 == 1)
	{
		j = 1;
		
		if(!pegs[(3 + from_i + j) % 3]->empty())
		{
			if ((pegs[from_i]->top() > pegs[(3 + from_i + j) % 3]->top()))
				j++;
		}
	}
	
	return j;
	
}

int display_peg(std::stack<int> peg)
{
	 while (peg.size() != 0)
	 {
		 std::cout << "|" << peg.top();
		 peg.pop();
	 }
	 
	 std::cout << std::endl;
	 
	 return 0;
}





