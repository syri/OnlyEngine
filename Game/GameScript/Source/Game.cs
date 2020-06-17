// Written by syri.
//
using Praesegmen;


namespace Game
{
    public class Game
    {
        public void OnStartup()
        {
            Logger.Initialise();
            Logger.Print(LogType.Info, true, string.Format("Engine Version: {0}.{1}.{2}",
                Application.GetEngineVersionYear().ToString(), Application.GetEngineVersionMajor().ToString(), Application.GetEngineVersionMinor().ToString()));
            Logger.Print(LogType.Info, true, string.Format("Game Version: {0}.{1}.{2}",
                Application.GetProjectVersionYear().ToString(), Application.GetProjectVersionMajor().ToString(), Application.GetProjectVersionMinor().ToString()));
        }

        public void OnUpdate()
        {}

    }
}
