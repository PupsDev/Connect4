#include <vector>

using namespace std;

class Puissance4
{
public:

    int sizeX = 7;
    int sizeY = 6;

    vector<vector<int>> board;

    Puissance4(){
        board = vector<vector<int>>();
    }
    
    Puissance4(vector<vector<int>> b, int x, int y){
        board = b;
        sizeX = x;
        sizeY = y;
    }

    ~Puissance4(){
        for(int i=0; i<board.size();i++){
            board[i].clear();
        }
        board.clear();
    }

    vector<Puissance4> generateNextMoves(int player){
        vector<Puissance4> res = vector<Puissance4>(0);
        for(int i = 0 ; i < board.size() ; i ++){
            if(!isColumnFull(i));
            res.push_back(play(player, i));
        }
        return res; 
    }

    Puissance4 play(int player, int place){
        if(!isColumnFull(place)){
            auto tmp = board;
            tmp[place].push_back(player);
            return(Puissance4(tmp, sizeX, sizeY));
        }else{
            cerr<<"erreur coup impossible"<<endl;
            return *this;
        }
    }

    bool isColumnFull(int c){
        return(board[c].size() >= sizeY); 
    }

    bool end(){
        return(false);
    }

    int evaluate(int depth){
        return(depth);
    }
};

ostream& operator<<(ostream& os, const Puissance4& g){

	for(int i = 0 ; i < g.board[0].size() ; i ++){
		for(int j = 0 ; j < g.board.size() ; j ++){
            if(g.board[j].size()>g.sizeY - i)
			os<<g.board[j][g.sizeY - i]<<" ";
		}
		os<<endl;
	}
	return(os);
}