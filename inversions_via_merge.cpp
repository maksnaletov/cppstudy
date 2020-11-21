#include <iostream>
#include <string>
#include <vector>

long inversions = 0;

void merge(std::vector<int> *a, const long l, const long m, const long r, std::vector<int> *buf_v){
	long i = l, j = m, k = 0;
	while(i != m && j != r){
		if((*a)[i] > (*a)[j]){
			(*buf_v)[k++] = (*a)[j++];
			inversions += m - i;
		}
		else (*buf_v)[k++] = (*a)[i++];
	}
	while(i < m) (*buf_v)[k++] = (*a)[i++];
	while(j < r) (*buf_v)[k++] = (*a)[j++];
	while(k--){
		(*a)[l + k] = (*buf_v)[k];
	}
}

void merge_sort(std::vector<int> *a, const long l, const long r, std::vector<int> *buf_v){
	long m = l - (l - r) / 2;
	if((r == l + 2) && ((*a)[l] > (*a)[l+1])){
		inversions++;
		(*a)[l] ^= (*a)[l + 1] ^= (*a)[l] ^= (*a)[l + 1];
	}
	else if(r > l + 2){		
		merge_sort(a, l, m, buf_v);
		merge_sort(a, m, r, buf_v);
		merge(a, l, m, r, buf_v);
	}
}

int main(){
	long n, i;
	std::cin >> n;
	std::vector<int> a, buf_v;
	std::string numbers, buf_s;
	getline(std::cin, numbers);
	getline(std::cin, numbers);
	for(i = 0, buf_s = ""; i < numbers.size(); i++){
		if(numbers[i] == ' '){
			a.push_back(std::stoi(buf_s));
			buf_v.push_back(0);
            buf_s = "";
		}
		else{
			buf_s += numbers[i];
		}
	}
	a.push_back(std::stoi(buf_s));
	merge_sort(&a, 0, a.size(), &buf_v);
	std::cout << inversions << std::endl;
	return 0;
}
