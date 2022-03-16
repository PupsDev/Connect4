#include <vector>

using namespace std;

class Puissance4
{
public:

    int sizeX = 7;
    int sizeY = 6;

    vector<vector<int>> board;

    Puissance4(){
        board = vector<vector<int>>(sizeX);
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
        //print();
        for(int i = 0 ; i < board.size() ; i ++){
            //cout<<"i : "<<i<<endl;
            if(!isColumnFull(i))
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

        if(full()){
            return(true);
        }

        if(evaluate(1) != 0)
        return(true);


        return false;
    }

    bool full(){
         for(int i = 0 ; i < sizeX ; i ++){
            if(board[i].size()<sizeY){
                return false;
            }
        }
        return true;
    }

    int evaluate(int depth){
        
		int maxAlign = 1;
		int prec = 0;

		vector<int> maxAlignHorizontal(sizeY,1);

       
		// for(int i = 0; i < board[0].size() ; i++){
		// 	cout<<i<<" : "<<board[0][i]<<endl;
		// }
		// cout<<board.size()<<endl;
        // cout<<board[0].size()<<endl;

		vector<int> precHorizontal = vector<int>(6);

        for(int i = 0 ; i < precHorizontal.size() ; i ++){
			precHorizontal[i] = (board[0].size()>i ? board[0][i]+1 : 0);
        }

        for(int x = 0 ; x < sizeX ; x++){
		    for(int y = 0 ; y < sizeY ; y ++){
				if(x!= 0 && precHorizontal[y] != 0 && (board[x].size()>y ? board[x][y]+1 : 0) == precHorizontal[y]){
					maxAlignHorizontal[y] ++;
					if(maxAlignHorizontal[y] >= 4){
						return precHorizontal[y]==1 ? - depth : depth;
					}
				}else{
					maxAlignHorizontal[y] = 1;
					precHorizontal[y] = (board[x].size()>y ? board[x][y]+1 : 0);
				}

				if(y!=0 && prec != 0 && (board[x].size()>y ? board[x][y]+1 : 0) == prec){
					maxAlign ++;
					if(maxAlign >= 4){
						return prec==1 ? - depth : depth;
					}
				}else{
					maxAlign = 1;
					prec = (board[x].size()>y ? board[x][y]+1 : 0);
				}
			}
		}

		precHorizontal.clear();


		int sy = 0;
		int sx = sizeX - 4;

		while(sy<=sizeY - 4){
			int y = sy;
			int x = sx;

			maxAlign = 1;
            x++;
            y++;

			prec = (board[x].size()>y ? board[x][y]+1 : 0);
 

			while(x<sizeX && y<sizeY){
				if(prec != 0 && (board[x].size()>y ? board[x][y]+1 : 0) == prec){
					maxAlign ++;
					if(maxAlign >= 4){
						return prec==1 ? - depth : depth;
                        
					}
				}else{
					maxAlign = 1;
					prec = (board[x].size()>y ? board[x][y]+1 : 0);
				}
				y++;
				x++;
			}

			if(sx>0){
				sx--;
			}else{
				sy++;
			}
		}


		sy = 0;
		sx = 4-1 ;

		while(sy<=sizeY - 4){
			int y = sy;
			int x = sx;

			maxAlign = 1;
            x--;
            y++;
			prec = (board[x].size()>y ? board[x][y]+1 : 0);
            

			while(x>=0 && y<sizeY){
				if(prec != 0 && (board[x].size()>y ? board[x][y]+1 : 0) == prec){
					maxAlign ++;
					if(maxAlign >= 4){
						return prec==1 ? - depth : depth;
					}
				}else{
					maxAlign = 1;
					prec = (board[x].size()>y ? board[x][y]+1 : 0);
				}
				y++;
				x--;
			}

			if(sx<sizeX){
				sx++;
			}else{
				sy++;
			}
		}

		return(0);

        //return(depth);
    }

    void print(){
        for(int i = 0 ; i < sizeY ; i ++){
            for(int j = 0 ; j < sizeX ; j ++){   
                cout<<(board[j].size()>i ? board[j][i] == 0 ? " O " : " X " : " _ ");
			}
            cout<<endl;
        }
		cout<<endl;
		cout<<endl;
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