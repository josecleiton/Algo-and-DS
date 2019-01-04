/*
    SIMPLE SPELL CHECKER EM C++ FEITO POR JOSÉ CLEITON
    USANDO MULTIWAY TRIES EM MEMÓRIA
    BIBLIOTECA EXTERNA UTILIZADA: NCURSES (compile usando -lcurses)
    ACEITO MELHORIAS (MIT LICENSE)
    CONTATO: jcleitonbc@gmail.com
*/
#ifndef _SPELL_CHECKER_HPP
#define _SPELL_CHECKER_HPP
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <cctype>
#include <ncurses.h>
#include "trie.hpp"
using namespace trie_implementation;

class SpellChecker: private Trie{

enum {MAX_SUGGEST=2};
enum {MISMATCH_STRICT=10, MATCH_STRICT};

bool userInput{};
fstream dict;

public:
    SpellChecker(){}

    SpellChecker(string _dict_filename){
        dict.open(_dict_filename, fstream::in|fstream::app);
        char* handle = new char[1024];
        if(!handle){
            cerr << strerror(errno) << endl;
            abort();
        }
        if(dict.is_open()){
            while(dict.good()){
                dict.getline(handle, 1024);
                if(isalpha(*handle) and !isupper(*handle))
                    push(handle);
                else if(*handle == '#')
                    userInput = true;
            }
            //cout << this->nodeCount << endl;
            //Trie::print();
            delete[] handle;
        }
        else{
            cerr << strerror(errno) << endl;
            delete[] handle;
            abort();
        }
    }

    ~SpellChecker(){
        dict.close();
    }

    enum input_flags {BACKSPACE = 127, CHAR_LIMIT};
    void run(){

        initscr();
        noecho();

        WINDOW* title = newwin(3, 45, 1, 12);
        refresh();

        mvwprintw(title, 1, 10, "STRICT SPELL CHECKER\n\n");
        wrefresh(title);


        WINDOW* content = newwin(7, 55, 3, 8);
        refresh();

        WINDOW* bottom = newwin(4, 55, 12, 5);
        refresh();

        wprintw(bottom, "By: Jose Cleiton (http://github.com/josecleiton).");
        wrefresh(bottom);

        vector<string> suggests(MAX_SUGGEST);
        char* input = new char[1024]();
        int cursor = 0;
        int op, cache;
        
        while(true){
            op = getch();
            if(op == '\n') break;
            cache = op;
            if(op < CHAR_LIMIT and isalnum(op)){
                if(op == BACKSPACE){
                    input[--cursor] = '\0';
                    mvwprintw(content, 0, 5, "\n%s\n", input);
                    for(auto& it: suggests) it = "";
                }
                else{
                    input[cursor++] = static_cast<char>(op);
                    if(cursor){
                        mvwprintw(content, 0, 5,"\n%s\n", input);
                        mvwprintw(content, 1, 13, "Suggest:\t");
                        seek(suggests, input);
                        for(auto it: suggests)
                            wprintw(content, "%s\t", it.c_str());
                        wrefresh(content);
                    }
                }
            }
        }
        if(!find(input, true)){
            input[--cursor] = cache;
            wclear(content);
            wrefresh(content);
            wattron(content, A_STANDOUT);
            mvwprintw(content, 1, 5, "Deseja adicionar: %s ao dicionario? (S ou N)  ", input);
            wrefresh(content);
            op = getch();
            wattroff(content, A_STANDOUT);
            if(op == 'S' or op == 's' or op == 'Y' or op == 'y' or op == '\n'){
                push(input);
                addToDict(input);
            }
        }

        // FREE MEMORY
        delete[] input;
        delwin(title);
        delwin(content);
        delwin(bottom);
        endwin();
    }
    
    int seek(vector<string>& result, char* input){
        unsigned i = 0;
        Node* handle = nullptr;
        int classf = search(root, input, handle);
        string temp(input);
        if(classf == MATCH or classf == MATCH_AND_COUNT or classf == MATCH_STRICT){
            extractNextStr(handle, temp, false);
            result[i++] = temp;
            temp.clear();
            temp = string(input);
            temp.pop_back();
            if(!temp.empty()){
                extractNextStr(handle, temp, true);
                result[i] = (temp != result[i-1]) ? temp: "";
            }
            return MATCH;
        }
        else{ // MISMATCH
            vector<string> container(MAX_IN_EXTRACT_FUNCTION);
            unsigned cursor = 0, count =0;
            temp.clear();
            extractAll(handle, temp, container, cursor);
            for(auto& strs: container)
                if(!strs.empty() and i < MAX_SUGGEST)
                    strs = input + strs;
                else break;
            for(auto& strs: container)
                if(!strs.empty() and i < MAX_SUGGEST)
                    result[i++] = strs;
                else break;
        }
        return MISMATCH;
    }

private:
    int search(Node* node, char* input, Node*& result){
        if(node){
            if(*input != '\0'){
                Key needle(*input);
                auto itFound = node->keys.find(needle);
                if(itFound != node->keys.end()){
                    int classf = search(itFound->ptr, input+1, result);
                    if(classf == MATCH_AND_COUNT and itFound->endOfString){
                        Key newKey(*itFound, 1);
                        node->swap(itFound, newKey);
                        result = node;
                        return MATCH_STRICT;
                    }
                    else if(!result){
                        result = node;
                        classf = MISMATCH;
                    }
                    return classf;
                }
                else{
                    itFound--;
                    result = itFound->ptr;
                    *input = itFound->data;
                    return MISMATCH;
                }
            }
            result = node;
            return MISMATCH_STRICT;
        }
        else if(*input) return MISMATCH;
        return MATCH_AND_COUNT;
    }

    void addToDict(char* _in){
        string input(_in);
        dict.clear();
        dict.flush();
        if(!userInput) dict << endl << "# USER INPUT BELOW" << endl;
        dict << input << endl;
    }

};

#endif //_SPELL_CHECKER_HPP
