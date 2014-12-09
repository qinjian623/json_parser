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
                                if (s.empty()) {
                                        return false;
                                }
                                n = s.back();
                                //n = s[0];
                                s.pop_back();
                                //s.erase(0, 1);
                                if (j_empty && is_empty_char(n)){
                                        continue;
                                }
                                cout << n << endl;
                                return true;
                        }
                }

                void back(char& b) {
                        s.push_back(b);
                        //s.insert(0, 1, b);
                }

        private:
                bool is_empty_char(char& c) {
                        if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
                                return true;
                        } else {
                                return false;
                        }
                }

                size_t cur;
                string& s;
};

int main() {
        cout << "Hello world" << endl;
        ArrayDFA adfa;
        ObjectDFA odfa;


        string s = "}";
        strstream sss(s);
        char appetizer = '{';
        Value* v = odfa.eat(sss, appetizer);
        //cout << v << endl;
        //cout << *v << endl;
        clock_t t = clock();
        cout << "Reading file" << endl;
        ifstream ifs;
        //ifs.open("/Users/qin/Downloads/MOCK_DATA(1).json");
        ifs.open("/tmp/json.json");
        filestream ssa(ifs);

        if (!ssa.next(appetizer)){}
        //strstream ssa(s);
        Value* a = odfa.eat(ssa, appetizer);
        t = clock() - t;
        printf ("It took me %ld clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);

        //cout << *a << endl;
        //cout << a->a->size() << endl;
        cout << "DONE" << endl;

        ifstream sfs;
        sfs.open("/tmp/json.json");
        s = "";
        string line;
        t = clock();
        while(std::getline(sfs, line)){
                s.append(line);
        }
        strlen(s.c_str());
        t = clock() - t;
        printf ("It took me %ld clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
}
