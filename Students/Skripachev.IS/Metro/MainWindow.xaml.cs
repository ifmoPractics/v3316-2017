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

namespace Metro
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {

        MetroNode[] m_currentButton = new MetroNode[2];
        List<MetroNode> m_listButton = new List<MetroNode>();
        bool m_nodeIsPressed = false;
        Line m_currentLine = null;
        Brush m_lastLineColor = null;
        Search m_search = new Search();

        public MainWindow()
        {
            InitializeComponent();

            m_currentButton[0] = null;
            m_currentButton[1] = null;
        }

        //Создание узла станции
        private MetroNode CreateNode(double x, double y, double w, double h, Brush color, string name)
        {
            Label nameStation = new Label()
            {
                Width = Double.NaN,
                Height = 30,
                Content = name
            };

            MetroNode tempLabel = new MetroNode(w, h, color, nameStation);
            m_listButton.Add(tempLabel);

            tempLabel.MouseUp += Button_MouseUp;
            tempLabel.MouseMove += Button_MouseMove;
            tempLabel.MouseDown += Button_MouseDown;
            tempLabel.Click += currentBut_Click;
            c_mainCanvas.Children.Add(tempLabel);
            c_mainCanvas.Children.Add(nameStation);
            Canvas.SetLeft(tempLabel, x);
            Canvas.SetTop(tempLabel, y);
            Canvas.SetZIndex(tempLabel, 2);
            Canvas.SetLeft(nameStation, 26);
            Canvas.SetZIndex(nameStation, 1);
            tempLabel.nameNode.SetValue(Canvas.LeftProperty, (double)tempLabel.GetValue(Canvas.LeftProperty) + 26);
            tempLabel.nameNode.SetValue(Canvas.TopProperty, (double)tempLabel.GetValue(Canvas.TopProperty));
            return tempLabel;
        }

        //Создание кнопок
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            string nameStation = "";
            NodeName n = new NodeName();
            if (n.ShowDialog() == true)
            {
                nameStation = n.GetName();
            }
            else return;
            CreateNode(50, 50, 25, 25, c_colorPicker.SelectedColor, nameStation);
        }

        //Перемещение станций
        private void Button_MouseMove(object sender, MouseEventArgs e)
        {
            if (m_nodeIsPressed)
            {
                //Button tempLabel = sender as Button;
                MetroNode tempLabel = sender as MetroNode;
                double currX = e.GetPosition(this).X - 10;
                double currY = e.GetPosition(this).Y - 10;
                tempLabel.SetValue(Canvas.LeftProperty, currX);
                tempLabel.SetValue(Canvas.TopProperty, currY);

                tempLabel.ReDrawLine((double)tempLabel.GetValue(Canvas.LeftProperty) + 12.5, (double)tempLabel.GetValue(Canvas.TopProperty) + 12.5);
                tempLabel.nameNode.SetValue(Canvas.LeftProperty, (double)tempLabel.GetValue(Canvas.LeftProperty) + 26);
                tempLabel.nameNode.SetValue(Canvas.TopProperty, (double)tempLabel.GetValue(Canvas.TopProperty));
            }
        }

        //Нажатие перед перемещением
        private void Button_MouseDown(object sender, MouseButtonEventArgs e)
        {
            m_nodeIsPressed = true;
        }

        //Прекращение перемещения приотпускании клавиши
        private void Button_MouseUp(object sender, MouseButtonEventArgs e)
        {
            m_nodeIsPressed = false;
        }

        //Добавление перегона
        private void b_addDist_Click(object sender, RoutedEventArgs e)
        {
            if (m_currentButton[0] != null && m_currentButton[1] != null)
            {
                if (m_currentButton[0].CountLines() > 5 || m_currentButton[1].CountLines() > 5)
                {
                    MessageBox.Show("The maximum number of overtures has been exceeded!", "Error!");
                    return;
                }

                if(m_currentButton[0] == m_currentButton[1])
                {
                    MessageBox.Show("You can not create a overture between one station!", "Error!");
                    return;
                }

                if (m_search.IsExist(m_currentButton[0], m_currentButton[1]))
                {
                    MessageBox.Show("Overture already exists!", "Error!");
                    return;
                }


                
                
                if (m_currentButton[0].NodeColor != m_currentButton[1].NodeColor)
                {
                    double smejY = 25;
                    if (m_currentButton[1].CountLines() >= 2)
                    {
                        smejY *= m_currentButton[1].CountLines()-1;
                    }

                    string nameStation = "";
                    NodeName n = new NodeName();
                    if (n.ShowDialog() == true)
                    {
                        nameStation = n.GetName();
                    }
                    else return;
                    MetroNode tempNode = CreateNode((double)m_currentButton[1].GetValue(Canvas.LeftProperty), (double)m_currentButton[1].GetValue(Canvas.TopProperty) + smejY,
                       25, 25, m_currentButton[0].NodeColor, nameStation);

                    MetroNode.NodesLine tempLine = new MetroNode.NodesLine();
                    tempLine.line = new Line();
                    tempLine.line.MouseDown += Line_MouseDown;
                    tempLine.line.Stroke = m_currentButton[0].NodeColor;
                    tempLine.line.StrokeThickness = 8.0;

                    int distance1 = 0;
                    Distance dis = new Distance();
                    dis.SetTextForMessage(String.Format("Enter the distance between the <{0}> and the <{1}>", m_currentButton[0].nameNode.Content, tempNode.nameNode.Content));
                    if (dis.ShowDialog() == true)
                    {
                            distance1 = dis.Dist();
                    }
                    else return;


                    int distance2 = 0;
                    Distance dis2 = new Distance();
                    dis2.SetTextForMessage(String.Format("Enter the distance between the <{0}> and the <{1}>", tempNode.nameNode.Content, m_currentButton[1].nameNode.Content));
                    if (dis2.ShowDialog() == true)
                    {
                        distance2 = dis2.Dist();
                    }
                    else return;

                    tempLine.line.X1 = (double)m_currentButton[0].GetValue(Canvas.LeftProperty) + 12.5;
                    tempLine.line.X2 = (double)tempNode.GetValue(Canvas.LeftProperty) + 12.5;
                    tempLine.line.Y1 = (double)m_currentButton[0].GetValue(Canvas.TopProperty) + 12.5;
                    tempLine.line.Y2 = (double)tempNode.GetValue(Canvas.TopProperty) + 12.5;
                    m_currentButton[0].AddLine(tempLine.line, 1, tempNode, m_currentButton[0].NodeColor);
                    m_search.AddEdge(m_currentButton[0], tempNode, distance1);
                    tempNode.AddLine(tempLine.line, 2, m_currentButton[0], tempNode.NodeColor);
                    m_search.AddEdge(tempNode, m_currentButton[0], distance1);
                    c_mainCanvas.Children.Add(tempLine.line);

                    MetroNode.NodesLine tempLine2 = new MetroNode.NodesLine();
                    tempLine2.line = new Line();
                    tempLine2.line.MouseDown += Line_MouseDown;
                    tempLine2.line.Stroke = Brushes.Black;
                    tempLine2.line.StrokeThickness = 8.0;

                    tempLine2.line.X1 = (double)tempNode.GetValue(Canvas.LeftProperty) + 12.5;
                    tempLine2.line.X2 = (double)m_currentButton[1].GetValue(Canvas.LeftProperty) + 12.5;
                    tempLine2.line.Y1 = (double)tempNode.GetValue(Canvas.TopProperty) + 12.5;
                    tempLine2.line.Y2 = (double)m_currentButton[1].GetValue(Canvas.TopProperty) + 12.5;
                    tempNode.AddLine(tempLine2.line, 1, m_currentButton[1], Brushes.Black);
                    m_search.AddEdge(tempNode, m_currentButton[1], distance2);
                    m_currentButton[1].AddLine(tempLine2.line, 2, tempNode, Brushes.Black);
                    m_search.AddEdge(m_currentButton[1], tempNode, distance2);
                    c_mainCanvas.Children.Add(tempLine2.line);
                    
                }
                else
                {
                    int distance = 0;
                    Distance dis = new Distance();
                    dis.SetTextForMessage(String.Format("Enter the distance between the <{0}> and the <{1}>", m_currentButton[0].nameNode.Content, m_currentButton[1].nameNode.Content));
                    if (dis.ShowDialog() == true)
                    {
                            distance = dis.Dist();
                    }
                    else return;
                    MetroNode.NodesLine line = new MetroNode.NodesLine();

                    line.line = new Line();
                    line.line.MouseDown += Line_MouseDown;
                    line.line.Stroke = m_currentButton[0].NodeColor;
                    line.line.StrokeThickness = 8.0;

                    line.line.X1 = (double)m_currentButton[0].GetValue(Canvas.LeftProperty) + 12.5;
                    line.line.X2 = (double)m_currentButton[1].GetValue(Canvas.LeftProperty) + 12.5;
                    line.line.Y1 = (double)m_currentButton[0].GetValue(Canvas.TopProperty) + 12.5;
                    line.line.Y2 = (double)m_currentButton[1].GetValue(Canvas.TopProperty) + 12.5;
                    m_currentButton[0].AddLine(line.line, 1, m_currentButton[1], m_currentButton[0].NodeColor);
                    m_search.AddEdge(m_currentButton[0], m_currentButton[1], distance);
                    m_currentButton[1].AddLine(line.line, 2, m_currentButton[0], m_currentButton[1].NodeColor);
                    m_search.AddEdge(m_currentButton[1], m_currentButton[0], distance);
                    c_mainCanvas.Children.Add(line.line);
                }
            }
        }

        //Нажатие перед перемещением
        private void Line_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (m_currentLine != null)
                m_currentLine.Stroke = m_lastLineColor;
            m_currentLine = sender as Line;
            m_lastLineColor = m_currentLine.Stroke;
            m_currentLine.Stroke = Brushes.Red;
            if (m_currentButton[0] != null)
            {
                m_currentButton[0].Background = m_currentButton[0].NodeColor;
                m_currentButton[0] = null;
            }
            if (m_currentButton[1] != null)
            {
                m_currentButton[1].Background = m_currentButton[1].NodeColor;
                m_currentButton[1] = null;
            }

        }

        //Выбор текущей кнопки
        private void currentBut_Click(object sender, RoutedEventArgs e)
        {
            if (m_currentLine != null)
            {
                m_currentLine.Stroke = m_lastLineColor;
                m_currentLine = null;
            }

            if (m_currentButton[0] != null)
                m_currentButton[0].Background = m_currentButton[0].NodeColor;
            m_currentButton[0] = m_currentButton[1];
            if (m_currentButton[0] != null)
                m_currentButton[0].Background = Brushes.Yellow;
            m_currentButton[1] = sender as MetroNode;
            if (m_currentButton[1] != null)
                m_currentButton[1].Background = Brushes.LightGreen;
        }


        //Обработчик нажатия клавиатуры
        private void Window_KeyDown(object sender, KeyEventArgs e)
        {
            switch (e.Key)
            {
                case Key.Delete:
                    {
                        if (m_currentButton[1] != null)
                        {
                            c_mainCanvas.Children.Remove(m_currentButton[1]);
                            c_mainCanvas.Children.Remove(m_currentButton[1].nameNode);
                            Line[] tempLines = m_currentButton[1].DeleteLine2(ref m_search);
                            m_listButton.Remove(m_currentButton[1]);
                            m_currentButton[1].nameNode = null;
                            m_currentButton[1] = null;
                            for (int i = 0; i < MetroNode.max_lines; i++)
                            {
                                if (tempLines[i] != null)
                                    c_mainCanvas.Children.Remove(tempLines[i]);
                            }
                        }
                        if (m_currentLine != null)
                        {
                            c_mainCanvas.Children.Remove(m_currentLine);
                            for (int i = 0; i < m_listButton.Count; i++)
                            {
                                m_listButton[i].DeleteOnlyLine2(m_currentLine,ref m_search);
                            }
                            m_currentLine = null;
                        }
                        break;
                    }
                case Key.Escape:
                    {
                        if (m_currentButton[0] != null)
                            m_currentButton[0].Background = m_currentButton[0].NodeColor;
                        if (m_currentButton[1] != null)
                            m_currentButton[1].Background = m_currentButton[1].NodeColor;
                        if (m_currentLine != null)
                            m_currentLine.Stroke = m_lastLineColor;
                        m_currentLine = null;
                        m_currentButton[0] = null;
                        m_currentButton[1] = null;
                        foreach(MetroNode n in m_listButton)
                        {
                            n.Background = n.NodeColor;
                        }
                        break;
                    }
            }
        }

        //Поиск пути
        private void Search_Click(object sender, RoutedEventArgs e)
        {
            l_search.Items.Clear();
            if (m_currentButton[0] != null && m_currentButton[1] != null)
            {
                List<MetroNode> way = m_search.SearchMinByDistance(m_currentButton[0], m_currentButton[1]);
                way.Reverse();
                foreach(MetroNode n in way)
                {
                    n.Background = Brushes.OrangeRed;
                    StackPanel panel = new StackPanel();
                    panel.Orientation = Orientation.Horizontal;
                    Label l = new Label();
                    l.Content = n.nameNode.Content;
                    panel.Children.Add(l);
                    panel.Background = n.NodeColor;
                    l_search.Items.Add(panel);
                }
            }
        }

        private void Search2_Click(object sender, RoutedEventArgs e)
        {
            l_search.Items.Clear();
            if (m_currentButton[0] != null && m_currentButton[1] != null)
            {
                List<MetroNode> way = m_search.SearchMinByOvertures(m_currentButton[0], m_currentButton[1]);
                way.Reverse();
                foreach (MetroNode n in way)
                {
                    n.Background = Brushes.OrangeRed;
                    StackPanel panel = new StackPanel();
                    panel.Orientation = Orientation.Horizontal;
                    Label l = new Label();
                    l.Content = n.nameNode.Content;
                    panel.Children.Add(l);
                    panel.Background = n.NodeColor;
                    l_search.Items.Add(panel);
                }
            }
        }
    }
}
