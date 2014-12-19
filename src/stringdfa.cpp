/*
 * stringdfa.cpp
 *
 *  Created on: 2014年12月5日
 *      Author: qin
 */

#include "stringdfa.hpp"
#include <sstream>
map<char, char> StringDFA::init_map(){
        map<char,char> control_chars;
        control_chars['\"'] = '\"';
        control_chars['\\'] = '\\';
        control_chars['/'] = '/';
        control_chars['b'] = '\b';
        control_chars['f'] = '\f';
        control_chars['n'] = '\n';
        control_chars['r'] = '\r';
        control_chars['t'] = '\t';
        // TODO hex number is not supported yet.
        //control_chars['u'] = '\f';
        return control_chars;
}

map<char, char> StringDFA::control_chars(StringDFA::init_map());

StringDFA::StringDFA() {
}

Value* StringDFA::eat(stream<char>& foods, char& appetizer) {
        foods.dont_jump_empty();
        char food;
        poo = new string();
        while (foods.next(food)) {
                if (food == '\\'){
                        if (foods.next(food)&&
                            insert_control_char(food)){
                        }else{
                                break;
                        }
                }else if (food == '\"'){
                        foods.jump_empty();
                        return shit();
                }else{
                        poo->push_back(food);
                }
        }
        foods.jump_empty();
        // The error / can't handle / foods empty exit.
        delete poo;
        return NULL;
}

inline Value* StringDFA::shit() {
        Value* ret = new Value(poo);
        //poo = NULL;
        return ret;
}


void StringDFA::wipe_ass(){
}

inline bool StringDFA::insert_control_char(const char& c) {
        char ch;
        switch (c) {
        case '\"':
                ch = c;
                break;
        case '\\':
                ch = c;
                break;
        case '/':
                ch = c;
                break;
        case 'b':
                ch = '\b';
                break;
        case 'f':
                ch = '\f';
                break;
        case 'n':
                ch = '\n';
                break;
        case 'r':
                ch = '\r';
                break;
        case 't':
                ch = '\t';
                break;
        default:
                return false;
        }
        poo->push_back(ch);
        return true;
        /*map<char, char>::iterator it = control_chars.find(c);
        if (it == control_chars.end()) {
                return false;
        } else {
                poo.push_back(it->second);
                return true;
        }*/
}
