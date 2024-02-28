//Слава Україні, Героям слава
 
#include <bits/stdc++.h>
 
using namespace std;

class Superpoder {
    string nome;
    int categoria;
public:
    string getNome() const {
        return nome;
    }
    int getCategoria() const {
        return categoria;
    }
    Superpoder(string nome_, int categoria_) : nome(nome_), categoria(categoria_) {}
};

class Personagem {
    string nome, nomeVidaReal;
    vector<Superpoder*> superpoderes;
public:
    bool adicionaSuperpoder(Superpoder* sp) {
        if(superpoderes.size() == 4) {
            return false;
        }
        superpoderes.push_back(sp);
        return true;
    }
    double getPoderTotal() {
        double ans = 0;
        for(auto current : superpoderes) {
            ans += current->getCategoria();
        }
        return ans;
    }
    string getNome() {
        return nome;
    }
    string getNomeVidaReal() {
        return nomeVidaReal;
    }
    Personagem(string nome_, string nomeVidaReal_) : nome(nome_), nomeVidaReal(nomeVidaReal_) {
        superpoderes.reserve(4);
    }
};

class SuperHeroi : public Personagem {
public:
    SuperHeroi(string nome_, string nomeVidaReal_) : Personagem(nome_, nomeVidaReal_) {}
    double getPoderTotal() {
        double ans = Personagem::getPoderTotal();
        ans *= 1.1;
        return ans;
    }
};

class Vilao : public Personagem {
    int tempoDePrisao;
public:
    Vilao(string nome_, string nomeVidaReal_, int tempoDePrisao_) : Personagem(nome_, nomeVidaReal_), tempoDePrisao(tempoDePrisao_) {}
    double getPoderTotal() {
        double ans = Personagem::getPoderTotal();
        ans *= 1.0 + (0.01 * tempoDePrisao);
        return ans;
    }
};

class Confronto {
public:
    string enfrentar(SuperHeroi &p1, Vilao &p2) {
        double v1 = p1.getPoderTotal();
        double v2 = p2.getPoderTotal();
        return (v1 == v2 ? "empate" : ((v1 > v2) ? p1.getNome() : p2.getNome()));
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    Superpoder soltar_teia("soltar teia", 3);
    Superpoder andar_parede("andar em paredes", 2);
    Superpoder sentido_apurado("sentido apurado", 1);
    Superpoder voar("voar", 3);
    Superpoder forca("forca", 5);
    Superpoder raiox("visao de raio x", 4);
    Superpoder sopro("sopro congelante", 4);
    Superpoder supersoldado("supersoldado", 3);
    Superpoder escudo("escudo", 3);
    Superpoder velocidade("velocidade", 5);
    Superpoder anel("anel magico", 5);
    Superpoder armadura("armadura", 4);
    Superpoder elo("dispositivos eletronicos", 2);
    Superpoder mente("mente agucada", 5);
    Superpoder tentaculos("tentaculos indestrutiveis", 5);
    Superpoder vel_2("velocidade", 1);
    SuperHeroi homem_aranha("Homem-Aranha", "Peter Parker");
    homem_aranha.adicionaSuperpoder(&soltar_teia);
    homem_aranha.adicionaSuperpoder(&andar_parede);
    homem_aranha.adicionaSuperpoder(&sentido_apurado);
    SuperHeroi super_homem("Super-Homem", "Clark Kent");
    super_homem.adicionaSuperpoder(&voar);
    super_homem.adicionaSuperpoder(&forca);
    super_homem.adicionaSuperpoder(&raiox);
    super_homem.adicionaSuperpoder(&sopro);
    SuperHeroi cpt_america("Capitao America", "Steve Rogers");
    cpt_america.adicionaSuperpoder(&supersoldado);
    cpt_america.adicionaSuperpoder(&escudo);
    SuperHeroi flash("Flash", "Barry Allen");
    flash.adicionaSuperpoder(&velocidade);
    SuperHeroi lanterna_verde("Lanterna-Verde", "Hal Jordan");
    lanterna_verde.adicionaSuperpoder(&anel);
    SuperHeroi homem_ferro("Homem de Ferro", "Tony Stark");
    homem_ferro.adicionaSuperpoder(&armadura);
    homem_ferro.adicionaSuperpoder(&elo);
    Vilao duende("Duende Verde", "Norman Osbourne", 10);
    duende.adicionaSuperpoder(&forca);
    Vilao lex("Lex Luthor", "Lex Luthor", 10);
    lex.adicionaSuperpoder(&mente);
    Vilao bizarro("Bizarro", "Bizarro", 10);
    bizarro.adicionaSuperpoder(&voar);
    bizarro.adicionaSuperpoder(&forca);
    bizarro.adicionaSuperpoder(&raiox);
    bizarro.adicionaSuperpoder(&sopro);
    Vilao octupus("Octupus", "Otto Octavius", 20);
    octupus.adicionaSuperpoder(&tentaculos);
    octupus.adicionaSuperpoder(&vel_2);
    Confronto luta;
    cout << luta.enfrentar(super_homem, bizarro) << "\n";
    return 0;
}