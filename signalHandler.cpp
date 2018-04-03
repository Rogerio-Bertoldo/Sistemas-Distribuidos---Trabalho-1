/*
	Autor: Rogerio Henrique Bertoldo da Silva
	[uso]: g++ --std=c++11 -signalHandler.cpp -o signalHandler
*/

#include<iostream>
#include<string>
#include<signal.h>
#include<unistd.h>

using namespace std;

//flag para interrupcao do programa
bool fim = false;


//signal handler para sinal SIGINT
void sigInt(int param) { cout<<"Sinal recebido: SIGINT\n";}


//signal handler para sinal SIGABRT
void sigAbrt(int param) { cout<<"Sinal recebido: SIGABRT\n";}


//signal handler para sinal SIGTERM
void sigTerm(int param) { cout<<"Sinal recebido: SIGTERM\nFinalizando processo...\n"; fim = true;}


int main(int argc, char* modo_espera[])
{
	//id do processo atual
	int id = getpid();
	
	string modo = modo_espera[1];

	cout<<"PID: "<<id<<"\n";

	signal(SIGINT, sigInt);
	signal(SIGABRT, sigAbrt);
	signal(SIGTERM, sigTerm);

	while(!fim)
	{
		if(modo == "busy")
		{
			while(!fim);
		}
	
		else if(modo == "block")
		{
			pause();
		}
	}
	
	

	
	
}
