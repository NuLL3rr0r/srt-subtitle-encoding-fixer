SetCompressor /SOLID lzma

OutFile "utfconv.exe"
InstallDir "$TEMP\~maral"
Icon "maral.ico"
SilentInstall silent

Section "MainSection" SEC01
  SetOutPath "$INSTDIR"
  #SetOverwrite on
  SetOverwrite off
  File "QtGui4.dll"
  File "QtCore4.dll"
  File "libgcc_s_dw2-1.dll"
  File "mingwm10.dll"
  File "Maral.exe"
  ExecWait '"$INSTDIR\maral.exe"'
  #SetOutPath "$TEMP"
  #Delete "$INSTDIR\Maral.exe"
  #Delete "$INSTDIR\mingwm10.dll"
  #Delete "$INSTDIR\libgcc_s_dw2-1.dll"
  #Delete "$INSTDIR\QtCore4.dll"
  #Delete "$INSTDIR\QtGui4.dll"
  #RMDir "$INSTDIR"
SectionEnd
