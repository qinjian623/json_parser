/*
 * booldfa.cpp
 *
 *  Created on: 2014,12,8,
 *      Author: qin
 */

#include "booldfa.hpp"
#include <algorithm>
#include <string>

Value* BoolDFA::eat(stream<char>& foods, char& appetizer){
        if (appetizer == 't' || appetizer == 'T'){
                t_or_f = true;
                if (n_bites(foods, 3)){
                        return shit();
                }
        }else if (appetizer == 'f' || appetizer == 'F'){
                t_or_f = false;
                if (n_bites(foods, 4)){
                        return shit();
                }
        }
        return NULL;
}

bool BoolDFA::n_bites(stream<char>& foods, int n){
        char food;
        for (int var = 0; var < n; ++var) {
                if (foods.next(food)){
                        buffer.push_back(food);
                }else{
                        return false;
                }
        }
        return true;
}

Value* BoolDFA::shit(){
        std::transform(buffer.begin(), buffer.end(), buffer.begin(), ::tolower);
        Value* ret = NULL;
        if (t_or_f == true && buffer == "rue"){
                ret = new Value(true);
        }
        if (t_or_f == false && buffer == "alse"){
                ret = new Value(false);
        }
        wipe_ass();
        return ret;
}

void BoolDFA::wipe_ass(){
        buffer.clear();
}


