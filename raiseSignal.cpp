/*
	Autor: Rogerio Henrique Bertoldo da Silva
	[uso]: g++ --std=c++11 raiseSignal.cpp -o raiseSignal
*/

#include<iostream>
#include<string>
#include<sstream>
#include<signal.h>
#include<unistd.h>

using namespace std;
const string sinais[] = {"SIGINT", "SIGABRT", "SIGTERM"};

//Envia o sinal sig para o processo cujo ID e dado por pid
int sendSignal(int pid, string sig)
{
	if(sig == "SIGINT")
		kill(pid, SIGINT);

	else if(sig == "SIGABRT")
		kill(pid, SIGABRT);
	
	else if(sig == "SIGTERM")
		kill(pid, SIGTERM);
}

int main(int numParam, char* sinal[])
{
	//Primeiro parametro: pid
	int pid_destino;
	stringstream(sinal[1]) >> pid_destino;

	//Segundo parametro: sinal a ser enviado
	string sig = sinal[2];

	//Verifica se o usuario esta enviando um sinal diferente dos sinais considerados
	for(int i = 0; i < 3; i++)
	{
		if(sig == sinais[i]) break;
		if(i==2)
		{
			if(sig != sinais[i])
			{
				cout<<"Sinal invalido\n";
				return -1;	
			}
			
		}
	}

	
	//Imprime uma mensagem de erro caso o processo nao seja encontrado
	if( sendSignal(pid_destino, sig) != 0)
	{
		cout<<"Processo nao encontrado\n";

	}

}
