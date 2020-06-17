// Written by syri.
//
using System;


namespace Praesegmen
{
    public static class Math
    {
        public static T Clamp<T>(this T Value, T Minimum, T Maximum) where T : IComparable<T>
        {
            if (Value.CompareTo(Minimum) < 0) return Minimum;
            else if (Value.CompareTo(Maximum) > 0) return Maximum;
            else return Value;
        }

    }
}
