param( [String] $fileBasenameNoExtension )

$sourcePath = "$fileBasenameNoExtension.cpp"
$outputPath = "$fileBasenameNoExtension.exe"

$exeExisted = Test-Path -Path $outputPath
$srcTime = $(Get-Item $sourcePath).LastWriteTime
$exeTime = if ($exeExisted) {
  $(Get-Item $outputPath).LastWriteTime
} else {
  New-Object DateTime(1970, 1, 1, 8, 0, 0)
}

$myDebugPath = "D:\Document\repos\Code-of-ACM\template\debug"

if ((-not $exeExisted) -or ($srcTime -gt $exeTime)) {
  & { 
    g++ -Wall -Wextra -Wfloat-equal "-Wl,--stack=536870912" `
    -DLOCAL "-I$myDebugPath" $sourcePath -o $outputPath
  }
  
  if ($LASTEXITCODE -ne 0) {
    Write-Host "$sourcePath Build Failed`n" -ForegroundColor Red
    exit 2438 # something wrong in the source code
  }

  Write-Host "$sourcePath Build Success`n" -ForegroundColor Green
} else {
  Write-Host "$outputPath is up to date`n" -ForegroundColor Cyan
}

$TimeWatcher = $(Measure-Command -Expression {
  & $outputPath | Out-Default
}).TotalMilliseconds
Write-Host "`nTime: $TimeWatcher ms"