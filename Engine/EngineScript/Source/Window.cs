// Written by syri.
//
using System;
using System.Runtime.InteropServices;


namespace Praesegmen
{
    public enum RendererType
    {
        D3D12 = 1,
		Vulkan
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct WindowDescriptor
    {
        [MarshalAs(UnmanagedType.BStr)]
        public string WindowTitle;

        public int X;
        public int Y;
        public uint Width;
        public uint Height;
        [MarshalAs(UnmanagedType.U1)]
        public bool Fullscreen;

        public IntPtr WindowHandle;
        public FloatColour ClearColour;

        public WindowDescriptor(string InWindowTitle, int InX, int InY, uint InWidth, uint InHeight, bool InFullscreen)
		{
            WindowTitle = InWindowTitle;
            X = InX;
            Y = InY;
            Width = InWidth;
            Height = InHeight;
            Fullscreen = InFullscreen;
            WindowHandle = (IntPtr)0;
            ClearColour = new FloatColour(0.0f, 0.0f, 0.0f, 0.0f);
        }

        public WindowDescriptor(string InWindowTitle, uint InWidth, uint InHeight, bool InFullscreen)
        {
            WindowTitle = InWindowTitle;
            X = 0;
            Y = 0;
            Width = InWidth;
            Height = InHeight;
            Fullscreen = InFullscreen;
            WindowHandle = (IntPtr)0;
            ClearColour = new FloatColour(0.0f, 0.0f, 0.0f, 0.0f);
        }

    }
}
