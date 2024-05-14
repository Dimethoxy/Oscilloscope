$directoryPath = "./"
$totalLoc = 0
$locPerLanguage = @{}  # Hashtable to store lines per language

# Display ignored folders
Write-Host "------------------------------------------------------------"
Write-Host "Ignored folders: build, external (except dmt)"
Write-Host "------------------------------------------------------------"

$files = Get-ChildItem -Path $directoryPath -File -Include *.h,*.cpp,CMakeLists.txt,*.ps1,*.sh -Recurse | Where-Object {
    $path = $_.FullName
    $path -notmatch "\\build\\" -and ($path -notmatch "\\external\\" -or $path -match "\\external\\dmt\\")
}

foreach ($file in $files) {
    $extension = $file.Extension.TrimStart('.')
    $loc = (Get-Content $file.FullName | Measure-Object -Line).Lines
    Write-Host "File: $($file.FullName), LOC: $loc"

    # Update lines count for the specific language
    if ($locPerLanguage.ContainsKey($extension)) {
        $locPerLanguage[$extension] += $loc
    } else {
        $locPerLanguage[$extension] = $loc
    }

    $totalLoc += $loc
}

Write-Host "------------------------------------------------------------"

# Display lines per language
foreach ($language in $locPerLanguage.Keys) {
    Write-Host "Total LOC for $language : $($locPerLanguage[$language])"
}
Write-Host "------------------------------------------------------------"
Write-Host "Combined LOC in folder: $totalLoc"
