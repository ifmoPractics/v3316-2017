using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections.Generic;

namespace WindowsGame1
{
    public class Figure
    {
        public List<int[,]> pieces;

        public Figure()
        {
            pieces = new List<int[,]>();
            /* I Piece */
            pieces.Add(new int[4, 4] {
                {0, 0, 0, 0},
                {1, 1, 1, 1},
                {0, 0, 0, 0},
                {0, 0, 0, 0}
                });
            /* L Piece */
            pieces.Add(new int[3, 3] {
                {0, 0, 1},
                {1, 1, 1},
                {0, 0, 0}
                });
            /* J Piece */
            pieces.Add(new int[3, 3] {
                {1, 0, 0},
                {1, 1, 1},
                {0, 0, 0}
                });
            /* O Piece */
            pieces.Add(new int[2, 2] {
                {1, 1},
                {1, 1}
                });
            /* S Piece */
            pieces.Add(new int[3, 3] {
                {0, 1, 1},
                {1, 1, 0},
                {0, 0, 0}
                });
            /* T Piece */
            pieces.Add(new int[3, 3] {
                {0, 1, 0},
                {1, 1, 1},
                {0, 0, 0}
                });
            /* Z Piece */
            pieces.Add(new int[3, 3] {
                {1, 1, 0},
                {0, 1, 1},
                {0, 0, 0}
                });
            
        }
       

    }
}
