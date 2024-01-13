param(
  [String] $fileBasenameNoExtension,
  [String] $compileFlags,
  [String] $includePath
)

$source = "$fileBasenameNoExtension.cpp"
$output = "$fileBasenameNoExtension.exe"

$srcTime = (Get-Item $source).LastWriteTime
$exeTime = if (Test-Path -Path $output) {
  (Get-Item $output).LastWriteTime
} else {
  [DateTime]::MinValue
}

$flags = Get-Content -Path $compileFlags

if ($srcTime -gt $exeTime) {
  & g++ $source -o $output @flags -I"$includePath" `
      -DKENSHIN # "-Wl,--stack=268435456" --verbose

  if ($LASTEXITCODE -ne 0) {
    Write-Host "$source Build Failed`n" -ForegroundColor Red
    exit 2438 # something wrong in the source code
  }

  Write-Host "$source Build Success`n" -ForegroundColor Green
} else {
  Write-Host "$output is up to date`n" -ForegroundColor Cyan
}

$TimeWatcher = Measure-Command { & ".\$output" | Out-Default }
Write-Host "`nTime: $( $TimeWatcher.Milliseconds ) ms"