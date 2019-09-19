REM NAS-Vérification
REM Programme d'administration Réseau professionnel,
REM Pour l'entreprise de pharmaco-vigilance BBAC,
REM Consistant à vérifier le nombre de fichiers et sous-dossiers d'un répertoire.

CHCP 1252
:execution
@echo off & cls
echo ^>^> Analyse d'un dossier (Taille, nombre de fichiers et de sous-dossiers) ^<^<
echo Les dossier disponibles directements analysables par leurs noms sont : 
echo.
echo [^> Dans le nas FLUCTUAT ^<]
echo  -^> CLT dans FLUCTUAT [taper "cltf"]
echo  -^> DIR dans FLUCTUAT [taper "dirf"]
echo  -^> INT dans FLUCTUAT [taper "intf"]
echo  -^> SAL dans FLUCTUAT [taper "salf"]
echo [^> Dans le nas MERGITUR ^<]
echo  -^> CLT dans MERGITUR [taper "cltm"]
echo  -^> DIR dans MERGITUR [taper "dirm"]
echo  -^> INT dans MERGITUR [taper "intm"]
echo  -^> SAL dans MERGITUR [taper "salm"]
echo.
set /p repertoire="Analyser un dossier [entrer nom ou chemin du dossier s'il n'est pas dans les suggestions ci-dessus]: "
echo Un fichier comparatif_dossiers.txt apparaitra sur votre bureau.
if /i "%repertoire%"=="cltf" set repertoire=z:
if /i "%repertoire%"=="dirf" set repertoire=y:
if /i "%repertoire%"=="intf" set repertoire=x:
if /i "%repertoire%"=="salf" set repertoire=w:
if /i "%repertoire%"=="cltm" set repertoire=v:\jeudi clt\clt
if /i "%repertoire%"=="dirm" set repertoire=v:\mardi dir\dir
if /i "%repertoire%"=="intm" set repertoire=v:\lundi int\int
if /i "%repertoire%"=="salm" set repertoire=v:\merdredi sal\sal
set /a file_count=0
set /a folder_count=0
set /a octets=0
echo.
echo (Exploration du dossier... Cela peut durer un moment.) 
for /f %%a in ('dir /s /b /a:-d "%repertoire%"') do set /a file_count+=1 
for /f %%a in ('dir /s /b /a:d "%repertoire%"') do set /a folder_count+=1	
setlocal EnableDelayedExpansion
for /f "tokens=3 delims= " %%a in ('dir /a /s "%repertoire%" ^| findstr /e /l "octets"') do (set octets=%%a)  
for /f %%a in ("%octets%") do (set octets=!octets!)
setlocal DisableDelayedExpansion
echo.
echo ^>^> Contenu du dossier
echo  * %file_count% fichiers
echo  * %folder_count% dossiers
echo. 
echo ^>^> Taille du dossier 
echo  * %octets% octets
echo Analyse du dossier de chemin %repertoire% >> comparatif_dossiers.log
echo Du %date% a %time% >> comparatif_dossiers.log
echo ^>^> Contenu du dossier >> comparatif_dossiers.log
echo  * %file_count% fichiers >> comparatif_dossiers.log
echo  * %folder_count% dossiers >> comparatif_dossiers.log
echo ^>^> Taille du dossier >> comparatif_dossiers.log
echo  * %octets% octets >> comparatif_dossiers.log
echo. >> comparatif_dossiers.log
echo.
set /p choix="Analyser un autre dossier pour comparer [Taper "o" ou "n"] ? "
if /i "%choix%"=="o" goto execution
if /i "%choix%"=="n" goto end
goto end
:end
exit 
