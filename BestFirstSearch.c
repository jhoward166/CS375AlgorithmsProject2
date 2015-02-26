#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct item{
	int weight;
	int value;
	int id;
	double ratio;
} item;

typedef struct node{
	int numItems;
	int prune;
	int profit;
	int capacity;
	double max;
	int level;
	item* taken; 
} node;

/*Algorithm designed to find the maximum profit of fractional backback. Takens in the total capacity and total number of items along with the an ordered list of all items and the weight value and position of the current node. Will return the maximum potential profit of a node at its position in the tree. 
*/
double maxProfit(int capacity, int quantity, item* items, int load, int cost, int taken, int pos){
	int held = taken;
	int index = 0;
	int value = cost;
	int weight = load;
	double diff;
	//printf("vars:\n\theld:%d\n\tindex:%d\n\tvalue:%d\n\tweight:%d\n\tpos:%d\n\tid:%d\n", held, index, value, weight, pos, items[index].id);
	while((capacity > (weight+items[index].weight)) && (held < quantity)){
		if(pos <= items[index].id){
			weight+=items[index].weight;
			value+=items[index].value;
			held++;
		}
		index++;
		//printf("vars:\n\theld:%d\n\tindex:%d\n\tvalue:%d\n\tweight:%d\n\tpos:%d\n\tid:%d\n", held, index, value, weight, pos, items[index].id);
	}
	if(held == quantity){
		//printf("answ:%f\n", (double)value);
		return (double)value;
	}
	diff = capacity - weight;
	if(diff > 0){
		//printf("answ: %d, %d, %f, %f\n",capacity, weight, diff, (double)(value+((diff/(double)items[index].weight)*(double)items[index].value)));
		return (double)(value+((diff/(double)items[index].weight)*(double)items[index].value));
	}
}

/*Main function takes in an input and output file to read from and write to respectively. Reads the problem and the items from the input file and outputs the solution to the output file. Uses nodes in a tree heirarchy and a best pick queue to find the solution efficiently using as few nodes as possible.
*/
int main(int argc, char** argv){
	int packCap;
	int totalItems;
	int leaf = 0;
	int visited =0;
	node maxProf;
	item* available;
	item* ordered;
	//item* taken;
	if(argc != 3){
		printf("Incorrect number of arguments. Input must be of the type:\n\tPrompt> BestFirstSearch <input.txt> <output.txt>\n");
		return 0;
	}
	FILE *infile = fopen(argv[1],"r");
	if(!infile){
		printf("%s could not be opened. Program terminated.\n", argv[1]);
		return -1;
	}
	char line[128];
	int number = 0;
	while(fgets(line, 128, infile)!=NULL){
		char* token;
		char* part1;
		char* part2;
		int val1;
		int val2;
		token = strtok(line, ",");
		part1 = token;
		token = strtok(NULL, ",");
		part2 = token;
		val1 = atoi(part1);
		val2 = atoi(part2);
		if(number == 0){
			totalItems = val1;
			packCap = val2;
			available = malloc((sizeof (struct item))* totalItems);
			ordered = malloc((sizeof (struct item))* totalItems);
			number++;
		}else{
			item tempItem;
			tempItem.weight = val1;
			tempItem.value = val2;
			tempItem.id = number-1;
			tempItem.ratio = (double)val2/ (double)val1;
			available[number-1] = tempItem;
			if(number==1){
				ordered[number-1] = tempItem;
			}else{
				int inc =0;
				item tempOrder;
				tempOrder = ordered[inc];
				while(tempOrder.ratio >= tempItem.ratio){
					inc++;
					tempOrder = ordered[inc];
				}
				int i;
				for(i=number-2; i> inc; i--){
					ordered[i-1] = ordered[i];
				}
				ordered[inc]= tempItem;
			}
			number++;
		}
	}
	close(infile);
	int j;	
	/*for(j=0; j<totalItems; j++){
		printf("%d %d %d %f\n", available[j].id, available[j].weight, available[j].value, available[j].ratio);
	}*/
	node initial;
	initial.profit = 0;
	initial.capacity = 0;
	initial.level = 0;
	initial.prune = 0;
	initial.numItems = 0;
	initial.taken = malloc(sizeof(struct item)*totalItems);
	initial.max = maxProfit(packCap, totalItems, ordered, 0, 0, 0, 0);
	maxProf.profit = -1;
	int nodes;
	nodes = ((int)exp2(totalItems)); 
	node queue[nodes];
	queue[0] = initial;
	int queueLen = 1;
	while(queueLen != 0){
		node parent;
		int top =0;
		int i;
		for(i=0; i<queueLen; i++){
			if(queue[i].max > queue[top].max){
				top = i;
			}
		}
		parent.level = queue[top].level;
		parent.profit = queue[top].profit;
		parent.capacity = queue[top].capacity;
		parent.numItems = queue[top].numItems;
		parent.taken = queue[top].taken;
		parent.profit = queue[top].profit;
		parent.max = queue[top].max;
		parent.prune = queue[top].prune;
		/*printf("\n%d\n",parent.profit);
		printf("%d\n",parent.capacity);
		printf("%d\n",parent.level);
		printf("%d\n",parent.prune);
		printf("%d\n",parent.numItems);
		printf("%f\n",parent.max);*/
		visited++;
		//delete(queue[i]);
		queue[top].max = -1;
		queue[top].profit = -1;
		for(i=top; i<queueLen-1; i++){
			queue[i] = queue[i+1];
		}
		queueLen-=1;
		if(parent.capacity > packCap || parent.max<maxProf.profit || parent.level==totalItems){
			parent.prune=1;
		}
		if(parent.prune == 0){
			node child1;
			child1.level = parent.level+1;
			child1.profit = parent.profit+(available[parent.level].value);
			child1.capacity = parent.capacity+(available[parent.level].weight);
			child1.numItems = parent.numItems+1;
			child1.taken = parent.taken;
			child1.taken[parent.numItems] = available[parent.level];
			child1.max = parent.max;
			child1.prune = 0;
			if(child1.max < maxProf.profit){
				child1.prune = 1;
			}else{
				queue[queueLen] = child1;
				queueLen++;
			}
			if(child1.capacity <= packCap && child1.profit > maxProf.profit){
				maxProf.profit = child1.profit;
				maxProf.numItems = child1.numItems;
				maxProf.taken = child1.taken;
			}
			/*printf("\n%d\n",child1.profit);
			printf("%d\n",child1.capacity);
			printf("%d\n",child1.level);
			printf("%d\n",child1.prune);
			printf("%d\n",child1.numItems);
			printf("%f\n",child1.max);*/
			node child2;
			child2.level = parent.level+1;
			child2.profit = parent.profit;
			child2.capacity = parent.capacity;
			child2.numItems = parent.numItems;
			child2.taken = parent.taken;
			child2.max = maxProfit(packCap, totalItems, ordered, parent.capacity, parent.profit, child2.numItems, child2.level);
			child2.prune = 0;
			if(child2.max < maxProf.profit){
				child2.prune = 1;
			}else{
				queue[queueLen] = child2;
				queueLen++;
			}
			if(child2.capacity <= packCap && child2.profit > maxProf.profit){
				maxProf.profit = child2.profit;
				maxProf.numItems = child2.numItems;
				maxProf.taken = child2.taken;
			}
			/*printf("\n%d\n",child2.profit);
			printf("%d\n",child2.capacity);
			printf("%d\n",child2.level);
			printf("%d\n",child2.prune);
			printf("%d\n",child2.numItems);
			printf("%f\n",child2.max);*/
		}else{
			leaf++;
		}
	}
	free(available);
	free(ordered);
	//printf("%d\n", maxProf.profit);
	FILE *outfile =  fopen(argv[2], "w");
	if(!outfile){
		printf("%s could not be opened. Program terminated.\n", argv[2]);
		return -1;
	}
	fprintf(outfile,"%d,%d,%d\n", totalItems, maxProf.profit, maxProf.numItems);
	fprintf(outfile,"%d,%d\n", visited, leaf);
	int k;
	for(k=0;k<maxProf.numItems; k++){
		fprintf(outfile,"%d,%d\n", maxProf.taken[k].weight, maxProf.taken[k].value);
	}
	close(outfile);
}

