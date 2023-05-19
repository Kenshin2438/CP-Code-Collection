param(
  [string] $fileDirname,
  [String] $fileBasenameNoExtension
)
Set-Location -Path $fileDirname

$source = "$fileBasenameNoExtension.cpp"
$output = "$fileBasenameNoExtension.exe"

$exeExisted = (Test-Path -Path $output)
$srcTime = (Get-Item $source).LastWriteTime
$exeTime = if ($exeExisted) {
  (Get-Item $output).LastWriteTime
} else {
  [DateTime]::MinValue
}

$myDebugPath = "D:\Document\repos\Code-of-ACM\template\debug"
$compilerArgs = @(
  $source,
  "-o",
  $output,
  "-Wall",
  "-Wextra",
  "-Wfloat-equal",
  "-Wl,--stack=536870912",
  "-DLOCAL",
  "-I$myDebugPath"
)

if ((-not $exeExisted) -or ($srcTime -gt $exeTime)) {
  & g++ @compilerArgs

  if ($LASTEXITCODE -ne 0) {
    Write-Host "$source Build Failed`n" -ForegroundColor Red
    exit 2438 # something wrong in the source code
  }

  Write-Host "$source Build Success`n" -ForegroundColor Green
} else {
  Write-Host "$output is up to date`n" -ForegroundColor Cyan
}

$TimeWatcher = (Measure-Command {
  & ".\$output" | Out-Default
}).TotalMilliseconds
Write-Host "`nTime: $TimeWatcher ms"