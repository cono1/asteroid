@echo off 
set SolutionDir = %~1
set Config = %~2

xcopy "%SolutionDir%Assets" "%SolutionDir%bin\%Config%\Assets" /e /v /y /i