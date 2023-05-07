param( 
  [string] $fileDirname, 
  [String] $fileBasenameNoExtension
)
Set-Location -Path $fileDirname

$source = "$fileBasenameNoExtension.cpp"
$output = "$fileBasenameNoExtension.exe"

$exeExisted = Test-Path -Path $output
$srcTime = $(Get-Item $source).LastWriteTime
$exeTime = if ($exeExisted) {
  $(Get-Item $output).LastWriteTime
} else {
  New-Object DateTime(1970, 1, 1, 8, 0, 0)
}

$myDebugPath = "D:\Document\repos\Code-of-ACM\template\debug"

if ((-not $exeExisted) -or ($srcTime -gt $exeTime)) {
  & { 
    g++ -Wall -Wextra -Wfloat-equal "-Wl,--stack=536870912" `
    -DLOCAL "-I$myDebugPath" $source -o $output
  }
  
  if ($LASTEXITCODE -ne 0) {
    Write-Host "$source Build Failed`n" -ForegroundColor Red
    exit 2438 # something wrong in the source code
  }

  Write-Host "$source Build Success`n" -ForegroundColor Green
} else {
  Write-Host "$output is up to date`n" -ForegroundColor Cyan
}

$TimeWatcher = $(Measure-Command -Expression {
  & .\$output | Out-Default
}).TotalMilliseconds
Write-Host "`nTime: $TimeWatcher ms"