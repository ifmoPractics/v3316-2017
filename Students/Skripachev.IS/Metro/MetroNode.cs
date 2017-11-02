using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Resources;
using System.Windows.Shapes;


namespace Metro
{
   
    class MetroNode : Button
    {
        public class NodesLine
        {
            public Line line = null;
            public int index;
            public MetroNode node2 = null;
            public Brush LineColor { get; set; }
        }

        public const int max_lines = 5;
        NodesLine[] lines = new NodesLine[max_lines];
        public Label nameNode = new Label();
        public Brush NodeColor { get; set; }
        

        //------------------------------dangerous--------------------------------
        public MetroNode Parent { get; set; }
        public int Cost { get; set; }
        public bool Visited { get; set; }
        //------------------------------dangerous--------------------------------

        public MetroNode(double w, double h, Brush color, Label name)
        {
            Width = w;
            Height = h;



            Uri resourceUri = new Uri("Images/if_78_Circle-Full_106138.png", UriKind.Relative);
            StreamResourceInfo streamInfo = Application.GetResourceStream(resourceUri);
            BitmapFrame temp = BitmapFrame.Create(streamInfo.Stream);
            var brush = new ImageBrush();
            brush.ImageSource = temp;
            Background = color;
            NodeColor = color;
            nameNode = name;
            BorderBrush = null;
            OpacityMask = brush;

            for (int i=0; i < max_lines; i++)
            {
                lines[i] = new NodesLine();
            }
        }

        //добавление линий связи
        public bool AddLine(Line l, int ind, MetroNode n2, Brush color)
        {
            for (int i = 0; i < max_lines; i++)
            {
                if (lines[i].line == null)
                {
                    lines[i].line = l;
                    lines[i].index = ind;
                    lines[i].node2 = n2;
                    return true;
                }
            }
            return false;
        }

        //Удаление линии
        public Line[] DeleteLine()
        {
            Line[] temp = new Line[max_lines];
            for (int i = 0; i < max_lines; i++)
            {
                if (lines[i].line != null)
                {
                    temp[i] = lines[i].line;
                    for (int j = 0; j < max_lines; j++)
                    {
                        if (lines[i].node2.lines[j].line == lines[i].line)
                            lines[i].node2.lines[j].line = null;
                    }
                    lines[i].line = null;
                }
            }
            return temp;
        }

        //Удаление линии
        public Line[] DeleteLine2(ref Search search)
        {
            Line[] temp = new Line[max_lines];
            for (int i = 0; i < max_lines; i++)
            {
                if (lines[i].line != null)
                {
                    temp[i] = lines[i].line;
                    for (int j = 0; j < max_lines; j++)
                    {
                        if (lines[i].node2.lines[j].line == lines[i].line)
                        {
                            lines[i].node2.lines[j].line = null;
                            search.DeleteElem(this, lines[i].node2);
                        }
                    }
                    lines[i].line = null;
                }
            }
            return temp;
        }

        //Удаление линии
        public bool DeleteOnlyLine(Line l)
        {
            for(int i=0; i< max_lines; i++)
            {
                if (lines[i].line == l)
                {

                    lines[i].line = null;
                    return true;
                }
            }
            return false;
        }

        public bool DeleteOnlyLine2(Line l, ref Search search)
        {
            for (int i = 0; i < max_lines; i++)
            {
                if (lines[i].line == l)
                {
                    search.DeleteElem(this, lines[i].node2);
                    lines[i].line = null;
                    return true;
                }
            }
            return false;
        }

        //Количество линий
        public int CountLines()
        {
            int count = 0;
            for (int i = 0; i < max_lines; i++)
            {
                if (lines[i].line != null)
                {
                    count++;
                }
            }
            return count;
        }

        //перерисовка соединений при движении станций
        public void ReDrawLine(double x, double y)
        {
            for (int i = 0; i < max_lines; i++)
            {
                if (lines[i].line != null)
                {
                    if(lines[i].index == 1)
                    {
                        lines[i].line.X1 = x;
                        lines[i].line.Y1 = y;
                    }
                    else
                    {
                        lines[i].line.X2 = x;
                        lines[i].line.Y2 = y;
                    }
                }
            }
        }
    }
}
