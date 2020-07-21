// Written by syri.
//
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text.RegularExpressions;


namespace ProjectBuilder
{
    public class ProjectBuilder
    {
        private static Regex s_CommandRegex = new Regex(@"/(?<name>.+?):(?<val>.+)");
        private static Dictionary<string, string> s_CommandArguments = new Dictionary<string, string>();
        
        private static string s_ProjectName = string.Empty;
        private static string s_EngineDirectory = string.Empty;
        private static string s_DevelopmentEnvironment = string.Empty;

        private static int Main(string[] InArguments)
        {
            if (GetArguments(InArguments))
            {
                RunPremake();
            }
            else
            {
                Console.WriteLine("Failed to create project. Check output above.");
            }

            return 0;
        }

        private static bool GetArguments(string[] InArguments)
        {
            // Gather and store arguments.
            foreach (string Argument in InArguments)
            {
                Match CommandMatch = s_CommandRegex.Match(Argument);
                if (CommandMatch.Success)
                {
                    s_CommandArguments.Add(CommandMatch.Groups[1].Value, CommandMatch.Groups[2].Value);
                }
            }

            if (!s_CommandArguments.TryGetValue("ProjectName", out s_ProjectName))
            {
                Console.WriteLine("Project Name not specified. Argument syntax: /ProjectName:{ProjectName}");

                return false;
            }
            if (!s_CommandArguments.TryGetValue("EngineDirectory", out s_EngineDirectory))
            {
                Console.WriteLine("Engine Directory not specified. Argument syntax: /EngineDirectory:{EngineDirectory}");

                return false;
            }
            if (!s_CommandArguments.TryGetValue("DevelopmentEnvironment", out s_DevelopmentEnvironment))
            {
                Console.WriteLine("Development Environment not specified. Argument syntax: /DevelopmentEnvironment:{DevelopmentEnvironment}");

                return false;
            }

            return true;
        }

        private static void RunPremake()
        {
            // Run premake5
            try
            {
                using (Process PremakeProcess = new Process())
                {
                    PremakeProcess.StartInfo.UseShellExecute = false;
                    PremakeProcess.StartInfo.FileName = s_EngineDirectory + @"Vendor\Premake\premake5.exe";
                    PremakeProcess.StartInfo.CreateNoWindow = false;
                    PremakeProcess.StartInfo.WorkingDirectory = s_EngineDirectory;
                    PremakeProcess.StartInfo.Arguments = s_DevelopmentEnvironment;
                    PremakeProcess.Start();
                    PremakeProcess.WaitForExit();
                }
            }
            catch (Exception InException)
            {
                Console.WriteLine(InException.Message);
            }
        }

    }
}
