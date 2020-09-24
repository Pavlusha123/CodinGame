#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

void BinarySearch(int& index, int previousIndex, int lastIndex)
{
    if (((index > previousIndex) && (index > lastIndex)) || ((index < previousIndex) && (index < lastIndex)))
    {
        index = (index + previousIndex) / 2;
    }
    else
    {
        index = (index + lastIndex) / 2;
    }
}

int main()
{
    int W; // width of the building.
    int H; // height of the building.
    cin >> W >> H; cin.ignore();
    int N; // maximum number of turns before game over.
    cin >> N; cin.ignore();
    int X0;
    int Y0;
    cin >> X0 >> Y0; cin.ignore();

    // game loop
    //Очередь для хранения предыдущих координат
    queue<int> coordsX;
    queue<int> coordsY;
    coordsX.push(X0);
    coordsY.push(Y0);
    int previousX;
    int previousY;
    int firstW = 0;
    int firstH = 0;
    while (1) {
        string bombDir; // the direction of the bombs from batman's current location (U, UR, R, DR, D, DL, L or UL)
        cin >> bombDir; cin.ignore();

        coordsX.push(X0);
        coordsY.push(Y0);
        previousX = coordsX.front(); coordsX.pop();
        previousY = coordsY.front(); coordsY.pop();


        if (bombDir.find("L") != string::npos)
        {
            W = X0;
            BinarySearch(X0, previousX, firstW);
        }

        if (bombDir.find("U") != string::npos)
        {
            H = Y0;
            BinarySearch(Y0, previousY, firstH);
        }

        if (bombDir.find("R") != string::npos)
        {
            firstW = X0;
            BinarySearch(X0, previousX, W);
        }

        if (bombDir.find("D") != string::npos)
        {
            firstH = Y0;
            BinarySearch(Y0, previousY, H);
        }

        cout << X0 << " " << Y0 << endl;
    }
}