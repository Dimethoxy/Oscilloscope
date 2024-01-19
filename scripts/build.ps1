# Windows PowerShell build script

# Step 1: Get the current script's directory
$dir = $PSScriptRoot

# Step 2: Check if ./build directory exists, and if it does, delete it
$buildPath = Join-Path $dir "../build"

if (Test-Path $buildPath -PathType Container) {
    Write-Host "Deleting existing ./build directory..."
    Remove-Item -Path $buildPath -Recurse -Force
}

# Step 3: Configure the project with CMake
Write-Host "Configuring the project with CMake..."
cmake -S $dir/../ -B $dir/../build

# Check if the configuration step was successful
if ($LastExitCode -ne 0) {
    Write-Host "CMake configuration failed. Exiting."
    exit $LastExitCode
}

# Step 4: Build the project with CMake
Write-Host "Building the project with CMake..."
cmake --build $dir/../build

# Check if the build step was successful
if ($LastExitCode -ne 0) {
    Write-Host "CMake build failed. Exiting."
    exit $LastExitCode
}

Write-Host "Build completed successfully."

# Step 5: Move the executable
$sourcePath = "$dir\..\build\src\Oscilloscope_artefacts\Debug\Standalone\Oscilloscope.exe"
$destinationPath = "$dir\..\output\windows"
# Check if the source file exists
if (Test-Path $sourcePath) {
    # Check if the destination directory exists, create it if not
    if (-not (Test-Path $destinationPath -PathType Container)) {
        New-Item -ItemType Directory -Path $destinationPath -Force
    }
    try {
        # Move the file
        Move-Item -Path $sourcePath -Destination $destinationPath -Force
        Write-Host "Oscilloscope.exe moved to $destinationPath successfully."
        # Execute the moved file
        $movedFilePath = Join-Path $destinationPath "Oscilloscope.exe"
        Start-Process -FilePath $movedFilePath
    } catch {
        Write-Error "Failed to move Oscilloscope.exe. $_"
    }
} else {
    Write-Error "Source file not found: $sourcePath"
}