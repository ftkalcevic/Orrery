using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TMC2130_Lookup
{
    public enum Config
    {
        EncoderPPR = 4096
    };

    public partial class Form1 : Form
    {

        TMCLookup lookupTable;
        SerialInterface serial;
        CircleDisplay circle;
        LineDisplay line;
        LineDisplay lineSeg;
        LookupTableDisplay lookup;
        Timer t;
        int tick;
        int stepping;
        int steps_per_rev;
        bool direction;
        StepMonitor stepmon;

        private void Init()
        {
            //MSLUT[0]= %10101010101010101011010101010100 = 0xAAAAB554
            //MSLUT[1]= %01001010100101010101010010101010 = 0x4A9554AA
            //MSLUT[2]= %00100100010010010010100100101001 = 0x24492929
            //MSLUT[3]= %00010000000100000100001000100010 = 0x10104222
            //MSLUT[4]= %11111011111111111111111111111111 = 0xFBFFFFFF
            //MSLUT[5]= %10110101101110110111011101111101 = 0xB5BB777D
            //MSLUT[6]= %01001001001010010101010101010110 = 0x49295556
            //MSLUT[7]= %00000000010000000100001000100010 = 0x00404222
            //MSLUTSEL= 0xFFFF8056:
            //X1=128, X2=255, X3=255
            //W3=%01, W2=%01, W1=%01, W0=%10
            //MSLUTSTART= 0x00F70000:
            //START_SIN_0= 0, START_SIN90= 247
            UInt32[] MSLUT = new UInt32[] {
                    0xAAAAB554,
                    0x4A9554AA,
                    0x24492929,
                    0x10104222,
                    0xFBFFFFFF,
                    0xB5BB777D,
                    0x49295556,
                    0x00404222
                };
            UInt32 MSLUTSEL = 0xFFFF8056;
            UInt32 MSLUTSTART = 0x00F70000;

            lookupTable = new TMCLookup();
            lookupTable.MakeFromRegisters(MSLUT, MSLUTSEL, MSLUTSTART);
            lookup.lookup = lookupTable;

            txtStepsPerRev.Text = Properties.Settings.Default.StepsPerRev.ToString();
            chkChangeDirection.Checked = Properties.Settings.Default.Direction;
            numPeriod.Value = Properties.Settings.Default.Period;
            foreach (var item in cboStepping.Items)
                if (((id_name)item).id == Properties.Settings.Default.Stepping)
                {
                    cboStepping.SelectedItem = item;
                    break;
                }

            serial = new SerialInterface("COM3", 115200);
            serial.open();
            serial.PositionUpdate += Serial_PositionUpdate;

            tick = 0;


        }

        class id_name
        {
            public int id { get; set; }
            public string name { get; set; }
            public id_name(int id, string name)
            {
                this.id = id;
                this.name = name;
            }
        };

        public Form1()
        {
            InitializeComponent();

            cboStepping.Items.Add(new id_name(1, "Full Step"));
            cboStepping.Items.Add(new id_name(2, "Half Step"));
            cboStepping.Items.Add(new id_name(4, "Quarter Step"));
            cboStepping.Items.Add(new id_name(8, "1/8"));
            cboStepping.Items.Add(new id_name(16, "1/16"));
            cboStepping.Items.Add(new id_name(32, "1/32"));
            cboStepping.Items.Add(new id_name(64, "1/64"));
            cboStepping.Items.Add(new id_name(256, "1/256"));
            cboStepping.DisplayMember = "name";
            cboStepping.ValueMember = "id";

            circle = new CircleDisplay();
            circle.Anchor = panelCircle.Anchor;
            circle.BackColor = System.Drawing.SystemColors.Window;
            circle.Location = panelCircle.Location;
            circle.Name = "circlePanel";
            circle.Size = panelCircle.Size;
            circle.TabIndex = 0;
            this.Controls.Add(this.circle);
            panelCircle.Visible = false;

            line = new LineDisplay();
            line.Anchor = panelLine.Anchor;
            line.BackColor = System.Drawing.SystemColors.Window;
            line.Location = panelLine.Location;
            line.Name = panelLine.Name;
            line.Size = panelLine.Size;
            line.TabIndex = panelLine.TabIndex;
            this.Controls.Add(this.line);
            panelLine.Visible = false;

            lineSeg = new LineDisplay();
            lineSeg.Anchor = panelLineSegment.Anchor;
            lineSeg.BackColor = System.Drawing.SystemColors.Window;
            lineSeg.Location = panelLineSegment.Location;
            lineSeg.Name = panelLineSegment.Name;
            lineSeg.Size = panelLineSegment.Size;
            lineSeg.TabIndex = panelLineSegment.TabIndex;
            this.Controls.Add(this.lineSeg);
            panelLineSegment.Visible = false;

            lookup = new LookupTableDisplay();
            lookup.Anchor = panelLookupTable.Anchor;
            lookup.BackColor = System.Drawing.SystemColors.Window;
            lookup.Location = panelLookupTable.Location;
            lookup.Name = panelLookupTable.Name;
            lookup.Size = panelLookupTable.Size;
            lookup.TabIndex = panelLookupTable.TabIndex;
            this.Controls.Add(this.lookup);
            panelLookupTable.Visible = false;

            Init();
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            Properties.Settings.Default.StepsPerRev = int.Parse(txtStepsPerRev.Text);
            Properties.Settings.Default.Direction = chkChangeDirection.Checked;
            Properties.Settings.Default.Stepping = ((id_name)cboStepping.SelectedItem).id;
            Properties.Settings.Default.Period = (int)numPeriod.Value;
            Properties.Settings.Default.Save();
        }

        private void T_Tick(object sender, EventArgs e)
        {
            //float tickAngle = (((direction?-1:1)*tick % 1024) + 1024) % 1024;
            //float stepAngle = 1024* (Program.zeroTo2PI(circle.angle) % (float)(2 * Math.PI / steps_per_rev * (stepping == 0 ? 1 : stepping))) / ((stepping == 0 ? 1 : stepping) * 2 * (float)Math.PI / steps_per_rev);

            //float error = tickAngle - stepAngle;
            //System.Diagnostics.Debug.WriteLine($"T:{tick} TA:{tickAngle} C:{circle.angle} SA:{stepAngle} E:{error}");
            //line.AddPoint(Math.Abs(tick), error);
            //lineSeg.AddPoint(Math.Abs(tick), error);
            //System.Diagnostics.Debug.WriteLine(tick);

            if (!direction)
                tick += 256 / stepping;
            else
                tick -= 256 / stepping;

            int a = lookupTable.lookup((uint)tick);
            int b = lookupTable.lookup((uint)(tick + (uint)lookupTable.lookupTable.Length));
            serial.SendPower(a, b);
            tbCurrent.Value = b;
            lookup.setStep(((tick % 1024) + 1024) % 1024);
            stepmon.MoveTick(0);
        }

        private void Serial_PositionUpdate(int position)
        {
            //System.Diagnostics.Debug.WriteLine(position);

            UInt16 p = (UInt16)position;
            p %= 4 * (int)Config.EncoderPPR;
            circle.angle = (float)(2 * Math.PI * (p) / (4 * (int)Config.EncoderPPR));

            if ( stepmon != null )
                stepmon.EncoderTick(position);
        }

        private void btnStart_Click(object sender, EventArgs e)
        {
            if (btnStart.Text == "Start")
            {
                stepping = ((id_name)cboStepping.SelectedItem).id;
                steps_per_rev = int.Parse(txtStepsPerRev.Text);
                direction = chkChangeDirection.Checked;
                tick = 256 / (stepping * 2);

                line.maxAngle = 2 * Math.PI;
                lineSeg.maxAngle = 2 * Math.PI / (steps_per_rev/4);

                if (stepmon == null)
                {
                    stepmon = new StepMonitor();
                    stepmon.NewSample += Stepmon_NewSample;
                }
                stepmon.stepping = stepping;
                stepmon.motor_steps_per_rev = steps_per_rev;

                if (t == null)
                {
                    t = new Timer();
                    t.Tick += T_Tick;
                }
                t.Interval = (int)numPeriod.Value;
                t.Start();

                btnStart.Text = "Stop";
            }
            else
            {
                t.Stop();
                btnStart.Text = "Start";
            }
        }

        private void Stepmon_NewSample(int tick, int encoderPosition)
        {
            double angle = 2 * Math.PI * (double)(encoderPosition - stepmon.wrapPoint) / ((int)Config.EncoderPPR * 4.0);
            double expectedAngle = 2 * Math.PI * (double)tick / (double)(stepping * steps_per_rev);
            expectedAngle = Program.zeroTo2PI(expectedAngle);
            angle = Program.zeroTo2PI(angle);
            System.Diagnostics.Debug.WriteLine($"Angle {angle} Expected {expectedAngle}");
            line.AddPoint(expectedAngle, angle);
            lineSeg.AddPoint(expectedAngle, angle);
        }

        private void numPeriod_ValueChanged(object sender, EventArgs e)
        {
            if (t != null)
                t.Interval = (int)numPeriod.Value;
        }

        private void btnStepBack_Click(object sender, EventArgs e)
        {
            if (t != null && !t.Enabled)
            {
                direction = !direction;
                T_Tick(null, null);
                direction = !direction;
            }
        }

        private void btnStepFwd_Click(object sender, EventArgs e)
        {
            if (t != null && !t.Enabled)
            {
                T_Tick(null, null);
            }
        }

        private void btnClear_Click(object sender, EventArgs e)
        {
            //if (t != null && !t.Enabled)
            {
                tick = 0;
                line.clear();
                lineSeg.clear();
                lookup.setStep(tick);
                stepmon.clear();
            }
        }

        private void tbCurrent_Scroll(object sender, EventArgs e)
        {

        }
    }
}
