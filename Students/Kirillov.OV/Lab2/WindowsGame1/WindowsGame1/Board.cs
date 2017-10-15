using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using WindowsGame1;
using System.Collections.Generic;
using Microsoft.Xna.Framework;



namespace WindowsGame1
{
    public class Board
    {
        public int[,] field;
        public int blockSize = 32;
        public int offset = 480;
        public int height = 19;
        public int width = 10;

        int currentBlockHeight;
        int[,] block;
        List<int> orderColor; //0-blue, 1-cian, 2-green, 3-orange, 4-purple,5-red,6,yellow
        public int blockColor;

        public int score;
        int counter;
        public int level;

        bool falling;

        public bool addTime;

        Vector2 pos = Vector2.Zero;
        public List<Vector2> blocksPos;
        public List<Vector2> allBlocks;
        public List<int> allBlocksColor;


        List<int[,]> order;

        Figure blocks = new Figure();

        public Board() {
            order = new List<int[,]>();
            blocksPos = new List<Vector2>();
            allBlocks = new List<Vector2>();
            orderColor = new List<int>();
            allBlocksColor = new List<int>();
            falling = false;
            score = 0;
            level = 0;
            blockColor = 0;
        }

        public void GameOver()
        {
            order.Clear();
            blocksPos.Clear();
            allBlocks.Clear();
            orderColor.Clear();
            allBlocksColor.Clear();
            falling = false;
            score = 0;
            level = 0;
        }

        public void SpawnBlocks()
        {
            CreateOrder();
            block = order[0];
            blockColor = orderColor[0];
            order.RemoveAt(0);
            orderColor.RemoveAt(0);
            currentBlockHeight = block.GetLength(0);
            blocksPos.Clear();
            pos = new Vector2(640, 0);
            for (int i = 0; i < currentBlockHeight; i++)
            {
                for (int j = 0; j < currentBlockHeight; j++)
                {
                    if (block[i, j] == 1)
                    {
                        blocksPos.Add(new Vector2(blockSize * j+640, i* blockSize));
                    }
                }
            }
            falling = true;
        }

        public void nextStep()
        {
            for (int i = 0; i < blocksPos.Count; i++)
            {
                blocksPos[i] = new Vector2(blocksPos[i].X, blocksPos[i].Y + blockSize);
            }
            pos = new Vector2(pos.X, pos.Y + blockSize);
            if (CheckCollisionVert(blocksPos))
            {
                for (int i = 0; i < blocksPos.Count; i++)
                {
                    blocksPos[i] = new Vector2(blocksPos[i].X, blocksPos[i].Y - blockSize);
                }
                pos = new Vector2(pos.X, pos.Y - blockSize);
                falling = false;
            }
           
        }

        public void addToAll()
        {
            foreach (var bl in blocksPos)
            {
                allBlocksColor.Add(blockColor);
                allBlocks.Add(bl);
            }
            counter = 0;
            CheckLine();
            Scoring();
            nextLevel();

        }

        void Scoring()
        {
            switch (counter)
            {
                case 1:
                    score += 100 * (level + 1);
                    break;
                case 2:
                    score += 300 * (level + 1);
                    break;
                case 3:
                    score += 500 * (level + 1);
                    break;
                case 4:
                    score += 1200 * (level + 1);
                    break;
                default:
                    break;
            }
        }

        void nextLevel()
        {
            if (level == 0 && score >= 2000) level++;
            else if (level == 1 && score >= 6800) level++;
            else if (level == 2 && score >= 12800) level++;
            else if (level == 3 && score >= 23600) level++;
            else if (level == 4 && score >= 42800) level++;
            else if (level == 5 && score >= 58400) level++;
            else if (level == 6 && score >= 84800) level++;
            else if (level == 7 && score >= 105200) level++;
            else if (level == 8 && score >= 138800) level++;
            else if (level == 9 && score >= 164000) level++;
            else if (level == 10 && score >= 204800) level++;
            else if (level == 11 && score >= 234800) level++;
            else if (level == 12 && score >= 282800) level++;
            else if (level == 13 && score >= 327600) level++;
            else if (level == 14 && score >= 382800) level++;
            else if (level == 15 && score >= 422400) level++;
        }

        public void Movement(bool right)
        {

            if (right)
            {
                for (int i = 0; i < blocksPos.Count; i++)
                {
                    blocksPos[i] = new Vector2(blocksPos[i].X + blockSize, blocksPos[i].Y);
                }
                pos = new Vector2(pos.X + blockSize, pos.Y);
                if (CheckCollisionHor(right, blocksPos))
                {
                    for (int i = 0; i < blocksPos.Count; i++)
                    {
                        blocksPos[i] = new Vector2(blocksPos[i].X - blockSize, blocksPos[i].Y);
                    }
                    pos = new Vector2(pos.X - blockSize, pos.Y);
                }
            }
            else
            {
                for (int i = 0; i < blocksPos.Count; i++)
                {
                    blocksPos[i] = new Vector2(blocksPos[i].X - blockSize, blocksPos[i].Y);
                }
                pos = new Vector2(pos.X - blockSize, pos.Y);
                if (CheckCollisionHor(right, blocksPos))
                {
                    for (int i = 0; i < blocksPos.Count; i++)
                    {
                        blocksPos[i] = new Vector2(blocksPos[i].X + blockSize, blocksPos[i].Y);
                    }
                    pos = new Vector2(pos.X + blockSize, pos.Y);
                }
            }
        }

        public void Instant()
        {
            int i = 0;
            while (falling)
            {
                i++;
                nextStep();
            }
            score += i*2;
        }

        public void SoftDrop()
        {
            score ++;
        }

        public void Rotate()
        {
            int[,] tmp = new int[currentBlockHeight, currentBlockHeight];
            for (int i = 0; i < currentBlockHeight; i++)
            {
                for (int j = 0; j < currentBlockHeight; j++)
                {
                    tmp[j, i] = block[i, currentBlockHeight - 1 - j];
                }
            }
            block = tmp;
            blocksPos.Clear();
            for (int i = 0; i < currentBlockHeight; i++)
            {
                for (int j = 0; j < currentBlockHeight; j++)
                {
                    if (block[i, j] == 1)
                    {
                        blocksPos.Add(new Vector2(pos.X + j * blockSize, pos.Y + i * blockSize));
                    }
                }
            }
            if (!AfterRotate())
            {
                ReverseRotate();
            }

        }

             public void ReverseRotate()
             {
                 int[,] tmp = new int[currentBlockHeight, currentBlockHeight];
                 for (int i = 0; i < currentBlockHeight; i++)
                 {
                     for (int j = 0; j < currentBlockHeight; j++)
                     {
                         tmp[j, i] = block[currentBlockHeight - 1 - i, j];
                     }
                 }
                 block = tmp;
                 blocksPos.Clear();
                 for (int i = 0; i < currentBlockHeight; i++)
                 {
                     for (int j = 0; j < currentBlockHeight; j++)
                     {
                         if (block[i, j] == 1)
                         {
                             blocksPos.Add(new Vector2(pos.X + j * blockSize, pos.Y + i * blockSize));
                         }
                     }
                 }

                 if (!AfterRotate())
                 {
                     Rotate();
                 }
             }
        bool AfterRotate()
        {
            if (CheckCollisionVert(blocksPos))
            {
                return false;
            }

            if (CheckCollisionHor(true, blocksPos) && (CheckCollisionHor(false, blocksPos)))
            {
                return false;
            }

            if (CheckCollisionHor(true, blocksPos))
            {
                for (int i = 0; i < blocksPos.Count; i++)
                {
                    blocksPos[i] = new Vector2(blocksPos[i].X - blockSize, blocksPos[i].Y);
                }
                pos = new Vector2(pos.X - blockSize, pos.Y);
                if (CheckCollisionHor(true, blocksPos) || CheckCollisionHor(false, blocksPos))
                {
                    for (int i = 0; i < blocksPos.Count; i++)
                    {
                        blocksPos[i] = new Vector2(blocksPos[i].X + blockSize, blocksPos[i].Y);
                    }
                    return false;
                }
                return true;
            }
            if (CheckCollisionHor(false, blocksPos))
            {
                for (int i = 0; i < blocksPos.Count; i++)
                {
                    blocksPos[i] = new Vector2(blocksPos[i].X + blockSize, blocksPos[i].Y);
                }
                pos = new Vector2(pos.X + blockSize, pos.Y);

                if (CheckCollisionHor(true, blocksPos) || CheckCollisionHor(false, blocksPos))
                {
                    for (int i = 0; i < blocksPos.Count; i++)
                    {
                        blocksPos[i] = new Vector2(blocksPos[i].X - blockSize, blocksPos[i].Y);
                    }
                    return false;
                }
                return true;

            }
            return true;
        }

        bool CheckCollisionHor(bool dir, List<Vector2> chBlock)
        {
            foreach (var bl in chBlock)
            {
                if (bl.X< offset && !dir || bl.X + blockSize > width * blockSize +offset && dir)
                {
                    return true;
                }
                foreach (var abl in allBlocks)
                {
                    if (bl.X == abl.X && bl.Y == abl.Y && !dir || bl.X == abl.X && dir && bl.Y == abl.Y)
                    {
                        return true;
                    }
                }
            }
            return false;
        }

        bool CheckCollisionVert(List<Vector2> chBlock)
        {
            for (int i = 0; i < chBlock.Count; i++)
            {
                foreach (var abl in allBlocks)
                {
                    if (chBlock[i].Y == abl.Y && chBlock[i].X == abl.X)
                    {              
                        return true;
                    }
                }
                if (chBlock[i].Y == height*blockSize)
                {
                    return true;
                }

            }
            return false;
        }

        public bool FreeSpace()
        {
            for (int i = 0; i < blocksPos.Count; i++)
            {
                foreach (var abl in allBlocks)
                {
                    if (blocksPos[i].Y + blockSize == abl.Y && blocksPos[i].X == abl.X)
                    {
                        falling = false;
                        return false;
                    }
                }
                if (blocksPos[i].Y + blockSize == height * blockSize)
                {
                    falling = false;
                    return false;
                }
            }
            falling = true;
            return true;
        }

        public bool CheckGameOver()
        {
            foreach (var abl in allBlocks)
            {
                if (abl.Y <= 0)
                {
                    return true;
                }
            }
            return false;
        }

        public void CheckLine()
        {
            int x;
            bool line = false;
            foreach (var bl1 in allBlocks)
            {
                x = 0;
                if (!line)
                {
                    foreach (var bl2 in allBlocks)
                    {
                        if (bl1 != bl2)
                        {
                            if (bl1.Y == bl2.Y)
                            {
                                x++;
                            }
                        }
                    }
                    if (x >= 9)
                    {
                        line = true;
                        counter++;
                        RemoveLine(bl1.Y);
                    }
                }
            }
            if (line)
            {
                CheckLine();
            }
        }

        void RemoveLine(float l)
        {
            List<Vector2> tmp = new List<Vector2>();
            List<int> tmpc = new List<int>();
            int x = 0;
            for (int i = 0; i < allBlocks.Count; i++)
            {
                if (allBlocks[i].Y != l)
                {
                    tmpc.Add(allBlocksColor[i]);
                    tmp.Add(allBlocks[i]);
                }
            }
            allBlocks = tmp;
            allBlocksColor = tmpc;
            for (int i = 0; i < allBlocks.Count; i++)
            {
                    if (allBlocks[i].Y < l)
                    {
                        allBlocks[i] = new Vector2(allBlocks[i].X, allBlocks[i].Y+blockSize);
                }
            }
        }

        void CreateOrder()
        {
            Random rnd = new Random();
            int x = 0;
            if (order.Count <= 1)
            {
                for (int i = 0; i < 5; i++)
                {
                    x = rnd.Next(blocks.pieces.Count);
                    order.Add(blocks.pieces[x]);
                    orderColor.Add(x);
                }
                order.Add(blocks.pieces[0]);
                orderColor.Add(0);

            }
        }

        public bool isFalling()
        {
            return falling;
        }

        public int[,] NextBlock()
        {
            return order[0];
        }
    }
}
