/*
	Implementação do algoritmo de Kruskal
	Para detectar ciclos iremos utilizar o algoritmo Union-Find que detecta
	ciclos em grafos NÃO direcionados.
*/

#include <iostream>
#include <vector>
#include <algorithm> // sort
#include <string.h> // memset
#define TAMANHO 9 
using namespace std;

class Aresta
{
	int vertice1, vertice2, peso;

public:

	Aresta(int v1, int v2, int peso)
	{
		vertice1 = v1;
		vertice2 = v2;
		this->peso = peso;
	}

	int obterVertice1()
	{
		return vertice1;
	}

	int obterVertice2()
	{
		return vertice2;
	}

	int obterPeso()
	{
		return peso;
	}

	// sobrescrita do operador "<"
	bool operator < (const Aresta& aresta2) const
	{
		return (peso < aresta2.peso);
	}
};

class Grafo
{
	int V; // número de vértices
	vector<Aresta> arestas; // vetor de arestas

public:

	Grafo(int V)
	{
		this->V = V;
	}

	// função que adiciona uma aresta
	void adicionarAresta(int v1, int v2, int peso)
	{
		Aresta aresta(v1, v2, peso);
		arestas.push_back(aresta);
	}

	// função que busca o subconjunto de um elemento "i"
	int buscar(int subset[], int i)
	{
		if(subset[i] == -1)
			return i;
		return buscar(subset, subset[i]);
	}

	// função para unir dois subconjuntos em um único subconjunto
	void unir(int subset[], int v1, int v2)
	{
		int v1_set = buscar(subset, v1);
		int v2_set = buscar(subset, v2);
		subset[v1_set] = v2_set;
	}

	/// função que roda o algoritmo de Kruskal
	void kruskal()
	{
		vector<Aresta> arvore;
		int size_arestas = arestas.size();

		// ordena as arestas pelo menor peso
		sort(arestas.begin(), arestas.end());

		// aloca memória para criar "V" subconjuntos
		int * subset = new int[V];

		// inicializa todos os subconjuntos como conjuntos de um único elemento
		memset(subset, -1, sizeof(int) * V);

		for(int i = 0; i < size_arestas; i++)
		{
			int v1 = buscar(subset, arestas[i].obterVertice1());
			int v2 = buscar(subset, arestas[i].obterVertice2());

			if(v1 != v2)
			{
				// se forem diferentes é porque NÃO forma ciclo, insere no vetor
				arvore.push_back(arestas[i]);
				unir(subset, v1, v2); // faz a união
			}
		}

		int size_arvore = arvore.size();

		// mostra as arestas selecionadas com seus respectivos pesos
		for(int i = 0; i < size_arvore; i++)
		{
			int v1 = 1 + arvore[i].obterVertice1();
			int v2 = 1 + arvore[i].obterVertice2();
			cout << "(" << v1 << ", " << v2 << ") = " << arvore[i].obterPeso() << endl;
		}
	}
};

int main(int argc, char *argv[])
{
	Grafo g(TAMANHO); // grafo
	
	// adiciona as arestas
	g.adicionarAresta(0, 1, 60);
	g.adicionarAresta(0, 2, 54);
	g.adicionarAresta(0, 3, 42);
	g.adicionarAresta(1, 0, 60);
	g.adicionarAresta(1, 3, 71);
	g.adicionarAresta(1, 5, 29);
	g.adicionarAresta(2, 0, 54);
	g.adicionarAresta(2, 3, 56);
	g.adicionarAresta(2, 4, 67);
	g.adicionarAresta(3, 0, 42);
	g.adicionarAresta(3, 1, 71);
	g.adicionarAresta(3, 2, 56);
	g.adicionarAresta(3, 4, 26);
	g.adicionarAresta(3, 5, 52);
	g.adicionarAresta(3, 6, 87);
	g.adicionarAresta(4, 2, 67);
	g.adicionarAresta(4, 3, 26);
	g.adicionarAresta(4, 6, 70);
	g.adicionarAresta(4, 8, 73);
	g.adicionarAresta(5, 1, 29);
	g.adicionarAresta(5, 3, 52);
	g.adicionarAresta(5, 6, 20);
	g.adicionarAresta(5, 7, 25);
	g.adicionarAresta(6, 3, 87);
	g.adicionarAresta(6, 4, 70);
	g.adicionarAresta(6, 5, 20);
	g.adicionarAresta(6, 7, 36);
	g.adicionarAresta(6, 8, 32);
	g.adicionarAresta(7, 5, 25);
	g.adicionarAresta(7, 6, 36);
	g.adicionarAresta(7, 9, 25);
	g.adicionarAresta(8, 4, 73);
	g.adicionarAresta(8, 6, 59);
	g.adicionarAresta(8, 9, 26);
	g.adicionarAresta(9, 6, 32);
	g.adicionarAresta(9, 7, 25);
	g.adicionarAresta(9, 8, 26);
	
	g.kruskal(); // roda o algoritmo de Kruskal
	
	return 0;
}
