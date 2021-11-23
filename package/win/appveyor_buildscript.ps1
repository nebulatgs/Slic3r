if (!(Test-Path "C:\projects\local-lib-$env:ARCH.7z")) {
    wget "https://bintray.com/lordofhyphens/Slic3r/download_file?file_path=local-lib-$env:ARCH.7z" -o "C:\projects\local-lib-$env:ARCH.7z" | Write-Output
}

if (Test-Path "C:\projects\local-lib-$env:ARCH.7z") {
    cmd /c "7z x C:\projects\local-lib-$env:ARCH.7z -oC:\projects\slic3r" -y | Write-Output
    rm -r 'C:\projects\slic3r\local-lib\Slic3r*'
}

$env:Path = "C:\Strawberry\c\bin;C:\Strawberry\perl\bin;" +     $env:Path
cd C:\projects\slic3r

rm -r 'C:\Program Files (x86)\Microsoft Vis*\bin' -Force

perl ./Build.pl

if ($LastExitCode -ne 0) {
		$host.SetShouldExit($LastExitCode)
		exit
}

cd package/win
./compile_wrapper.ps1 524 | Write-Output
./package_win32.ps1 524| Write-Output
