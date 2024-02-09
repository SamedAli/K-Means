# Store the current directory (source directory)
$sourceDir = Get-Location
# Define the build directory
$buildDir = "build"

# Check if the build directory exists
if (Test-Path $buildDir -PathType Container) {
    Write-Host "Build directory already exists."
} else {
    Write-Host "Build directory does not exist. Creating..."
    New-Item -ItemType Directory -Path $buildDir | Out-Null
}

# Change directory to the build directory
Set-Location $buildDir

# Run CMake
Write-Host "Running CMake..."
cmake ..

# Check if CMake was successful
if ($LASTEXITCODE -eq 0) {
    Write-Host "CMake completed successfully."

    # Run make
    Write-Host "Running make..."
    make

    # Check if make was successful
    if ($LASTEXITCODE -eq 0) {
        Write-Host "Make completed successfully."

        # Run the executable
        Write-Host "Running the executable..."
        ./MyExecutable.exe

        # Go back to the source directory
        Set-Location $sourceDir
    } else {
        Write-Host "Make failed. Exiting..."
    }
} else {
    Write-Host "CMake failed. Exiting..."
}
