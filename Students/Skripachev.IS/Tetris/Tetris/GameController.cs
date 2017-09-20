using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Runtime.Serialization;

namespace Tetris
{
    [Serializable]
    public class GameController
    {
        Random random = new Random();


        const int column = 10;
        const int row = 15;

        public uint score;

        public Figure currentFigure;
        public Point[,] figField;

        public event EventHandler EGameOver;

        public FigureType[,] field = new FigureType[column, row];
        public FigureType currentType;
        public FigureType currentColor;
        public FigureType nextFigure;

        public bool isActiveFigure;

        //double squareSize;


        public GameController(double height, double width)
        {
            //squareSize = height / row;
            score = 0;
            isActiveFigure = false;
            currentType = FigureType.None;
            for (int i = 0; i < column; i++)
            {
                for (int j = 0; j < row; j++)
                {
                    field[i, j] = FigureType.None;
                }
            }
            nextFigure = GenerateNextFigure();
        }

        //Генерация следующей фигуры
        public FigureType GenerateNextFigure()
        {
            FigureType next = (FigureType)random.Next(0, 7);
            return next;
        }

        //Создание фигуры (генерация)
        public void CreateFigure()
        {
            if (!isActiveFigure)
            {
                currentType = nextFigure;
                switch (currentType)
                {
                    case FigureType.I:
                        {
                            currentFigure = new FigureI(new Point(4, 0));
                            currentColor = FigureType.I;
                            break;
                        }
                    case FigureType.T:
                        {
                            currentFigure = new FigureT(new Point(4, 0));
                            currentColor = FigureType.T;
                            break;
                        }
                    case FigureType.O:
                        {
                            currentFigure = new FigureO(new Point(4, 1));
                            currentColor = FigureType.O;
                            break;
                        }
                   case FigureType.Z:
                        {
                            currentFigure = new FigureZ(new Point(5, 0));
                            currentColor = FigureType.Z;
                            break;
                        }
                    case FigureType.S:
                        {
                            currentFigure = new FigureS(new Point(4, 0));
                            currentColor = FigureType.S;
                            break;
                        }
                    case FigureType.J:
                        {
                            currentFigure = new FigureJ(new Point(4, 0));
                            currentColor = FigureType.J;
                            break;
                        }
                    case FigureType.L:
                        {
                            currentFigure = new FigureL(new Point(4, 0));
                            currentColor = FigureType.L;
                            break;
                        }
                }

                isActiveFigure = true;
                figField = currentFigure.GetFieldValue();
                for(int i=0; i<4; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        if(figField[i,j].x!=-5 && figField[i, j].y != -5)
                        {
                            if (field[figField[i, j].x, figField[i, j].y] != FigureType.None)
                            {
                                GameOver();
                                return;
                            }
                            else
                            {
                                field[figField[i, j].x, figField[i, j].y] = FigureType.Current;
                            }
                        }
                    }
                }
                nextFigure = GenerateNextFigure();
            }
        }

        
        //Конец игры
        public void GameOver()
        {
            //MessageBox.Show("GameOver!");
            EventHandler handler = EGameOver;
            if (handler != null)
            {
               handler(this, null);
            }
        }

        //получение текущего цвета
        public FigureType GetCurrentColor()
        {
            return currentColor;
        }

        //Получение поля
        public FigureType[,] GetField()
        {
            return field;
        }

        //Получение типа следующей фигуры
        public FigureType GetNextFigure()
        {
            return nextFigure;
        }

        //Функция обновления
        public void Update()
        {
            
            if (isActiveFigure)
            {
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        if (figField[i, j].x != -5 && figField[i, j].y != -5)
                        {
                            if (figField[i, j].y + 1 == 15 || (field[figField[i, j].x, figField[i, j].y + 1] != FigureType.None && field[figField[i, j].x, figField[i, j].y + 1] != FigureType.Current))
                            {
                                isActiveFigure = false;
                                SaveFigure(currentColor);
                                UpdateScore();
                                return;
                            }

                        }
                    }
                }

                ReField();
                currentFigure.Move(Direction.Down);
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        if (figField[i, j].x != -5 && figField[i, j].y != -5)
                        {
                            if (field[figField[i, j].x, figField[i, j].y] != FigureType.None)
                            { 
                                GameOver();
                                return;
                            }
                            else
                            {
                            field[figField[i, j].x, figField[i, j].y] = FigureType.Current;
                            }
                        }
                    }
                }
            }
            else
            {
                CreateFigure();
            }

        }

        //Уничтожение полоски кубиков и изменение счета
        public void UpdateScore()
        {
            for (int i = (row-1); i >= 0; i--)
            {
                int isFullLine = 0;
                for (int j = 0; j < column; j++)
                {
                    if (field[j, i] != FigureType.None && field[j, i] != FigureType.Current)
                        isFullLine++;
                }
                if(isFullLine == 10)
                {
                    for (int k = i - 1; k >= 0; k--)
                    {
                        for (int j = 0; j < column; j++)
                        {
                            if (field[j, k] != FigureType.None && field[j, k] != FigureType.Current)
                            {
                                field[j, k + 1] = field[j, k];
                                field[j, k] = FigureType.None;
                            }
                            else if(field[j, k] == FigureType.None)
                            {
                                field[j, k + 1] = FigureType.None;
                            }
                        }
                    }
                    i++;
                    score += 100;
                }
            }
                
        }

        //Получить значение счета
        public uint GetScore()
        {
            return score;
        }

        //Перерасчет поля
        public void ReField()
        {
            for (int i = 0; i < column; i++)
            {
                for (int j = 0; j < row; j++)
                {
                    if (field[i, j] == FigureType.Current)
                        field[i, j] = FigureType.None;
                }
            }
        }


        //Вращение объекта
        public void Rotate()
        {
            Point[,] tmpFig = currentFigure.TryRotate();
            if (tmpFig != null)
            {
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        if (tmpFig[i, j].x != -5 && tmpFig[i, j].y != -5)
                        {
                            if (tmpFig[i, j].x > 9 || tmpFig[i, j].x < 0 || tmpFig[i, j].y < 0 || tmpFig[i, j].y > 14)
                                return;
                            else if (field[tmpFig[i, j].x, tmpFig[i, j].y] != FigureType.None && field[tmpFig[i, j].x, tmpFig[i, j].y] != FigureType.Current)
                                return;
                        }
                    }
                }
            }


            currentFigure.Rotate();
            ReField();
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    if (figField[i, j].x != -5 && figField[i, j].y != -5)
                    {
                        if (field[figField[i, j].x, figField[i, j].y] != FigureType.None)
                        {
                            GameOver();
                            return;
                        }
                        else
                        {
                            field[figField[i, j].x, figField[i, j].y] = FigureType.Current;
                        }
                    }
                }
            }

        }


        //Сохранение положения фигуры
        public void SaveFigure(FigureType type)
        {
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    if (figField[i, j].x != -5 && figField[i, j].y != -5)
                        field[figField[i, j].x, figField[i, j].y] = type;
                }
            }
            currentType = FigureType.None;
        }


        //Движение фигуры влево и вправо
        public void Move(Direction dir)
        {
            if (isActiveFigure)
            {
                //for (int i = 0; i < 4; i++)
                //{
                //    for (int j = 3; j >= 0; j--)
                //    {
                //        if (figField[i, j].y + 1 == 15)
                //        {
                //            return;
                //        }
                //    }
                //}

                switch (dir)
                {
                    case Direction.Left:
                        {
                            for (int i = 0; i < 4; i++)
                            {
                                for (int j = 0; j < 4; j++)
                                {
                                    if (figField[i, j].x != -5 && figField[i, j].y != -5)
                                    {
                                        if (figField[i, j].x - 1 == -1)
                                        {
                                            return;
                                        }
                                        else if ((field[figField[i, j].x - 1, figField[i, j].y] != FigureType.None && field[figField[i, j].x - 1, figField[i, j].y] != FigureType.Current))
                                        {
                                            return;
                                        }

                                    }
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
                                    if (figField[i, j].x != -5 && figField[i, j].y != -5)
                                    {
                                        if (figField[i, j].x + 1 == 10)
                                        {
                                            return;
                                        }
                                        else if ((field[figField[i, j].x + 1, figField[i, j].y] != FigureType.None && field[figField[i, j].x + 1, figField[i, j].y] != FigureType.Current))
                                        {
                                            return;
                                        }
                                    }
                                }
                            }
                            break;
                        }
                }

                ReField();
                currentFigure.Move(dir);
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        if (figField[i, j].x != -5 && figField[i, j].y != -5)
                        {
                            if (field[figField[i, j].x, figField[i, j].y] != FigureType.None)
                            {
                                GameOver();
                                return;
                            }
                            else
                            {
                                field[figField[i, j].x, figField[i, j].y] = FigureType.Current;
                            }
                        }
                    }
                }
            }
            
        }


        //Конец файла

    }
}
