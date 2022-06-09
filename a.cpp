#include<iostream>
#include<vector>

using namespace std;

char *maze;
char *buffer;
int N;

bool get(int x, int y, char* ptr){
	char byte = ptr[(x + N*y)/8];
	char mask = 0b10000000 >> ((x + N*y)%8);
	return byte & mask;
}

// Direction
//  0
// 3 1
//  2
bool offset(int x, int y, char* ptr, char direction){
	switch(direction){
		case 0:
			return get(x, y-1, ptr);
		case 1:
			return get(x+1, y, ptr);
		case 2:
			return get(x, y+1, ptr);
		case 3:
			return get(x-1, y, ptr);
		default:
			exit(1);
	}
}

void go(int &x, int &y, char direction){
	switch(direction){
		case 0:
			y--;
			return;
		case 1:
			x++;
			return;
		case 2:
			y++;
			return;
		case 3:
			x--;
			return;
		default:
			exit(1);
	}
}

void unset(int x, int y, char* ptr){
	char mask = 0b10000000 >> ((x + N*y)%8);
	mask ^= 0b11111111;
	ptr[(x + N*y)/8] &= mask;
	return;
}

void set(int x, int y, char* ptr){
	char mask = 0b10000000 >> ((x + N*y)%8);
	ptr[(x + N*y)/8] |= mask;
	return;
}

int solve(int x, int y){
	int count = 0;

	vector<char> walked_path;
	// Each element in this vector shows the
	// direction to the previous step

	while(true){
		const bool here = get(x, y, maze);

		if(!get(x, y, buffer)){
			count++;
			set(x, y, buffer);
		}

		char i;
		for(i = 0; i < 4; i++) {
			if( i == 0 && y == 0 ||
			    i == 1 && x == N-1 ||
			    i == 2 && y == N-1 ||
			    i == 3 && x == 0)
				continue;
			if(!offset(x, y, buffer, i) && (here ^ offset(x, y, maze, i)))
				break;
		}
		if(i == 4){
			if(!walked_path.size())
				break;
			go(x, y, walked_path.back());
			walked_path.pop_back();
			continue;
		}
		walked_path.push_back((i+2) % 4);
		go(x, y, i);
	}
	return count;
}

int main(){
	int m;
	cin >> N >> m;
	maze = new char[N*N/8 + 1] {0};
	for(char i = 0; i < N; i++){
		for(char j = 0; j < N; j++){
			char c;
			do{
				cin >> c;
			}while(c == '\n');
			if(c == '1')
				set(j, i, maze);
		}
	}
	for(int i = 0; i < m; i++){
		int x, y;
		cin >> x >> y;
		buffer = new char[N*N/8 + 1] {0};
		cout << solve(x-1, y-1) << endl;
		delete buffer;
	}
	delete maze;
}
