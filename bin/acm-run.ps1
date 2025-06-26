param( [String] $FileBasenameNoExtension )

$source = "$FileBasenameNoExtension.cpp"
$output = "$FileBasenameNoExtension.exe"

$srcTime = (Get-Item $source).LastWriteTime
$exeTime = if (Test-Path -Path $output) {
  (Get-Item $output).LastWriteTime
} else {
  [DateTime]::MinValue
}

if ($srcTime -gt $exeTime) {
  $flags = Get-Content -Path "$PSScriptRoot\compile_flags.txt"
  & g++ @flags $source -o $output "-Wl,--stack=268435456"

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
