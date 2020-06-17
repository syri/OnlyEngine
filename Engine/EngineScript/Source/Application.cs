// Written by syri.
//
using System;
using System.Runtime.InteropServices;


namespace Praesegmen
{
    public class Application
    {
        [DllImport("Praesegmen.dll", EntryPoint = "?GetEngineVersionYear@Application@Engine@@QEBAHXZ")]
        public extern static int GetEngineVersionYear();

        [DllImport("Praesegmen.dll", EntryPoint = "?GetEngineVersionMajor@Application@Engine@@QEBAHXZ")]
        public extern static int GetEngineVersionMajor();

        [DllImport("Praesegmen.dll", EntryPoint = "?GetEngineVersionMinor@Application@Engine@@QEBAHXZ")]
        public extern static int GetEngineVersionMinor();

        [DllImport("Praesegmen.dll", EntryPoint = "?GetProjectVersionYear@Application@Engine@@QEBAHXZ")]
        public extern static int GetProjectVersionYear();

        [DllImport("Praesegmen.dll", EntryPoint = "?GetProjectVersionMajor@Application@Engine@@QEBAHXZ")]
        public extern static int GetProjectVersionMajor();

        [DllImport("Praesegmen.dll", EntryPoint = "?GetProjectVersionMinor@Application@Engine@@QEBAHXZ")]
        public extern static int GetProjectVersionMinor();

        //[DllImport("Praesegmen.dll", EntryPoint = "?CreateNewWindow@Application@Engine@@QEAAXPEAUWindowDescriptor@2@W4RendererType@2@@Z")]
        //public extern static void CreateNewWindow(ref WindowDescriptor InWindowDescriptor, RendererType InRendererType);
        public static void CreateNewWindow(ref WindowDescriptor InWindowDescriptor, RendererType InRendererType)
        {
            Logger.Print(LogType.Error, true, "CreateNewWindow C# Binding is Disabled.");
        }

    }
}
