using System;
using System.Linq;
using System.IO;
using System.Text;
using System.Collections;
using System.Collections.Generic;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
class Player
{
    static void Main(string[] args)
    {
        string[] inputs;
        inputs = Console.ReadLine().Split(' ');
        int W = int.Parse(inputs[0]); // width of the building.
        int H = int.Parse(inputs[1]); // height of the building.
        int N = int.Parse(Console.ReadLine()); // maximum number of turns before game over.
        inputs = Console.ReadLine().Split(' ');
        int X0 = int.Parse(inputs[0]);
        int Y0 = int.Parse(inputs[1]);

        // game loop
        // Координаты текущих границ поиска
        int firstX = 0;
        int firstY = 0;
        int lastX = W - 1;
        int lastY = H - 1;
        bool Xfound = false;
        bool Yfound = false;
        Queue<int> XCoords = new Queue<int>();
        Queue<int> YCoords = new Queue<int>();
        XCoords.Enqueue(X0);
        YCoords.Enqueue(Y0);
        YCoords.Enqueue(Y0);
        bool outsideBounds = false;
        string XbombDir = "UNKNOWN";
        string YbombDir = "UNKNOWN";
        byte curStep = 0;
        bool Xdirection = true; //true - asc; false - desc
        bool Ydirection = true; //true - asc; false - desc
        while (true)
        {
            string bombDir = Console.ReadLine(); // Current distance to the bomb compared to previous distance (COLDER, WARMER, SAME or UNKNOWN)
            Console.Error.WriteLine($"{bombDir}");
            Console.Error.WriteLine($"X {firstX} {X0} {lastX}");
            Console.Error.WriteLine($"Y {firstY} {Y0} {lastY}");

            CheckCoords(X0, firstX, lastX, ref Xfound, ref XbombDir);
            CheckCoords(Y0, firstY, lastY, ref Yfound, ref YbombDir);

            if (curStep == 0)
            {
                YbombDir = bombDir;
                if (!Yfound)
                {
                    BinarySearch(ref Y0, ref firstY, ref lastY, ref Ydirection, ref YCoords, ref Yfound, YbombDir, ref outsideBounds);
                }
                CheckCoords(X0, firstX, lastX, ref Xfound, ref XbombDir);
                if (!Xfound)
                {
                    Console.Error.WriteLine($"Xturn");
                    Step(ref X0, ref firstX, ref lastX, ref Xdirection, ref XCoords, ref Xfound, XbombDir, outsideBounds, W - 1);
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
                    BinarySearch(ref X0, ref firstX, ref lastX, ref Xdirection, ref XCoords, ref Xfound, XbombDir, ref outsideBounds);
                }
                CheckCoords(Y0, firstY, lastY, ref Yfound, ref YbombDir);
                if (!Yfound)
                {
                    Console.Error.WriteLine($"Yturn");
                    Step(ref Y0, ref firstY, ref lastY, ref Ydirection, ref YCoords, ref Yfound, YbombDir, outsideBounds, H - 1);
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
            Console.Error.WriteLine($"X {firstX} {X0} {lastX}");
            Console.Error.WriteLine($"Y {firstY} {Y0} {lastY}");

            Console.Error.WriteLine($"X {XbombDir}");
            Console.Error.WriteLine($"Y {YbombDir}");

            curStep++;
            if (curStep == 2) curStep = 0;
            Console.Error.WriteLine($"Xfound:{Xfound} Yfound:{Yfound}");
            Console.WriteLine($"{X0} {Y0}");
        }

        static void Step(ref int curIndex, ref int firstIndex, ref int lastIndex, ref bool direction, ref Queue<int> Coords, ref bool IndexFound, string bombDir, bool outsideBounds, int Bound)
        {
            Console.Error.WriteLine($"dir {direction}");
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
            Console.Error.WriteLine($"outside {outsideBounds}");
            if (!IndexFound)
            {
                if (curIndex == lastIndex)
                {
                    curIndex = (firstIndex + lastIndex) / 2;
                }
                else if (curIndex == firstIndex)
                {
                    curIndex = (int)Math.Ceiling((firstIndex + lastIndex) / 2.0);
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
            Console.Error.WriteLine($"dir {direction}");
            Coords.Enqueue(curIndex);
        }

        static void BinarySearch(ref int curIndex, ref int firstIndex, ref int lastIndex, ref bool direction, ref Queue<int> Coords, ref bool IndexFound, string bombDir, ref bool outsideBounds)
        {
            int prevIndex = Coords.Dequeue();
            int midIndex = prevIndex + curIndex;
            Console.Error.WriteLine($"bin dir {direction}");
            Console.Error.WriteLine($"prev {midIndex} cur {curIndex}");
            if (curIndex > prevIndex)
            {
                switch (bombDir)
                {
                    case "WARMER":
                        firstIndex = (int)Math.Ceiling((midIndex) / 2.0);
                        if (midIndex % 2 == 0) firstIndex++;
                        //curIndex = (int)Math.Ceiling((curIndex + lastIndex) / 2.0);
                        break;

                    case "COLDER":
                        lastIndex = (midIndex) / 2;
                        if (midIndex % 2 == 0) lastIndex--;
                        //curIndex = (prevIndex + firstIndex) / 2;
                        //direction = false;
                        break;

                    case "SAME":
                        //IndexFound = true;
                        firstIndex = (midIndex) / 2;
                        lastIndex = firstIndex;
                        curIndex--;
                        break;
                }
            }
            else
            {
                switch (bombDir)
                {
                    case "WARMER":
                        lastIndex = (midIndex) / 2;
                        if (midIndex % 2 == 0) lastIndex--;
                        //curIndex = (curIndex + firstIndex) / 2;
                        break;

                    case "COLDER":
                        firstIndex = (int)Math.Ceiling((midIndex) / 2.0);
                        if (midIndex % 2 == 0) firstIndex++;
                        //curIndex = (int)Math.Ceiling((prevIndex + lastIndex) / 2.0);
                        //direction = true;
                        break;

                    case "SAME":
                        //IndexFound = true;
                        firstIndex = (midIndex) / 2;
                        lastIndex = firstIndex;
                        curIndex++;
                        break;
                }
            }
            if (curIndex > lastIndex || curIndex < firstIndex) outsideBounds = true;
        }

        static void CheckCoords(int curIndex, int firstIndex, int lastIndex, ref bool IndexFound, ref string bombDir)
        {
            if (firstIndex == lastIndex)
            {
                IndexFound = true;
                bombDir = "UNKNOWN";
            }
        }
    }
}