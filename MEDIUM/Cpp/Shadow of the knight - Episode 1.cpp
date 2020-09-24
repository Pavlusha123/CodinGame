#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>

using namespace std;

void BinarySearch(int& index, int lastIndex)
{
    if (lastIndex > index)
    {
        index = ceil((index + lastIndex) / 2.0);
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

    queue<int> coordsX;
    queue<int> coordsY;
    int previousX;
    int previousY;
    int firstW = 0;
    int firstH = 0;
    while (1) {
        string bombDir; // the direction of the bombs from batman's current location (U, UR, R, DR, D, DL, L or UL)
        cin >> bombDir; cin.ignore();

        if (bombDir.find("L") != string::npos)
        {
            W = X0;
            BinarySearch(X0, firstW);
        }

        if (bombDir.find("U") != string::npos)
        {
            H = Y0;
            BinarySearch(Y0, firstH);
        }

        if (bombDir.find("R") != string::npos)
        {
            firstW = X0;
            BinarySearch(X0, W);
        }

        if (bombDir.find("D") != string::npos)
        {
            firstH = Y0;
            BinarySearch(Y0, H);
        }

        cout << X0 << " " << Y0 << endl;
    }
}