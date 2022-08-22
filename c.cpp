#include<iostream>
#include<string.h>

using namespace std;

class Undigraph{
	private:
		unsigned char * matrix;
		int n;

	public:
		Undigraph(int n){
			this->n = n;
			matrix = new unsigned char[(1+n)*n/16+1]{0};
		}

		void release(){
			delete matrix;
		}

		Undigraph operator*(Undigraph m){
			Undigraph mat(n);
			for(int i = 0; i < n; i++)
				for(int j = 0; j < n; j++)
					for(int k = 0; k < n; k++)
						if(at(i, k) && m.at(k, j)){
							mat.set(i, j);
							break;
						}
			return mat;
		}

		Undigraph operator^(Undigraph m){
			Undigraph mat(n);
			for(int i = 0; i < (1+n)*n/16+1; i++)
				mat.matrix[i] = m.matrix[i] ^ matrix[i];
			return mat;
		}

		Undigraph operator&(Undigraph m){
			Undigraph mat(n);
			for(int i = 0; i < (1+n)*n/16+1; i++)
				mat.matrix[i] = m.matrix[i] & matrix[i];
			return mat;
		}

		Undigraph& operator&=(Undigraph m){
			*this = *this & m;
			return *this;
		}

		Undigraph operator|(Undigraph m){
			Undigraph mat(n);
			for(int i = 0; i < (1+n)*n/16+1; i++)
				mat.matrix[i] = m.matrix[i] | matrix[i];
			return mat;
		}

		Undigraph operator|=(Undigraph m){
			*this = *this | m;
			return *this;
		}

		Undigraph& operator=(Undigraph m){
			memcpy(matrix, m.matrix, (1+n)*n/16+1);
			return *this;
		}

		Undigraph& operator*=(Undigraph m){
			*this = *this * m;
			return *this;
		}

		bool at(int x, int y){
			if(x > y)
				return at(y, x);
			int index = y-x + (n+n-x+1)*x/2;
			unsigned char byte = matrix[index/8];
			return byte & 0x80>>index%8;
		}

		void set(int x, int y){
			if(x > y)
				return set(y, x);
			int index = y-x + (n+n-x+1)*x/2;
			matrix[index/8] = matrix[index/8] | 0x80>>index%8;
			return;
		}

		void unset(int x, int y){
			if(x > y)
				return unset(y, x);
			int index = y-x + (n+n-x+1)*x/2;
			matrix[index/8] = matrix[index/8] & (0x80>>index%8^0xFF);
			return;
		}

		bool empty(){
			for(int i = 0; i < (1+n)*n/16+1; i++)
				if(matrix[i])
					return false;
			return true;
		}
};

int main(){
	int n, m, p;
	cin>>n>>m>>p;
	Undigraph probe(n);
	for(int i = 0; i < m; i++){
		int a, b;
		cin>>a>>b;
		probe.set(a-1, b-1);
	}
	Undigraph known(n);
	known = probe;
	for(int i = 0; i < n; i++)
		known.set(i, i);
	Undigraph mask(n);
	for(int i = 0; i < n; i++)
		for(int j = i; j < n; j++)
			mask.set(i, j);

	Undigraph step(n);
	step = probe;
	while(!probe.empty()){
		probe *= step;
		probe &= known^mask;
		known |= probe;
	}

	for(int i = 0; i < p; i++){
		int x, y;
		cin>>x>>y;
		if(known.at(x, y))
			cout<<"Yes"<<endl;
		else
			cout<<"No"<<endl;
	}
	probe.release();
	step.release();
	known.release();
	mask.release();
}
