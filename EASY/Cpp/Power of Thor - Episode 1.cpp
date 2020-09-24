#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void CheckCoord(int lightCoord, int& thorCoord, string forward, string backward, string& direction)
{
    if (lightCoord == thorCoord) { return; }
    else if (lightCoord < thorCoord) { direction += backward; thorCoord--; }
    else if (lightCoord > thorCoord) { direction += forward; thorCoord++; }
}

int main()
{
    int lightX; // the X position of the light of power
    int lightY; // the Y position of the light of power
    int initialTX; // Thor's starting X position
    int initialTY; // Thor's starting Y position
    cin >> lightX >> lightY >> initialTX >> initialTY; cin.ignore();

    string Direction;
    while (1) {
        int remainingTurns; // The remaining amount of turns Thor can move. Do not remove this line.
        cin >> remainingTurns; cin.ignore();

        Direction = "";
        CheckCoord(lightY, initialTY, "S", "N", Direction);
        CheckCoord(lightX, initialTX, "E", "W", Direction);

        cout << Direction << endl;
    }
}