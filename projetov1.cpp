#include <iostream>
#include <cstdlib>
#include <stdlib.h>
//#include <conio.h>
#include <unistd.h>// no LINUX

using namespace std;


class tower {
public:
    int tower_x;
    int tower_y;
    int fire_speed;
    int range;
}tower1;

class enemy {
public:
    int enemy_x;
    int enemy_y;
    int moving_speed;
    int health;
    void move () {enemy_y++;}
} enemy1, enemy2, enemy3;

class Crystal {
public:
    int crystal_x;
    int crystal_y;
    int health;

} crystal;


class map : public tower, public enemy, public Crystal {
public:
    int width;
    int height;
    int x;
    int y;
    void draw();
} map1;

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
                        and enemy1.enemy_y!=crystal.crystal_y)
                        cout << "*";
                    else if (i==tower1.tower_x and j==tower1.tower_y)
                        cout << "_";
                    else if (i==crystal.crystal_x and j==crystal.crystal_y)
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


void setup () {
    map1.height = 20;
    map1.width = 20;
    enemy1.enemy_x = 10;
    enemy1.enemy_y = 0;
    enemy2.enemy_x = 10;
    enemy2.enemy_y = -20;
    enemy3.enemy_x = 10;
    enemy3.enemy_y = -40;
    tower1.tower_x = 12;
    tower1.tower_y = 3;
    crystal.crystal_x = 10;
    crystal.crystal_y = 19;
    crystal.health = 3;

}


int main ()
{
    setup();
    int thereisgame = true;

    while (thereisgame)
    {
    map1.draw();
    usleep(100000);
    enemy1.move();
    enemy2.move();
    enemy3.move();
    // Se um inimigo colidir com o crystal, o crystal perderá saúde
    if ( enemy1.enemy_y == crystal.crystal_y or enemy2.enemy_y == crystal.crystal_y
        or enemy3.enemy_y == crystal.crystal_y)
    {
        crystal.health--;
    }
    // detectar se o cristal foi destruído
    if (crystal.health == 0)
    {
        cout << "GAME OVER!";
        thereisgame = false;
    }
    }
}
