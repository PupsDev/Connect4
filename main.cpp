#include <iostream>
#include "connect.h"
#include "minimax.h"

using namespace std;


int main(){


	Minimax<Puissance4> minimax;
	minimax.depth = 5;

	auto current = Puissance4();
	
	

	int i = 0;
	while(!current.end()){
		//cout<<i<<endl;
		current = minimax.play(current,i);
		i = 1-i;
		if(!current.end()){
			current.print();
			int col;
			cout<<"jouer : ";
			cin>>col;
			current = current.play(i,col);
			
			i = 1-i;
		}
		current.print();

	}

	if(current.evaluate(1) == 0){
		cout<<"Égalité"<<endl;
	}else if(current.evaluate(1)<0){
		cout<<"Joueur 1 a gagné"<<endl;
	} else{
		cout<<"Joueur 2 a gagné"<<endl;
	}

}