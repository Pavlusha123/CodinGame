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
        //Очередь для хранения предыдущих координат
        Queue<int> coordsX = new Queue<int>();
        Queue<int> coordsY = new Queue<int>();
        coordsX.Enqueue(X0);
        coordsY.Enqueue(Y0);
        int previousX;
        int previousY;
        int firstW = 0;
        int firstH = 0;

        while (true)
        {
            string bombDir = Console.ReadLine(); // the direction of the bombs from batman's current location (U, UR, R, DR, D, DL, L or UL)
            coordsX.Enqueue(X0);
            coordsY.Enqueue(Y0);
            previousX = coordsX.Dequeue();
            previousY = coordsY.Dequeue();


            if (bombDir.Contains('L'))
            {
                W = X0;
                BinarySearching(ref X0, previousX, firstW);
            }

            if (bombDir.Contains('U'))
            {
                H = Y0;
                BinarySearching(ref Y0, previousY, firstH);
            }

            if (bombDir.Contains('R'))
            {
                firstW = X0;
                BinarySearching(ref X0, previousX, W);
            }

            if (bombDir.Contains('D'))
            {
                firstH = Y0;
                BinarySearching(ref Y0, previousY, H);
            }

            // the location of the next window Batman should jump to.
            Console.WriteLine($"{X0} {Y0}");
        }

        void BinarySearching(ref int index, int previousIndex, int lastIndex)
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
    }
}