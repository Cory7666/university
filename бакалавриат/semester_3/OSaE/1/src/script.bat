@echo off

setlocal EnableDelayedExpansion



set log_file=%~N0.log
set input_file_1=%1%
set input_file_2=%2%
set output_file_name=%3%



echo ---===   Start of a new session   ===--- 1>>%log_file%


REM Проверка на существование переменной окружения EXT.
set EXT 1>nul 2>&1
if errorlevel 1 (
	set EXT=.doc 1>nul 2>&1
	echo [WARNING] The EXT variable is not set. Setting the default value. 1>>%log_file%
)

REM Создание log-файла, если таковой не существует.
if not exist "%log_file%" ( echo Creating file 1>"%log_file%" )


REM Проверка, задан ли первый аргумент. Вывести ошибку, если не задан.
if not exist "%input_file_1%" (
	echo [ERROR] Invalid first argument.
	echo [ERROR] Invalid first argument. 1>>%log_file%
	goto :EOF
)

REM Проверка, задан ли второй аргумент. Вывести ошибку, если не задан.
if not exist "%input_file_2%" (
echo [ERROR] Invalid second argument.
echo [ERROR] Invalid second argument. 1>>%log_file%
goto :EOF
)


REM Если не задан третий аргумент, то попросить пользователя выбрать имя третьего файла.
if /I "%output_file_name%" == "" (
	echo [WARNING] Missed third argument. 1>>%log_file%
	
	:loop1
	set /P answer="Use the name of the first file as the name of the third [Y/n]? "
	
	if /I "!answer!" == "y" set output_file_name=%~N1
	if /I "!answer!" == "yes" set output_file_name=%~N1
	if /I "!answer!" == "" set output_file_name=%~N1
	if /I "!answer!" == "n" set output_file_name=%~N2
	if /I "!answer!" == "no" set output_file_name=%~N2
	
	if /I "!output_file_name!" == "" goto :loop1
	
	echo  *  Used filename: !output_file_name!
	echo  *  Final file name: !output_file_name!%EXT%
	echo [DEBUG] Used filename: !output_file_name! 1>>%log_file%
	echo [DEBUG] Final file name: !output_file_name!%EXT% 1>>%log_file%
)


REM Объединение двух файлов.
echo Merge "%input_file_1%" and "%input_file_2%" and copy to "%output_file_name%!EXT!".
copy "%input_file_1%" + "%input_file_2%" "%output_file_name%!EXT!" 1>nul 2>&1

if not errorlevel 1 (
	echo  *  Success
	echo [DEBUG] Successful file creation. 1>>%log_file%
)

if errorlevel 1 (
	echo  *  Error
	echo [ERROR] Failed file creation. 1>>%log_file%
)



endlocal