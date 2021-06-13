using System;
using System.IO.Ports;

namespace TMC2130_Lookup
{
    class SerialInterface
    {
        public delegate void PositionUpdateDelegate(int position);
        public event PositionUpdateDelegate PositionUpdate;

        private SerialPort port;
        private string buffer;

        public SerialInterface(string portName, int baud)
        {
            port = new SerialPort(portName,baud);
            buffer = "";
        }

        public void open()
        {
            port.Open();

            port.DataReceived += Port_DataReceived;
            port.ErrorReceived += Port_ErrorReceived;
        }

        public void SendPower(int coila, int coilb)
        {
            string s = $"{coila},{coilb}\n";
            port.Write(s);
        }

        private void Port_ErrorReceived(object sender, SerialErrorReceivedEventArgs e)
        {
            throw new System.NotImplementedException();
        }

        private void Port_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            buffer += port.ReadExisting();

            int index = 0;
            while ( index >= 0 )
            {
                index = buffer.IndexOf('\n');
                if (index >= 0)
                {
                    string s = buffer.Substring(0, index+1);
                    buffer = buffer.Substring(index + 1);
                    //System.Diagnostics.Debug.WriteLine(s);
                    UInt16 n;
                    if (UInt16.TryParse(s, out n))
                    {
                        //System.Diagnostics.Debug.WriteLine(n);
                        //System.Diagnostics.Debug.WriteLine((Int16)n);
                        if (PositionUpdate != null)
                            PositionUpdate((Int16)n);
                    }
                }
            }

        }
    }
}
