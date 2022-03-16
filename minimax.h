#include <bits/stdc++.h>

template <class T>
class Minimax
{
public:
	int depth;

	Minimax(int dp){
		depth = dp;
	}

	Minimax(){
		depth = 100;
	}

	T play(T game,int player){ //quel player joue l'ordinateur
		vector<T> nexts = game.generateNextMoves(player);
		//cout<<"minimax 21 -> Taille "<<nexts.size()<<endl;
		T res;
		if(player == 0){ //minimiser
			int min = evaluate(nexts[0], player, depth);
			int i_min = 0;

			for(int i = 1 ; i < nexts.size() ; i++){
				int eval = evaluate(nexts[i], player, depth);
				if(eval<min){
					min = eval; 
					i_min = i;
				}
			}
			res = nexts[i_min];

		}else{ //maximiser
			int max = evaluate(nexts[0], player, depth);
			int i_max = 0;

			for(int i = 1 ; i < nexts.size() ; i++){
				int eval = evaluate(nexts[i], player, depth);
				if(eval>max){
					max = eval; 
					i_max = i;
				}
			}
			res = nexts[i_max];
		}	
		return res;
	}

	int evaluate(T game, int player, int depth){
		int eval = game.evaluate(depth);

		if(!game.end() && depth != 0){
			vector<T> nexts = game.generateNextMoves(1-player);
			if(1-player == 0){ //minimiser
				int min = evaluate(nexts[0], 1-player, depth-1);
				int i_min = 0;

				for(int i = 1 ; i < nexts.size() ; i++){
					int eval = evaluate(nexts[i], 1-player, depth-1);
					if(eval<min){
						min = eval; 
						i_min = i;
					}
				}
				eval = min;

			}else{ //maximiser
				int max = evaluate(nexts[0], 1-player, depth-1);
				int i_max = 0;

				for(int i = 1 ; i < nexts.size() ; i++){
					int eval = evaluate(nexts[i], 1-player, depth-1);
					if(eval>max){
						max = eval; 
						i_max = i;
					}
				}
				eval = max;
			}
		}

		return eval;
	}
};