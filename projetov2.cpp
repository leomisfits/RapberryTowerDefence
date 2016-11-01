#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <unistd.h>
#include <cmath>
#include <wiringPi.h>
#include <iostream>

using namespace std;

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

//cristal = 10

// Classe torre com as suas propriedades

class Basictower {
public:
    tower(int tower_x, int tower_y){
        tlocation.x = tower_x;
        tlocation.y = tower_y;
    }
    void shoot_effect(int tower_){
        digitalWrite (towerSort(tower_),  LOW) ; delay (70) ;
        digitalWrite (towerSort(tower_), HIGH) ;
}
protected:
    Point tlocation; //localizacao
    int fire_speed = 1;
    int range = 2; // Alance do tiro
    float accuracy = 0.75;
   
}; // Inicialmente, você só tem uma torre disponivel para atacar os inimigos

// Classe inimigo e suas propriedades

class enemy {
public:
    enemy (int enemy_x, int enemy_y) {
        elocation.x = enemy_x;
        elocation.y = enemy_y;
    }
    Point elocation; //localizacao do inimigo
    int moving_speed;
    int health = 3; // Saude do inimigo
    void move () {Elocation.y++;} // Move o inimigo em direção ao cristal
} enemy1, enemy2, enemy3; // Existem vários inimigos no jogo

// Classe do crystal, que é alvo dos inimigos

class Crystal {
public:
    int crystal_x; // Posição x do Crystal no mapa
    int crystal_y; // Posição y do Crystal no mapa
    int health; // Saúde do crystal (quando chegar a 0, o crystal é destruído e você perde o jogo)
    Crystal() {health = 10;} // Saúde do crystal no inicio do jogo

} crystal; // Só existe um cristal no jogo. Se ele for destruído, você perde.

// Uma classe mapa que vai herdar todas as classes iniciais

class point{
    public:
        int x;
        int y;
    point(int x, int y){
        this->x = x;
        this->y = y;
    }
    int distanceTo(int x, int y){
        return static_cast<int>(sqrt(pow(this->x-x, 2) + pow(this->y-y, 2)));
    }
    int DistanceTo(Point point){
            return DistanceTo(point.X, point.Y);
     }
}


class map {
public:
    int width; // Tamanho da largura do mapa
    int height; // Tamanho da altura do mapa
    bool OnMap(Point point){
            return point.X >= 0 && point.X < width && 
                   point.Y >= 0 && point.Y < height;
    }
    void draw(); // É dentro desta função que todo o desenho do jogo ocorre
} map1;

// A função abaixo desenha o estado do jogo a cada intervalo de tempo (menos de 1 segundo)
void map::draw()
{
    system("clear");
    for (int i = 0; i < width+2; i++)
        cout << "#";
        cout << endl;

        for (int i = 0; i < height; i++)
        {

            for (int j = 0; j < height; j++)
            {
                if (j == 0)
                    cout << "#";
                    if (i==enemy1.enemy_x and (j==enemy1.enemy_y or j==enemy2.enemy_y or j==enemy3.enemy_y)
                        and enemy1.enemy_y!=crystal.crystal_y) // Mostra o desenho dos inimigos em seu devido lugar
                        cout << "*";
                    else if (i==tower1.tower_x and j==tower1.tower_y) // Mostra o desenho da torre em seu devido lugar
                        cout << "_";
                    else if (i==crystal.crystal_x and j==crystal.crystal_y) // Mostra o desenho do cristal em seu devido lugar
                        cout << "@";
                    else
                    cout << " ";

                if (j == width-1)
                    cout << "#";
            }
            cout << endl;
        }
        for (int i = 0; i < width+2; i++)
            cout << "#";
        cout << endl;
}


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

void setup () {
    map1.height = 20; // Altura do mapa
    map1.width = 20; // Largura do mapa
    enemy1.enemy_x = 10;
    enemy1.enemy_y = 0;
    enemy1.make_stronger(); // Os inimigos vão ficando mais fortes a cada nivel
    enemy2.enemy_x = 10;
    enemy2.enemy_y = -3;
    enemy2.make_stronger(); // Os inimigos vão ficando mais fortes a cada nivel
    enemy3.enemy_x = 10;
    enemy3.enemy_y = -6;
    enemy3.make_stronger(); // Os inimigos vão ficando mais fortes a cada nivel
    tower1.tower_x = 12;
    tower1.tower_y = 3;
    // O cristal possui uma posição fixa no mapa.
    crystal.crystal_x = 10;
    crystal.crystal_y = 19;

}


int main ()
{
    int thereisgame = true; // Inicialmente, há jogo até que você perca o jogo.
    int counter(26); // Um auxiliar que será usado para saber quando um nivel acaba
    pinsetup();
    while (thereisgame) // Enquanto houver jogo.
    {
    if (counter>25) { // Inicia um novo nivel
        counter = 0; // Zera o contador
        setup(); // Seta os valores iniciais novamente, mas faz os inimigos ficarem mais poderosos
    }
    // INICIO DO JOGO
    map1.draw(); // Mostra o mapa
    usleep(100000); // Faz uma micro-pausa
    enemy1.move(); // Move o inimigo 1. O mesmo para as linhas abaixo
    enemy2.move();
    enemy3.move();
    counter++; // Aumenta o contador. Quando chegar a 26, o nivel acaba.
    // Se um inimigo colidir com o crystal, o crystal perderá saúde
    if ( enemy1.enemy_y == crystal.crystal_y or enemy2.enemy_y == crystal.crystal_y
        or enemy3.enemy_y == crystal.crystal_y) // Se o inimigo atingir o cristal...
    {
        crystal.health = crystal.health - enemy1.health; // O cristal perde pontos de saúde equivalentes aos pontos
        // de saúde do inimigo
    }
    if (crystal.health <= 0) // Detectar se o cristal foi destruído
    {
        thereisgame = false; // Caso o crystal tenha sido destruído, o jogo acaba.
        cout << "GAME OVER!"; // Mostra na tela que o jogo acabou.
    }
    // FIM DO JOGO
    }
}
