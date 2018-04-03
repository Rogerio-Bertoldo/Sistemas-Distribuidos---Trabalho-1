/*
	Autor: Rogerio Henrique Bertoldo da Silva
	[uso]: g++ --std=c++11 Pipes.cpp -o Pipes
*/
#include<unistd.h>
#include<signal.h>
#include<iostream>
#include<sstream>
#include<time.h>
using namespace std;

#define TAMANHO_STRING 20

//converte uma string para char*
char* stringToCharArray(string param)
{
	char* res = new char[param.length()];
	for(int i = 0; i < param.length(); i++)
	{
		*(res + i) = param[i];
	}

	return res;
}


//Retorna true se o parametro num for primo. Caso contrario, retorna false
bool ePrimo(int num)
{
	if(num == 0 || num == 1) return false;
	if(num == 2 || num == 3) return true;
	for(int i = 2; i < num/2 ; i++)
	{
		if( (num % i) == 0) return false;
	}

	return true;
}

int main(int argc, char* argv[])
{
	int num = 1;                 //armazena os numeros aleatorios
	char numero[TAMANHO_STRING]; //armazena o numero enviado entre os processos
	int desc[2];                 //descritor de leitura/escrita
	int pid;                     //armazena os ids dos processos 
	int totalNumeros;            //quantidade de numeros aleatorios gerados
	stringstream(argv[1]) >> totalNumeros;

	//Cria o pipe
	if(pipe(desc) < 0)
	{
		cerr<<"Nao foi possivel criar o pipe\n";
		return -1;
	}

	//Chama a funcao fork() para criar o processo filho
	pid = fork();


	if( pid == -1)
	{
		cerr<<"Nao foi possivel criar processo filho\n";
		return -1;
	}


	if(pid)
	{
		//Fecha o descritor de leitura
		close(desc[0]);

		for(int i = 0; i < totalNumeros + 1; i++)
		{
			srand(time(NULL));

			//gera os numeros aleatorios
			//ultimo numero enviado deve ser 0
			if(i != totalNumeros) num += rand() % 100 + 1;
			else num = 0;


			char* valor = stringToCharArray(to_string(num));


			//escreve valor no pipe
			write(desc[1], valor, TAMANHO_STRING);

			//encerra o processo
			if(num == 0) kill(pid,SIGTERM);
		}

							
				
	}
	else
	{
		//fecha descritor de escrita
		close(desc[1]);
		int valor;


		for(int i = 0; i < totalNumeros + 1; i++)
		{
			//cout<<"lendo\n";
			//le valor recebido
			read(desc[0],numero,TAMANHO_STRING);
			cout<<numero<<"		";

			//converte para int
			stringstream(numero) >> valor;

			if(ePrimo(valor)) cout<<"true\n";
			else cout<<"false\n";

			//encerra o processo
			if(valor == 0) kill(pid,SIGTERM);


		}
		

	}

}

