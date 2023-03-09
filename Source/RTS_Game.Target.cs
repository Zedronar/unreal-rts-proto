using UnrealBuildTool;
using System.Collections.Generic;

public class RTS_GameTarget : TargetRules
{
    public RTS_GameTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V2;

        ExtraModuleNames.AddRange(new string[] { "RTS_Game" });
    }
}