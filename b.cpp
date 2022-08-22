#include<iostream>
#include<string.h>

using namespace std;

template<typename T>
void integrate(T* dest, T* ptr1, unsigned int size1, T* ptr2, unsigned int size2){
	unsigned int i=0, j=0;
	T* buffer = new T[size1+size2];
	while(i < size1 && j < size2)
		buffer[i+j-1] = ptr1[i]>ptr2[j] ? ptr1[i++] : ptr2[j++];
	if(i == size1)
		memcpy(buffer+i+j, ptr2+j, (size2-j) * sizeof(T));
	else
		memcpy(buffer+i+j, ptr1+i, (size1-i) * sizeof(T));
	memcpy(dest, buffer, (size1+size2) * sizeof(T));
	delete buffer;
	return;
}

template<typename T>
void sort(T* ptr, unsigned int size){

	for(int i = 0; ; i++){
		if( (size>>i) & 0b1 ){

			if( size>>i == 0b1 )
				break;

			unsigned int mask = 0b1;
			bool flag = false;
			for(int j = 0; j < 8*sizeof(unsigned int); j++){
				if(size & 0b1<<j){
					sort(ptr + (size & mask>>1), 0b1 << j);
					if(flag){
						integrate(ptr, ptr, size & mask>>1, ptr + (size & mask>>1), 0b1<<j);
					}
					flag = true;
				}
				mask <<= 1;
				mask |= 0b1;
			}

			return;
		}
	}

	for(int i = 0; 0b1<<i < size; i++){
		for(unsigned int j = 0; j < size; j += (0b1<<i)*2)
			integrate(ptr+j, ptr+j, 0b1<<i, ptr+j+(0b1<<i), 0b1<<i);
	}
	return;
}

int main(){
	long m, n;
	cin>>m>>n;
	if(m >= n){
		cout<<0;
		return 0;
	}
	int* defense = new int[m];
	int* attack = new int[n];
	for(long i = 0; i < m; i++)
		cin>>defense[i];
	for(long i = 0; i < n; i++)
		cin>>attack[i];

	sort(defense, m);
	sort(attack, n);

	unsigned long long sum = 0;
	long i = m-1, j = n-1;
	while(i >= 0){
		if(attack[j] > defense[i]){
			i--;
			j--;
		}else
			sum += attack[j--];
		if(j < i){
			cout<<0;
			return 0;
		}
	}
	for(; j >= 0; j--)
		sum += attack[j];


	cout<<sum;
}
