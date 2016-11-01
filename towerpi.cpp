#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <cmath>
#include <wiringPi.h>
#include <iostream>
#include <cstdlib>

using namespace std;
namespace towerGame{
    int enemySort(int num){
      if (num == 1)
        return 8;
      if (num == 2)
        return 9;
      if (num == 3)
        return 7;
      if (num == 4)
        return 0;
      if (num == 5)
        return 1;
      if (num == 6)
        return 2;
      if (num == 7)
        return 3;
      if (num == 8)
        return 4;
      if (num == 9)
        return 5;
      else
        return 404;
    }

    int towerSort(int num){
      if(num == 1)
        return 14;
      if (num == 2)
        return 6;
      if (num == 3)
        return 13;
      if (num == 4)
        return 12;
      else
        return 404;
    }

    class Point{
        public:
            int x;
            int y;
        Point(int x, int y){
            this->x = x;
            this->y = y;
        }
        Point(){}
        int distanceTo(int x, int y){
            return static_cast<int>(sqrt(pow(this->x-x, 2) + pow(this->y-y, 2)));
        }
        int distanceTo(Point point){
            return distanceTo(point.x, point.y);
        }
    };
    //cristal = 10

    // Classe torre com as suas propriedades
    class enemy {
    public:
        void move () {
            if(ableToMove()){
                if(elocation.y > 0 && elocation.y < 10)
                    digitalWrite (enemySort(elocation.y), LOW);
                elocation.y = elocation.y + 1;
                if(elocation.y > 0 && elocation.y < 10)
                    digitalWrite (enemySort(elocation.y), HIGH);
            }
        } // Move o inimigo em direção ao cristal
        enemy (int enemy_x, int enemy_y) {
            elocation.x = enemy_x;
            elocation.y = enemy_y;
            health = 4;
            moving_speed = 50;
        }
        bool hasStriked(){
            return elocation.y == 10;
        }
        bool ableToMove(){
            return moving_speed > rand() % 50 + 1;
        }
        bool isAlive(){
          if(health > 0)
            return true;
          else
            return false;
        }
        Point getLocation(){
            return elocation;
        }
        int getHealth(){return health;}
       void decreaseHealth(){ health--;}
    protected:
        Point elocation; //localizacao do inimigo
        int moving_speed; // 0.5 aprox casas por segundo
        int health; // Saude do inimigo
    }; // Existem vários inimigos no jogo


    class BasicTower {
    public:
        BasicTower(int towerid){
          if(towerid == 1){
            tlocation.x = 2;
            tlocation.y = 2;
            digitalWrite (towerSort(towerid), HIGH) ;
          }
          if(towerid == 2){
            tlocation.x = 2;
            tlocation.y = 4;
            digitalWrite (towerSort(towerid), HIGH) ;
          }
          if(towerid == 3){
            tlocation.x = 2;
            tlocation.y = 6;
            digitalWrite (towerSort(towerid), HIGH) ;
          }
          if(towerid == 4){
            tlocation.x = 2;
            tlocation.y = 8;
            digitalWrite (towerSort(towerid), HIGH) ;
          }
          accuracy = 75;
          range = 2;
          fire_speed = 1;
        }
        void shoot_effect(){
            digitalWrite (towerSort(towerid),  LOW) ; delay (70) ;
            digitalWrite (towerSort(towerid), HIGH) ;
        }
        bool hitTarget(){
          return (accuracy > rand()%100 + 1);
        }
        void shoot(enemy en){
          if((en.isAlive()) && (en.getLocation().distanceTo(tlocation) < range)){
            shoot_effect();
            if(hitTarget()){
               en.decreaseHealth();
            }
          }
        }
    protected:
        Point tlocation; //localizacao
        int towerid;
        int fire_speed;
        int range; // Alance do tiro
        int accuracy; // 75% of accuracy
       
    }; // Inicialmente, você só tem uma torre disponivel para atacar os inimigos

    // Classe inimigo e suas propriedades

    // Classe do crystal, que é alvo dos inimigos

    class Crystal {
    public:
        Crystal(){
            health = 10;
            clocation.y = 10;
            clocation.x = 1;
        }
        int getHealth(){
            return health;
        }
        void setHealth(int value){
            health = health - value;
        }
    protected:
        Point clocation; //localizacao do cristal
        int health; // Saúde do crystal (quando chegar a 0, o crystal é destruído e você perde o jogo)

    }; // Só existe um cristal no jogo. Se ele for destruído, você perde.

    // Uma classe mapa que vai herdar todas as classes iniciais


    class map {
    public:
        int width = 5; // Tamanho da largura do mapa
        int height = 10; // Tamanho da altura do mapa
        bool OnMap(Point point){
                return point.x >= 0 && point.x < width && 
                       point.y >= 0 && point.y < height;
        }
    } map1;


    // Declara valores iniciais toda vez que um novo nivel é feito
    void pinsetup(){
      pinMode (14, OUTPUT);
      pinMode (12, OUTPUT);
      pinMode (13, OUTPUT);
      pinMode (6, OUTPUT);
      pinMode (5, OUTPUT);
      pinMode (4, OUTPUT);
      pinMode (3, OUTPUT);
      pinMode (2, OUTPUT);
      pinMode (1, OUTPUT);
      pinMode (0, OUTPUT);
      pinMode (7, OUTPUT);
      pinMode (8, OUTPUT);
      pinMode (9, OUTPUT);
      pinMode (10, OUTPUT);
    }


    int main ()
    {
        Crystal crystal;
        int thereisgame = true; // Inicialmente, há jogo até que você perca o jogo.
        int counter(26); // Um auxiliar que será usado para saber quando um nivel acaba
        pinsetup();
        int numtower;
        cout <<"choose a basic tower, 1 - 2 - 3 - 4 :";
        cin >> numtower;
        BasicTower tower1(numtower);
        enemy enemy1(1,-3);
        enemy enemy2(1,-1);
        enemy enemy3(1, 0);
        while (thereisgame) // Enquanto houver jogo.
        {
           if (counter>25) { // Inicia um novo nivel
                counter = 0; // Zera o contador
            }
            // INICIO DO JOGO
            tower1.shoot(enemy1);
            tower1.shoot(enemy2);
            tower1.shoot(enemy3);
            usleep(100000); // Faz uma micro-pausa
            enemy1.move(); // Move o inimigo 1. O mesmo para as linhas abaixo
            enemy2.move();
            enemy3.move();
            counter++; // Aumenta o contador. Quando chegar a 26, o nivel acaba.
            // Se um inimigo colidir com o crystal, o crystal perderá saúde
            if ( (enemy1.hasStriked() or enemy2.hasStriked()
                or enemy3.hasStriked())) // Se o inimigo atingir o cristal...
            {
                crystal.setHealth(enemy1.getHealth()); // O cristal perde pontos de saúde equivalentes aos pontos
                // de saúde do inimigo
            }
            if (crystal.getHealth() <= 0) // Detectar se o cristal foi destruído
            {
                thereisgame = false; // Caso o crystal tenha sido destruído, o jogo acaba.
                cout << "GAME OVER!"; // Mostra na tela que o jogo acabou.
            }
            // FIM DO JOGO
            }
    }
}
