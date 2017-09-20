using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;
using System.Windows.Media.Effects;
using System.Runtime.Serialization.Formatters.Binary;
using System.IO;


namespace Tetris
{
    /// <summary>
    /// Логика взаимодействия для Window1.xaml
    /// </summary>
    public partial class Window1 : Window
    {

        Image[,] field = new Image[10, 15];
        public GameController gameCntrl;

        DropShadowEffect effect;

        Records records = new Records();

        public DispatcherTimer timer;

        public bool isPlaying;
        public bool isWasSaved;
        public Window1()
        {
            InitializeComponent();

            LoadLastSave();

            timer = new DispatcherTimer();
            timer.Tick += new EventHandler(timer_Tick);
            timer.Interval = TimeSpan.FromMilliseconds(500);
            //timer.Start();
            DrawField();
            
            records.Load();

            effect = new DropShadowEffect();
            effect.ShadowDepth = 0;
            effect.BlurRadius = 50;
            effect.RenderingBias = RenderingBias.Performance;
            effect.Direction = 360;
            effect.Opacity = 70;
        }


        public void LoadLastSave()
        {
            BinaryFormatter form = new BinaryFormatter();
            if (File.Exists("SaveInfo.txt"))
            {
                using (FileStream input = File.Open("SaveInfo.txt", FileMode.OpenOrCreate))
                {
                    isWasSaved = (bool)form.Deserialize(input);
                }
            }
            else
            {
                isWasSaved = false;
            }
        }

        public void SaveLastSave()
        {
            BinaryFormatter form = new BinaryFormatter();
            using (FileStream output = File.Open("SaveInfo.txt", FileMode.Create))
            {
                form.Serialize(output, isWasSaved);
            }
        }


        public void DrawField()
        {
            for (int i = 0; i < 10; i++)
            {
                for (int j = 0; j < 15; j++)
                {
                    field[i, j] = new Image();
                    BitmapImage bi = new BitmapImage(new Uri("Resources/empty.png", UriKind.Relative));
                    field[i, j].Source = bi;
                    field[i, j].Width = 40;
                    field[i, j].Height = 40;
                    canvasMain.Children.Add(field[i, j]);
                    Canvas.SetLeft(field[i, j], i * 40);
                    Canvas.SetTop(field[i, j], j * 40);
                }
            }
        }

        private void timer_Tick(object sender, EventArgs e)
        {

            gameCntrl.Update();
            if (isPlaying)
            {
                RedrowField();
                l_score.Content = String.Format("{0}", gameCntrl.GetScore());
                SetImageForNextFigure();
            }

        }

        public void SetImageForNextFigure()
        {
            FigureType next = gameCntrl.GetNextFigure();
            Image tmpImg = new Image();

            switch (next)
            {
                case FigureType.I:
                    tmpImg.Source = new BitmapImage(new Uri("Resources/IFigure.png", UriKind.Relative));
                    break;
                case FigureType.T:
                    tmpImg.Source = new BitmapImage(new Uri("Resources/TFigure.png", UriKind.Relative));
                    break;
                case FigureType.O:
                    tmpImg.Source = new BitmapImage(new Uri("Resources/OFigure.png", UriKind.Relative));
                    break;
                case FigureType.Z:
                    tmpImg.Source = new BitmapImage(new Uri("Resources/ZFigure.png", UriKind.Relative));
                    break;
                case FigureType.S:
                    tmpImg.Source = new BitmapImage(new Uri("Resources/SFigure.png", UriKind.Relative));
                    break;
                case FigureType.J:
                    tmpImg.Source = new BitmapImage(new Uri("Resources/JFigure.png", UriKind.Relative));
                    break;
                case FigureType.L:
                    tmpImg.Source = new BitmapImage(new Uri("Resources/LFigure.png", UriKind.Relative));
                    break;
            }
            NextFigure.Source = tmpImg.Source;
        }

        public void RedrowField()
        {
            FigureType[,] gameField = gameCntrl.GetField();
            FigureType color = gameCntrl.GetCurrentColor();
            for (int i = 0; i < 10; i++)
            {
                for (int j = 0; j < 15; j++)
                {
                    if (gameField[i, j] == FigureType.Current)
                    {
                        Canvas.SetZIndex(field[i, j], 1);
                        switch (color)
                        {
                            case FigureType.I:
                                {
                                    field[i, j].Source = new BitmapImage(new Uri("Resources/Blue.png", UriKind.Relative));
                                    effect.Color = Colors.Blue;
                                    field[i, j].Effect = effect;
                                    break;
                                }
                            case FigureType.T:
                                {
                                    field[i, j].Source = new BitmapImage(new Uri("Resources/Orange.png", UriKind.Relative));
                                    effect.Color = Colors.Orange;
                                    field[i, j].Effect = effect;
                                    break;
                                }
                            case FigureType.O:
                                {
                                    field[i, j].Source = new BitmapImage(new Uri("Resources/Green.png", UriKind.Relative));
                                    effect.Color = Colors.GreenYellow;
                                    field[i, j].Effect = effect;
                                    break;
                                }
                            case FigureType.Z:
                                {
                                    field[i, j].Source = new BitmapImage(new Uri("Resources/Pink.png", UriKind.Relative));
                                    effect.Color = Colors.DarkViolet;
                                    field[i, j].Effect = effect;
                                    break;
                                }
                            case FigureType.S:
                                {
                                    field[i, j].Source = new BitmapImage(new Uri("Resources/Yellow.png", UriKind.Relative));
                                    effect.Color = Colors.Yellow;
                                    field[i, j].Effect = effect;
                                    break;
                                }
                            case FigureType.J:
                                {
                                    field[i, j].Source = new BitmapImage(new Uri("Resources/BlueLight.png", UriKind.Relative));
                                    effect.Color = Colors.Aqua;
                                    field[i, j].Effect = effect;
                                    break;
                                }
                            case FigureType.L:
                                {
                                    field[i, j].Source = new BitmapImage(new Uri("Resources/Red.png", UriKind.Relative));
                                    effect.Color = Colors.Red;
                                    field[i, j].Effect = effect;
                                    break;
                                }
                        }
                    }
                    else if (gameField[i, j] != FigureType.None)
                    {
                        Canvas.SetZIndex(field[i, j], 0);
                        field[i, j].Effect = null;
                        switch (gameField[i, j])
                        {
                            case FigureType.I:
                                {
                                    field[i, j].Source = new BitmapImage(new Uri("Resources/Blue.png", UriKind.Relative));
                                    break;
                                }
                            case FigureType.T:
                                {
                                    field[i, j].Source = new BitmapImage(new Uri("Resources/Orange.png", UriKind.Relative));
                                    break;
                                }
                            case FigureType.O:
                                {
                                    field[i, j].Source = new BitmapImage(new Uri("Resources/Green.png", UriKind.Relative));
                                    break;
                                }
                            case FigureType.Z:
                                {
                                    field[i, j].Source = new BitmapImage(new Uri("Resources/Pink.png", UriKind.Relative));
                                    break;
                                }
                            case FigureType.S:
                                {
                                    field[i, j].Source = new BitmapImage(new Uri("Resources/Yellow.png", UriKind.Relative));
                                    break;
                                }
                            case FigureType.J:
                                {
                                    field[i, j].Source = new BitmapImage(new Uri("Resources/BlueLight.png", UriKind.Relative));
                                    break;
                                }
                            case FigureType.L:
                                {
                                    field[i, j].Source = new BitmapImage(new Uri("Resources/Red.png", UriKind.Relative));
                                    break;
                                }
                        }
                    }
                    else
                    {
                        Canvas.SetZIndex(field[i, j], 0);
                        field[i, j].Effect = null;
                        field[i, j].Source = new BitmapImage(new Uri("Resources/empty.png", UriKind.Relative));
                    }

                }
            }
        }

        private void Window_KeyDown(object sender, KeyEventArgs e)
        {
            if (isPlaying)
            {
                if (gameCntrl.isActiveFigure)
                {
                    if (e.Key == Key.Left)
                        gameCntrl.Move(Direction.Left);
                    if (e.Key == Key.Right)
                        gameCntrl.Move(Direction.Right);
                    if (e.Key == Key.Down)
                        gameCntrl.Update();
                    if (e.Key == Key.Up)
                        gameCntrl.Rotate();
                    RedrowField();

                }
            }
        }


        private void b_NewGame_Click(object sender, RoutedEventArgs e)
        {
            p_MainMenu.IsEnabled = false;
            p_MainMenu.Visibility = Visibility.Hidden;

            p_GameMenu.IsEnabled = true;
            p_GameMenu.Visibility = Visibility.Visible;

            isPlaying = true;
            isWasSaved = false;

            gameCntrl = new GameController(this.Height, this.Width);
            gameCntrl.EGameOver += GameCntrl_EGameOver;
            timer.Start();
        }

        private void GameCntrl_EGameOver(object sender, EventArgs e)
        {
            isPlaying = false;
            timer.Stop();

            records.Save(gameCntrl.GetScore());

            p_MainMenu.IsEnabled = true;
            p_MainMenu.Visibility = Visibility.Visible;

            p_GameMenu.IsEnabled = false;
            p_GameMenu.Visibility = Visibility.Hidden;


            isWasSaved = false;
            MessageBox.Show("GameOver!");
        }

        private void b_Resume_Click(object sender, RoutedEventArgs e)
        {
            if (isWasSaved)
            {
                LoadGame();
                p_MainMenu.IsEnabled = false;
                p_MainMenu.Visibility = Visibility.Hidden;

                p_GameMenu.IsEnabled = true;
                p_GameMenu.Visibility = Visibility.Visible;

                isPlaying = true;
                gameCntrl.EGameOver += GameCntrl_EGameOver;
                timer.Start();
            }

        }

        private void b_Records_Click(object sender, RoutedEventArgs e)
        {
            p_MainMenu.IsEnabled = false;
            p_MainMenu.Visibility = Visibility.Hidden;

            p_Records.IsEnabled = true;
            p_Records.Visibility = Visibility.Visible;

            l_Records.Content = records.GetRecString();
        }

        private void b_Exit_Click(object sender, RoutedEventArgs e)
        {
            if (isWasSaved)
                SaveGame();
            SaveLastSave();
            Environment.Exit(0);
        }

        private void b_ToMainMenu_Click(object sender, RoutedEventArgs e)
        {
            p_MainMenu.IsEnabled = true;
            p_MainMenu.Visibility = Visibility.Visible;

            p_GameMenu.IsEnabled = false;
            p_GameMenu.Visibility = Visibility.Hidden;

            isPlaying = false;
            isWasSaved = true;
            gameCntrl.EGameOver -= GameCntrl_EGameOver;                 //Чуть не умер на этом месте :)
            SaveGame();

            timer.Stop();
        }

        private void b_Pause_Click(object sender, RoutedEventArgs e)
        {
            if (isPlaying)
            {
                timer.Stop();
                b_Pause.Content = "Resume";
                isPlaying = false;
            }
            else
            {
                timer.Start();
                b_Pause.Content = "Pause";
                isPlaying = true;
            }
        }

        private void b_ToMenuFromRec_Click(object sender, RoutedEventArgs e)
        {
            p_MainMenu.IsEnabled = true;
            p_MainMenu.Visibility = Visibility.Visible;

            p_Records.IsEnabled = false;
            p_Records.Visibility = Visibility.Hidden;

        }

        private void SaveGame()
        {
            BinaryFormatter form = new BinaryFormatter();
            using (FileStream output = File.Open("GameCntrl.txt", FileMode.Create))
            {
                form.Serialize(output, gameCntrl);
            }
        }

        private void LoadGame()
        {
            BinaryFormatter form = new BinaryFormatter();
            if (File.Exists("GameCntrl.txt"))
            {
                using (FileStream input = File.Open("GameCntrl.txt", FileMode.OpenOrCreate))
                {
                    gameCntrl = new GameController(0, 0);
                    gameCntrl = (GameController)form.Deserialize(input);
                }
            }
        }
    }
}

