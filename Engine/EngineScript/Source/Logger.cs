// Written by syri.
//
using System;
using System.Runtime.InteropServices;


namespace Praesegmen
{
    public enum LogType
    {
        Info = 1,
        Warning,
        Error,

        Success,
        Failure
    }

    public class Logger
    {
        // External Definitions used for enabling VT100 / ANSI compatibility.
        private const int STD_OUTPUT_HANDLE = -11;
        private const uint ENABLE_VIRTUAL_TERMINAL_PROCESSING = 0x0004;
        private const uint DISABLE_NEWLINE_AUTO_RETURN = 0x0008;

        [DllImport("kernel32.dll")]
        private static extern bool GetConsoleMode(IntPtr hConsoleHandle, out uint lpMode);

        [DllImport("kernel32.dll")]
        private static extern bool SetConsoleMode(IntPtr hConsoleHandle, uint dwMode);

        [DllImport("kernel32.dll", SetLastError = true)]
        private static extern IntPtr GetStdHandle(int nStdHandle);

        [DllImport("kernel32.dll")]
        public static extern uint GetLastError();

        // Logger
        [DllImport("Praesegmen.dll", EntryPoint = "?Print@Logger@Engine@@SAXW4LogType@2@_NPEB_W@Z")]
        public extern static void Print(LogType InLogType, bool InForceEndline, [MarshalAs(UnmanagedType.BStr)] string InMessage);

        public static void Initialise()
        {
            // Setup VT100 / ANSI compatibility.
            var StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
            if (!GetConsoleMode(StdOut, out uint OutConsoleMode)) Print(LogType.Error, true, "Failed to get console mode.");
            OutConsoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN;
            if (!SetConsoleMode(StdOut, OutConsoleMode)) Print(LogType.Error, true, $"Failed to set console mode. Error: {GetLastError()}");
        }

    }
}
