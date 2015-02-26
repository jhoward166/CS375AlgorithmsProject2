README
BestFirstSearch solves the 0/1 backpack problem using the best first queue solution. After recieving input from the input file it stores the items in an array. It then uses this array to create another sorted array by the greatest value per unit descending. Using these arrays and a max profit function it creates nodes to solve for the optimal choice of items to chose the items that will ensure that the backpack has the highest total value.

SAMPLE INPUT
./BestFirstSearch <input.txt> <output.txt>

This command will launch the program. Inside the input file the lines should be as follows (taken from assignment page):

Line 1: n(the size of the problem, that is the total number of items),C(the total weight limit)
Lines 2 to n+1: wi(the weight of item i),pi(the profit of item i)
The example in slide 13 of lecture 22 in the input file format:
4,16
2,40
5,30
10,50
5,10 

SAMPLE OUTPUT
The program sends its standardized output to the user designated output file. The file should look as follows (taken from assignment page):

Line 1: the size of the problem(i.e., the total number of items),the optimal value(i.e., the maximum profit),the size (k) of the first optimal solution found(i.e., the size of the first optimal subset of items found to produce the maximum profit)
Line 2: the total number of nodes visited,the total number of leaf nodes visited (both by the algorithm from the start to the end of the search including the root and the last node visited in the binary search
space tree)
Lines 3 to 3+(k-1): each line contains the weight and profit of an item selected in order for the first optimal solution found
The solution for the above example in the output file format:
4,90,2
11,6
2,40
10,50 
