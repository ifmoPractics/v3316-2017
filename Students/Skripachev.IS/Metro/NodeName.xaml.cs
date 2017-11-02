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
    /// Логика взаимодействия для NodeName.xaml
    /// </summary>
    public partial class NodeName : Window
    {

        public NodeName()
        {
            InitializeComponent();
        }

        private void b_ok_Click(object sender, RoutedEventArgs e)
        {
            this.DialogResult = true;
        }

        public string GetName()
        {
            return t_name.Text;
        }

        private void t_name_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (!t_name.Text.Equals(String.Empty))
            {
                b_ok.IsEnabled = true;
                return;
            }
            b_ok.IsEnabled = false;
        }
    }
}
