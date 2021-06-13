using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing;
using System.Drawing.Drawing2D;

namespace TMC2130_Lookup
{
    class CircleDisplay: System.Windows.Forms.Panel
    {
        float scaleX, scaleY;
        float offsetX, offsetY;
        float _angle;

        public float angle
        {
            set
            {
                _angle = value;
                Invalidate();
            }
            get
            {
                return _angle;
            }
        }

        public CircleDisplay()
        {
            angle = 0;
            DoubleBuffered = true;
        }

        float ScaleX(float x)
        {
            return (float)(x * scaleX + offsetX);
        }

        float ScaleY(float y)
        {
            return (float)(y * scaleY + offsetY);
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);

            Graphics g = e.Graphics;

            RectangleF circleRect = new RectangleF(ScaleX(10), ScaleY(10), ScaleX(80), ScaleY(80));
            for (int i = 0; i < 20; i += 4)
            {
                g.FillPie(Brushes.LightGray, circleRect.X, circleRect.Y, circleRect.Width, circleRect.Height, 360 * (float)i / 20, 2 * 360 / 20);
            }

            g.DrawEllipse(Pens.Red, new RectangleF(ScaleX(10), ScaleY(10), ScaleX(80), ScaleY(80) ) );
            g.DrawLine(Pens.Blue, ScaleX(50.0F), ScaleY(50.0F),
                                                ScaleX(50.0F + 40.0F * (float)Math.Cos(_angle)),
                                                ScaleY(50.0F + 40.0F * (float)Math.Sin(_angle)));
        }

        protected override void OnSizeChanged(EventArgs e)
        {
            CalculateScale();
            base.OnSizeChanged(e);
        }

        private void CalculateScale()
        {
            if (Width > Height)
            {
                scaleX = scaleY = Height / 100;
                offsetX = (Width - Height)/ 2;
                offsetY = 0;
            }
            else
            {
                scaleX = scaleY = Width / 100;
                offsetX = 0;
                offsetY = (Height - Width) / 2;
            }
        }
    }
}
