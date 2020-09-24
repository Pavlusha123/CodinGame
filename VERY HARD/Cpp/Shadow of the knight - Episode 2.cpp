#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

void CheckCoords(int curIndex, int firstIndex, int lastIndex, bool& IndexFound, string& bombDir)
{
    if (firstIndex == lastIndex)
    {
        IndexFound = true;
        bombDir = "UNKNOWN";
    }
};

void Step(int& curIndex, int& firstIndex, int& lastIndex, bool& direction, queue<int>& Coords, bool& IndexFound, string bombDir, bool outsideBounds, int Bound)
{
    if (curIndex == lastIndex || curIndex - firstIndex > lastIndex - curIndex)
    {
        direction = false;
    }
    if (curIndex == firstIndex || curIndex - firstIndex < lastIndex - curIndex)
    {
        direction = true;
    }
    if (curIndex == lastIndex && curIndex == firstIndex)
    {
        IndexFound = true;
    }
    int prevIndex = curIndex;
    if (!IndexFound)
    {
        if (curIndex == lastIndex)
        {
            curIndex = (firstIndex + lastIndex) / 2;
        }
        else if (curIndex == firstIndex)
        {
            curIndex = int(ceil((firstIndex + lastIndex) / 2.0));
        }
        else
        {
            if ((firstIndex + lastIndex) % 2 == 0) curIndex = firstIndex + lastIndex - curIndex;
            else curIndex = firstIndex + lastIndex - curIndex + 1;
            if (curIndex < 0) curIndex = 0;
            if (curIndex > Bound) curIndex = Bound;

        }
        if (curIndex == prevIndex && curIndex < lastIndex) curIndex++;
        if (curIndex == prevIndex && curIndex > firstIndex) curIndex--;
        outsideBounds = false;
    }
    Coords.push(curIndex);
};

void BinarySearch(int& curIndex, int& firstIndex, int& lastIndex, bool& direction, queue<int>& Coords, bool& IndexFound, string bombDir, bool& outsideBounds)
{
    int prevIndex = Coords.front();
    Coords.pop();
    int midIndex = prevIndex + curIndex;
    if (curIndex > prevIndex)
    {
        if (bombDir == "WARMER")
        {
            firstIndex = int(ceil((midIndex) / 2.0));
            if (midIndex % 2 == 0) firstIndex++;
        }
        if (bombDir == "COLDER")
        {
            lastIndex = (midIndex) / 2;
            if (midIndex % 2 == 0) lastIndex--;
        }
        if (bombDir == "SAME")
        {
            firstIndex = (midIndex) / 2;
            lastIndex = firstIndex;
            curIndex--;
        }
    }
    else
    {
        if (bombDir == "WARMER")
        {
            lastIndex = (midIndex) / 2;
            if (midIndex % 2 == 0) lastIndex--;
        }
        if (bombDir == "COLDER")
        {
            firstIndex = int(ceil((midIndex) / 2.0));
            if (midIndex % 2 == 0) firstIndex++;
        }
        if (bombDir == "SAME")
        {
            firstIndex = (midIndex) / 2;
            lastIndex = firstIndex;
            curIndex++;
        }
    }
    if (curIndex > lastIndex || curIndex < firstIndex) outsideBounds = true;
};

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
    int firstX = 0;
    int firstY = 0;
    int lastX = W - 1;
    int lastY = H - 1;
    bool Xfound = false;
    bool Yfound = false;
    queue <int> XCoords;
    queue <int> YCoords;
    XCoords.push(X0);
    YCoords.push(Y0);
    YCoords.push(Y0);
    bool outsideBounds = false;
    string XbombDir = "UNKNOWN";
    string YbombDir = "UNKNOWN";
    int curStep = 0;
    bool Xdirection = true; //true - asc; false - desc
    bool Ydirection = true; //true - asc; false - desc


    while (1) {
        string bombDir; // Current distance to the bomb compared to previous distance (COLDER, WARMER, SAME or UNKNOWN)
        cin >> bombDir; cin.ignore();

        CheckCoords(X0, firstX, lastX, Xfound, XbombDir);
        CheckCoords(Y0, firstY, lastY, Yfound, YbombDir);

        if (curStep == 0)
        {
            YbombDir = bombDir;
            if (!Yfound)
            {
                BinarySearch(Y0, firstY, lastY, Ydirection, YCoords, Yfound, YbombDir, outsideBounds);
            }
            CheckCoords(X0, firstX, lastX, Xfound, XbombDir);
            if (!Xfound)
            {
                Step(X0, firstX, lastX, Xdirection, XCoords, Xfound, XbombDir, outsideBounds, W - 1);
            }
            else
            {
                curStep++;
            }
        }
        if (curStep == 1)
        {
            XbombDir = bombDir;
            if (!Xfound)
            {
                BinarySearch(X0, firstX, lastX, Xdirection, XCoords, Xfound, XbombDir, outsideBounds);
            }
            CheckCoords(Y0, firstY, lastY, Yfound, YbombDir);
            if (!Yfound)
            {
                Step(Y0, firstY, lastY, Ydirection, YCoords, Yfound, YbombDir, outsideBounds, H - 1);
            }
            else
            {
                curStep++;
            }
        }

        if (Xfound && Yfound)
        {
            X0 = firstX;
            Y0 = firstY;
        }
        curStep++;
        if (curStep == 2) curStep = 0;

        cout << X0 << " " << Y0 << endl;
    }
}

