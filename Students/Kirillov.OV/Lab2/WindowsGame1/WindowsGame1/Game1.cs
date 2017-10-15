using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Media;

namespace WindowsGame1
{
    /// <summary>
    /// This is the main type for your game
    /// </summary>
    public class Game1 : Microsoft.Xna.Framework.Game
    {
        GraphicsDeviceManager graphics;
        SpriteBatch spriteBatch;
        Board board = new Board();
        Texture2D t;
        Texture2D sprite;
        Texture2D[] sprites;
        SpriteFont font;
        SpriteFont font2;
        Song song;
        Texture2D gBack;
        Texture2D menu;
        Texture2D score;

        int menuButton;
        bool pressed =false;

        bool paused;

        int StepTime = 350;
        int Time = 0;
        int KeyElapsed = 0;

        bool rotate = true;
        bool instant = true;
        bool softDrop = false;

        List<int> highscore;


        int GameState = 0; // 0 - Menu, 1 - InGame, 2 - High Score

        public Game1()
        {
            graphics = new GraphicsDeviceManager(this);
            graphics.PreferredBackBufferHeight = 720;
            graphics.PreferredBackBufferWidth = 1280;
            Content.RootDirectory = "Content";
            MediaPlayer.IsRepeating = true;
            MediaPlayer.Volume = 0.050f;
            menuButton = 0;
            paused = false;
            highscore = new List<int>();
        }

        /// <summary>
        /// Allows the game to perform any initialization it needs to before starting to run.
        /// This is where it can query for any required services and load any non-graphic
        /// related content.  Calling base.Initialize will enumerate through any components
        /// and initialize them as well.
        /// </summary>
        protected override void Initialize()
        {
            // TODO: Add your initialization logic here
            
            base.Initialize();
        }

        /// <summary>
        /// LoadContent will be called once per game and is the place to load
        /// all of your content.
        /// </summary>
        protected override void LoadContent()
        {
            // Create a new SpriteBatch, which can be used to draw textures.
            spriteBatch = new SpriteBatch(GraphicsDevice);
             t = new Texture2D(GraphicsDevice, board.blockSize*board.width, board.blockSize*board.height);
             Color[] data = new Color[board.blockSize * board.width *board.blockSize * board.height];
             for (int i = 0; i < data.Length; ++i) data[i] = Color.Chocolate;
             t.SetData(data);
            //sprite = Texture2D.FromStream(GraphicsDevice, File.OpenRead("red"));
            sprites = new Texture2D[7];
            sprites[0] = Content.Load<Texture2D>("blue");
            sprites[1] = Content.Load<Texture2D>("cian");
            sprites[2] = Content.Load<Texture2D>("green");
            sprites[3] = Content.Load<Texture2D>("orange");
            sprites[4] = Content.Load<Texture2D>("purple");
            sprites[5] = Content.Load<Texture2D>("red");
            sprites[6] = Content.Load<Texture2D>("yellow");

            sprite = Content.Load<Texture2D>("red");
             font = Content.Load<SpriteFont>("Font");
             song = Content.Load<Song>("Song");
            gBack = Content.Load<Texture2D>("GameBackground");
            menu = Content.Load<Texture2D>("Menu");
            font2 = Content.Load<SpriteFont>("SpriteFont1");
            if (File.Exists("highscore.txt"))
            {
                var s = File.ReadAllLines("highscore.txt");
                int i = 0;
                foreach (var line in s)
                {
                    if (i < 10)
                    {
                        highscore.Add(Convert.ToInt32(line));
                    }
                    i++;
                }
            }
                else
                {
                   var f=  File.Create("highscore.txt");
                    f.Close();
                }
                score = Content.Load<Texture2D>("score");
            // TODO: use this.Content to load your game content here
        }

        /// <summary>
        /// UnloadContent will be called once per game and is the place to unload
        /// all content.
        /// </summary>
        protected override void UnloadContent()
        {
            // TODO: Unload any non ContentManager content here
        }

        /// <summary>
        /// Allows the game to run logic such as updating the world,
        /// checking for collisions, gathering input, and playing audio.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Update(GameTime gameTime)
        {
            KeyboardState kState = Keyboard.GetState();
            // Allows the game to exit
            if (GamePad.GetState(PlayerIndex.One).Buttons.Back == ButtonState.Pressed)
                this.Exit();
            Time += gameTime.ElapsedGameTime.Milliseconds;
            KeyElapsed += gameTime.ElapsedGameTime.Milliseconds;
            
            if (GameState == 0)
            {
                MediaPlayer.Stop();
                if (kState.IsKeyUp(Keys.Up) && kState.IsKeyUp(Keys.Down) && kState.IsKeyUp(Keys.Left) && kState.IsKeyUp(Keys.Right) && kState.IsKeyUp(Keys.Enter))
                {
                    pressed = false;
                }
                if (kState.IsKeyDown(Keys.Up) && !pressed) {
                    if (menuButton !=3 && menuButton != 0)
                    {
                        menuButton--;
                    }
                    pressed = true;
                }
                else if (kState.IsKeyDown(Keys.Down) && !pressed) {
                    if (menuButton != 3 && menuButton != 2)
                    {
                        menuButton++;
                    }
                    pressed = true;
                }
                else if (kState.IsKeyDown(Keys.Left) && !pressed) {
                    menuButton = 0;
                    pressed = true;
                }
                else if (kState.IsKeyDown(Keys.Right) && !pressed){
                    menuButton = 3;
                    pressed = true;
                }
                else if (kState.IsKeyDown(Keys.Enter) && !pressed)
                {
                    switch (menuButton)
                    {
                        case 0:
                            GameState = 1;
                            board.GameOver();
                            MediaPlayer.Play(song);
                            break;
                        case 1:
                            GameState = 1;
                            MediaPlayer.Play(song);
                            break;
                        case 2:
                            this.Exit();
                            break;
                        case 3:
                            GameState = 2;
                            break;
                        default:
                            break;
                    }
                    pressed = true;
                    
                }
            }
            else if (GameState == 1)
            {
                if (kState.IsKeyDown(Keys.Escape))
                {
                    GameState = 0;
                    MediaPlayer.Stop();
                }

                if (kState.IsKeyUp(Keys.Z) && kState.IsKeyUp(Keys.X))
                {
                    rotate = true;
                }
                if (kState.IsKeyDown(Keys.Z) && rotate)
                {
                    board.Rotate();
                    rotate = false;
                    if (!board.isFalling())
                    {
                        Time = 0;
                    }
                }
                if (kState.IsKeyDown(Keys.X) && rotate)
                {
                    board.ReverseRotate();
                    rotate = false;
                    if (!board.isFalling())
                    {
                        Time = 0;
                    }
                }

                if (kState.IsKeyUp(Keys.Up))
                {
                    instant = true;
                }
                if (kState.IsKeyDown(Keys.Up) && instant)
                {
                    board.Instant();
                    instant = false;
                }
                if (kState.IsKeyUp(Keys.Down)) softDrop = false;
                if (kState.IsKeyDown(Keys.Down))
                {
                    softDrop = true;
                    Time = 999;
                }
                if (KeyElapsed > 35)
                {

                    if (kState.IsKeyDown(Keys.Right))
                    {
                        board.Movement(true);
                    }
                    else if (kState.IsKeyDown(Keys.Left))
                    {
                        board.Movement(false);
                    }
                    KeyElapsed = 0;
                }

                if (!board.isFalling())
                {
                    if (board.blocksPos.Count > 0)
                    {
                        board.FreeSpace();
                        Time = 0;
                    }
                }

                if (!board.isFalling())
                {
                    softDrop = false;
                    board.addToAll();
                    board.SpawnBlocks();
                }
                else
                {
                    if (Time > StepTime - board.level * 20)
                    {
                        if (softDrop) board.SoftDrop();
                        board.nextStep();
                        Time = 0;
                    }
                }
                if (board.CheckGameOver())
                {
                    highscore.Add(board.score);
                    highscore.Sort();
                    highscore.Reverse();
                    TextWriter tw = new StreamWriter("highscore.txt");
                    foreach (var s in highscore)
                        tw.WriteLine(s);

                    tw.Close();
                    GameState = 0;
                }
            }
            else if (GameState == 2)
            {
                
                MediaPlayer.Stop();

                if (kState.IsKeyUp(Keys.Enter)){
                    pressed = false;
                }
               if (kState.IsKeyDown(Keys.Enter) && !pressed)
                {
                    GameState = 0;
                    pressed = true;
                }
                
            }
            base.Update(gameTime);
        }

        /// <summary>
        /// This is called when the game should draw itself.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Draw(GameTime gameTime)
        {
            GraphicsDevice.Clear(Color.CornflowerBlue);
            spriteBatch.Begin();
            if (GameState == 0)
            {
                spriteBatch.Draw(menu, new Vector2(0, 0), Color.White);
                if (menuButton == 0)
                {
                    spriteBatch.DrawString(font, "New Game", new Vector2(160 - font.MeasureString("New Game").X / 2, 125 - font.MeasureString("New Game").Y / 2), Color.Green);
                }
                else
                {
                    spriteBatch.DrawString(font, "New Game", new Vector2(160 - font.MeasureString("New Game").X / 2, 125 - font.MeasureString("New Game").Y / 2), Color.Black);
                }
                if (menuButton == 1)
                {
                    spriteBatch.DrawString(font, "Continue", new Vector2(160 - font.MeasureString("Continue").X / 2, 330 - font.MeasureString("Continue").Y / 2), Color.Green);
                }
                else
                {
                    spriteBatch.DrawString(font, "Continue", new Vector2(160 - font.MeasureString("Continue").X / 2, 330 - font.MeasureString("Continue").Y / 2), Color.Black);
                }
                if (menuButton == 2)
                {
                    spriteBatch.DrawString(font, "Exit", new Vector2(160 - font.MeasureString("Exit").X / 2, 535 - font.MeasureString("Exit").Y / 2), Color.Green);
                }
                else
                {
                    spriteBatch.DrawString(font, "Exit", new Vector2(160 - font.MeasureString("Exit").X / 2, 535 - font.MeasureString("Exit").Y / 2), Color.Black);
                }
                if (menuButton == 3)
                {
                    spriteBatch.DrawString(font2, "High Score", new Vector2(600 - font2.MeasureString("High Score").X / 2, 250 - font2.MeasureString("High Score").Y / 2), Color.Green);
                }
                else
                {
                    spriteBatch.DrawString(font2, "High Score", new Vector2(600 - font2.MeasureString("High Score").X / 2, 250 - font2.MeasureString("High Score").Y / 2), Color.Black);
                }

                if (highscore.Count > 0)
                {
                    spriteBatch.DrawString(font, highscore[0].ToString(), new Vector2(600 - font.MeasureString(highscore[0].ToString()).X / 2, 350 - font.MeasureString(highscore[0].ToString()).Y / 2), Color.Black);
                }

            }
            else if (GameState == 1)
            {
                spriteBatch.Draw(gBack, new Vector2(0, 0), Color.White);

                int x = 0;
                foreach (var item in board.allBlocks)
                {
                   // spriteBatch.Draw(sprite, new Vector2(item.X, item.Y), Color.White);
                    spriteBatch.Draw(sprites[board.allBlocksColor[x]], new Vector2(item.X, item.Y), Color.White);
                    x++;
                }
                foreach (var item in board.blocksPos)
                {
                    //   spriteBatch.Draw(sprites[board.orderColor[0]], new Vector2(item.X, item.Y), Color.White);
                    spriteBatch.Draw(sprites[board.blockColor], new Vector2(item.X, item.Y), Color.White);
                }
                spriteBatch.DrawString(font, board.score.ToString(), new Vector2(980 - font.MeasureString(board.score.ToString()).X/2, 140 - font.MeasureString(board.score.ToString()).Y / 2), Color.Black);
                spriteBatch.DrawString(font, board.level.ToString(), new Vector2(330 - font.MeasureString(board.level.ToString()).X / 2, 140- font.MeasureString(board.level.ToString()).Y /2), Color.Black);
                if (highscore.Count > 0)
                {
                    spriteBatch.DrawString(font, highscore[0].ToString(), new Vector2(980 - font.MeasureString(highscore[0].ToString()).X / 2, 360 - font.MeasureString(highscore[0].ToString()).Y / 2), Color.Black);
                }


                if (board.isFalling())
                {
                    int[,] next = board.NextBlock();
                    for (int i = 0; i < next.GetLength(0); i++)
                    {
                        for (int j = 0; j < next.GetLength(0); j++)
                        {
                            if (next[i, j] == 1)
                            {
                                spriteBatch.Draw(sprite, new Vector2(board.blockSize * j + 280, i * board.blockSize + 320), Color.White);
                            }
                        }
                    }
                }

            }
            else if (GameState == 2)
            {
                spriteBatch.Draw(score, new Vector2(0, 0), Color.White);
                int offset = 0;
                int i = 0;
                foreach (var item in highscore)
                {
                    if (i <= 9)
                    {
                        spriteBatch.DrawString(font, item.ToString(), new Vector2(840 - font.MeasureString(item.ToString()).X / 2, 90 - font.MeasureString(item.ToString()).Y / 2 + offset), Color.White);
                        offset += 50;
                        i++;
                    }
                }
            }
            spriteBatch.End();
            // TODO: Add your drawing code here

            base.Draw(gameTime);
        }

    }
}
