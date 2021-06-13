using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TMC2130_Lookup
{
    class TMCLookup
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

        public readonly int lookupCount = 1024;
        public int [] lookupTable;
        private UInt32[] mslut;
        private UInt32 mslutsel;
        private UInt32 mslutstart;

        public TMCLookup()
        {
            lookupTable = new int [256];
            mslut = null;
            mslutsel = 0;
            mslutstart = 0;
        }

    int W(int w, int bit)
        {
            switch (w & 0x3)
            {
                case 0:
                    return bit == 0 ? -1 : 0;
                case 1:
                    return bit == 0 ? 0 : 1;
                case 2:
                    return bit == 0 ? 1 : 2;
                case 3:
                    return bit == 0 ? 2 : 3;
            }
            return 0;
        }

        public void MakeFromRegisters( UInt32[] _mslut, UInt32 _mslutsel, UInt32 _mslutstart)
        {
            mslut = _mslut;
            mslutsel = _mslutsel;
            mslutstart = _mslutstart;


            UInt32 w0 = mslutsel & 0x3;
            UInt32 w1 = (mslutsel >> 2) & 0x3;
            UInt32 w2 = (mslutsel >> 4) & 0x3;
            UInt32 w3 = (mslutsel >> 6) & 0x3;

            UInt32 x1 = (mslutsel >> 8) & 0xFF;
            UInt32 x2 = (mslutsel >> 16) & 0xFF;
            UInt32 x3 = (mslutsel >> 24) & 0xFF;

            UInt32 start_sin = mslutstart & 0xFF;
            UInt32 start_sin90 = (mslutstart >> 16) & 0xFF;

            lookupTable[0] = (int)start_sin;
            for (int i = 0; i < 255; i++)
            {
                UInt32 w = 0;
                if (i < x1)
                    w = w0;
                else if (i < x2)
                    w = w1;
                else if (i < x3)
                    w = w2;
                else
                    w = w3;

                int bit = (mslut[i / 32] & (1 << (i & 31))) == 0 ? 0 : 1;

                lookupTable[i+1] = lookupTable[i] + W((int)w, bit);
            }
        }

        public int lookup(UInt32 v)
        {
            v = v % (UInt32)(4*lookupTable.Length);
            long index = v % lookupTable.Length;
            long segment = v / lookupTable.Length;

            switch (segment)
            {
                case 0:
                default:
                    return lookupTable[index];
                case 1:
                    return lookupTable[lookupTable.Length - 1 - index];
                case 2:
                    return -lookupTable[index];
                case 3:
                    return -lookupTable[lookupTable.Length - 1 - index];
            }
        }

        public void DragTo(int index, int power)
        {
            int i = 0;
            if (index < 256)
            {
                i = index;
            }
            else if (index < 512)
            {
                i = 512 - index;
            }
            else if (index < 768)
            {
                i = index - 512;
                power = -power;
            }
            else 
            {
                i = 512 - (index - 512);
                power = -power;
            }

            //lookupTable[i] = power;
            //System.Diagnostics.Debug.WriteLine($"Drag {i} from {lookupTable[i]} to {power}");
            lookupTable[i] = power;
            for (int j = i - 1; j >= 0; j--)
            {
                int diff = lookupTable[j] - lookupTable[j + 1];
                if (Math.Abs(diff) > 2)
                {
                    lookupTable[j] = lookupTable[j + 1] + Math.Sign(diff) * 2;
                }
            }
            for (int j = i + 1; j < lookupTable.Length; j++)
            {
                int diff = lookupTable[j] - lookupTable[j - 1];
                if (Math.Abs(diff) > 2)
                {
                    lookupTable[j] = lookupTable[j - 1] + Math.Sign(diff) * 2;
                }
            }
        }
    }
}
