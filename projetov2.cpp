#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <windows.h> // unistd.h no LINUX

using namespace std;

// Classe torre com as suas propriedades

class tower {
    tower(int tower_x, int tower_y){
            this->tower_x = tower_x;
            this->tower_y = tower_y;
    }
protected:
    int tower_x; // Posição x no mapa
    int tower_y; // Posição y no mapa
    int fire_speed = 1;
    int range = 2; // Alance do tiro
}; // Inicialmente, você só tem uma torre disponivel para atacar os inimigos

// Classe inimigo e suas propriedades

class enemy {
public:
    enemy () {health = 0;} // Os inimigos começam com 0 de saude
    int enemy_x; // Posição x do inimigo no mapa
    int enemy_y; // Posição y do inimigo no mapa
    int moving_speed;
    int health; // Saude do inimigo
    void make_stronger() {health++;} // Os inimigos vão ficando mais fortes a cada nivel
    void move () {enemy_y++;} // Move o inimigo em direção ao cristal
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

class map : public tower, public enemy, public Crystal {
public:
    int width; // Tamanho da largura do mapa
    int height; // Tamanho da altura do mapa
    int x;
    int y;
    void draw(); // É dentro desta função que todo o desenho do jogo ocorre
} map1;

// A função abaixo desenha o estado do jogo a cada intervalo de tempo (menos de 1 segundo)
void map::draw()
{
    system("cls");
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

    while (thereisgame) // Enquanto houver jogo.
    {
    if (counter>25) { // Inicia um novo nivel
        counter = 0; // Zera o contador
        setup(); // Seta os valores iniciais novamente, mas faz os inimigos ficarem mais poderosos
    }
    // INICIO DO JOGO
    map1.draw(); // Mostra o mapa
    Sleep(100); // Faz uma micro-pausa
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
