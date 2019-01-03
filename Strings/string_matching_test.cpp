#include "string_matching.hpp"
using namespace string_matching;
void kmp_test(void){
    KMP kmp;
    string text = "kababcabcdajabcdabdef";
    string pattern = "ab";
    //int substring_index = a.firstMatch(text , "abcdab");
    auto matches =  kmp.allMatches(text, pattern);
    cout << "KMP TEST" << endl;
    cout << matches.size() << " matches of \"" << pattern << "\" in text \"" << text << "\":" << endl;
    for(auto index: matches) cout << index << " ";
    cout << endl;
}

void bm_test(void){
    BoyerMoore bm;
    string text = "kababcabcdajabcdabdef";
    string pattern = "ab";
    auto matches = bm.match(text, pattern);
    cout << "BOYER-MOORE TEST" << endl;
    cout << matches.size() << " matches of \"" << pattern << "\" in text \"" << text << "\":" << endl;
    for(auto index: matches) cout << index << " ";
    cout << endl;
}

int main(){
    kmp_test();
    cout << endl;
    bm_test();
    return 0;
}