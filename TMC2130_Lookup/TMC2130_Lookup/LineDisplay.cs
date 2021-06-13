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
    class LineDisplay : System.Windows.Forms.Panel
    {
        class PointSample
        {
            public float angle;
            public float error;

        }

        float scaleX, scaleY;
        float offsetX, offsetY;
        List<PointSample> points;
        float maxY;

        public bool autoScaleY;
        public double _maxAngle;


        public double maxAngle
        {
            set
            {
                _maxAngle = value;
                CalculateScale();
            }
            get
            {
                return _maxAngle;
            }
        }

        public LineDisplay()
        {
            points = new List<PointSample>();
            _maxAngle = 100;
            maxY = 0.01f;
            autoScaleY = true;
            DoubleBuffered = true;
        }

        public void clear()
        {
            points = new List<PointSample>();
            maxY = 0.01f;
            CalculateScale();
        }

        public void AddPoint(double expectedAngle, double angle)
        {
            float error = (float)Program.negPI2PI(angle - expectedAngle);
            if (autoScaleY && Math.Abs(error) > maxY)
            {
                maxY = Math.Abs(error);
                CalculateScale();
            }

            points.Add(new PointSample() { angle = (float)expectedAngle % (float)_maxAngle, error = (float)(angle - expectedAngle) });
            Invalidate();
        }

        float ScaleX(float x)
        {
            return (float)(x * scaleX + offsetX);
        }

        float ScaleY(float y)
        {
            return Height - (float)(y * scaleY + offsetY);
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);

            Graphics g = e.Graphics;

            g.DrawLine(new Pen(Color.Red, 1), ScaleX(0), ScaleY(0), ScaleX((float)_maxAngle), ScaleY(0));
            GraphicsPath p = new GraphicsPath();
            for (int i = 0; i < points.Count - 1; i++)
            {
                if (Math.Abs(points[i].angle - points[i + 1].angle) > _maxAngle/2)
                {
                    g.DrawPath(new Pen(Color.Blue, 1), p);
                    p = new GraphicsPath();
                }
                else
                {
                    p.AddLine(ScaleX(points[i].angle), ScaleY(points[i].error), ScaleX(points[i + 1].angle), ScaleY(points[i + 1].error));
                }
            }
            g.DrawPath(new Pen(Color.Blue, 1), p);
        }

        protected override void OnSizeChanged(EventArgs e)
        {
            CalculateScale();
            base.OnSizeChanged(e);
        }

        private void CalculateScale()
        {
            scaleX = (float)Width / (float)_maxAngle;
            scaleY = (float)Height / (float)(maxY*2.2);
            offsetX = 0;
            offsetY = Height/2;
        }
    }
}
