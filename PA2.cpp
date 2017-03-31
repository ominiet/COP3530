#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;

class HashTable{
	public:

		int* table;
		int buckets;

		HashTable(int size);	//constructor
		void hash(int ins);		//hashing function
		int getInt(int get);	//checks if int is in table
		int getMax();			//finds max multiplication
		int linearProbe(int key, int probeFor);//collision handling
		void print();			//not used in project just for testing
};

HashTable::HashTable(int size){
	buckets = size;			//creates enough buckets for inputs
	table = new int[size];	//makes array for the necessary table
	memset(table, -1, buckets * 4);	//fills array with 
}

void HashTable::hash(int ins){
	int key = ins % buckets;	//basic hashing function
	if (table[key] != -1){		//if index is used, probe for empty spot
		key = linearProbe(key,-1);//probes for new key
	} 
	table[key] = ins;//places element at key
}

int HashTable::getInt(int get){
	bool isIn = false;
	int key = get % buckets;
	if (table[key] == get){	//if element is at expected location -> true
		isIn = true;
	}
	else if (table[linearProbe(key,get)] == get){//else if need to search for it by probing
		isIn = true;
	} 
	if (isIn == false){		//else return neg 1
		get = -1;
	}
	return get;
}

int HashTable::getMax(){
	int max = -1;
	int temp = -1;
	for (int i = 0; i < (buckets - 1); i ++){
		for (int j = (i + 1); j < buckets; j++){//permutes through all elements of an array
			if (table[i] > 0 && table [j] > 0)	//if elements are both greater than 0, check if product is in array
			temp = getInt(table[i]*table[j]);	//checks if product is in array
			if(temp > max){						//keeps track of largest valid product
				max = temp;
			}
		}
	}
	return max;
}

int HashTable::linearProbe(int key, int probeFor){
	int offset = 0;
	while (true){		
		offset *= -1;				
		if (offset >= 0) offset ++;			//checks next locations after then before for an open slot
		else offset --;
		key = key + offset;					//makes key new offsetted key
		if ((key) >= 0 && (key) < buckets){	//if the key is within the range, move to next check
			if (table[key] == probeFor) {	//if the key is what you are probing for, stop finding new keys
				break;
			}
		}
		if (abs(key) > buckets){			//times out search for key if it has checked every location
			key = -1;						
			break;
		}
	}
	return key;
}
void HashTable::print(){					//unused in final submission
	for (int x = 0; x < buckets; x++){
		cout << table[x] << " ";
	}
	cout << "\n";
}

int main(){
	int size;
	int maxMult = -1;
	int temp = -1;
	int hash = -1;
	bool hasNeg = false;
	cin >> size;

	HashTable* table = new HashTable(size);

	for (int i = 0; i < size; i++){			//takes input 
		cin >> hash;
		if (hash < 1) hasNeg = true;		//only hashes if the number is in Z+
		table->hash(hash);					
	}
	maxMult = table->getMax();
	if (hasNeg == true) maxMult = -1;
	cout << maxMult;						//final print

	return 0;
}