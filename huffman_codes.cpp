#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>


typedef std::pair<std::string, int> qunit_t;

class OrderQueue{
public:
    bool operator() (qunit_t& u1, qunit_t& u2){
        return u1.second > u2.second; 
    }
};

typedef std::priority_queue<qunit_t, std::vector<qunit_t>, OrderQueue> q_t;

void huffman_encode(std::string msg){
	std::map <std::string, int> freqs_map;
	std::map <std::string, int> :: iterator it_f;
	std::map <char, std::string> codes_map;
	std::map <char, std::string> :: iterator it_c;
	int i;
	
	for(i = 0; i < msg.size(); i++){
		std::string key = {msg[i]};
		if(freqs_map.find(key) == freqs_map.end()){
			freqs_map[key] = 1;
			codes_map[key[0]] = std::string();
		}
		else freqs_map[key]++;
	}
	
	q_t codes_q;
	for(it_f = freqs_map.begin(); it_f != freqs_map.end(); it_f++){
	    qunit_t qunit(it_f->first, it_f->second);
	    codes_q.push(qunit);
	}
	
	if(codes_q.size() == 1) codes_map[codes_map.begin()->first] = "0";
	while(codes_q.size() > 1){
	    qunit_t uold, unew;
	    unew.first = "";
	    unew.second = 0;
	    for(int times = 0; times < 2; times++){
    	    uold = codes_q.top();
    	    codes_q.pop();
    	    for(i = 0; i < uold.first.size(); i++){
    	        char sym = uold.first[i];
    	        codes_map[sym] = (times? '1':'0') + codes_map[sym];
    	    }
    	    unew.first += uold.first;
    	    unew.second += uold.second;
	    }
	    codes_q.push(unew);
	}
	
	std::string coded_msg = "";
	for(i = 0; i < msg.size(); i++){
	    coded_msg += codes_map[msg[i]];
	}
	
	std::cout << codes_map.size() << ' ' << coded_msg.size() << std::endl;
	for(it_c = codes_map.begin(); it_c != codes_map.end(); it_c++){
	    std::cout << it_c->first << ": " << it_c->second << std::endl;
	}
	std::cout << coded_msg;
}

int main(int argc, char** argv) {
	std::string msg;
	getline(std::cin, msg);
	huffman_encode(msg);
	return 0;
}
