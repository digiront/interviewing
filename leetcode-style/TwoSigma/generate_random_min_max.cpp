// Example program
#include <iostream>
#include <string>
#include <random>

using namespace std;
int randomGen(int min, int max)
{
	int range = max-min + 1;
	return rand()%range + min;
}

int betterRandomGen(int min, int max) {
    static random_device rd; // obtain a random number from hardware
    static default_random_engine eng(rd()); // seed the generator
    uniform_int_distribution<> dist(min, max); // generate a number between 0 and N
    return dist(eng);
}

int main()
{
    cout << randomGen(0, 10) << endl;
    cout << betterRandomGen(0, 10) << endl;
    cout << "Done." << endl;
    return 0;
}
