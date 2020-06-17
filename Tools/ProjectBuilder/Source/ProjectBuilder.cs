// Written by syri.
//
using System;
using System.Collections.Generic;
using System.Text.RegularExpressions;


namespace ProjectBuilder
{
    public class ProjectBuilder
    {
        private static int Main(string[] Arguments)
        {
            Regex CommandRegex = new Regex(@"/(?<name>.+?):(?<val>.+)");

            Dictionary<string, string> CommandArguments = new Dictionary<string, string>();
            foreach (string Argument in Arguments)
            {
                Match CommandMatch = CommandRegex.Match(Argument);
                if (CommandMatch.Success)
                {
                    CommandArguments.Add(CommandMatch.Groups[1].Value, CommandMatch.Groups[2].Value);
                }
            }

            if (CommandArguments.Count > 0)
            {
                foreach (KeyValuePair<string, string> Argument in CommandArguments)
                {
                    Console.WriteLine(Argument.Key + ": " + Argument.Value);
                }
            }

            Console.Write(": ");
            Console.ReadLine();

            return 0;
        }

    }
}
