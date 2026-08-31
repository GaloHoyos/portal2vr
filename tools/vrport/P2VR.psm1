# P2VR.psm1 - analisis estatico de PE para portar offsets entre builds de Portal 2.
#
# Reemplaza los scripts sueltos de 852_6\VRport\, que estaban hardcodeados a ese
# build. Ademas corrige un bug de sig.ps1: usaba el offset de archivo como si
# fuera un RVA, sin la conversion por secciones que vt.ps1 si hacia.
#
#   Import-Module .\tools\vrport\P2VR.psm1 -Force
#   Get-P2VRVtable  -Build corehub -Module materialsystem -Class ".?AVCMaterialSystem@@"
#   Get-P2VRBytes   -Build corehub -Module client -Rva 0x17BAF0 -Length 32
#   Test-P2VRSignature -Build corehub -Module client -Pattern "56 8B F1 6A 00"

$script:Builds = @{
    "corehub" = "C:\Users\galoh\OneDrive\Documents\Leaks Valve\corehub wowwww"
    "852_0"   = "C:\Users\galoh\OneDrive\Documents\Leaks Valve\corehub wowwww"
    "852_6"   = "C:\Users\galoh\OneDrive\Documents\Leaks Valve\852_6"
    "852_1"   = "C:\Users\galoh\OneDrive\Documents\Leaks Valve\852_1"
}

# Los nombres de archivo cambian de capitalizacion entre builds (corehub trae
# Client.dll y 852_6 client.dll), asi que se prueban varios candidatos.
$script:ModulePaths = @{
    "client"         = @("portal2\bin\client.dll", "portal2\bin\Client.dll")
    "server"         = @("portal2\bin\server.dll", "portal2\bin\Server.dll")
    "engine"         = @("bin\engine.dll")
    "materialsystem" = @("bin\materialsystem.dll", "bin\MaterialSystem.dll")
    "vguimatsurface" = @("bin\vguimatsurface.dll")
    "vgui2"          = @("bin\vgui2.dll")
    "shaderapidx9"   = @("bin\shaderapidx9.dll")
}

function Resolve-P2VRModule {
    [CmdletBinding()]
    param([Parameter(Mandatory)][string]$Build, [Parameter(Mandatory)][string]$Module)

    if (-not $script:Builds.ContainsKey($Build)) {
        throw "Build desconocido '$Build'. Conocidos: $($script:Builds.Keys -join ', ')"
    }
    $root = $script:Builds[$Build]
    if (-not $script:ModulePaths.ContainsKey($Module)) {
        throw "Modulo desconocido '$Module'. Conocidos: $($script:ModulePaths.Keys -join ', ')"
    }
    foreach ($rel in $script:ModulePaths[$Module]) {
        $p = Join-Path $root $rel
        if (Test-Path -LiteralPath $p) { return $p }
    }
    throw "No se encontro '$Module' bajo '$root'"
}

# Parsea las cabeceras PE una sola vez y cachea, porque estos DLL pesan varios MB.
function Get-P2VRImage {
    [CmdletBinding()]
    param([Parameter(Mandatory)][string]$Build, [Parameter(Mandatory)][string]$Module)

    if (-not $script:ImageCache) { $script:ImageCache = @{} }
    $key = "$Build/$Module"
    if ($script:ImageCache.ContainsKey($key)) { return $script:ImageCache[$key] }

    $path  = Resolve-P2VRModule -Build $Build -Module $Module
    $bytes = [System.IO.File]::ReadAllBytes($path)

    $peOff    = [System.BitConverter]::ToInt32($bytes, 0x3C)
    $numSec   = [System.BitConverter]::ToUInt16($bytes, $peOff + 6)
    $optSize  = [System.BitConverter]::ToUInt16($bytes, $peOff + 20)
    $optOff   = $peOff + 24
    $imgBase  = [System.BitConverter]::ToUInt32($bytes, $optOff + 28)
    $secOff   = $optOff + $optSize

    $sections = @()
    for ($i = 0; $i -lt $numSec; $i++) {
        $o = $secOff + $i * 40
        $sections += [PSCustomObject]@{
            Name    = [System.Text.Encoding]::ASCII.GetString($bytes, $o, 8).TrimEnd([char]0)
            VSize   = [System.BitConverter]::ToUInt32($bytes, $o + 8)
            VA      = [System.BitConverter]::ToUInt32($bytes, $o + 12)
            RawSize = [System.BitConverter]::ToUInt32($bytes, $o + 16)
            RawPtr  = [System.BitConverter]::ToUInt32($bytes, $o + 20)
        }
    }

    $img = [PSCustomObject]@{
        Path = $path; Bytes = $bytes; ImageBase = $imgBase; Sections = $sections
    }
    $script:ImageCache[$key] = $img
    return $img
}

function ConvertTo-P2VRFileOffset {
    param([Parameter(Mandatory)]$Image, [Parameter(Mandatory)][uint32]$Rva)
    foreach ($s in $Image.Sections) {
        $span = [Math]::Max($s.VSize, $s.RawSize)
        if ($Rva -ge $s.VA -and $Rva -lt ($s.VA + $span)) {
            $off = $s.RawPtr + ($Rva - $s.VA)
            if ($off -ge $Image.Bytes.Length) { return -1 }
            return [int]$off
        }
    }
    return -1
}

function ConvertTo-P2VRRva {
    param([Parameter(Mandatory)]$Image, [Parameter(Mandatory)][int]$FileOffset)
    foreach ($s in $Image.Sections) {
        if ($FileOffset -ge $s.RawPtr -and $FileOffset -lt ($s.RawPtr + $s.RawSize)) {
            return [uint32]($s.VA + ($FileOffset - $s.RawPtr))
        }
    }
    return [uint32]0
}

<#
.SYNOPSIS
Vuelca los N primeros bytes de cada slot de la vtable de una clase, ubicada por
su nombre RTTI. Es el metodo mas confiable para portar offsets: no depende de
que la firma de bytes sobreviva al cambio de compilador entre builds.
#>
function Get-P2VRVtable {
    [CmdletBinding()]
    param(
        [Parameter(Mandatory)][string]$Build,
        [Parameter(Mandatory)][string]$Module,
        [Parameter(Mandatory)][string]$Class,   # p.ej. ".?AVCMaterialSystem@@"
        [int]$Slots = 40,
        [int]$Bytes = 16
    )

    $img = Get-P2VRImage -Build $Build -Module $Module
    $b   = $img.Bytes

    # 1) el TypeDescriptor: el nombre RTTI, terminado en NUL, precedido por
    #    8 bytes (vftable de type_info + spare).
    $needle  = [System.Text.Encoding]::ASCII.GetBytes($Class)
    $nameOff = -1
    for ($i = 0; $i -lt $b.Length - $needle.Length; $i++) {
        $ok = $true
        for ($j = 0; $j -lt $needle.Length; $j++) {
            if ($b[$i + $j] -ne $needle[$j]) { $ok = $false; break }
        }
        if ($ok -and $b[$i + $needle.Length] -eq 0) { $nameOff = $i; break }
    }
    if ($nameOff -lt 0) {
        Write-Output "NO existe RTTI para $Class en $Module ($Build)"
        return
    }

    $tdVA = $img.ImageBase + (ConvertTo-P2VRRva -Image $img -FileOffset ($nameOff - 8))
    Write-Output ("{0}/{1} :: {2}" -f $Build, $Module, $Class)
    Write-Output ("  ImageBase=0x{0:X}  TypeDescriptor VA=0x{1:X}" -f $img.ImageBase, $tdVA)

    # 2) los COL (RTTICompleteObjectLocator) que apuntan a ese TypeDescriptor:
    #    campo pTypeDescriptor en +12, con signature==0 en +0.
    $nd   = [System.BitConverter]::GetBytes([uint32]$tdVA)
    $cols = @()
    for ($i = 0; $i -lt $b.Length - 4; $i += 4) {
        if ($b[$i] -eq $nd[0] -and $b[$i+1] -eq $nd[1] -and $b[$i+2] -eq $nd[2] -and $b[$i+3] -eq $nd[3]) {
            $c = $i - 12
            if ($c -ge 0 -and [System.BitConverter]::ToUInt32($b, $c) -eq 0) { $cols += $c }
        }
    }
    if (-not $cols) { Write-Output "  (sin COL: la clase no tiene vtable propia)"; return }

    # 3) la vtable arranca justo despues del puntero al COL.
    foreach ($c in $cols) {
        $colVA = $img.ImageBase + (ConvertTo-P2VRRva -Image $img -FileOffset $c)
        $cn = [System.BitConverter]::GetBytes([uint32]$colVA)
        for ($i = 0; $i -lt $b.Length - 4; $i += 4) {
            if ($b[$i] -ne $cn[0] -or $b[$i+1] -ne $cn[1] -or $b[$i+2] -ne $cn[2] -or $b[$i+3] -ne $cn[3]) { continue }
            $vt = $i + 4
            Write-Output ("--- VTABLE RVA=0x{0:X} ---" -f (ConvertTo-P2VRRva -Image $img -FileOffset $vt))
            for ($k = 0; $k -lt $Slots; $k++) {
                $fv = [System.BitConverter]::ToUInt32($b, $vt + $k * 4)
                if ($fv -lt $img.ImageBase) { break }
                $ff = ConvertTo-P2VRFileOffset -Image $img -Rva ($fv - $img.ImageBase)
                if ($ff -lt 0) { break }
                $hex = ""
                for ($m = 0; $m -lt $Bytes; $m++) { $hex += ("{0:X2} " -f $b[$ff + $m]) }
                Write-Output ("  [{0,3}] RVA=0x{1:X6}  {2}" -f $k, ($fv - $img.ImageBase), $hex)
            }
        }
    }
}

<#
.SYNOPSIS
Vuelca bytes crudos en un RVA. A diferencia del sig.ps1 viejo, convierte el RVA
a offset de archivo en vez de usarlo directo como indice.
#>
function Get-P2VRBytes {
    [CmdletBinding()]
    param(
        [Parameter(Mandatory)][string]$Build,
        [Parameter(Mandatory)][string]$Module,
        [Parameter(Mandatory)][uint32]$Rva,
        [int]$Length = 40
    )
    $img = Get-P2VRImage -Build $Build -Module $Module
    $off = ConvertTo-P2VRFileOffset -Image $img -Rva $Rva
    if ($off -lt 0) { Write-Output ("RVA 0x{0:X} fuera de las secciones mapeadas" -f $Rva); return }

    $hex = ""
    for ($i = 0; $i -lt $Length; $i++) { $hex += ("{0:X2} " -f $img.Bytes[$off + $i]) }
    Write-Output ("{0}/{1} RVA=0x{2:X} (file 0x{3:X}), {4} bytes:" -f $Build, $Module, $Rva, $off, $Length)
    Write-Output "  $hex"
}

function Initialize-P2VRMatcher {
    if ("P2VRMatch" -as [type]) { return }
    Add-Type -TypeDefinition @"
using System.Collections.Generic;
public static class P2VRMatch {
  // p[] usa -1 como comodin. Devuelve los offsets de archivo que matchean.
  public static List<int> Find(byte[] d, short[] p, int max) {
    var r = new List<int>(); int n = d.Length, m = p.Length;
    for (int i = 0; i <= n - m; i++) {
      int j = 0;
      for (; j < m; j++) { short q = p[j]; if (q >= 0 && d[i + j] != (byte)q) break; }
      if (j == m) { r.Add(i); if (r.Count >= max) break; }
    }
    return r;
  }
}
"@
}

function ConvertTo-P2VRPattern {
    param([Parameter(Mandatory)][string]$Pattern)
    $tokens = $Pattern.Trim() -split '\s+'
    $out = New-Object 'System.Int16[]' $tokens.Length
    for ($i = 0; $i -lt $tokens.Length; $i++) {
        if ($tokens[$i] -eq '?' -or $tokens[$i] -eq '??') { $out[$i] = -1 }
        else { $out[$i] = [int16][System.Convert]::ToInt32($tokens[$i], 16) }
    }
    return $out
}

<#
.SYNOPSIS
Verifica que una firma de bytes matchee exactamente una vez. Una firma ambigua
devuelve un puntero cualquiera y crashea lejos del origen, asi que la unicidad
no es opcional.
#>
function Test-P2VRSignature {
    [CmdletBinding()]
    param(
        [Parameter(Mandatory)][string]$Build,
        [Parameter(Mandatory)][string]$Module,
        [Parameter(Mandatory)][string]$Pattern
    )
    Initialize-P2VRMatcher
    $img = Get-P2VRImage -Build $Build -Module $Module
    $hits = [P2VRMatch]::Find($img.Bytes, (ConvertTo-P2VRPattern $Pattern), 5)

    $rvas = @()
    foreach ($h in $hits) { $rvas += ("0x{0:X}" -f (ConvertTo-P2VRRva -Image $img -FileOffset $h)) }
    Write-Output ("matches={0}  [{1}]" -f $hits.Count, ($rvas -join ", "))
    if     ($hits.Count -eq 1) { Write-Output "  --> UNICA, sirve" }
    elseif ($hits.Count -eq 0) { Write-Output "  --> no matchea" }
    else                       { Write-Output "  --> AMBIGUA, alargar la firma" }
}

Export-ModuleMember -Function Resolve-P2VRModule, Get-P2VRImage, Get-P2VRVtable,
    Get-P2VRBytes, Test-P2VRSignature, ConvertTo-P2VRFileOffset, ConvertTo-P2VRRva
