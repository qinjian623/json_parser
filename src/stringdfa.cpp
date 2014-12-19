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
        /*if (appetizer != '\"') {
                foods.back(appetizer);
                return NULL;
        }*/

        foods.dont_jump_empty();
        char food;
        bool in_control_char = false;
        while (foods.next(food)) {
                if (!in_control_char){
                        if (food == '\\'){
                                in_control_char = true;
                                continue;
                        }else if (food == '\"') {
                                // The success exit.
                                foods.jump_empty();
                                return shit();
                        }
                }
                if (in_control_char) {
                        in_control_char = false;
                        if (!insert_control_char(food)) {
                                break;
                        }
                } else {
                        poo.push_back(food);
                }
        }
        foods.jump_empty();

        // The error / can't handle / foods empty exit.
        return NULL;
}

Value* StringDFA::shit() {
        Value* ret = new Value(new string(poo));
        wipe_ass();
        return ret;
}

void StringDFA::wipe_ass() {
        poo.clear();
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
        poo.push_back(ch);
        /*map<char, char>::iterator it = control_chars.find(c);
        if (it == control_chars.end()) {
                return false;
        } else {
                poo.push_back(it->second);
                return true;
        }*/
}
