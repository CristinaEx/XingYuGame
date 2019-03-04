#include<vector>
#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;

int game_4(vector<int> initial,int mode);
int game_8(vector<int> initial,int mode);
int game_finish(vector<int> initial);
vector<int> game_finish_move(vector<int> initial,int num,int pos);

int printGame(vector<int> initial){
	cout<<endl;
	for(int i = 0;i < 16;i++){
		if(initial[i] == 0)
			cout<<"\t";
		else
			cout<<initial[i]<<"\t";
		if(i%4 == 3)
			cout<<endl; 
	}
}

//返回next 
//列 
vector<int> moveColumn(vector<int> initial,int empty_pos,int next_empty_pos){
	vector<int> next = initial;
	int j = 0;
	for(int i = 0;i < 4;i++){
		if(j == empty_pos/4)
			j++;
		if(i == next_empty_pos/4)
			next[empty_pos%4+4*i] = 0;
		else{
			next[empty_pos%4+4*i] = initial[empty_pos%4+4*j];
			j++;
		}
	}
	return next;
}

//返回next 
//行 
vector<int> moveRow(vector<int> initial,int empty_pos,int next_empty_pos){
	vector<int> next = initial;
	int j = 0;
	for(int i = 0;i < 4;i++){
		if(j == empty_pos%4)
			j++;
		if(i == next_empty_pos%4)
			next[empty_pos-empty_pos%4+i] = 0;
		else{
			next[empty_pos-empty_pos%4+i] = initial[empty_pos-empty_pos%4+j];
			j++;
		}
	}
	return next;
}

//成功返回0，不成功返回1
int game(vector<int> initial){
	vector<int> next = initial;
	int pos = 0;//需向该方向移动 
	for(;pos < 16;pos++){
		if(initial[pos] != pos+1)
			break;
	}
	if(pos == 16){
		cout<<"finish"<<endl;
		return 0;
	}
	else if(pos > 7)
		return game_finish(initial);
	int now_pos = 0;//目前的应在目标位置的方块的位置 
	for(;now_pos < 16;now_pos++){
		if(initial[now_pos] == pos+1)
			break;
	}
	int empty_pos = 0;//目前的空位位置 
	for(;empty_pos < 16;empty_pos++){
		if(initial[empty_pos] == 0)
			break;
	}
	switch(pos){
		case 0:
		case 4:
			if(empty_pos/4 < now_pos/4 ){
				if(empty_pos%4 == now_pos%4){
					next = moveColumn(initial,empty_pos,now_pos);
					break;
				}
				next = moveRow(initial,empty_pos,empty_pos-empty_pos%4+now_pos%4);
			}
			else if(empty_pos%4 < now_pos%4){
				if(empty_pos/4 == now_pos/4){
					next = moveRow(initial,empty_pos,now_pos);
					break;
				}
				next = moveColumn(initial,empty_pos,now_pos - now_pos%4 + empty_pos%4);
			}
			else if(empty_pos/4==now_pos/4){
				if(empty_pos < 12)
					next = moveColumn(initial,empty_pos,empty_pos+4);
				else
					next = moveColumn(initial,empty_pos,empty_pos-4);
			}
			else if(empty_pos%4==now_pos%4){
				if(empty_pos%4 < 3)
					next = moveRow(initial,empty_pos,empty_pos+1);
				else
					next = moveRow(initial,empty_pos,empty_pos-1);
			}
			else{
				if(pos%4 < now_pos%4)
					next = moveRow(initial,empty_pos,empty_pos-empty_pos%4+now_pos%4-1);
				else
					next = moveColumn(initial,empty_pos,now_pos-now_pos%4+empty_pos%4-4);
			}
			break;
		case 1:
		case 2:
		case 5:
		case 6:
			if(now_pos%4 < pos%4){
				if(empty_pos%4 <= now_pos%4){
					if(empty_pos/4 == now_pos/4)
						if(empty_pos < 12)
							next = moveColumn(initial,empty_pos,empty_pos+4);
						else
							next = moveColumn(initial,empty_pos,empty_pos-4);
					else
						next = moveRow(initial,empty_pos,empty_pos-empty_pos%4+now_pos%4+1);
				}
				else
					if(empty_pos/4 == now_pos/4)
						next = moveRow(initial,empty_pos,now_pos);
					else
						next = moveColumn(initial,empty_pos,now_pos-now_pos%4+empty_pos%4);
			} 
			else if(empty_pos%4 < pos%4){
				if(empty_pos/4 == now_pos/4)
					if(empty_pos < 12)
						next = moveColumn(initial,empty_pos,empty_pos+4);
					else
						next = moveColumn(initial,empty_pos,empty_pos-4);
				else
					next = moveRow(initial,empty_pos,empty_pos+1);
			}
			else if(empty_pos/4 < now_pos/4 ){
				if(empty_pos%4 == now_pos%4){
					next = moveColumn(initial,empty_pos,now_pos);
					break;
				}
				next = moveRow(initial,empty_pos,empty_pos-empty_pos%4+now_pos%4);
			}
			else if(empty_pos%4 < now_pos%4){
				if(empty_pos/4 == now_pos/4){
					next = moveRow(initial,empty_pos,now_pos);
					break;
				}
				next = moveColumn(initial,empty_pos,now_pos - now_pos%4 + empty_pos%4);
			}
			else if(empty_pos/4==now_pos/4){
				if(empty_pos < 12)
					next = moveColumn(initial,empty_pos,empty_pos+4);
				else
					next = moveColumn(initial,empty_pos,empty_pos-4);
			}
			else if(empty_pos%4==now_pos%4){
				if(empty_pos%4 < 3)
					next = moveRow(initial,empty_pos,empty_pos+1);
				else
					next = moveRow(initial,empty_pos,empty_pos-1);
			}
			else{
				if(pos%4 < now_pos%4)
					next = moveRow(initial,empty_pos,empty_pos-empty_pos%4+now_pos%4-1);
				else
					next = moveColumn(initial,empty_pos,now_pos-now_pos%4+empty_pos%4-4);
			}
			break;
		case 3:
			return game_4(initial,0);
		case 7:
			return game_8(initial,0);
		default:
			return 1;
	}
	printGame(next);
	return game(next);
}

int game_4(vector<int> initial,int mode){
	int pos = 0;//需向该方向移动 
	for(;pos < 16;pos++){
		if(initial[pos] != pos+1)
			break;
	}
	if(pos > 3)
		return game(initial);
	pos = 7;
	vector<int> next = initial;
	int empty_pos = 0;//目前的空位位置 
	for(;empty_pos < 16;empty_pos++){
		if(initial[empty_pos] == 0)
			break;
	}
	int now_pos = 0;//目前的应在目标位置的方块的位置 
	for(;now_pos < 16;now_pos++){
		if(initial[now_pos] == 4)
			break;
	}
	switch(mode){
		//将4放在pos = 7处 
		case 0:
			if(empty_pos == 3)
				next = moveColumn(initial,empty_pos,now_pos-now_pos%4+3);
			else if(empty_pos/4 < now_pos/4 ){
				if(empty_pos%4 == now_pos%4)
						next = moveColumn(initial,empty_pos,now_pos);
				else
					next = moveRow(initial,empty_pos,empty_pos-empty_pos%4+now_pos%4);
			}
			else if(empty_pos%4 > now_pos%4){
				if(empty_pos/4 == now_pos/4)
					next = moveRow(initial,empty_pos,now_pos);
				else
					next = moveColumn(initial,empty_pos,now_pos - now_pos%4 + empty_pos%4);
			}
			else if(empty_pos/4==now_pos/4){
				if(empty_pos < 12)
					next = moveColumn(initial,empty_pos,empty_pos+4);
				else
					next = moveColumn(initial,empty_pos,empty_pos-4);
			}
			else if(empty_pos%4==now_pos%4){
				if(empty_pos%4 < 3)
					next = moveRow(initial,empty_pos,empty_pos+1);
				else
					next = moveRow(initial,empty_pos,empty_pos-1);
			}
			else{
				if(pos%4 > now_pos%4)
					next = moveRow(initial,empty_pos,empty_pos-empty_pos%4+now_pos%4+1);
				else
					next = moveColumn(initial,empty_pos,now_pos-now_pos%4+empty_pos%4-4);
			}
			printGame(next);
			if(next[7] == 4)
				return game_4(next,1);
			return game_4(next,0);
		//将0放在pos=5处 
		case 1:
			if(empty_pos%4 != 1)
				next = moveRow(initial,empty_pos,empty_pos-empty_pos%4+1);
			else
				next = moveColumn(initial,empty_pos,5);
			printGame(next);
			if(next[5] == 0)
				return  game_4(next,2);
			return game_4(next,1);
		case 2:
			next = moveColumn(initial,empty_pos,1);
			printGame(next);
			return game_4(next,3);
		case 3:
			next = moveRow(initial,empty_pos,3);
			printGame(next);
			return game_4(next,4);
		case 4:
			next = moveColumn(initial,empty_pos,7);
			printGame(next);
			return game_4(next,5);
		case 5:
			next = moveRow(initial,empty_pos,6);
			printGame(next);
			return game_4(next,6);
		case 6:
			next = moveColumn(initial,empty_pos,2);
			printGame(next);
			return game_4(next,7);
		case 7:
			next = moveRow(initial,empty_pos,1);
			printGame(next);
			return game_4(next,8);
		case 8:
			next = moveColumn(initial,empty_pos,5);
			printGame(next);
			return game(next);
		default:
			return 1;
	}
	return 0;
}

int game_8(vector<int> initial,int mode){
	int pos = 0;//需向该方向移动 
	for(;pos < 16;pos++){
		if(initial[pos] != pos+1)
			break;
	}
	if(pos > 7)
		return game(initial);
	pos = 7;
	vector<int> next = initial;
	int empty_pos = 0;//目前的空位位置 
	for(;empty_pos < 16;empty_pos++){
		if(initial[empty_pos] == 0)
			break;
	}
	int now_pos = 0;//目前的应在目标位置的方块的位置 
	for(;now_pos < 16;now_pos++){
		if(initial[now_pos] == 8)
			break;
	}
	switch(mode){
		//将8放在pos = 7处 
		case 0:
			if(empty_pos == 7)
				next = moveColumn(initial,empty_pos,now_pos-now_pos%4+3);
			else if(empty_pos/4 < now_pos/4 ){
				if(empty_pos%4 == now_pos%4)
						next = moveColumn(initial,empty_pos,now_pos);
				else
					next = moveRow(initial,empty_pos,empty_pos-empty_pos%4+now_pos%4);
			}
			else if(empty_pos%4 > now_pos%4){
				if(empty_pos/4 == now_pos/4)
					next = moveRow(initial,empty_pos,now_pos);
				else
					next = moveColumn(initial,empty_pos,now_pos - now_pos%4 + empty_pos%4);
			}
			else if(empty_pos/4==now_pos/4){
				if(empty_pos < 12)
					next = moveColumn(initial,empty_pos,empty_pos+4);
				else
					next = moveColumn(initial,empty_pos,empty_pos-4);
			}
			else if(empty_pos%4==now_pos%4){
				if(empty_pos%4 < 3)
					next = moveRow(initial,empty_pos,empty_pos+1);
				else
					next = moveRow(initial,empty_pos,empty_pos-1);
			}
			else{
				if(pos%4 > now_pos%4)
					next = moveRow(initial,empty_pos,empty_pos-empty_pos%4+now_pos%4+1);
				else
					next = moveColumn(initial,empty_pos,now_pos-now_pos%4+empty_pos%4-4);
			}
			printGame(next);
			if(next[11] == 8)
				return game_8(next,1);
			return game_8(next,0);
		//将0放在pos=9处 
		case 1:
			if(empty_pos%4 != 1)
				next = moveRow(initial,empty_pos,empty_pos-empty_pos%4+1);
			else
				next = moveColumn(initial,empty_pos,9);
			printGame(next);
			if(next[9] == 0)
				return  game_8(next,2);
			return game_8(next,1);
		case 2:
			next = moveColumn(initial,empty_pos,5);
			printGame(next);
			return game_8(next,3);
		case 3:
			next = moveRow(initial,empty_pos,7);
			printGame(next);
			return game_8(next,4);
		case 4:
			next = moveColumn(initial,empty_pos,11);
			printGame(next);
			return game_8(next,5);
		case 5:
			next = moveRow(initial,empty_pos,10);
			printGame(next);
			return game_8(next,6);
		case 6:
			next = moveColumn(initial,empty_pos,6);
			printGame(next);
			return game_8(next,7);
		case 7:
			next = moveRow(initial,empty_pos,5);
			printGame(next);
			return game_8(next,8);
		case 8:
			next = moveColumn(initial,empty_pos,9);
			printGame(next);
			return game(next);
		default:
			return 1;
	}
	return 0;
}

//pos处逆时针转一下 
/*
pos = 0时 
x x x x    x x x x
x x x x -> x x x x
p p x x -> p   x x
p   x x    p p x x
*/
vector<int> game_finish_move_2(vector<int> initial,int pos){
	vector<int> next = initial;
	int empty_pos = 0;//目前的空位位置 
	for(;empty_pos < 16;empty_pos++){
		if(initial[empty_pos] == 0)
			break;
	}
	if(empty_pos/4 == 2){
		initial = moveColumn(initial,empty_pos,empty_pos+4);
		printGame(initial);
		empty_pos = empty_pos+4;
	} 
	initial = moveRow(initial,empty_pos,empty_pos-empty_pos%4+pos);
	printGame(initial);
	empty_pos = empty_pos-empty_pos%4+pos;
	initial = moveColumn(initial,empty_pos,empty_pos-4);
	printGame(initial);
	empty_pos = empty_pos-4;
	next = moveRow(initial,empty_pos,empty_pos+1);
	printGame(initial);
	return next;
}

int game_finish(vector<int> initial){
	int pos = 0;//需向该方向移动 
	for(;pos < 16;pos++){
		if(initial[pos] != pos+1)
			break;
	}
	switch(pos){
		case 11:
			if(initial[12] == 13 && initial[13] == 14 && initial[14] == 15){
				initial = moveColumn(initial,15,11);
				printGame(initial);
				return game_finish(initial);
			}
		case 10:
			if(initial[12] == 13 && initial[13] == 14){
				//排列11和15 
				initial = game_finish_move(initial,15,2);
				printGame(initial);
				int empty_pos = 0;//目前的空位位置 
				for(;empty_pos < 16;empty_pos++)
					if(initial[empty_pos] == 0)
						break;
				if(empty_pos == 14){
					initial = moveRow(initial,14,15);
					printGame(initial);
				}
				if(empty_pos == 15){
					initial = moveColumn(initial,15,11);
					printGame(initial);
				}
				//empty_pos == 11
				if(initial[15] == 11){
					initial = moveColumn(initial,11,15);
					printGame(initial);
					initial = moveRow(initial,15,14);
					printGame(initial);
					initial = moveColumn(initial,14,10);
					printGame(initial);
					initial = moveRow(initial,10,11);
					printGame(initial);
					initial = moveColumn(initial,11,15);
					printGame(initial);
					return game_finish(initial);
				}
				/*
				15 12 
				11  	的状况 
				*/
				return empty_pos;
			}
		case 9:
			if(initial[12] == 13){
				//排列10和14 
				initial = game_finish_move(initial,14,1);
				//将10放在pos=10处
				for(;pos < 16;pos++){
					if(initial[pos] == 10)
						break;
				}
				if(pos != 13)
					initial =  game_finish_move(initial,10,2);
				else{
				int empty_pos = 0;//目前的空位位置 
				for(;empty_pos < 16;empty_pos++)
					if(initial[empty_pos] == 0)
						break;
				if(empty_pos/4 == 2){
					initial = moveColumn(initial,empty_pos,empty_pos+4);
					printGame(initial);
					empty_pos = empty_pos + 4;
				}
				initial = moveRow(initial,empty_pos,13);
				printGame(initial);
				initial = moveColumn(initial,13,9);
				printGame(initial);
				initial = moveRow(initial,9,10);
				printGame(initial);
				initial = moveColumn(initial,10,14);
				printGame(initial);
				initial = moveRow(initial,14,15);
				printGame(initial);
				initial = moveColumn(initial,15,11);
				printGame(initial);
				initial = moveRow(initial,11,9);
				printGame(initial);
				initial = moveColumn(initial,9,13);
				printGame(initial);
				initial = moveRow(initial,13,14);
				printGame(initial);
				initial = moveColumn(initial,14,10);
				printGame(initial);
				initial = moveRow(initial,10,11);
				printGame(initial);
				}
				initial = game_finish_move_2(initial,1);
				printGame(initial);
				return game_finish(initial);		
			}
		case 8:
			//排列9和13 
			initial = game_finish_move(initial,13,0);
			//将9放在pos=9处
			for(;pos < 16;pos++){
				if(initial[pos] == 9)
					break;
			}
			if(pos != 12)
				initial =  game_finish_move(initial,9,1);
			else{
				int empty_pos = 0;//目前的空位位置 
				for(;empty_pos < 16;empty_pos++)
					if(initial[empty_pos] == 0)
						break;
				if(empty_pos/4 == 2){
					initial = moveColumn(initial,empty_pos,empty_pos+4);
					printGame(initial);
					empty_pos = empty_pos + 4;
				}
				initial = moveRow(initial,empty_pos,12);
				printGame(initial);
				initial = moveColumn(initial,12,8);
				printGame(initial);
				initial = moveRow(initial,8,9);
				printGame(initial);
				initial = moveColumn(initial,9,13);
				printGame(initial);
				initial = moveRow(initial,13,14);
				printGame(initial);
				initial = moveColumn(initial,14,10);
				printGame(initial);
				initial = moveRow(initial,10,8);
				printGame(initial);
				initial = moveColumn(initial,8,12);
				printGame(initial);
				initial = moveRow(initial,12,13);
				printGame(initial);
				initial = moveColumn(initial,13,9);
				printGame(initial);
				initial = moveRow(initial,9,10);
				printGame(initial);
			}
			initial = game_finish_move_2(initial,0);
			printGame(initial);
			return game_finish(initial);
		case 16:
			cout<<"finish"<<endl;
			return 0;
		default:
			return 1;
	}
	return 0;
} 

//num -> 第三行pos处 
vector<int> game_finish_move(vector<int> initial,int num,int pos){
	vector<int> next = initial;
	int now_pos = 0;//目前的应在目标位置的方块的位置 
	for(;now_pos < 16;now_pos++){
		if(initial[now_pos] == num)
			break;
	}
	int empty_pos = 0;//目前的空位位置 
	for(;empty_pos < 16;empty_pos++){
		if(initial[empty_pos] == 0)
			break;
	}
	if(now_pos/4 != 2){
		if(empty_pos/4 == 2)
			if(empty_pos%4 == now_pos%4){
				next = moveColumn(initial,empty_pos,empty_pos+4);
				printGame(next);
				return game_finish_move(next,num,pos);
			}
			else{
				int next_empty_pos = empty_pos-empty_pos%4+now_pos%4;
				next = moveRow(initial,empty_pos,next_empty_pos);
				printGame(next);
				next = moveColumn(next,next_empty_pos,next_empty_pos+4);
				printGame(next);
				return game_finish_move(next,num,pos);
			} 
		else{
			if(empty_pos%4 != now_pos%4){
				next = moveColumn(initial,empty_pos,empty_pos-4);
				printGame(next);
				return game_finish_move(next,num,pos);
			}
			else{
				next = moveRow(initial,empty_pos,empty_pos-empty_pos%4 == 0?-1:1);
				printGame(next);
				return game_finish_move(next,num,pos);
			}
		}
	}
	else if(now_pos%4 != pos){
		if(empty_pos%4 < now_pos%4){
			if(empty_pos/4 == 2){
				next = moveRow(initial,empty_pos,now_pos);
				printGame(next);
				return game_finish_move(next,num,pos);
			}
			else{
				next = moveColumn(initial,empty_pos,empty_pos-4);
				printGame(next);
				return game_finish_move(next,num,pos);
			}
		}
		else if(empty_pos%4 == now_pos%4){
			next = moveRow(initial,empty_pos,empty_pos-empty_pos%4+now_pos%4-1);
			printGame(next);
			return game_finish_move(next,num,pos);
		}
		else{
			if(empty_pos/4 == 2){
				next = moveColumn(initial,empty_pos,empty_pos+4);
				printGame(next);
				return game_finish_move(next,num,pos);
			}
			else{
				next = moveRow(initial,empty_pos,empty_pos-empty_pos%4+now_pos%4-1);
				printGame(next);
				return game_finish_move(next,num,pos);
			}
		}
	}
	return next;
}

int main() {
	//设定随机数种子
	srand( (unsigned)time(NULL));
	vector<int> nums = vector<int>();
	for(int i = 0;i <= 15;i++){
		nums.push_back(i);
	}
	vector<int> initial = vector<int>();//初始化游戏数据 
	while(!nums.empty()){
		int index = rand()%nums.size();
		initial.push_back(nums[index]);
		vector<int>::iterator it = nums.begin();
		for(int i = 0;i < index;i++)
			it++;
		nums.erase(it);
	}
	printGame(initial);
	return game(initial);
}
