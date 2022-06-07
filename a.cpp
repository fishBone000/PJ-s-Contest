#include<iostream>

using namespace std;

char *maze;
int N;

bool get(int x, int y, char* ptr){
	char byte = maze[(x + N*y)/8];
	char mask = 010000000 >> ((x + N*y)%8);
	return byte & mask;
}

// Direction
//  0
// 3 1
//  2
bool offset(int x, int y, char* ptr, char direction){
	switch(direction){
		case 0:
			return get(x, y-1);
		case 1:
			return get(x+1, y);
		case 2:
			return get(x, y+1);
		default:
			return get(x-1, y);
}

void unset(int x, int y, char* ptr){
	char mask = 010000000 >> ((x + N*y)%8);
	mask ^= 011111111;
	maze[(x + N*y)/8] &= mask;
	return;
}

void set(int x, int y, char* ptr){
	char mask = 010000000 >> ((x + N*y)%8);
	maze[(x + N*y)/8] |= mask;
	return;
}

int solve(int x, int y){
	char *buffer = new char[N*N/8 + 1];

	vector<char> walked_path;
	// Each element in this vector shows the
	// direction of previous step

	bool flag = true;
	while(flag){
		const bool here = get(x, y, maze);
		set(x, y, buffer);
		for(int i = 0; i < 4; i++)
			if(!offset(x, y, buffer, i) && (here ^ offset(x, y, maze, i)))
				switch(i){
					case 0:
	}
}

int main(){
	int m;
	cin >> N >> m;
	maze = new char[N*N/8 + 1];
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++){
			char c;
			cin >> c;
			if(c == '1')
				set(j, i, maze);
		}
	for(int i = 0; i < m; i++){
		int x, y;
		cin >> x >> y;
		cout << solve(x, y)<<endl;
	}
}