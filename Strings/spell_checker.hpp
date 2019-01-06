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
#include <algorithm>
#include <string>
#include <cstring>
#include <cctype>
#include <ctime>
#include <ncurses.h>
#include "trie.hpp"
using namespace trie_implementation;

class SpellChecker: private Trie{

enum {MAX_SUGGEST=2};
enum {MISMATCH_STRICT=10, MATCH_STRICT};

bool userInput{};
fstream dict;
unsigned level;
string dictFilename;

public:
    SpellChecker(){}

    SpellChecker(string _dfn): dictFilename(_dfn){
        dict.open(dictFilename, fstream::in|fstream::app);
        char* handle = new char[128];
        if(!handle){
            cerr << strerror(errno) << endl;
            abort();
        }
        if(dict.is_open()){
            while(dict.good()){
                dict.getline(handle, 1024);
                if(isalpha(*handle) and !isupper(*handle))
                    push(handle);
            }
            level = height();
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
        if(userInput) reorganizeDict();
        else dict.close();
    }

    enum input_flags {BACKSPACE = 0x7F, CHAR_LIMIT};
    void run(){
        
        initscr();
        noecho();

        WINDOW* title = newwin(3, 45, 1, 12);
        refresh();

        mvwprintw(title, 1, 10, "STRICT SPELL CHECKER\n\n");
        wrefresh(title);


        WINDOW* content = newwin(7, 80, 3, 8);
        refresh();

        WINDOW* bottom = newwin(4, 55, 12, 10);
        refresh();

        wprintw(bottom, "By: Jose Cleiton (http://github.com/josecleiton).");
        wrefresh(bottom);

        vector<string> suggestions(MAX_SUGGEST);
        char* input = new char[1024]();
        int cursor = 0;
        int op, sk = MATCH;
        char cache;
        bool first = true;

        while(true){
            wclear(content);
            if(first){
                wattron(content, A_BOLD);
                mvwprintw(content, 2, 2,"Digite alguma letra para comecar a analise");
                wattroff(content, A_BOLD);
                wrefresh(content);
                wclear(content);
                first = false;
            }
            op = getch();
            if(op == '\n') break;
            cache = static_cast<char>(op);
            if(op == BACKSPACE and cursor) input[--cursor] = '\0';
            else if(isalpha(op)) input[cursor++] = static_cast<char>(op);
            if(strlen(input)){
                mvwprintw(content, 0, 0,"\n%s\n", input);
                mvwprintw(content, 3, 0, "Sugestao:\t");
                if(cursor < level){
                    seek(suggestions, input);
                    for(auto it: suggestions)
                        wprintw(content, "%s\t", it.c_str());
                }
                for(auto& it: suggestions) it = "";
            }
            else wclear(content);
            wrefresh(content);
        }
        if(!find(input, true)){
            input[--cursor] = cache;
            wclear(content);
            wrefresh(content);
            wattron(content, A_STANDOUT);
            mvwprintw(content, 1, 5, "Deseja adicionar: ");
            wattron(content, A_BOLD);
            wprintw(content, "%s", input);
            wattroff(content, A_BOLD);
            wprintw(content, " ao dicionario? (S ou N)  ");
            wrefresh(content);
            op = getch();
            wattroff(content, A_STANDOUT);
            if(op == '\n' or op == 's' or op == 'y'){
                push(input);
                addToDict(input);
            }
        }
        
        wclear(title);
        wrefresh(title);

        wclear(content);
        wattron(content, A_BOLD);
        mvwprintw(content, 2, 2, "Analise finalizada. Aperte qualquer tecla para sair...");
        wrefresh(content);
        
        getch();

        // FREE MEMORY
        delete[] input;
        delwin(title);
        delwin(content);
        delwin(bottom);
        endwin();
    }

private:
    int seek(vector<string>& result, char* input){
        unsigned i = 0, tam=0;
        char cache = '\0';
        Node* handle = nullptr;
        int classf = search(root, input, handle, tam, cache);
        string temp(input);
        if(classf == MATCH or classf == MATCH_AND_COUNT or classf == MATCH_STRICT){
            classf = extractNextStr(handle, temp);
            result[i++] = temp;
            if(classf != COMPLETE_MATCH){
                temp.clear();
                temp = string(input);
                if(extractNextStr(handle, temp, true, result[i-1][temp.size()]) and temp != result[i-1])
                    result[i] = temp;
            }
            return MATCH;
        }
        else if(heightAux(handle) >= strlen(input) - MAX_SUGGEST){ // MISMATCH
            vector<string> container(MAX_IN_EXTRACT_FUNCTION);
            unsigned cursor = 0, count = 0;
            string aux;
            extractAll(handle, aux, container, cursor);
            //if(cache) temp[tam] = cache;

            vector<int> index(MAX_SUGGEST);
            srand(time(NULL));
            for(unsigned i=0; i<MAX_SUGGEST; i++)
                index[i] = rand()%cursor;
            // PEGA APENAS OS ITENS UNICOS
            index.resize(distance(index.begin(), unique(index.begin(), index.end())));
            cursor = 0;
            if(cache and classf == MISMATCH) temp[tam-1] = cache;
            for(auto item: index)
                result[cursor++] = string(temp, 0, tam) + container[item];
        }
        return MISMATCH;
    }

    int search(Node* node, char* input, Node*& result, unsigned& tam, char& flag){
        if(node){
            if(*input != '\0'){
                Key needle(*input);
                auto itFound = node->keys.lower_bound(needle);
                if(itFound->data == *input){
                    int classf = search(itFound->ptr, input+1, result, tam, flag);
                    if((classf == MATCH_AND_COUNT) and itFound->endOfString and !result){
                        Key newKey(*itFound, 1);
                        node->swap(itFound, newKey);
                        result = node;
                        tam++;
                        return MATCH_STRICT;
                    }
                    else if(!result){
                        result = node;
                        classf = MISMATCH_STRICT;
                    }
                    tam += (classf == MISMATCH or classf == MISMATCH_STRICT or classf == MATCH_STRICT);
                    return classf;
                }
                else{
                    itFound--;
                    flag = itFound->data;
                    if(itFound->ptr){
                        result = itFound->ptr;
                        tam++;
                        return MISMATCH;
                    }
                    else{
                        result = node;
                        return MISMATCH_STRICT;
                    }
                }
            }
            result = node;
            return MATCH_AND_COUNT;
        }
        else if(*input) return MISMATCH;
        return MATCH_AND_COUNT;
    }

    void addToDict(char* _in){
        string input(_in);
        dict.clear();
        dict.flush();
        dict << input << endl;
        userInput = true;
    }

    void reorganizeDict(void){
        vector<string> toSort(stringCount);
        int i=0;
        dict.seekg(fstream::beg);
        while(dict.good())
            dict >> toSort[i++];
        sort(toSort.begin(), toSort.end());
        dict.close();

        dict.open(dictFilename+"copy", fstream::out);
        if(dict.is_open()){
            for(auto str: toSort)
                dict << str << endl;
            dict.close();
            remove(dictFilename.c_str());
            rename(string(dictFilename+"copy").c_str(), dictFilename.c_str());
        }
        else{
            cerr << dictFilename+"copy " << strerror(errno) << endl;
            abort();
        }
    }

};

#endif //_SPELL_CHECKER_HPP
