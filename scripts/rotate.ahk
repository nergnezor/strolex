#SingleInstance force

nFrames := 18
dr := 1
iStart := 32
i := iStart
rotate := i
firstTime := true

^j::
; Send ^a
; Send ^+r
Loop, %nFrames%
{
    ; Send ^c
    ; Send ^+v
    Send ^+z
    Sleep, 500
    Send %rotate%
    Sleep, 500
    Send {Return}
    rotate += dr

    Sleep, 500
    Send ^+s
    Sleep, 500
    Send {Right}{Left}{Left}{Left}{Left}
    Send {BackSpace}
    if (i > 9)
        Send {BackSpace}
    if (i > 99)
        Send {BackSpace}
    Send %i%
    ; MsgBox, [ "", "firstTime", (i > 10), 1000]
    Send {Return}
    Sleep, 500
    Send {Return}
    i += 1

    Sleep, 1000
    Send ^z
    Sleep, 500
    ; firstTime = false
}
; width := Clipboard
; newWidth := wis
; ; variable += Clipboard           ; add 1 to variable

; Send , %variable%       ; autotype the new value
; ; Clipboard := variable   ; update clipboard
; ; }