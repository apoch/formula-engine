using System;
using System.Windows.Forms;

namespace FormulaEdit
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new MainForm());
        }
    }


    internal class Utilities
    {
        static internal void ResizeControls(FlowLayoutPanel parent)
        {
            int w = parent.ClientRectangle.Width - 10;

            foreach (Control c in parent.Controls)
            {
                c.Width = w;
            }
        }
    }
}
