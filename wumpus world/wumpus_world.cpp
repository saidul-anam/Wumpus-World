#include <iostream>
#include <cmath>
#include <sstream>

using namespace std;

#define GRIDSIZE 4
#define UP      0
#define DOWN    2
#define LEFT    3
#define RIGHT   1
#define MAX_SHOTS 3

/*string to_str(int x)
{
    std::string out_string;
    std::stringstream ss;
    ss << x;
    return ss.str();
}

*/
class Position
{

    int x, y;

public:

    Position (int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    Position() {}
    void moveRight()
    {
        if(x>=0&&x<=2){
        x++;}
    }

    void moveLeft()
    {
        if(x>=1&&x<=3){
        x--;}
    }

    void moveUp()
    {  if(y>=0&&y<=2){
        y++;}
    }

    void moveDown()
    {   if(y>=1&&y<=3){
        y--;}
    }

    bool isAdjacent(Position p)
    {
   if(abs(x-p.x)+abs(y-p.y)==1){
    return true;
   }
   else return false;
    }

    bool isSamePoint(Position p)
    {
       if(abs(x-p.x)+abs(y-p.y)==0){
       return true;
      }
     else return false;
    }
    int getX()
    {
        return x;
    }

    int getY()
    {
        return y;
    }

};

class Wumpus
{

    bool killed;
    Position p;

public:

    Wumpus(int x, int y)
    {
        p = Position(x, y);
        killed = false;
    }

    Wumpus()
    {
      int x=rand()%GRIDSIZE;
      int y=rand()%GRIDSIZE;
      while(x==0&&y==0){
        x=rand()%GRIDSIZE;
        y=rand()%GRIDSIZE;
      }
      p=Position(x,y);
      killed=false;
          }

    void kill()
    {
        killed = true;
    }
  bool wumpusalive(){
  return !killed;

  }
    Position getPosition()
    {
        return p;
    }

};

class Pit
{

    bool killed;
    Position p;

public:

     Pit(int x, int y)
    {
        p = Position(x, y);
    }

      Pit()
    {
      int x=rand()%GRIDSIZE;
      int y=rand()%GRIDSIZE;
      while(x==0&&y==0){
        x=rand()%GRIDSIZE;
        y=rand()%GRIDSIZE;
      }
      p=Position(x,y);
          }
    Position getPosition()
    {
        return p;
    }

};


class Player
{

     int direction;
    int total_shots;
    bool killed;
    Position p;

public:

    Player()
    {
       direction=UP;
       total_shots=MAX_SHOTS;
       killed=false;
       p=Position(0,0);
    }

    void turnLeft()
    {
    if(direction==UP) {
            direction=LEFT;
    }
    else if(direction==LEFT){
            direction=DOWN;
            }
      else if(direction==RIGHT){
           direction=UP;
            }
      else if(direction==DOWN){
            direction =RIGHT;
            }
    }

    void turnRight()
    {
    if(direction==UP) {
            direction=RIGHT;
    }
    else if(direction==LEFT){
            direction=UP;
            }
      else if(direction==RIGHT){
           direction=DOWN;
            }
      else if(direction==DOWN){
            direction =LEFT;
            }
    }

    void moveForward()
    {
    if (direction==UP){
         p.moveUp();
    }
      else if (direction==RIGHT){
         p.moveRight();
    }

    else if (direction==LEFT){
         p.moveLeft();
    }
     else if (direction==DOWN){
         p.moveDown();
    }
    }

    bool isAdjacent(Position pos)
    {
        return p.isAdjacent(pos);
    }

    bool isSamePoint(Position pos)
    {
        return p.isSamePoint(pos);
    }
    void kill()
    {
        killed = true;
    }
    int getDirection(){
    return direction;
    }

    string getPositionInfo()
    {
        return "Player is now at " + to_string(p.getX()) + ", " + to_string(p.getY());
    }
    string getDirectionInfo()
    {
        string s;
        if (direction == UP) s = "up";
        if (direction == DOWN) s = "down";
        if (direction == LEFT) s = "left";
        if (direction == RIGHT) s = "right";
        return "Player is moving at direction: " + s;
    }
   Position getPosition(){
 return p;
 }
 void shots(){
 total_shots--;}
 int shotsavail(){
 return total_shots;}
};

class WumpusWorld
{

private:

    Player player;
    Wumpus wumpus;
    Position gold_position;
    Pit pit;
    bool ended;

public:

    WumpusWorld()
    {
       player=Player();
       wumpus=Wumpus();
       ended=false;
       int x=rand()%GRIDSIZE;
       int y=rand()%GRIDSIZE;
       while((x==0&&y==0)||abs(wumpus.getPosition().getX()-x)+abs(wumpus.getPosition().getY()-y)==0){
           x=rand()%GRIDSIZE;
        y=rand()%GRIDSIZE;
       }
       gold_position=Position(x,y);
        int a=rand()%GRIDSIZE;
        int b=rand()%GRIDSIZE;
        while((a==0&&b==0)||(abs(a-x)+abs(b-y)==0)||(wumpus.getPosition().getX()-a)+abs(wumpus.getPosition().getY()-b)==0){
            a=rand()%GRIDSIZE;
            b=rand()%GRIDSIZE;
        }
        pit=Pit(a,b);
    }
    WumpusWorld(int wumpus_x, int wumpus_y)
    {
       wumpus=Wumpus(wumpus_x,wumpus_y);
        player=Player();
       int x=rand()%GRIDSIZE;
       int y=rand()%GRIDSIZE;
   while((x==0&&y==0)||(wumpus_x==x&&wumpus_y==y)){
           x=rand()%GRIDSIZE;
        y=rand()%GRIDSIZE;
       }
       gold_position=Position(x,y);
        int a=rand()%GRIDSIZE;
        int b=rand()%GRIDSIZE;
     while((a==0&&b==0)||(abs(a-x)+abs(b-y)==0)||(wumpus_x==a&&wumpus_y==b)){
            a=rand()%GRIDSIZE;
            b=rand()%GRIDSIZE;
        }
        pit=Pit(a,b);
          ended=false;
    }
    WumpusWorld(int wumpus_x, int wumpus_y, int gold_x, int gold_y)
    {
        player=Player();
        ended=false;
             wumpus=Wumpus(wumpus_x,wumpus_y);
             gold_position=Position(gold_x,gold_y);
                int a=rand()%GRIDSIZE;
        int b=rand()%GRIDSIZE;
     while((a==0&&b==0)||(abs(gold_x-a)+abs(gold_y-b)==0)||(wumpus_x==a&&wumpus_y==b)){
            a=rand()%GRIDSIZE;
            b=rand()%GRIDSIZE;
        }
             pit=Pit(a,b);
    }

    WumpusWorld(int wumpus_x, int wumpus_y, int gold_x, int gold_y, int pit_x, int pit_y)
    {
      player=Player();
      wumpus=Wumpus(wumpus_x,wumpus_y);
      gold_position=Position(gold_x,gold_y);
      pit=Pit(pit_x,pit_y);
      ended=false;
    }

    void moveForward()
    {
        player.moveForward();
        return showGameState();
    }

    void turnLeft()
    {
        player.turnLeft();
        return showGameState();
    }

    void turnRight()
    {
        player.turnRight();
        return showGameState();
    }

    void shoot()
    {
     if(player.shotsavail()<=0){
            cout<<"all shoot is finished"<<endl;
        return;
     }
      player.shots();
        if(!wumpus.wumpusalive()){
                cout<<"wompus is already dead"<<endl;
            return ;
        }
       int player_x=player. getPosition().getX();
            int player_y=player. getPosition().getY();
              int wumpus_x=wumpus. getPosition().getX();
                int wumpus_y=wumpus. getPosition().getY();
              if(player_x!=wumpus_x&&player_y!=wumpus_y){
                cout<<"wumpus is out of your sight"<<endl;
              }
              else{
                if(player_x==wumpus_x){
                    if(player.getDirection()==UP&&player_y<wumpus_y){
                            cout<<"Congratulations!You just killed the wompus"<<endl;
                    wumpus.kill();
                    }
              else  if(player.getDirection()==DOWN&&player_y>wumpus_y){
                            cout<<"Congratulations!You just killed the wompus"<<endl;
                    wumpus.kill();
                    }
                    else {
                        cout<<"Turn around!Wumpus is behind you"<<endl;
                    }

                }
               else if(player_y==wumpus_y){
                    if(player.getDirection()==RIGHT&&player_x<wumpus_x){
                            cout<<"Congratulations!You just killed the wompus"<<endl;
                    wumpus.kill();
                    }
              else  if(player.getDirection()==LEFT&&player_y<wumpus_y){
                            cout<<"Congratulations!You just killed the wompus"<<endl;
                    wumpus.kill();
                    }
                    else {
                        cout<<"Turn around!Wumpus is behind you"<<endl;
                    }
                }
              }
     }
    void showGameState()
    {
        cout << player.getPositionInfo() << endl;
        cout << player.getDirectionInfo() << endl;
 if(wumpus.wumpusalive()){
        if (player.isAdjacent(wumpus.getPosition()))
        {
            cout << "stench!" << endl;
                 if (player.isAdjacent(pit.getPosition()))
        {
            cout << "Breeze!" << endl;
        }
            return;
        }
        if (player.isSamePoint(wumpus.getPosition()))
        {
            cout << "Player is killed!" << endl;
            player.kill();
            cout << "Game over!" << endl;
            ended = true;
            return;
        }}

         if (player.isAdjacent(pit.getPosition()))
        {
            cout << "Breeze!" << endl;
            return;
        }
        if (player.isSamePoint(pit.getPosition()))
        {

            cout << "you step in the Pit! Now rot here forever!" << endl;
              player.kill();
            ended = true;
            return;
        }

        if (player.isSamePoint(gold_position))
        {
            cout << "Got the gold!" << endl;
            cout << "Game ended, you won!" << endl;
            ended = true;
            return;
        }
    }

    bool isOver()
    {
        return ended;
    }
};
int main()
{
    int c, wumpus_x, wumpus_y, gold_x, gold_y, pit_x, pit_y;
      FILE *f1=fopen("input.txt","r");
      if(f1==NULL){
        cout<<"failed to open"<<endl;
        return 1;
      }
    int x=fscanf(f1,"%d %d %d %d %d %d",&wumpus_x,&wumpus_y,&gold_x,&gold_y,&pit_x,&pit_y);
    fclose(f1);
    WumpusWorld w;
    if(x==6){
 w=  WumpusWorld(wumpus_x, wumpus_y, gold_x, gold_y, pit_x, pit_y);}
  else if(x==4){
    w=  WumpusWorld(wumpus_x, wumpus_y, gold_x, gold_y);}
  else if(x==2){
    w=  WumpusWorld(wumpus_x,wumpus_y);
  }
  else {
    w=  WumpusWorld();
  }
    w.showGameState();
    while (!w.isOver())
    {
        cout << "1: move forward" << endl;
        cout << "2: Turn left" << endl;
        cout << "3: Turn right" << endl;
        cout << "4: Shoot" << endl;
        cin >> c;
        if (c == 1)
        {
            w.moveForward();
        }
        else if (c == 2)
        {
            w.turnLeft();
        }
        else if (c == 3)
        {
            w.turnRight();
        }
        else if (c == 4)
        {
            w.shoot();
        }
    }
    return 0;
}
