param($srcPath)

$srcTime = $(Get-Item "$srcPath.cpp" -ErrorAction Stop).lastwritetime 

try {
  $exeTime = $(Get-Item "$srcPath.exe" -ErrorAction SilentlyContinue).lastwritetime 
} catch {
  $exeTime = 0
}

$myDebug = "D:\\Document\\repos\\Code-of-ACM\\template\\debug"

if ($exeTime -lt $srcTime) {
  g++ "$srcPath.cpp" -o "$srcPath.exe"    `
  -Wall -Wextra -Wfloat-equal             `
  -O2 "-Wl,--stack=536870912"             `
  -DLOCAL "-I$myDebug"

  Write-Host "$srcPath.exe Build Success" -ForegroundColor Green
} else {
  Write-Host "$srcPath.exe is up to date" -ForegroundColor Cyan
}

Write-Host ""
time "$srcPath.exe"