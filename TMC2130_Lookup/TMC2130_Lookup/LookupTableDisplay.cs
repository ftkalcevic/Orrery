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
    class LookupTableDisplay : System.Windows.Forms.Panel
    {
        const int CLICK_DISTANCE = 4;       // # pixels click distance squared
        const int SELECT_RECT = 5;          
        float scaleX, scaleY;
        float offsetX, offsetY;
        int activeLookup;
        int selectedPoint;
        RectangleF selectRect;
        TMCLookup m_lookup;
        List<PointF> scaledLookup;
        PointF startClick;
        bool dragging;

        public TMCLookup lookup
        {
            set
            {
                m_lookup = value;
                MakeScaledValues();
            }
        }

        public LookupTableDisplay()
        {
            dragging = false;
            activeLookup = -1;
            selectedPoint = -1;
            DoubleBuffered = true;
        }

        float ScaleX(float x)
        {
            return (float)(x * scaleX + offsetX);
        }

        float ScaleY(float y)
        {
            return Height - (float)(y * scaleY + offsetY);
        }

        float ReverseScaleY(float sy)
        {
            // sy = Height - (y * scale + offs )
            // sy - height = -y * scale - offs
            // sy - height + offs = -y * scale
            // y = -(sy - half + offs )/ scale
            return  -(sy - Height + offsetY) / scaleY;
        }

        private void MakeScaledValues()
        {
            if (m_lookup != null && m_lookup.lookupCount > 0)
            {
                scaledLookup = new List<PointF>(m_lookup.lookupCount);
                for (int i = 0; i < m_lookup.lookupCount; i++)
                {
                    scaledLookup.Add(new PointF(ScaleX(i), ScaleY(m_lookup.lookup((uint)i))));
                }
            }
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);

            if (m_lookup == null)
                return;

            Graphics g = e.Graphics;
            g.DrawLine(new Pen(Color.Red, 1), ScaleX(0), ScaleY(256), ScaleX(0), ScaleY(-256));
            g.DrawLine(new Pen(Color.Red, 1), ScaleX(0), ScaleY(0), ScaleX(1024), ScaleY(0));

            GraphicsPath p = new GraphicsPath();
            for (int i = 0; i < m_lookup.lookupCount-1; i++)
            {
                p.AddLine(scaledLookup[i].X, scaledLookup[i].Y, scaledLookup[i + 1].X, scaledLookup[i + 1].Y );
            }
            g.DrawPath(new Pen(Color.Blue, 1), p);

            if (selectedPoint >= 0)
            {
                g.DrawRectangle(new Pen(Color.Red, 1), selectRect.X, selectRect.Y, selectRect.Width, selectRect.Height);
            }

            if ( activeLookup >= 0 )
                g.DrawLine(new Pen(Color.Green, 1), ScaleX(activeLookup), ScaleY(256), ScaleX(activeLookup), ScaleY(-256));
        }

        protected override void OnSizeChanged(EventArgs e)
        {
            CalculateScale();
            MakeScaledValues();
            Invalidate();
            base.OnSizeChanged(e);
        }

        private void CalculateScale()
        {
            scaleX = (float)Width / (float)1024;
            scaleY = (float)Height / (float)(256 * 2.2);
            offsetX = 0;
            offsetY = Height / 2;
        }

        public void setStep(int lookup)
        {
            //Invalidate(new Rectangle((int)ScaleX(activeLookup), (int)ScaleY(256), (int)ScaleX(activeLookup), (int)ScaleY(-256)));
            activeLookup = lookup;
            //Invalidate(new Rectangle((int)ScaleX(activeLookup), (int)ScaleY(256), (int)ScaleX(activeLookup), (int)ScaleY(-256)));
            Invalidate();
        }

        float distanceSq(PointF pt1, PointF pt2)
        {
            float dx = pt1.X - pt2.X;
            float dy = pt1.Y - pt2.Y;

            return dx * dx + dy * dy;
        }

        private int findPoint(PointF pt)
        {
            int newSelectedPoint = -1;
            for (int i = 0; i < scaledLookup.Count; i++)
            {
                if (distanceSq(pt, scaledLookup[i]) < CLICK_DISTANCE)
                {
                    newSelectedPoint = i;
                    break;
                }
            }
            return newSelectedPoint;
        }

        private bool selectPoint(PointF pt)
        {
            int newSelectedPoint = findPoint(pt);
            if (newSelectedPoint != selectedPoint)
            {
                selectedPoint = newSelectedPoint;
                if (selectedPoint >= 0)
                {
                    selectRect = new RectangleF(scaledLookup[selectedPoint].X - SELECT_RECT / 2, scaledLookup[selectedPoint].Y - SELECT_RECT / 2, SELECT_RECT, SELECT_RECT);
                }
                Invalidate();
            }
            return selectedPoint >= 0;
        }

        protected override void OnMouseDown(MouseEventArgs e)
        {
            PointF click = new PointF(e.X, e.Y);
            dragging = selectPoint(click);
            base.OnMouseDown(e);
        }

        protected override void OnMouseMove(MouseEventArgs e)
        {
            if (dragging)
            {
                m_lookup.DragTo(selectedPoint, (int)Math.Round(ReverseScaleY(e.Y)));
                MakeScaledValues();
                selectRect = new RectangleF(scaledLookup[selectedPoint].X - SELECT_RECT / 2, scaledLookup[selectedPoint].Y - SELECT_RECT / 2, SELECT_RECT, SELECT_RECT);
                Invalidate();
            }
            else
            {
                selectPoint(new PointF(e.X, e.Y));
            }

            base.OnMouseMove(e);
        }

        protected override void OnMouseUp(MouseEventArgs e)
        {
            dragging = false;
            base.OnMouseUp(e);
        }
    }
}
