$workDirectory = Split-Path -Parent $MyInvocation.MyCommand.Definition
$Env:Path=$Env:Path+
    ";C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Tools\MSVC\14.28.29333\bin\Hostx64\x64"
$Env:INCLUDE="C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Tools\MSVC\14.28.29333\include"+
    ";C:\Program Files (x86)\Windows Kits\10\Include\10.0.18362.0\cppwinrt"+
    ";C:\Program Files (x86)\Windows Kits\10\Include\10.0.18362.0\shared"+
    ";C:\Program Files (x86)\Windows Kits\10\Include\10.0.18362.0\ucrt"+
    ";C:\Program Files (x86)\Windows Kits\10\Include\10.0.18362.0\um"+
    ";C:\Program Files (x86)\Windows Kits\10\Include\10.0.18362.0\winrt"+
    ";"+$workDirectory+"\glfw\include"+
    ";"+$workDirectory+"\glad\include"
$Env:LIB="C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Tools\MSVC\14.28.29333\lib\x64"+
    ";C:\Program Files (x86)\Windows Kits\10\Lib\10.0.18362.0\um\x64"+
    ";C:\Program Files (x86)\Windows Kits\10\Lib\10.0.18362.0\ucrt\x64"+
    ";C:\Program Files (x86)\Windows Kits\10\Lib\10.0.18362.0\ucrt_enclave\x64"+
    ";"+$workDirectory+"\glfw\lib-vc2019\"
cd ./build

$res = ""
$code_pwd = "../src"

Get-ChildItem $code_pwd | ForEach-Object -Process {
    if($_ -is [System.IO.FileInfo]) {
        $res=$res+" "+$code_pwd+"/"+$_.name
    }
}

$cmd = "cl.exe /Zi /EHsc /Fe: ./main.exe "+
    "../main.cpp ../glad/src/glad.c $res "+
    "/link glfw3.lib glfw3dll.lib user32.lib, gdi32.lib, shell32.lib, vcruntime.lib, msvcrt.lib"

Invoke-Expression $cmd

cd ..
