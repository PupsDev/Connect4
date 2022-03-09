#include <iostream>
#include "connect.h"
#include "minimax.h"

using namespace std;


int main(){


	Minimax<Puissance4> minimax;

	auto current = Puissance4();

	int i = 0;
	while(!current.end()){
		
		current = minimax.play(current,i);
		cout<<current<<endl;
		i = 1-i;
		if(!current.end()){
			int col = 3;
			current = current.play(i,col);
			i = 1-i;
		}
		

	}

	if(current.end() == 0){
		cout<<"Égalité"<<endl;
	}else if(current.end() == 1){
		cout<<"Joueur 1 a gagné"<<endl;
	} else{
		cout<<"Joueur 2 a gagné"<<endl;
	}

}