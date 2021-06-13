using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TMC2130_Lookup
{
    class StepMonitor
    {
        public delegate void NewSampleDelegate(int tick, int angle);
        public event NewSampleDelegate NewSample;

        enum State
        {
            WaitForZero,
            Trace
        };

        enum EventType
        {
            Tick,
            Encoder
        };
        
        State state;
        int lastEncoder;
        bool firstEncoder;
        bool wrap;
        public int wrapPoint;
        int tick;

        List<int> samples;
        List<List<int>> sampleCollection;
        
        public int stepping;
        public int motor_steps_per_rev;

        public void Reset()
        {
            state = State.WaitForZero;
            firstEncoder = true;
            wrap = false;
            tick = 0;
            sampleCollection = new List<List<int>>();
            samples = new List<int>();
        }
        public StepMonitor()
        {
            Reset();
        }
        public void EncoderTick(int encoder)
        {
            if (!firstEncoder)
            {
                StateMachine(encoder, EventType.Encoder);
            }

            lastEncoder = encoder;
            firstEncoder = false;
        }
        public void MoveTick(UInt32 move)
        {
            StateMachine(tick, EventType.Tick);
            tick++;
        }

        private bool hasWrapped(int n)
        {
            return Math.Abs(lastEncoder - n) > (int)Config.EncoderPPR * 4 / 2;
        }

        private void StateMachine(int n, EventType e)
        {
            switch (state)
            {
                case State.WaitForZero:
                    if (e == EventType.Encoder)
                    {
                        // look for a big jump - wrap
                        if ( hasWrapped(n) )
                        {
                            System.Diagnostics.Debug.WriteLine("Home");
                            //if (!wrap)
                            //{
                                wrap = true;
                            //    break;
                            //}
                            wrapPoint = n;
                            tick = 0;
                            state = State.Trace;
                        }
                    }
                    break;

                case State.Trace:
                    // Remember data
                    if (e == EventType.Encoder)
                    {
                        if (hasWrapped(n))
                        {
                            wrap = true;
                            wrapPoint = n;
                        }
                        lastEncoder = n;
                    }
                    else if (e == EventType.Tick)
                    {
                        System.Diagnostics.Debug.Write($"Tick {tick} {lastEncoder} ");
                        if (wrap)
                        {
                            sampleCollection.Add(samples);
                            samples = new List<int>();
                            wrap = false;
                        }
                        samples.Add(lastEncoder);
                        if (NewSample!=null)
                            NewSample(tick,lastEncoder);
                    }
                    break;
            }
        }

        public void clear()
        {
            wrapPoint = 0;
        }
    }
}
