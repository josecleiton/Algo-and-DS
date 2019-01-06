#include "spell_checker.hpp"
using namespace trie;

int main(int argc, char* argv[]){
    if(argc > 1){
        if(argv[1] != string("-h")) spell_test(argv[1]);
        else spell_help();
    }
    else{
        string input;
        cout << "Use a flag -h para ver a pagina de ajuda. " << endl << endl;
        cout << "\tDigite o caminho do dicionário para iniciar o spell checker: ";
        getline(cin, input);
        if(!input.empty()) spell_test(input);
        else{
            cout << "Um caminho para o arquivo dicionario nao foi especificado" << endl;
            exit(1);
        }
    }
    return 0;
}
