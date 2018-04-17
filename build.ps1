$compiler_build = "C:\Program Files (x86)\Atmel\Studio\7.0\AtmelStudio.exe"
$arguments_build = "App.atsln /rebuild debug /out BuildOutput_Debug.txt"
Start-Process $compiler_build $arguments_build -Verb runAs | Out-Null
