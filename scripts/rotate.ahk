#SingleInstance force

nFrames := 10
dr := 1
i := 11
rotate := i
^j::
; Send ^a
; Send ^+r
Loop, %nFrames%
{
    ; Send ^c
    ; Send ^+v
    Send ^+z
    Send %rotate%
    Sleep, 300
    Send {Return}
    rotate += dr

    Send ^+s
    Sleep, 300
    Send {Left}{Left}{Left}{Left}
    Send {BackSpace}
    if i > 10
        Send {BackSpace}
        if i > 100
            Send {BackSpace}

    ; MsgBox, [ "", "hej", %i%, 2000]
    Send %i%
    Send {Return}
    Sleep, 300
    Send {Return}
    i += 1

    Sleep, 500
    Send ^z
}
; width := Clipboard
; newWidth := wis
; ; variable += Clipboard           ; add 1 to variable

; Send , %variable%       ; autotype the new value
; ; Clipboard := variable   ; update clipboard
; ; }