@echo off
setlocal
setlocal enabledelayedexpansion
chcp 65001
set _file="../README.md"
(
@echo # This repository is for personal learning purposes only.
@echo:
@echo ## Quiz list
@echo:
@set _url=https://github.com/kevin85112/Quiz/tree/master/Quiz/
) > %_file%
for /d %%i in (*) do (
  @if exist "%%i" (
    @set _variable=%%i
    @echo - [!_variable!]^(%_url%!_variable!^)>> %_file%
    )
  )
endlocal