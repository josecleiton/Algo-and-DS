#include "spell_checker.hpp"
using namespace trie;

void trie_test(void){
    Trie trie;
    const int LIMIT_TEST = 5;
    char strs[80][80] = {"A", "ABC", "ABA", "ABB", "ABCD"};
    for(int i=0; i<LIMIT_TEST; i++)
        trie.push(strs[i]);
    cout << trie.find(strs[1]) << endl;
    trie.erase(strs[4]);
    trie.print();
    cout << "ALTURA: " << trie.height() << endl;
    cout << "Numero de Strings: " << trie.count() << endl;
    cout << "Numero de nos: " << trie.size() << endl;
}

void spell_test(string filename){
    SpellChecker sc(filename);
}

int main(int argc, char* argv[]){
    if(argc > 1) spell_test(argv[1]);
    else{
        string input;
        cout << "Digite o caminho do dicionário para iniciar o spell checker (para testar a trie, deixe vazio): ";
        getline(cin, input);
        if(!input.empty()) spell_test(input);
        else trie_test();
    }
    return 0;
}
