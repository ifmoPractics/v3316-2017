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
    /// Логика взаимодействия для Colorpicker.xaml
    /// </summary>
    public partial class Colorpicker : UserControl
    {
        public Colorpicker()
        {
            InitializeComponent();
        }

        public Brush SelectedColor
        {
            get { return (Brush)GetValue(SelectedColorProperty); }
            set { SetValue(SelectedColorProperty, value); }
        }

        // Using a DependencyProperty as the backing store for SelectedColor.  
        // This enables animation, styling, binding, etc...
        public static readonly DependencyProperty SelectedColorProperty =
            DependencyProperty.Register("SelectedColor",
        typeof(Brush), typeof(Colorpicker), new UIPropertyMetadata(null));
    }
}
