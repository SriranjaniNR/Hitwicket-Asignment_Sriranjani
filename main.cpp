#include <algorithm>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
class gameui
{  
    vector<vector<string>>board;
    
public:
  int flag;
  int e;
  int killA;
  int killB;
  gameui(vector<vector<string>>board2)//constructor
  {  
     board=board2;
     flag=0;
  }
    vector<int>findstring(string to_search)//to search the piece
    {   vector<string>::iterator it;
        for(int i=0;i<5;i++)
        {   it=find (board[i].begin(), board[i].end(),to_search);
            if(it!=board[i].end())
                {
                    int p=it - board[i].begin();
                    return {i,p};
                }
        }
    }
    bool check(int x,int y,string q)//check whether it is own key
    {   char p=q[0];
        string t=board[x][y];
        if(t==" -  ")
          return false;
        else if(t.substr(0,2)==q)
           {e=4;
           return true;
           }
        else if(p=='A'&&t.substr(0,2)=="B-")
        {   killB++;
            return false;
        }
        else if(p=='B'&&t.substr(0,2)=="A-")
        {   killB++;
            return false;
        }
    }
    void error()
    {
        if(e==0)e==2;
    }
    bool checkmove(string move)
    {
        if(move[0]!='P')
        { e=1;
          return 1;
        }
        else if(move[1]<='1'&&move[1]>='5')
        { e=1;
          return 1;
        }
        else if(move[3]!='F'||move[3]!='B'||move[3]!='R'||move[3]!='L')
        {
            e=1;
            return 1;
        }
        else
        {
            return 0;
        }
    }
    void moveplace(int x,int y,string move,char p,string q)//placing the move
    {   
        if(p=='A'&&!flag){
        string t=move.substr(0,2);
                  if(move[3]=='F')
                   {   if(x-1>0&&!check(x-1,y,q))
                       board[x-1][y]=q+t;
                       else{
                        
                        flag=1;
                       }
                       
                   }
                 else if(move[3]=='B')
                   {  if(x+1<4&&x+1>0&&!check(x+1,y,q))board[x+1][y]=q+t;
                       else{
                        flag=1;
                       }
                   }
                  else if(move[3]=='L')
                   {  if(y-1>0&&!check(x,y-1,q))board[x][y-1]=q+t;
                       else{
                          
                        flag=1;
                       }
                   }
                  else if(move[3]=='R')
                   {  if(y+1<4&&y+1>0&&!check(x,y+1,q))board[x][y+1]=q+t;
                       else{
                           
                        flag=1;
                       }
                   }
             }
        else if(p=='B'&&!flag){
            string t=move.substr(0,2);
                  if(move[3]=='B')
                   {   if(x-1>0&&!check(x-1,y,q))
                       board[x-1][y]=q+t;
                       else{
                        flag=1;
                       }
                   }
                 else if(move[3]=='F')
                   {  if(x+1<4&&x+1>0&&!check(x+1,y,q))board[x+1][y]=q+t;
                       else{
                           
                        flag=1;
                       }
                   }
                  else if(move[3]=='L')
                   {  if(y-1>0&&!check(x,y-1,q))board[x][y-1]=q+t;
                       else{
                           
                        flag=1;
                       }
                   }
                  else if(move[3]=='R')
                   {  if(y+1<4&&y+1>0&&!check(x,y+1,q))board[x][y+1]=q+t;
                       else{
                        flag=1;
                       }
                   }
             }
             if(flag)error();
    }
    
    
    void board_placement(vector<string>pos,char p,string move)
    {   string q="A-";
        if(p=='A')
          {
              if(move==" ")
                {
                    for(int i=0;i<5;i++)
                    {
                        board[4][i]=pos[i];
                    }
                }
              else
              {  
                 string t=move.substr(0,2);
                 vector<int>places=findstring(q+t);
                 int x=places[0];
                 int y=places[1];
                 
                 moveplace(x,y,move,'A',q);
                 if(!flag)
                 board[x][y]=" - ";
              }
          }
         else if(p=='B')
         { string q="B-";
            if(move==" ")
                {
                    for(int i=0;i<5;i++)
                    {
                        board[0][i]=pos[i];
                    }
                } 
            else
              {  
                 string t=move.substr(0,2);
                 vector<int>places=findstring(q+t);
                 int x=places[0];
                 int y=places[1];
                 moveplace(x,y,move,'B',q);
                 if(!flag)
                 board[x][y]=" - ";
                   
              }
         }
    }
    void display()
    {   //cout<<"display"<<endl;
        for(int i=0;i<5;i++)
        {
            for(int j=0;j<5;j++)
            {
                cout<<board[i][j]<<" ";
            }
            cout<<endl;
        }
    }
};

main()
{   vector<vector<string>> vec(5,vector<string>(5," -  "));
    gameui g(vec);
    vector<string>posA{"A-P3", "A-P2", "A-P5", "A-P4","A-P1"};
    vector<string>posB{"B-P2", "B-P1", "B-P3", "B-P5", "B-P4"};
    g.board_placement(posA,'A'," ");
    g.board_placement(posB,'B'," ");
    g.display();
    string move;
    int i=0;
    while(true){
    if(i==0){
      cin>>move;
      g.board_placement(posA,'A',move);
      while(g.flag)
      {  if(g.e==4)cout<<"Friendly piece!Move Again"<<endl;
         else if(g.e==2)cout<<"Out of Boundary"<<endl;
          cin>>move;
          g.board_placement(posA,'A',move);
      }
      i=1;
      
    }
    else if(i==1)
    { cin>>move;
      g.board_placement(posB,'B',move);
      while(g.flag)
      {
          if(g.e==4)cout<<"Friendly piece!Move Again"<<endl;
          else if(g.e==2)cout<<"Out of Boundary"<<endl;
          cin>>move;
          g.board_placement(posA,'B',move);
      }
      i=0;
    }
    g.display();
    if(g.killA==5)
        {
            cout<<"B is winner"<<endl;
            break;
        }
    else if(g.killB==5)
    {
          cout<<"A is winner"<<endl;
            break;
    }
    }
    return 0;
}


