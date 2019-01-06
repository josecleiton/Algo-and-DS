#include "spell_checker.hpp"

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

void spell_test(void){
    SpellChecker sc("./sc-dict.txt");
    sc.run();
}

int main(){
    //trie_test();
    spell_test();
    return 0;
}
