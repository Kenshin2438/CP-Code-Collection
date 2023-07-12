param( [String] $fileBasenameNoExtension )

$source = "$fileBasenameNoExtension.cpp"
$output = "$fileBasenameNoExtension.exe"

$existed = (Test-Path -Path $output)
$srcTime = (Get-Item $source).LastWriteTime
$exeTime = if ($existed) {
  (Get-Item $output).LastWriteTime
} else {
  [DateTime]::MinValue
}

$compilerArgs = @(
  $source,
  "-o",
  $output,
  "-std=gnu++17",
  "-Wall",
  "-Wextra",
  "-Wfloat-equal",
  "-Wshadow",
  "-Wconversion",
  "-Wno-sign-conversion",
  "-Wno-unused-const-variable",
  "-Wl,--stack=268435456",
  "-O2",
  "-DKENSHIN"
)

if ((-not $existed) -or ($srcTime -gt $exeTime)) {
  & g++ @compilerArgs

  if ($LASTEXITCODE -ne 0) {
    Write-Host "$source Build Failed`n" -ForegroundColor Red
    exit 2438 # something wrong in the source code
  }

  Write-Host "$source Build Success`n" -ForegroundColor Green
} else {
  Write-Host "$output is up to date`n" -ForegroundColor Cyan
}

$TimeWatcher = Measure-Command { & ".\$output" | Out-Default }
Write-Host "`nTime: $( $TimeWatcher.TotalMilliseconds ) ms"