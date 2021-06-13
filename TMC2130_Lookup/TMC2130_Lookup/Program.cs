using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TMC2130_Lookup
{
    static class Program
    {
        /// <summary>
        ///  The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.SetHighDpiMode(HighDpiMode.SystemAware);
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
        }

        static public float zeroTo2PI(float angle)
        {
            return (float)zeroTo2PI((double)angle);
        }

        static public double zeroTo2PI(double angle)
        {
            return (Math.PI * 2 + (angle % (2 * Math.PI))) % (2 * Math.PI);
        }

        static public double negPI2PI(double a)
        {
            return (Program.zeroTo2PI(a) + Math.PI) % (2*Math.PI) - Math.PI;
        }
    }
}
