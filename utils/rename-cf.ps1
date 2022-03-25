Get-ChildItem . | Rename-Item -NewName { $_.Name + ".in" }
Get-ChildItem . | Rename-Item -NewName { $_.Name -Replace ".a.in",".out" }