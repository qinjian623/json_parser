/*
 * config_parser.cpp
 *
 *  Created on: 2014,11,25
 *      Author: qin
 *
 */

#include <vector>
#include <map>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstring>
#include "dfa.hpp"
#include "value.hpp"
#include "valuedfa.hpp"
#include "stringdfa.hpp"
#include "number_dfa.hpp"
#include "objectdfa.hpp"
#include "arraydfa.hpp"

using namespace std;

class ArrayDFA;
class ValueDFA;

class Parser {
        public:
                Value& parse(istream& file);
        private:
};

class filestream: public stream<char>{
public:
        filestream(ifstream& ifs): f(ifs){
                s.clear();
                std::getline(f, s);
                std::reverse(s.begin(), s.end());
        }
        
        bool next(char& n){
                while (true) {
                        if (s.empty()) {
                                if(!std::getline(f, s)){
                                        return false;
                                }
                                std::reverse(s.begin(), s.end());
                        }
                        n = s.back();
                        s.pop_back();
                        if (j_empty && is_empty_char(n)){
                                continue;
                        }
                        //cout << n;
                        return true;
                }
        }
        void back(char& b) {
                s.push_back(b);
        }
private:
        bool is_empty_char(char& c) {
                if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
                        return true;
                } else {
                        return false;
                }
        }
        
        ifstream& f;
        string s;
};

class strstream: public stream<char> {
public:
        strstream(string& in):s(in) {
                std::reverse(in.begin(), in.end());
                cur = in.size();
                j_empty = true;
        }

        bool next(char& n) {
                while (true) {
                        cur--;
                        if (cur <=0){
                                return false;
                        }
                        n = s[cur];
                        if (j_empty && is_empty_char(n)){
                                continue;
                        }
                        return true;
                        /*if (s.empty()) {
                                return false;
                        }
                        n = s.back();
                        s.pop_back();
                        if (j_empty && is_empty_char(n)){
                                continue;
                        }
                        return true;*/
                }
        }

        void back(char& b) {
                cur++;
                //s.push_back(b);
        }

private:
        inline bool is_empty_char(char& c) {
                return c == ' ' || c == '\t' || c == '\n' || c == '\r';
        }

        size_t cur;
        string& s;
};


void load_file(string& file, string& s){
        ifstream sfs;
        sfs.open(file);
        s = "";
        string line;
        while(std::getline(sfs, line)){
                s += line;
        }
}


int main() {
        string test_json_file = "/home/qin/Downloads/MOCK_DATA.json";
        string s;
        cout << "Reading file" << endl;
        load_file(test_json_file, s);

        strstream ssa(s);
        ArrayDFA adfa;

        char appetizer;
        ssa.next(appetizer);

        clock_t t = clock();
        Value* a = adfa.eat(ssa, appetizer);
        t = clock() - t;
        printf ("It took me %ld clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
        cout << "DONE" << endl;

        s = "";
        load_file(test_json_file, s);
        t = clock();
        size_t l = strlen(s.c_str());
        t = clock() - t;
        printf ("It took me %ld clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
        cout << l << endl;

}
