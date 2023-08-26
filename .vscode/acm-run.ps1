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

$flags = Get-Content D:\Document\repos\Code-of-ACM\.vscode\compile_flags.txt

if ((-not $existed) -or ($srcTime -gt $exeTime)) {
  & g++ $source -o $output @flags

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