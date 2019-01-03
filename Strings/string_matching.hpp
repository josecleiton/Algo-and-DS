#ifndef _STRING_MATCHING_HPP
#define _STRING_MATCHING_HPP

#include <iostream>
#include <string>
#include <vector>
#define ALPHABET_LEN 256
using namespace std;

namespace string_matching{

// KNUTH-MORRIS-PRATT ALGORITHM
class KMP{

typedef vector<int> __table;

private:
    __table createTable(string pattern){ // partial match table (failure function)
        const int patternLen = pattern.size();
        __table matchTable(patternLen);
        for(int i=0, j=i+1; j < patternLen; j++){
            if(pattern[i] == pattern[j])
                matchTable[j] = ++i;
            else i=0;
        }
        return matchTable;
    }

public:
    KMP(){}

    KMP(string _t, string _p, vector<int>& result){
        result = allMatches(_t, _p);
    }

    int firstMatch(string text, string pattern, __table matchTable = __table() ){
        //__table table = ; // RETORNA A "FAILURE TABLE"
        const int patternLen = pattern.size(), textLen = text.size();
        if(patternLen > textLen) return -1;
        if(matchTable.empty()) matchTable = createTable(pattern);
        int i=0, j=0;
        while(j < patternLen and i < textLen){
            if(text[i] == pattern[j]){
              i++; j++; // ambos os cursores avançam
            }
            else{
                if(j) j = matchTable[j-1];
                else i++;
            }
        }
        return (j == patternLen) ? i-patternLen : -1;
    }
    
    // A FUNÇÃO ABAIXO RETORNA OS INDICES DE TODAS AS OCORRENCIAS DAS SUBSTRINGS
    vector<int> allMatches(string text, string pattern){
        vector<int> result;
        __table matchTable = createTable(pattern);
        int index = 0, j = 0; // iterator no vetor result
        const int textLen = text.size(), patternLen = pattern.size();
        int nextSubString = 0; // cursor para a proxima substring
        while(nextSubString < textLen){
            index = firstMatch(string(text, nextSubString), pattern, matchTable);
            if(index != -1) index += nextSubString; 
            else break; // SE NÃO ENCONTROU PARE A ITERAÇÃO
            result.push_back(index);
            nextSubString = patternLen + index;
        }
        return result;
    }

};

//BOYER-MOORE ALGORITHM
class BoyerMoore{
    
    struct __table{
        vector<int> bcs; // BAD CHAR SHIFT
        vector<int> gcs; // GOOD CHAR SHIFT
        __table(vector<int> _d1, vector<int> _d2): bcs(_d1), gcs(_d2){}
    };

    int patternLen, textLen;

    __table createTable(string& pattern){ // function delta
        return __table(badChar(pattern), goodChar(pattern));
    }

    vector<int> badChar(string &pattern){
        vector<int> bcs(ALPHABET_LEN, patternLen);
        int i=0;
        for(auto ch: pattern)
            bcs[ch] = patternLen- i++ -1;
        return bcs;
    }

    vector<int> goodChar(string& pattern){
        vector<int> suff(patternLen), goodSuff(patternLen, patternLen);
        suffixes(suff, pattern);
        int j=0;
        for(int i=patternLen-1; i >= 0; i--)
            if(suff[i] == i+1)
                for(; j < patternLen-1-i; j++)
                    if(goodSuff[j] == patternLen)
                        goodSuff[j] = patternLen-1-i;
        for(int i=0; i <= patternLen-2; i++)
            goodSuff[patternLen-1-suff[i]] = patternLen-1-i;
        return goodSuff;
    }

    void suffixes(vector<int>& suff, string& pattern){
        suff[patternLen-1] = patternLen;
        int f=0, g = patternLen-1;
        for(int i=patternLen-2; i >= 0; i--){
            if(i > g and suff[i+patternLen-1-f] < i-g)
                suff[i] = suff[i+patternLen-1-f];
            else{
                if(i < g)
                    g = i;
                f = i;
                while(g >= 0 and pattern[g] == pattern[g+patternLen-1-f])
                    --g;
                suff[i] = f-g;
            }
        }
    }

public:
    BoyerMoore(){}

    BoyerMoore(string text, string pattern){
        match(text, pattern);
    }

    vector<int> match(string text, string pattern){
        vector<int> result;
        textLen = text.size();
        patternLen = pattern.size();
        if(patternLen > textLen) return result;
        __table table = createTable(pattern);
        int j=0, i;
        while(j <= textLen-patternLen){
            for(i=patternLen-1; i >= 0 and pattern[i] == text[i+j]; i--);
            if(i < 0){
                result.push_back(j);
                j += table.gcs[0];
            }
            else
                j += max(table.gcs[i], table.bcs[text[i+j]-patternLen+1+i]);
        }
        return result;
    }
};

} // namespace string_matching

#endif //_STRING_MATCHING_HPP