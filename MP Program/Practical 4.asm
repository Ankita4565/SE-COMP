;Write an ALP to count no. of positive and negative numbers from the array.
section .data
welmsg db 10,'Welcome to count positive and negative numbers in an array',10
welmsg_len equ $-welmsg
pmsg db 10,'Count of +ve numbers::'
pmsg_len equ $-pmsg
nmsg db 10,'Count of -ve numbers::'
nmsg_len equ $-nmsg
nwline db 10
array dw 8505h,90ffh,87h,88h,8a9fh,0adh,02h,8507h
arrcnt equ 8
pcnt db 0
ncnt db 0
section .bss
dispbuff resb 2
%macro print 2 
mov eax, 4 
mov ebx, 1
mov ecx, %1 
mov edx, %2 
int 80h 
%endmacro
section .text 
global _start 
_start: 
print welmsg,welmsg_len ;print title
mov esi,array
mov ecx,arrcnt 
up1: 
bt word[esi],15
jnc pnxt 
inc byte[ncnt] 
jmp pskip 
pnxt: inc byte[pcnt] 
pskip: inc esi 
inc esi
loop up1 
print pmsg,pmsg_len ;prints pmsg
mov bl,[pcnt] 
call disp8num 
print nmsg,nmsg_len 
mov bl,[ncnt] 
call disp8num 
print nwline,1 
exit:
mov eax,01
mov ebx,0
int 80h
disp8num:
mov ecx,2 
mov edi,dispbuff ;Temp buffer
dup1: 
rol bl,4 
mov al,bl 
and al,0fh 
cmp al,09 
jbe dskip 
dskip:
add al,30h ;Add 30h to accumulator
mov [edi],al ;Store ASCII code in temp buff (move contents
inc edi
loop dup1 
print dispbuff,2 
ret 