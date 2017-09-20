using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tetris
{
    [Serializable]
    public struct Point :ICloneable
    {
        public int x;
        public int y;

        public Point(int X,int Y)
        {
            x = X;
            y = Y;
        }

        public object Clone()
        {
            return new Point { x = this.x, y = this.y };
        }
    }

    [Serializable]
    public enum FigureType
    {
        I,
        T,
        O,
        Z,
        S,
        J,
        L,
        None,
        Current
    }

    [Serializable]
    public enum Direction
    {
        Left,
        Right,
        Down
    }

    [Serializable]
    public enum FigureCondition
    {
        Left,
        Right,
        Up,
        Down
    }

    [Serializable]
    public class Figure
    {
        public Point[,] fig = new Point[4, 4];
        public Point[,] tmpFig = new Point[4, 4];

        public FigureCondition condition;

        public Figure()
        {
            for(int i=0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    fig[i, j].x = -5;
                    fig[i, j].y = -5;
                }
            }
            condition = FigureCondition.Left;
        }

        public Point[,] GetFieldValue()
        {
            return fig;
        }

        public void Move(Direction dir)
        {
            switch (dir)
            {
                case Direction.Down:
                    {
                        for (int i = 0; i < 4; i++)
                        {
                            for (int j = 3; j >= 0; j--)
                            {
                                if (fig[i, j].x != -5 && fig[i, j].y != -5 )
                                    //if(fig[i, j].y < 14)
                                        fig[i, j].y++;
                                    //else return;
                                
                            }
                        }
                        break;
                    }
                case Direction.Right:
                    {
                        for (int i = 3; i >= 0; i--)
                        {
                            for (int j = 0; j < 4; j++)
                            {
                                if (fig[i, j].x != -5 && fig[i, j].y != -5)
                                    if (fig[i, j].x < 9)
                                        fig[i, j].x++;
                                    else return;
                            }
                        }
                        break;
                    }
                case Direction.Left:
                    {
                        for (int i = 0; i < 4; i++)
                        {
                            for (int j = 0; j < 4; j++)
                            {
                                if (fig[i, j].x != -5 && fig[i, j].y != -5 )
                                    if(fig[i, j].x > 0)
                                        fig[i, j].x--;
                                    else return;
                            }
                        }
                        break;
                    }
            }
        }

        public virtual void Rotate() { }

        public virtual Point[,] TryRotate()
        {
            return null;
        }

        //public void SetFieldEmpty()
        //{
        //    for (int i = 0; i < 4; i++)
        //    {
        //        for (int j = 0; j < 4; j++)
        //        {
        //            fig[i, j].x = -1;
        //            fig[i, j].y = -1;
        //        }
        //    }
        //}
    }

    [Serializable]
    public class FigureI :Figure
    {
        //Конструктор
        public FigureI(Point startPoint)
        {
            for (int i = 0; i < 4; i++)
            {
                base.fig[1, i] = startPoint;
                base.fig[1, i].y += i;
            }
            
        }

        //Вращение
        public override void Rotate()
        {

            switch (base.condition)
            {
                case FigureCondition.Left:
                    {
                        base.fig[3, 1] = new Point(base.fig[1, 3].x + 2, base.fig[1, 3].y - 2);
                        base.fig[1, 3] = new Point(-5, -5);

                        base.fig[2, 1] = new Point(base.fig[1, 2].x + 1, base.fig[1, 2].y - 1);
                        base.fig[1, 2] = new Point(-5, -5); 

                        base.fig[0, 1] = new Point(base.fig[1, 0].x - 1, base.fig[1, 0].y + 1);
                        base.fig[1, 0] = new Point(-5, -5);

                        base.condition = FigureCondition.Up;
                        //return base.tmpFig;
                        break;
                    }
                case FigureCondition.Up:
                    {
                        base.fig[2, 0] = new Point(base.fig[3, 1].x - 1, base.fig[3, 1].y - 1);
                        base.fig[3, 1] = new Point(-5, -5);

                        base.fig[2, 2] = new Point(base.fig[1, 1].x + 1, base.fig[1, 1].y + 1);
                        base.fig[1, 1] = new Point(-5, -5);

                        base.fig[2, 3] = new Point(base.fig[0, 1].x + 2, base.fig[0, 1].y + 2);
                        base.fig[0, 1] = new Point(-5, -5);

                        base.condition = FigureCondition.Right;
                        //return base.tmpFig;
                        break;
                    }
                case FigureCondition.Right:
                    {
                        base.fig[0, 2] = new Point(base.fig[2, 0].x - 2, base.fig[2, 0].y + 2);
                        base.fig[2, 0] = new Point(-5, -5);

                        base.fig[1, 2] = new Point(base.fig[2, 1].x - 1, base.fig[2, 1].y + 1);
                        base.fig[2, 1] = new Point(-5, -5);

                        base.fig[3, 2] = new Point(base.fig[2, 3].x + 1, base.fig[2, 3].y - 1);
                        base.fig[2, 3] = new Point(-5, -5);

                        base.condition = FigureCondition.Down;
                        //return base.tmpFig;
                        break;
                    }
                case FigureCondition.Down:
                    {
                        base.fig[1, 0] = new Point(base.fig[3, 2].x - 2, base.fig[3, 2].y - 2);
                        base.fig[3, 2] = new Point(-5, -5);

                        base.fig[1, 1] = new Point(base.fig[2, 2].x - 1, base.fig[2, 2].y - 1);
                        base.fig[2, 2] = new Point(-5, -5);

                        base.fig[1, 3] = new Point(base.fig[0, 2].x + 1, base.fig[0, 2].y + 1);
                        base.fig[0, 2] = new Point(-5, -5);

                        base.condition = FigureCondition.Left;
                        //return base.tmpFig;
                        break;
                    }
            }

                    //switch (base.condition)
                    //{
                    //    case FigureCondition.Left:
                    //        {
                    //            base.fig = (Point[,])TryRotate().Clone();
                    //            base.condition = FigureCondition.Up;
                    //            break;
                    //        }
                    //    case FigureCondition.Up:
                    //        {
                    //            base.fig = (Point[,])TryRotate().Clone();
                    //            base.condition = FigureCondition.Right;
                    //            break;
                    //        }
                    //    case FigureCondition.Right:
                    //        {
                    //            base.fig = (Point[,])TryRotate().Clone();
                    //            base.condition = FigureCondition.Down;
                    //            break;
                    //        }
                    //    case FigureCondition.Down:
                    //        {
                    //            base.fig = (Point[,])TryRotate().Clone();
                    //            base.condition = FigureCondition.Left;
                    //            break;
                    //        }
                    //}
        }

        //Попытка вращения
        public override Point[,] TryRotate()
        {

            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    base.tmpFig[i, j].x = -5;
                    base.tmpFig[i, j].y = -5;
                }
            }
            switch (base.condition)
            {
                case FigureCondition.Left:
                    {
                        base.tmpFig[3, 1] = new Point(base.fig[1, 3].x + 2, base.fig[1, 3].y - 2);
                        base.tmpFig[1, 3] = new Point(-5, -5);

                        base.tmpFig[2, 1] = new Point(base.fig[1, 2].x + 1, base.fig[1, 2].y - 1);
                        base.tmpFig[1, 2] = new Point(-5, -5);

                        base.tmpFig[0, 1] = new Point(base.fig[1, 0].x - 1, base.fig[1, 0].y + 1);
                        base.tmpFig[1, 0] = new Point(-5, -5);

                        //base.condition = FigureCondition.Up;
                        return base.tmpFig;
                        //break;
                    }
                case FigureCondition.Up:
                    {
                        base.tmpFig[2, 0] = new Point(base.fig[3, 1].x - 1, base.fig[3, 1].y - 1);
                        base.tmpFig[3, 1] = new Point(-5, -5);

                        base.tmpFig[2, 2] = new Point(base.fig[1, 1].x + 1, base.fig[1, 1].y + 1);
                        base.tmpFig[1, 1] = new Point(-5, -5);

                        base.tmpFig[2, 3] = new Point(base.fig[0, 1].x + 2, base.fig[0, 1].y + 2);
                        base.tmpFig[0, 1] = new Point(-5, -5);

                        //base.condition = FigureCondition.Right;
                        return base.tmpFig;
                        //break;
                    }
                case FigureCondition.Right:
                    {
                        base.tmpFig[0, 2] = new Point(base.fig[2, 0].x - 2, base.fig[2, 0].y + 2);
                        base.tmpFig[2, 0] = new Point(-5, -5);

                        base.tmpFig[1, 2] = new Point(base.fig[2, 1].x - 1, base.fig[2, 1].y + 1);
                        base.tmpFig[2, 1] = new Point(-5, -5);

                        base.tmpFig[3, 2] = new Point(base.fig[2, 3].x + 1, base.fig[2, 3].y - 1);
                        base.tmpFig[2, 3] = new Point(-5, -5);

                        //base.condition = FigureCondition.Down;
                        return base.tmpFig;
                        //break;
                    }
                case FigureCondition.Down:
                    {
                        base.tmpFig[1, 0] = new Point(base.fig[3, 2].x - 2, base.fig[3, 2].y - 2);
                        base.tmpFig[3, 2] = new Point(-5, -5);

                        base.tmpFig[1, 1] = new Point(base.fig[2, 2].x - 1, base.fig[2, 2].y - 1);
                        base.tmpFig[2, 2] = new Point(-5, -5);

                        base.tmpFig[1, 3] = new Point(base.fig[0, 2].x + 1, base.fig[0, 2].y + 1);
                        base.tmpFig[0, 2] = new Point(-5, -5);

                        //base.condition = FigureCondition.Left;
                        return base.tmpFig;
                        //break;
                    }
                default:
                    return null;
            }
        }

    }

    [Serializable]
    public class FigureT : Figure
    {
        //Конструктор
        public FigureT(Point startPoint)
        {
            
            base.fig[1, 0] = startPoint;

            base.fig[1, 1].x = startPoint.x;
            base.fig[1, 1].y = startPoint.y+1;

            base.fig[1, 2].x = startPoint.x;
            base.fig[1, 2].y = startPoint.y + 2;

            base.fig[2, 1].x = startPoint.x + 1;
            base.fig[2, 1].y = startPoint.y + 1;
        }
        
        //Вращение
        public override void Rotate()
        {

            switch (base.condition)
            {
                case FigureCondition.Left:
                    {
                        base.fig[2, 0] = new Point(base.fig[1, 1].x + 1, base.fig[1, 1].y - 1);
                        base.fig[1, 1] = new Point(-5, -5);

                        base.fig[3, 0] = new Point(base.fig[1, 2].x + 2, base.fig[1, 2].y - 2);
                        base.fig[1, 2] = new Point(-5, -5);

                        base.condition = FigureCondition.Up;
                        //return base.tmpFig;
                        break;
                    }
                case FigureCondition.Up:
                    {
                        base.fig[3, 1] = new Point(base.fig[2, 0].x + 1, base.fig[2, 0].y + 1);
                        base.fig[2, 0] = new Point(-5, -5);

                        base.fig[3, 2] = new Point(base.fig[1, 0].x + 2, base.fig[1, 0].y + 2);
                        base.fig[1, 0] = new Point(-5, -5);

                        base.condition = FigureCondition.Right;
                        //return base.tmpFig;
                        break;
                    }
                case FigureCondition.Right:
                    {
                        base.fig[2, 2] = new Point(base.fig[3, 1].x - 1, base.fig[3, 1].y + 1);
                        base.fig[3, 1] = new Point(-5, -5);

                        base.fig[1, 2] = new Point(base.fig[3, 0].x - 2, base.fig[3, 0].y + 2);
                        base.fig[3, 0] = new Point(-5, -5);

                        base.condition = FigureCondition.Down;
                        //return base.tmpFig;
                        break;
                    }
                case FigureCondition.Down:
                    {
                        base.fig[1, 1] = new Point(base.fig[2, 2].x - 1, base.fig[2, 2].y - 1);
                        base.fig[2, 2] = new Point(-5, -5);

                        base.fig[1, 0] = new Point(base.fig[3, 2].x - 2, base.fig[3, 2].y - 2);
                        base.fig[3, 2] = new Point(-5, -5);

                        base.condition = FigureCondition.Left;
                        //return base.tmpFig;
                        break;
                    }
            }

        }

        //Попытка вращения
        public override Point[,] TryRotate()
        {

            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    base.tmpFig[i, j].x = -5;
                    base.tmpFig[i, j].y = -5;
                }
            }
            switch (base.condition)
            {
                case FigureCondition.Left:
                    {
                        base.tmpFig[2, 0] = new Point(base.fig[1, 1].x + 1, base.fig[1, 1].y - 1);
                        base.tmpFig[1, 1] = new Point(-5, -5);

                        base.tmpFig[3, 0] = new Point(base.fig[1, 2].x + 2, base.fig[1, 2].y - 2);
                        base.tmpFig[1, 2] = new Point(-5, -5);

                        //base.condition = FigureCondition.Up;
                        return base.tmpFig;
                        //break;
                    }
                case FigureCondition.Up:
                    {
                        base.tmpFig[3, 1] = new Point(base.fig[2, 0].x + 1, base.fig[2, 0].y + 1);
                        base.tmpFig[2, 0] = new Point(-5, -5);

                        base.tmpFig[3, 2] = new Point(base.fig[1, 0].x + 2, base.fig[1, 0].y + 2);
                        base.tmpFig[1, 0] = new Point(-5, -5);

                        //base.condition = FigureCondition.Right;
                        return base.tmpFig;
                        //break;
                    }
                case FigureCondition.Right:
                    {
                        base.tmpFig[2, 2] = new Point(base.fig[3, 1].x - 1, base.fig[3, 1].y + 1);
                        base.tmpFig[3, 1] = new Point(-5, -5);

                        base.tmpFig[1, 2] = new Point(base.fig[3, 0].x - 2, base.fig[3, 0].y + 2);
                        base.tmpFig[3, 0] = new Point(-5, -5);

                        //base.condition = FigureCondition.Down;
                        return base.tmpFig;
                        //break;
                    }
                case FigureCondition.Down:
                    {
                        base.tmpFig[1, 1] = new Point(base.fig[2, 2].x - 1, base.fig[2, 2].y - 1);
                        base.tmpFig[2, 2] = new Point(-5, -5);

                        base.tmpFig[1, 0] = new Point(base.fig[3, 2].x - 2, base.fig[3, 2].y - 2);
                        base.tmpFig[3, 2] = new Point(-5, -5);

                        //base.condition = FigureCondition.Left;
                        return base.tmpFig;
                        //break;
                    }
                default:
                    return null;
            }
        }
    }

    [Serializable]
    public class FigureO : Figure
    {
        //Конструктор
        public FigureO(Point startPoint)
        {

            base.fig[1, 1] = startPoint;

            base.fig[1, 2].x = startPoint.x;
            base.fig[1, 2].y = startPoint.y + 1;

            base.fig[2, 1].x = startPoint.x + 1;
            base.fig[2, 1].y = startPoint.y;

            base.fig[2, 2].x = startPoint.x + 1;
            base.fig[2, 2].y = startPoint.y + 1;
        }

        //Вращение
        public override void Rotate()  {}

        //Попытка вращения
        public override Point[,] TryRotate() { return null; }
    }

    [Serializable]
    public class FigureZ : Figure
    {
        //Конструктор
        public FigureZ(Point startPoint)
        {

            base.fig[2, 0] = startPoint;

            base.fig[2, 1].x = startPoint.x;
            base.fig[2, 1].y = startPoint.y + 1;

            base.fig[1, 1].x = startPoint.x - 1;
            base.fig[1, 1].y = startPoint.y + 1;

            base.fig[1, 2].x = startPoint.x - 1;
            base.fig[1, 2].y = startPoint.y + 2;
        }

        //Вращение
        public override void Rotate()
        {

            switch (base.condition)
            {
                case FigureCondition.Left:
                    {
                        base.fig[1, 0] = new Point(base.fig[1, 1].x, base.fig[1, 1].y - 1);
                        base.fig[1, 1] = new Point(-5, -5);

                        base.fig[3, 1] = new Point(base.fig[1, 2].x + 2, base.fig[1, 2].y - 1);
                        base.fig[1, 2] = new Point(-5, -5);

                        base.condition = FigureCondition.Up;
                        //return base.tmpFig;
                        break;
                    }
                case FigureCondition.Up:
                    {
                        base.fig[1, 1] = new Point(base.fig[1, 0].x, base.fig[1, 0].y + 1);
                        base.fig[1, 0] = new Point(-5, -5);

                        base.fig[1, 2] = new Point(base.fig[3, 1].x - 2, base.fig[3, 1].y + 1);
                        base.fig[3, 1] = new Point(-5, -5);

                        base.condition = FigureCondition.Left;
                        //return base.tmpFig;
                        break;
                    }
            }

        }

        //Попытка вращения
        public override Point[,] TryRotate()
        {

            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    base.tmpFig[i, j].x = -5;
                    base.tmpFig[i, j].y = -5;
                }
            }
            switch (base.condition)
            {
                case FigureCondition.Left:
                    {
                        base.tmpFig[1, 0] = new Point(base.fig[1, 1].x, base.fig[1, 1].y - 1);
                        base.tmpFig[1, 1] = new Point(-5, -5);

                        base.tmpFig[3, 1] = new Point(base.fig[1, 2].x + 2, base.fig[1, 2].y - 1);
                        base.tmpFig[1, 2] = new Point(-5, -5);

                        //base.condition = FigureCondition.Up;
                        return base.tmpFig;
                        //break;
                    }
                case FigureCondition.Up:
                    {
                        base.tmpFig[1, 1] = new Point(base.fig[1, 0].x, base.fig[1, 0].y + 1);
                        base.tmpFig[1, 0] = new Point(-5, -5);

                        base.tmpFig[1, 2] = new Point(base.fig[3, 1].x - 2, base.fig[3, 1].y + 1);
                        base.tmpFig[3, 1] = new Point(-5, -5);

                        //base.condition = FigureCondition.Right;
                        return base.tmpFig;
                        //break;
                    }
                default:
                    return null;
            }
        }
    }

    [Serializable]
    public class FigureS : Figure
    {
        //Конструктор
        public FigureS(Point startPoint)
        {

            base.fig[1, 0] = startPoint;

            base.fig[1, 1].x = startPoint.x;
            base.fig[1, 1].y = startPoint.y + 1;

            base.fig[2, 1].x = startPoint.x + 1;
            base.fig[2, 1].y = startPoint.y + 1;

            base.fig[2, 2].x = startPoint.x + 1;
            base.fig[2, 2].y = startPoint.y + 2;
        }

        //Вращение
        public override void Rotate()
        {

            switch (base.condition)
            {
                case FigureCondition.Left:
                    {
                        base.fig[2, 0] = new Point(base.fig[1, 0].x + 1, base.fig[1, 0].y);
                        base.fig[1, 0] = new Point(-5, -5);

                        base.fig[3, 0] = new Point(base.fig[2, 2].x + 1, base.fig[2, 2].y - 2);
                        base.fig[2, 2] = new Point(-5, -5);

                        base.condition = FigureCondition.Up;
                        //return base.tmpFig;
                        break;
                    }
                case FigureCondition.Up:
                    {
                        base.fig[1, 0] = new Point(base.fig[2, 0].x - 1, base.fig[2, 0].y);
                        base.fig[2, 0] = new Point(-5, -5);

                        base.fig[2, 2] = new Point(base.fig[3, 0].x - 1, base.fig[3, 0].y + 2);
                        base.fig[3, 0] = new Point(-5, -5);

                        base.condition = FigureCondition.Left;
                        //return base.tmpFig;
                        break;
                    }
            }

        }

        //Попытка вращения
        public override Point[,] TryRotate()
        {

            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    base.tmpFig[i, j].x = -5;
                    base.tmpFig[i, j].y = -5;
                }
            }
            switch (base.condition)
            {
                case FigureCondition.Left:
                    {
                        base.tmpFig[2, 0] = new Point(base.fig[1, 0].x + 1, base.fig[1, 0].y);
                        base.tmpFig[1, 0] = new Point(-5, -5);

                        base.tmpFig[3, 0] = new Point(base.fig[2, 2].x + 1, base.fig[2, 2].y - 2);
                        base.tmpFig[2, 2] = new Point(-5, -5);

                        //base.condition = FigureCondition.Up;
                        return base.tmpFig;
                        //break;
                    }
                case FigureCondition.Up:
                    {
                        base.tmpFig[1, 0] = new Point(base.fig[2, 0].x - 1, base.fig[2, 0].y);
                        base.tmpFig[2, 0] = new Point(-5, -5);

                        base.tmpFig[2, 2] = new Point(base.fig[3, 0].x - 1, base.fig[3, 0].y + 2);
                        base.tmpFig[3, 0] = new Point(-5, -5);

                        //base.condition = FigureCondition.Right;
                        return base.tmpFig;
                        //break;
                    }
                default:
                    return null;
            }
        }
    }

    [Serializable]
    public class FigureJ : Figure
    {
        //Конструктор
        public FigureJ(Point startPoint)
        {

            base.fig[1, 0] = startPoint;

            base.fig[1, 1].x = startPoint.x;
            base.fig[1, 1].y = startPoint.y + 1;

            base.fig[1, 2].x = startPoint.x;
            base.fig[1, 2].y = startPoint.y + 2;

            base.fig[2, 0].x = startPoint.x + 1;
            base.fig[2, 0].y = startPoint.y;
        }

        //Вращение
        public override void Rotate()
        {

            switch (base.condition)
            {
                case FigureCondition.Left:
                    {
                        base.fig[3, 0] = new Point(base.fig[1, 1].x + 2, base.fig[1, 1].y - 1);
                        base.fig[1, 1] = new Point(-5, -5);

                        base.fig[3, 1] = new Point(base.fig[1, 2].x + 2, base.fig[1, 2].y - 1);
                        base.fig[1, 2] = new Point(-5, -5);

                        base.condition = FigureCondition.Up;
                        //return base.tmpFig;
                        break;
                    }
                case FigureCondition.Up:
                    {
                        base.fig[3, 2] = new Point(base.fig[2, 0].x + 1, base.fig[2, 0].y + 2);
                        base.fig[2, 0] = new Point(-5, -5);

                        base.fig[2, 2] = new Point(base.fig[1, 0].x + 1, base.fig[1, 0].y + 2);
                        base.fig[1, 0] = new Point(-5, -5);

                        base.condition = FigureCondition.Right;
                        //return base.tmpFig;
                        break;
                    }
                case FigureCondition.Right:
                    {
                        base.fig[1, 2] = new Point(base.fig[3, 1].x - 2, base.fig[3, 1].y + 1);
                        base.fig[3, 1] = new Point(-5, -5);

                        base.fig[1, 1] = new Point(base.fig[3, 0].x - 2, base.fig[3, 0].y + 1);
                        base.fig[3, 0] = new Point(-5, -5);

                        base.condition = FigureCondition.Down;
                        //return base.tmpFig;
                        break;
                    }
                case FigureCondition.Down:
                    {
                        base.fig[1, 0] = new Point(base.fig[2, 2].x - 1, base.fig[2, 2].y - 2);
                        base.fig[2, 2] = new Point(-5, -5);

                        base.fig[2, 0] = new Point(base.fig[3, 2].x - 1, base.fig[3, 2].y - 2);
                        base.fig[3, 2] = new Point(-5, -5);

                        base.condition = FigureCondition.Left;
                        //return base.tmpFig;
                        break;
                    }
            }

        }

        //Попытка вращения
        public override Point[,] TryRotate()
        {

            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    base.tmpFig[i, j].x = -5;
                    base.tmpFig[i, j].y = -5;
                }
            }
            switch (base.condition)
            {
                case FigureCondition.Left:
                    {
                        base.tmpFig[3, 0] = new Point(base.fig[1, 1].x + 2, base.fig[1, 1].y - 1);
                        base.tmpFig[1, 1] = new Point(-5, -5);

                        base.tmpFig[3, 1] = new Point(base.fig[1, 2].x + 2, base.fig[1, 2].y - 1);
                        base.tmpFig[1, 2] = new Point(-5, -5);

                        //base.condition = FigureCondition.Up;
                        return base.tmpFig;
                        //break;
                    }
                case FigureCondition.Up:
                    {
                        base.tmpFig[3, 2] = new Point(base.fig[2, 0].x + 1, base.fig[2, 0].y + 2);
                        base.tmpFig[2, 0] = new Point(-5, -5);

                        base.tmpFig[2, 2] = new Point(base.fig[1, 0].x + 1, base.fig[1, 0].y + 2);
                        base.tmpFig[1, 0] = new Point(-5, -5);

                        //base.condition = FigureCondition.Right;
                        return base.tmpFig;
                        //break;
                    }
                case FigureCondition.Right:
                    {
                        base.tmpFig[1, 2] = new Point(base.fig[3, 1].x - 2, base.fig[3, 1].y + 1);
                        base.tmpFig[3, 1] = new Point(-5, -5);

                        base.tmpFig[1, 1] = new Point(base.fig[3, 0].x - 2, base.fig[3, 0].y + 1);
                        base.tmpFig[3, 0] = new Point(-5, -5);

                        //base.condition = FigureCondition.Down;
                        return base.tmpFig;
                        //break;
                    }
                case FigureCondition.Down:
                    {
                        base.tmpFig[1, 0] = new Point(base.fig[2, 2].x - 1, base.fig[2, 2].y - 2);
                        base.tmpFig[2, 2] = new Point(-5, -5);

                        base.tmpFig[2, 0] = new Point(base.fig[3, 2].x - 1, base.fig[3, 2].y - 2);
                        base.tmpFig[3, 2] = new Point(-5, -5);

                        //base.condition = FigureCondition.Left;
                        return base.tmpFig;
                        //break;
                    }
                default:
                    return null;
            }
        }
    }

    [Serializable]
    public class FigureL : Figure
    {
        //Конструктор
        public FigureL(Point startPoint)
        {

            base.fig[1, 0] = startPoint;

            base.fig[1, 1].x = startPoint.x;
            base.fig[1, 1].y = startPoint.y + 1;

            base.fig[1, 2].x = startPoint.x;
            base.fig[1, 2].y = startPoint.y + 2;

            base.fig[2, 2].x = startPoint.x + 1;
            base.fig[2, 2].y = startPoint.y + 2;
        }

        //Вращение
        public override void Rotate()
        {

            switch (base.condition)
            {
                case FigureCondition.Left:
                    {
                        base.fig[2, 0] = new Point(base.fig[1, 2].x + 1, base.fig[1, 2].y - 2);
                        base.fig[1, 2] = new Point(-5, -5);

                        base.fig[3, 0] = new Point(base.fig[2, 2].x + 1, base.fig[2, 2].y - 2);
                        base.fig[2, 2] = new Point(-5, -5);

                        base.condition = FigureCondition.Up;
                        //return base.tmpFig;
                        break;
                    }
                case FigureCondition.Up:
                    {
                        base.fig[3, 1] = new Point(base.fig[1, 0].x + 2, base.fig[1, 0].y + 1);
                        base.fig[1, 0] = new Point(-5, -5);

                        base.fig[3, 2] = new Point(base.fig[1, 1].x + 2, base.fig[1, 1].y + 1);
                        base.fig[1, 1] = new Point(-5, -5);

                        base.condition = FigureCondition.Right;
                        //return base.tmpFig;
                        break;
                    }
                case FigureCondition.Right:
                    {
                        base.fig[2, 2] = new Point(base.fig[3, 0].x - 1, base.fig[3, 0].y + 2);
                        base.fig[3, 0] = new Point(-5, -5);

                        base.fig[1, 2] = new Point(base.fig[2, 0].x - 1, base.fig[2, 0].y + 2);
                        base.fig[2, 0] = new Point(-5, -5);

                        base.condition = FigureCondition.Down;
                        //return base.tmpFig;
                        break;
                    }
                case FigureCondition.Down:
                    {
                        base.fig[1, 1] = new Point(base.fig[3, 2].x - 2, base.fig[3, 2].y - 1);
                        base.fig[3, 2] = new Point(-5, -5);

                        base.fig[1, 0] = new Point(base.fig[3, 1].x - 2, base.fig[3, 1].y - 1);
                        base.fig[3, 1] = new Point(-5, -5);

                        base.condition = FigureCondition.Left;
                        //return base.tmpFig;
                        break;
                    }
            }

        }

        //Попытка вращения
        public override Point[,] TryRotate()
        {

            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    base.tmpFig[i, j].x = -5;
                    base.tmpFig[i, j].y = -5;
                }
            }
            switch (base.condition)
            {
                case FigureCondition.Left:
                    {
                        base.tmpFig[2, 0] = new Point(base.fig[1, 2].x + 1, base.fig[1, 2].y - 2);
                        base.tmpFig[1, 2] = new Point(-5, -5);

                        base.tmpFig[3, 0] = new Point(base.fig[2, 2].x + 1, base.fig[2, 2].y - 2);
                        base.tmpFig[2, 2] = new Point(-5, -5);

                        //base.condition = FigureCondition.Up;
                        return base.tmpFig;
                        //break;
                    }
                case FigureCondition.Up:
                    {
                        base.tmpFig[3, 1] = new Point(base.fig[1, 0].x + 2, base.fig[1, 0].y + 1);
                        base.tmpFig[1, 0] = new Point(-5, -5);

                        base.tmpFig[3, 2] = new Point(base.fig[1, 1].x + 2, base.fig[1, 1].y + 1);
                        base.tmpFig[1, 1] = new Point(-5, -5);

                        //base.condition = FigureCondition.Right;
                        return base.tmpFig;
                        //break;
                    }
                case FigureCondition.Right:
                    {
                        base.tmpFig[2, 2] = new Point(base.fig[3, 0].x - 1, base.fig[3, 0].y + 2);
                        base.tmpFig[3, 0] = new Point(-5, -5);

                        base.tmpFig[1, 2] = new Point(base.fig[2, 0].x - 1, base.fig[2, 0].y + 2);
                        base.tmpFig[2, 0] = new Point(-5, -5);

                        //base.condition = FigureCondition.Down;
                        return base.tmpFig;
                        //break;
                    }
                case FigureCondition.Down:
                    {
                        base.tmpFig[1, 1] = new Point(base.fig[3, 2].x - 2, base.fig[3, 2].y - 1);
                        base.tmpFig[3, 2] = new Point(-5, -5);

                        base.tmpFig[1, 0] = new Point(base.fig[3, 1].x - 2, base.fig[3, 1].y - 1);
                        base.tmpFig[3, 1] = new Point(-5, -5);

                        //base.condition = FigureCondition.Left;
                        return base.tmpFig;
                        //break;
                    }
                default:
                    return null;
            }
        }
    }
}
