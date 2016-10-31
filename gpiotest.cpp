#include "GPIOClass.h"
 
using namespace std;

int main(){
	GPIOClass* gpio3 = new GPIOClass("3"); // inimigo 1
	GPIOClass* gpio5 = new GPIOClass("5"); // inimigo 2
	GPIOClass* gpio7 = new GPIOClass("7"); // inimigo 3
	GPIOClass* gpio11 = new GPIOClass("11"); // inimigo 4
	GPIOClass* gpio12 = new GPIOClass("12"); // inimigo 5
	GPIOClass* gpio13 = new GPIOClass("13"); // inimigo 6
	GPIOClass* gpio15 = new GPIOClass("15"); // inimigo 7
	GPIOClass* gpio16 = new GPIOClass("16"); // inimigo 8
	GPIOClass* gpio18 = new GPIOClass("18"); // inimigo 9
	GPIOClass* gpio19 = new GPIOClass("19"); // torre 4 (encontra-se em frente ao inimigo 8)
	GPIOClass* gpio21 = new GPIOClass("21"); // torre 3 (encontra-se em frente ao inimigo 6)
	GPIOClass* gpio22 = new GPIOClass("22"); // torre 2 (encontra-se em frente ao inimigo 4)
	GPIOClass* gpio23 = new GPIOClass("23"); // torre 1 (encontra-se em frente ao inimigo 2)
	GPIOClass* gpio40 = new GPIOClass("40");
	gpio3->setdir_gpio("out");
	gpio5->setdir_gpio("out");
	gpio7->setdir_gpio("out");
	gpio11->setdir_gpio("out");
	gpio12->setdir_gpio("out");
	gpio13->setdir_gpio("out");
	gpio15->setdir_gpio("out");
	gpio16->setdir_gpio("out");
	gpio18->setdir_gpio("out");
	gpio19->setdir_gpio("out");
	gpio21->setdir_gpio("out");
	gpio22->setdir_gpio("out");
	gpio23->setdir_gpio("out");
	gpio40->setdir_gpio("out");
	while(true){
		gpio3->setval_gpio("1");
	}
}