
namespace TMC2130_Lookup
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.btnStart = new System.Windows.Forms.Button();
            this.panelCircle = new System.Windows.Forms.Panel();
            this.panelLine = new System.Windows.Forms.Panel();
            this.label1 = new System.Windows.Forms.Label();
            this.txtStepsPerRev = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.cboStepping = new System.Windows.Forms.ComboBox();
            this.panelLineSegment = new System.Windows.Forms.Panel();
            this.chkChangeDirection = new System.Windows.Forms.CheckBox();
            this.numPeriod = new System.Windows.Forms.NumericUpDown();
            this.label3 = new System.Windows.Forms.Label();
            this.panelLookupTable = new System.Windows.Forms.Panel();
            this.btnStepBack = new System.Windows.Forms.Button();
            this.btnStepFwd = new System.Windows.Forms.Button();
            this.btnClear = new System.Windows.Forms.Button();
            this.tbCurrent = new System.Windows.Forms.TrackBar();
            ((System.ComponentModel.ISupportInitialize)(this.numPeriod)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.tbCurrent)).BeginInit();
            this.SuspendLayout();
            // 
            // btnStart
            // 
            this.btnStart.Location = new System.Drawing.Point(12, 369);
            this.btnStart.Name = "btnStart";
            this.btnStart.Size = new System.Drawing.Size(75, 23);
            this.btnStart.TabIndex = 0;
            this.btnStart.Text = "Start";
            this.btnStart.UseVisualStyleBackColor = true;
            this.btnStart.Click += new System.EventHandler(this.btnStart_Click);
            // 
            // panelCircle
            // 
            this.panelCircle.Location = new System.Drawing.Point(13, 13);
            this.panelCircle.Name = "panelCircle";
            this.panelCircle.Size = new System.Drawing.Size(200, 200);
            this.panelCircle.TabIndex = 1;
            // 
            // panelLine
            // 
            this.panelLine.Location = new System.Drawing.Point(220, 13);
            this.panelLine.Name = "panelLine";
            this.panelLine.Size = new System.Drawing.Size(200, 200);
            this.panelLine.TabIndex = 2;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(13, 241);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(54, 15);
            this.label1.TabIndex = 3;
            this.label1.Text = "Stepping";
            // 
            // txtStepsPerRev
            // 
            this.txtStepsPerRev.Location = new System.Drawing.Point(116, 270);
            this.txtStepsPerRev.Name = "txtStepsPerRev";
            this.txtStepsPerRev.Size = new System.Drawing.Size(100, 23);
            this.txtStepsPerRev.TabIndex = 6;
            this.txtStepsPerRev.Text = "20";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(13, 270);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(71, 15);
            this.label2.TabIndex = 5;
            this.label2.Text = "Motor Steps";
            // 
            // cboStepping
            // 
            this.cboStepping.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboStepping.FormattingEnabled = true;
            this.cboStepping.Location = new System.Drawing.Point(116, 238);
            this.cboStepping.Name = "cboStepping";
            this.cboStepping.Size = new System.Drawing.Size(121, 23);
            this.cboStepping.TabIndex = 7;
            // 
            // panelLineSegment
            // 
            this.panelLineSegment.Location = new System.Drawing.Point(426, 13);
            this.panelLineSegment.Name = "panelLineSegment";
            this.panelLineSegment.Size = new System.Drawing.Size(200, 200);
            this.panelLineSegment.TabIndex = 2;
            // 
            // chkChangeDirection
            // 
            this.chkChangeDirection.AutoSize = true;
            this.chkChangeDirection.CheckAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.chkChangeDirection.Location = new System.Drawing.Point(13, 297);
            this.chkChangeDirection.Name = "chkChangeDirection";
            this.chkChangeDirection.Size = new System.Drawing.Size(74, 19);
            this.chkChangeDirection.TabIndex = 8;
            this.chkChangeDirection.Text = "Direction";
            this.chkChangeDirection.UseVisualStyleBackColor = true;
            // 
            // numPeriod
            // 
            this.numPeriod.Location = new System.Drawing.Point(116, 321);
            this.numPeriod.Maximum = new decimal(new int[] {
            100000,
            0,
            0,
            0});
            this.numPeriod.Name = "numPeriod";
            this.numPeriod.Size = new System.Drawing.Size(97, 23);
            this.numPeriod.TabIndex = 9;
            this.numPeriod.ValueChanged += new System.EventHandler(this.numPeriod_ValueChanged);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(13, 323);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(86, 15);
            this.label3.TabIndex = 10;
            this.label3.Text = "Step Period ms";
            // 
            // panelLookupTable
            // 
            this.panelLookupTable.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panelLookupTable.Location = new System.Drawing.Point(260, 238);
            this.panelLookupTable.Name = "panelLookupTable";
            this.panelLookupTable.Size = new System.Drawing.Size(525, 304);
            this.panelLookupTable.TabIndex = 11;
            // 
            // btnStepBack
            // 
            this.btnStepBack.Location = new System.Drawing.Point(116, 369);
            this.btnStepBack.Name = "btnStepBack";
            this.btnStepBack.Size = new System.Drawing.Size(46, 23);
            this.btnStepBack.TabIndex = 12;
            this.btnStepBack.Text = "<";
            this.btnStepBack.UseVisualStyleBackColor = true;
            this.btnStepBack.Click += new System.EventHandler(this.btnStepBack_Click);
            // 
            // btnStepFwd
            // 
            this.btnStepFwd.Location = new System.Drawing.Point(177, 369);
            this.btnStepFwd.Name = "btnStepFwd";
            this.btnStepFwd.Size = new System.Drawing.Size(48, 23);
            this.btnStepFwd.TabIndex = 13;
            this.btnStepFwd.Text = ">";
            this.btnStepFwd.UseVisualStyleBackColor = true;
            this.btnStepFwd.Click += new System.EventHandler(this.btnStepFwd_Click);
            // 
            // btnClear
            // 
            this.btnClear.Location = new System.Drawing.Point(13, 399);
            this.btnClear.Name = "btnClear";
            this.btnClear.Size = new System.Drawing.Size(75, 23);
            this.btnClear.TabIndex = 14;
            this.btnClear.Text = "Clear";
            this.btnClear.UseVisualStyleBackColor = true;
            this.btnClear.Click += new System.EventHandler(this.btnClear_Click);
            // 
            // tbCurrent
            // 
            this.tbCurrent.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.tbCurrent.Location = new System.Drawing.Point(791, 241);
            this.tbCurrent.Maximum = 256;
            this.tbCurrent.Minimum = -256;
            this.tbCurrent.Name = "tbCurrent";
            this.tbCurrent.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.tbCurrent.Size = new System.Drawing.Size(45, 304);
            this.tbCurrent.TabIndex = 15;
            this.tbCurrent.TickStyle = System.Windows.Forms.TickStyle.TopLeft;
            this.tbCurrent.Scroll += new System.EventHandler(this.tbCurrent_Scroll);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(855, 553);
            this.Controls.Add(this.tbCurrent);
            this.Controls.Add(this.btnClear);
            this.Controls.Add(this.btnStepFwd);
            this.Controls.Add(this.btnStepBack);
            this.Controls.Add(this.panelLookupTable);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.numPeriod);
            this.Controls.Add(this.chkChangeDirection);
            this.Controls.Add(this.cboStepping);
            this.Controls.Add(this.txtStepsPerRev);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.panelLineSegment);
            this.Controls.Add(this.panelLine);
            this.Controls.Add(this.panelCircle);
            this.Controls.Add(this.btnStart);
            this.Name = "Form1";
            this.Text = "Form1";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            ((System.ComponentModel.ISupportInitialize)(this.numPeriod)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.tbCurrent)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnStart;
        private System.Windows.Forms.Panel panelCircle;
        private System.Windows.Forms.Panel panelLine;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txtStepsPerRev;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox cboStepping;
        private System.Windows.Forms.Panel panelLineSegment;
        private System.Windows.Forms.CheckBox chkChangeDirection;
        private System.Windows.Forms.NumericUpDown numPeriod;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Panel panelLookupTable;
        private System.Windows.Forms.Button btnStepBack;
        private System.Windows.Forms.Button btnStepFwd;
        private System.Windows.Forms.Button btnClear;
        private System.Windows.Forms.TrackBar tbCurrent;
    }
}

