#include <bits/stdc++.h>
#define FOR(i,a) for(int i=0; i<a; i++)
#define FORIT(it, container) for(auto it = container.begin(); it != container.end(); it++)
#define pb push_back
#define MAP(t1, t2, ord) map<t1, t2, ord<t1>> 
#define UMAP(t1, t2) unordered_map<t1, t2>
#define matrix(name, type, n, m) vector<vector<type>> name (n, vector<type> (m))
using namespace std;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<string> vstr;
typedef vector<bool> vbit;
typedef pair<ll, ll> pii;

struct carta {
	int val{};
	char naipe{};
	constexpr bool match(const carta& ot){
		return (this->val == ot.val) or (this->naipe == ot.naipe);
	}
};

struct player {
	map<int, map<char, char, greater<char>>, greater<int>> mao;
	int id;
	//metodos
	carta busca_carta(const carta& c){
		map<char, char, greater<char>>::iterator search_naipe;
		// auto rem = this->mao.end();
		carta resultado;

		FORIT(it, this->mao){
			if(it->first == c.val){
				resultado.val = it->first;
				resultado.naipe = it->second.begin()->first;
				it->second.erase(it->second.begin());
				if(it->second.empty()){
//					rem = it;
					mao.erase(it);
				}
				break;

			}
			else if((search_naipe = it->second.lower_bound(c.naipe)) != it->second.end()){
				resultado.val = it->first;
				resultado.naipe = search_naipe->first;
				it->second.erase(search_naipe);
				if(it->second.empty()){
					//rem = it;
					mao.erase(it);
				}
				break;
			}
		}
		return resultado;
	}
};

void punicao(const int v, int& saque, bool& vez, bool& sentido){
	switch(v){
		case 1:
			saque=1;
			vez=false;
			break;
		case 7:
			saque=2;
			vez=false;
			break;
		case 11:
			saque=vez=false;
			break;
		case 12:
			sentido = !sentido;
			break;
	}
}

int main() {
	int p, m, n;
	carta descarte, tmp_c;
	while(cin>>p>>m>>n and p+m+n){
		list<player> jogo;
		list<player>::iterator atual;
		queue<carta> cava;
		FOR(i, p){
			player tmp_p;
			tmp_p.id = i+1;
			 FOR(j, m){
			 	cin>>tmp_c.val>>tmp_c.naipe;
			 	tmp_p.mao[tmp_c.val][tmp_c.naipe];
			 	n--;
			 }
			 jogo.pb(tmp_p);
		}
		cin>>descarte.val>>descarte.naipe;
		n--;
		while(n){
			cin>>tmp_c.val>>tmp_c.naipe;
			cava.push(tmp_c);
			n--;
		}

		/* COMEÇO DO JOGO (PIRDI HUR DUR) */
		bool cw = true; // 1 horario | 0 antihorario
		bool vez = true; // se joga ou não
		int saque = 1; // cartas que serão cavadas

		punicao(descarte.val, saque, vez, cw);
		atual = jogo.begin();
		while(true){
			if(vez){
				tmp_c = atual->busca_carta(descarte);
				if(tmp_c.val){
					if(!atual->mao.empty()){
						descarte = tmp_c;
						punicao(descarte.val, saque, vez, cw);
						goto JOGADO;
					}
					else{
						cout<<atual->id<<endl;
						break;
					}
				}
			}

			if(vez+saque){
				if(vez){
					tmp_c = cava.front();
					cava.pop();
					if(!tmp_c.match(descarte)){
						atual->mao[tmp_c.val][tmp_c.naipe];
					}
					else{
						descarte = tmp_c;
						punicao(descarte.val, saque, vez, cw);
					}
				}
				else{
					FOR(i, saque){
						tmp_c = cava.front();
						cava.pop();
						atual->mao[tmp_c.val][tmp_c.naipe];
					}
					saque = vez = 1;
				}
			}
			else
				saque = vez = 1;

		JOGADO:
			if(cw){
				atual++;
				if(atual == jogo.end()) atual++;
			}
			else {
				atual--;
				if(atual == jogo.end()) atual--;
			}
		}
	}
	return 0;
}
