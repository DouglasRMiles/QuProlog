; -- qpwin.iss --
[Setup]
AppName=QuProlog
AppVerName=QuProlog version #QPVER#
AppCopyright=Copyright C 2011 Peter Robinson
DefaultDirName=c:\QuProlog
DefaultGroupName=QuProlog
OutputBaseFilename=QuProlog_setup#QPVER#
ChangesEnvironment=true

[files]
Source: "README.txt"; Destdir: "{app}"
Source: "bin\*"; Destdir: "{app}\bin"
Source: "examples\*"; Destdir: "{app}\examples"
Source: "doc\manual\*"; Destdir: "{app}\doc\manual"
Source: "doc\user\*"; Destdir: "{app}\doc\user"

[Registry]
Root: HKLM; Subkey: "SYSTEM\CurrentControlSet\Control\Session Manager\Environment"; ValueType: string; ValueName: "QPHOME"; ValueData: "{app}"; Flags: uninsdeletevalue uninsdeletekeyifempty

[Tasks]
Name: modifypath; Description: Add application directory to your environmental path; Flags: unchecked

[Code]
const
    ModPathName = 'modifypath';
    ModPathType = 'user';

function ModPathDir(): TArrayOfString;
begin
    setArrayLength(Result, 1)
    Result[0] := ExpandConstant('{app}\bin');
end;
#include "modpath.iss"

[Run]
Filename: "{app}\bin\make_executables.bat";

