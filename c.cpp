#include<iostream>
#include<string.h>

using namespace std;

int main(){
	int n, m, p;
	cin>>n>>m>>p;
	short * map = new short[n] {0};
	short ** parts = new short*[n+1];
	for(int i = 0; i < n+1; i++)
		parts[i] = new short[n+1]{0};

	for(int i = 0; i < m; i++){
		short a, b;
		cin>>a>>b;
		if(map[a] == 0 && map[b] == 0){
			short dest = 0;
			for(int i = 1; i <= n; i++)
				if(parts[i][0] == 0)
					dest = i;
			if(!dest)
				exit(1);

			map[a] = map[b] = dest;
			parts[dest][ ++parts[dest][0] ] = a;
			parts[dest][ ++parts[dest][0] ] = b;
		}else if(map[a] == 0 || map[b] == 0){
			short zero = map[a]==0 ? a : b;
			short nonzero = map[a]==0 ? b : a;
			map[zero] = map[nonzero];
			short nzpart = map[nonzero];
			parts[nzpart][ ++parts[nzpart][0] ] = zero;
		}else{
			short dest = a<b ? a : b;
			short source = a<b ? b : a;
			short srcpart = map[source];
			short destpart = map[dest];
			for(int i = 1; i <= parts[srcpart][0]; i++){
				map[ parts[srcpart][i] ] = destpart;
				parts[destpart][ ++parts[destpart][0] ] = 
					parts[srcpart][i];
			}
			parts[srcpart][0] = 0;
		}
	}

	for(int i = 0; i < p; i++){
		short a, b;
		cin>>a, b;
		if(map[a] == map[b] && map[a] != 0 && map[b] != 0)
			cout<<"Yes"<<endl;
		else
			cout<<"No"<<endl;
	}
	return 0;
}
