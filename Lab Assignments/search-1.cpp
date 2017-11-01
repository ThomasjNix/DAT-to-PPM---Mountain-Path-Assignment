/*
 * Thomas Nix
 * ITCS 3112
 * Professor Subramanian
 * Completed 10/25/2017
 */

//Included dependancies
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

template <class T, class U>
void search(T a[], int first, int last, U key, bool& found, int& location);


int main(){
	int a[15] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	float b[15] = {1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9,10.1,11.2,12.3,13.4,14.5,15.6};
	char c[15] = {'a','b','c','d','e','f','g','h','i','j'};
	int key1, key4;
	float key2, key5;
	char key3, key6;
	
	cout << "Enter first number to be located: ";
	cin >> key1;
	cout << "Enter second number to be located: ";
	cin >> key4;
	cout << "Enter first float to be located: ";
	cin >> key2;
	cout << "Enter second float to be located: ";
	cin >> key5;
	cout << "Enter first char to be located: ";
	cin >> key3;
	cout << "Enter second char to be located: ";
	cin >> key6;
	int location1,location2,location3,location4,location5,location6, finalIndex, finalIndex2;
	finalIndex = 14;
	finalIndex2 = 9;
	bool found1;
	bool found2;
	bool found3;
	bool found4;
	bool found5;
	bool found6;

	search<int,int>(a,0,finalIndex,key1,found1,location1);
	search<float,float>(b,0,finalIndex,key2,found2,location2);
	search<char,char>(c,0,finalIndex2,key3,found3,location3);
	search<int,int>(a,0,finalIndex,key4,found4,location4);
	search<float,float>(b,0,finalIndex,key5,found5,location5);
	search<char,char>(c,0,finalIndex2,key6,found6,location6);
	
	if (found1){
		cout << key1 << " is in index location " << location1 << endl;
	}else{
		cout << key1 << " is not in the array." << endl;
	}
	
	if (found2){
		cout << key2 << " is in index location " << location2 << endl;
	}else{
		cout << key2 << " is not in the array." << endl;
	}
	
	if (found3){
		cout << key3 << " is in index location " << location3 << endl;
	}else{
		cout << key3 << " is not in the array." << endl;
	}
	
	if (found4){
		cout << key4 << " is in index location " << location4 << endl;
	}else{
		cout << key4 << " is not in the array." << endl;
	}
	
	if (found5){
		cout << key5 << " is in index location " << location5 << endl;
	}else{
		cout << key5 << " is not in the array." << endl;
	}
	
	if (found6){
		cout << key6 << " is in index location " << location6 << endl;
	}else{
		cout << key6 << " is not in the array." << endl;
	}
	
	return 0;

}

template <class T, class U>
void search(T a[], int first, int last, U key, bool& found, int& location){
		int mid;
		if (first > last){
			found = false;
		}else{
			mid = ((first+last)/2);
			
			if (key == a[mid]){
				found = true;
				location = mid;
			}else if(key < a[mid]){
				search(a,first,mid-1,key,found,location);
			}else if(key > a[mid]){
				search(a,mid+1,last,key,found,location);
			}
		}
		
}



