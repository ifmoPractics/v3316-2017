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
using System.Windows.Shapes;

namespace Metro
{
    /// <summary>
    /// Логика взаимодействия для Distance.xaml
    /// </summary>
    public partial class Distance : Window
    {
        private int Result;
        public bool IsCorrect = false;

        public Distance()
        {
            InitializeComponent();
        }

        private void b_ok_Click(object sender, RoutedEventArgs e)
        {
            this.DialogResult = true;
            IsCorrect = true;
        }

        public void SetTextForMessage(string _text)
        {
            t_dis.Text = _text;
        }

        public int Dist()
        {
            return Result;
        }

        private void t_distance_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (!t_distance.Text.Equals(String.Empty))
            {
                if (Int32.TryParse(t_distance.Text, out Result))
                {
                    b_ok.IsEnabled = true;
                    return;
                }
            }
            b_ok.IsEnabled = false;
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            //this.DialogResult = false;
        }
    }
}
