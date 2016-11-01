#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <cmath>
#include <wiringPi.h>
#include <iostream>
#include <cstdlib>

using namespace std;
// a funcao abaixo serve apenas para enumerar os leds de forma ascendente
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
// a funcao abaixo serve apenas para enumerar os leds de forma ascendente
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
// Classe ponto, cada objeto tem um ponto no mapa.
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
        return static_cast<int>(sqrt(pow(this->x-x, 2) + pow(this->y-y, 2))); // a distancia entre um ponto e outro eh calculada aqui
    }
    int distanceTo(Point point){
        return distanceTo(point.x, point.y); // tambem pode-se usar como parametro outro Point
    }
};
//classe inimigo
class enemy {
public:
    void move () {
        if(ableToMove()){ // o inimigo tem uma chance de nao conseguir mover-se 
          if(elocation.y > 0 && elocation.y < 10){
            digitalWrite (enemySort(elocation.y), LOW); // apaga o led atual do inimigo caso ele tenha conseguido se mover.
          }
            elocation.y = elocation.y + 1; // aqui o inimigo ja conseguiu mover-se em uma casa
        }
    } // Move o inimigo em direção ao cristal
    enemy (int enemy_x, int enemy_y) { // construtor do inimigo, aceita parametros de coordenadas.
        elocation.x = enemy_x;
        elocation.y = enemy_y;
        health = 4;
        moving_speed = 0;
    }
    bool hasStriked(){ // caso ele tenha chegado na posicao onde fica o cristal a funcao retorna verdadeiro
        return elocation.y == 10;
    }
    bool ableToMove(){ // caso 20 seja maior que um numero aleatorio entre 1 e 50 retorna verdadeiro
      if(moving_speed == 3){
        moving_speed = 0;
        return true;
      }
       if(isAlive()){
        moving_speed++;
        return false;
       }
       else{
        return false;
       }

    }
    bool isAlive(){  // se o inimigo tiver mais de 0 de health retorna verdadeiro
      if(health > 0){
        if(elocation.y > 0 && elocation.y < 10){
          digitalWrite (enemySort(elocation.y), HIGH); // se a posicao estiver entre 0 e 10 liga o led correspondente do inimigo
        }
        return true;
      }
      else{
        if(elocation.y > 0 && elocation.y < 10){
          digitalWrite (enemySort(elocation.y), LOW); // se for falso desliga o led atual
        }
        return false;
      }
    }
  void reset(){ // funcao para resetar inimigos, e assim poder gerar inimigos novos
   health = 4;
   elocation.y = rand()%3 - 3; // a posicao inicial deles fica entre 0 a -3
  }
    Point getLocation(){ // retorna a localizacao
        return elocation;
    }
    int getHealth(){return health;} // retorna a vida atual
   void decreaseHealth(){ // diminui pontos de vida
     health = health - 4;
     cout << health;
     digitalWrite(enemySort(elocation.y), LOW); delay(50);//
     digitalWrite(enemySort(elocation.y),HIGH);           // pisca o led para demonstrar que foi atingido por uma torre
    }
protected:
    Point elocation; //localizacao do inimigo
    int moving_speed; // casas por segundo
    int health; // Saude do inimigo
}; // Existem vários inimigos no jogo


class BasicTower {
public:
  // construtor da torre basica aceita como parametro um id, se for 1 sera a primeira torre do mapa, localizado nas coordenadas (2,2) se for 2 torre das coordenadas (2,4) e assim por diante
    BasicTower(int towerid){
      if(towerid == 1){
        tlocation.x = 2;
        tlocation.y = 2;
        digitalWrite (towerSort(towerid), HIGH) ; // acende o led da torre de towerid1 (2,2)
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
      this->towerid = towerid;
      accuracy = 75;
      range = 3;
      fire_speed = 1;
    }
    void shoot_effect(){ // efeito de pisca para demonstrar o tiro
        digitalWrite (towerSort(towerid),  LOW) ; delay (100) ;
        digitalWrite (towerSort(towerid), HIGH) ;
    }
    bool hitTarget(){ // chances de erro de tiro
      return (accuracy > rand()%100 + 1);
    }
    void shoot(enemy en){
      if((en.isAlive()) && (en.getLocation().distanceTo(tlocation) < range)){ // caso o inimigo esteja vivo, e esteja dentro do range, atire
        this->shoot_effect(); // efeito de tiro
        if(hitTarget()){ // chances de erro
           en.decreaseHealth(); // se acertar diminua a vida
        }
      }
    }
protected:
    Point tlocation; //localizacao
    int towerid;
    int fire_speed;
    int range; // Alance do tiro
    int accuracy; // 75% of accuracy
   
}; 
// Classe do crystal, que é alvo dos inimigos
class Crystal {
public:
    Crystal(){
        health = 10; // comeca com 10 de vida
        clocation.y = 10;
        clocation.x = 1;
    }
    int getHealth(){
        return health;
    }
    void setHealth(int value){
        health = health - value;
    }
    //quando a funcao abaixo eh chamada o led do cristal pisca
    void crystalBlink(){
      digitalWrite (10,  LOW) ; delay (100) ;
      digitalWrite (10, HIGH) ;
    }
protected:
    Point clocation; //localizacao do cristal
    int health; // Saúde do crystal (quando chegar a 0, o crystal é destruído e você perde o jogo)

}; // Só existe um cristal no jogo. Se ele for destruído, você perde.


class map {
public:
    int width = 5; // Tamanho da largura do mapa
    int height = 10; // Tamanho da altura do mapa
    bool OnMap(Point point){
            return point.x >= 0 && point.x < width && 
                   point.y >= 0 && point.y < height;
    }
};


// Declara valores iniciais toda vez que um novo nivel é feito
int main (){
    wiringPiSetup();
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
    digitalWrite(1, LOW);
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(14, LOW);
    digitalWrite(10, LOW);
    digitalWrite(9, LOW);
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);
    digitalWrite(0, LOW);
    digitalWrite(10, HIGH);
    Crystal crystal;
    int thereisgame = true; // Inicialmente, há jogo até que você perca o jogo.
    int counter(26); // Um auxiliar que será usado para saber quando um nivel acaba
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
            enemy1.reset();
            enemy2.reset();
            enemy3.reset();
        }
        // INICIO DO JOGO
        tower1.shoot(enemy1);
        tower1.shoot(enemy2);
        tower1.shoot(enemy3);
        usleep(600000); // Faz uma micro-pausa
        enemy1.move(); // Move o inimigo 1. O mesmo para as linhas abaixo
        enemy2.move();
        enemy3.move();
        counter++; // Aumenta o contador. Quando chegar a 26, o nivel acaba.
        // Se um inimigo colidir com o crystal, o crystal perderá saúde
        if (enemy1.hasStriked()){
          crystal.setHealth(enemy1.getHealth());
          crystal.crystalBlink();
        }if (enemy2.hasStriked()){
          cout << enemy2.getHealth();
          crystal.setHealth(enemy2.getHealth());
          crystal.crystalBlink();
        }if (enemy3.hasStriked()){
          cout << enemy3.getHealth();
          crystal.setHealth(enemy3.getHealth());
          crystal.crystalBlink();
        }
        if (crystal.getHealth() <= 0) // Detectar se o cristal foi destruído
        {
            thereisgame = false; // Caso o crystal tenha sido destruído, o jogo acaba.
            cout << "GAME OVER!"; // Mostra na tela que o jogo acabou.
        }
        // FIM DO JOGO
        }
 return 0;
}
