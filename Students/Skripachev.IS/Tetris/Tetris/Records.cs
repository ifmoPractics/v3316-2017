using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Serialization.Formatters.Binary;
using System.IO;
using System.Windows;

namespace Tetris
{
    class Records
    {
        const int countOfRecords = 3;
        uint[] records = new uint[countOfRecords];

        public Records()
        {
            for (int i = 0; i < countOfRecords; i++)
            {
                records[i] = 0;
            }
        }

        public void Load()
        {
            BinaryFormatter form = new BinaryFormatter();
            if (File.Exists("Records.txt"))
            {
                using (FileStream input = File.Open("Records.txt", FileMode.OpenOrCreate))
                {

                    records = (uint[])form.Deserialize(input);
                }
            }
        }

        void Swap(ref uint t1, ref uint t2)
        {
            uint temp = t1;
            t1 = t2;
            t2 = temp;
        }

        public void Save(uint rec = 0)
        {
            for (int i = 0; i < countOfRecords; i++)
            {
                if (rec > records[i])
                {
                    Swap(ref rec, ref records[i]);
                }
            }
            BinaryFormatter form = new BinaryFormatter();
            using (FileStream output = File.Open("Records.txt",FileMode.Create))
            {
                form.Serialize(output, records);
            }
        }

        public string GetRecString()
        {
            string result="";
            for (int i = 0; i < countOfRecords; i++)
            {
                result += String.Format("Place {0}:   {1}\n", i + 1, records[i]);
            }
            return result;
        }
    }

    //[Serializable]
    //public class Dog
    //{
    //    public int t = 2;
    //    public string name = "Kek";
    //    public Random random = new Random();
    //    public Figure currentFigure;
    //    public Point[,] figField;
    //    public event EventHandler EGameOver;
    //    public FigureType[,] field = new FigureType[5, 6];
    //}
}
