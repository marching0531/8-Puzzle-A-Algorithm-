#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <algorithm>

#define PUZZLE_NUM 9

using namespace std;

typedef struct node{
	char state[ PUZZLE_NUM ];
	int f;
	int g;
	bool operator<(const node &o) const{
		return f < o.f;
	}
}NODE;

NODE start = {{2,8,3,1,6,4,7,-1,5},4};
NODE goal = {{1,2,3,8,-1,4,7,6,5},5};
int g = 0;
vector<NODE> open,close;

void draw(NODE &node);
void findChild();
int findEmpty();
int manhattan(NODE &node);
bool checkClose(char *node);
void swap(NODE &node, int empty, int point);
void drawClose();
int checkOpen(char *node);
void drawOpen();
void pushNode(NODE &node, char *state[PUZZLE_NUM], int empty, int point);

void draw(NODE &node){

	for(int i = 0; i < PUZZLE_NUM; i++){
		if(i%3 == 0) 
			printf("\n");
		if(node.state[i] == -1)
			printf("  ");
		else
			printf("%d ", node.state[i]);
	}
	printf("\n\nf(n) is %d and g(n) is %d\n",node.f,g);
	
	//printf("\n==============\n");
}

void findChild(){
	
	int empty = 0;
	NODE tmpNode;
	char *tmpState[PUZZLE_NUM];
	
	memcpy(tmpState,open.front().state,9);
	empty = findEmpty();
	close.push_back(open.front());
	open.erase(open.begin());
	g++;
	
	if( empty != -1){

		if((empty % 3) != 0){//left
			pushNode(tmpNode,tmpState,empty,empty-1);
                }

		if(empty > 2){//up 
			pushNode(tmpNode,tmpState,empty,empty-3);
		}

		if((empty % 3) != 2){//right
			pushNode(tmpNode,tmpState,empty,empty +1);
                }

		if(empty < 6){//down
			pushNode(tmpNode,tmpState,empty,empty +3);
		}	
			
	}
	sort(open.begin(),open.end());
	return;	
}

void pushNode(NODE &node, char *state[PUZZLE_NUM], int empty, int point){
	memcpy(node.state,state,9);
	swap(node,empty,point);
	node.g = g;
	node.f = manhattan(node);
	if(checkOpen(node.state) != 0)
		open[checkOpen(node.state)].f = node.f;
	else if(checkClose(node.state))
		open.push_back(node);
}

void swap(NODE &node, int empty, int point){

	int tmp = node.state[empty];
	node.state[empty] = node.state[point];
	node.state[point] = tmp;
	
}

int findEmpty(){

	for(int i = 0; i < PUZZLE_NUM; i++){
		if(open.front().state[i] == -1)
			return i;
	}

	return -1;
}

int manhattan(NODE &node){
	
	int cmp = 0;
	char *tmpStr[PUZZLE_NUM];
	memcpy(tmpStr,goal.state,9);
	for(int i = 0; i < PUZZLE_NUM; i++){
		
		if(node.state[i] != -1 && memcmp(node.state+i,goal.state+i,1) !=0)
			cmp += 1;
	}
	
	return cmp + node.g;
}

bool checkClose(char *node){

	for(int i = 0; i < close.size(); i++){
		if(memcmp(node,close[i].state,9) == 0)
			return false;
	}
	return true;
}

int checkOpen(char *node){

	for(int i = 0; i < open.size(); i++){
		if(memcmp(node,open[i].state,9) == 0)
			return i;
	}
	return 0;
}

void drawClose(){
	
	printf("current closed queue state is \n");
	for(int i = 0; i < close.size(); i++){

		for(int j = 0; j < PUZZLE_NUM; j++){
			if(j%3 == 0) 
				printf("\n");
			if(close[i].state[j] == -1)
				printf("  ");
			else
				printf("%d ", close[i].state[j]);
	}	
	printf("\n\nf(n) is %d and g(n) is %d\n",close[i].f,close[i].g);
}
}

void drawOpen(){

	printf("current opened queue state is \n");
	for(int i = 0; i < open.size(); i++){

		for(int j = 0; j < PUZZLE_NUM; j++){
			if(j%3 == 0) 
				printf("\n");
			if(open[i].state[j] == -1)
				printf("  ");
			else
				printf("%d ", open[i].state[j]);
	}
	printf("\n\nf(n) is %d and g(n) is %d\n",open[i].f,open[i].g);
	
}
}

int main(){
	open.push_back(start);
	printf("start state is \n");
	draw(open.front());
	while(!open.empty()){
		if(memcmp(open.front().state, goal.state, 9) == 0){
			printf("Found Goal!\n");
			draw(open.front());
			break;
		}
		else{
			findChild();
			draw(open.front());
			g = open.front().g;
		}
	}
	return 0;
}
