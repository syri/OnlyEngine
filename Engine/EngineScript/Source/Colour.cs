// Written by syri.
//
using System.Runtime.InteropServices;


namespace Praesegmen
{
    [StructLayout(LayoutKind.Sequential)]
    public struct FloatColour
    {
        public float Red;
        public float Green;
        public float Blue;
        public float Alpha;

        public FloatColour(float InRed, float InGreen, float InBlue, float InAlpha)
        {
            Red = InRed;
            Green = InGreen;
            Blue = InBlue;
            Alpha = InAlpha;
            Clamp();
        }

        public void Clamp()
        {
            Red = Math.Clamp(Red, 0.0f, 1.0f);
            Green = Math.Clamp(Green, 0.0f, 1.0f);
            Blue = Math.Clamp(Blue, 0.0f, 1.0f);
            Alpha = Math.Clamp(Alpha, 0.0f, 1.0f);
        }

    }
}
