/*
 * 26/05/2016
 * 
 * Course work of a friend of mine.
 */

using System;

namespace kris
{
    class Program
    {
        static void Main(string[] args)
        {
            double[,] grades = new double[10, 3];
            for (int i = 0; i < 10; i++)
            { 
                for (int j = 0; j < 3; j++)
                {
                    Console.WriteLine("Molq vuvedete ocenka {0} na uchenik {1}: ", j, i);
                    Double.TryParse(Console.ReadLine(), out grades[i, j]);
                }
            }

            double grade;
            for (int i = 0; i < 10; i++)
            {
                grade = (grades[i, 0] + grades[i, 1] + grades[i, 2]) / 3.0f;
                Console.WriteLine("Srednata ocenka na uchenik {0} e {1}.", i, grade.ToString("0.00"));
            }

            Console.Write("Natisnete buton za da izlezete ot programata...");
            Console.ReadKey();
        }
    }
}
