Program for Overlapping:
section .data
menumsg db 10,10,'---Menu for Overlapped Block Transfer---',10
db 10,'1.Block transfer without using string instruction'
db 10,'2.Block Transfer with using string instructions'
db 10,'3.Exit'
db 10,'Enter Your choice::'
menumsg_len equ $-menumsg
wrchmsg db 10,10,'Wrong Choice Entered....Please try again!!!',10,10
wrchmsg_len equ $-wrchmsg
blk_bfrmsg db 10,'Block contents before transfer::'
blk_bfrmsg_len equ $-blk_bfrmsg
blk_afrmsg db 10,'Block contents after transfer::'
blk_afrmsg_len equ $-blk_afrmsg
position db 10,'Enter position to overlap::'
pos_len equ $-position
srcblk db 01h,02h,03h,04h,05h,00h,00h,00h,00h,00h
cnt equ 05
spacechar db 20h
lfmsg db 10,10
section .bss
optionbuff resb 02
dispbuff resb 02
pos resb 00
%macro dispmsg 2
mov eax,04
mov ebx,01
mov ecx,%1
mov edx,%2
int 80h
%endmacro
%macro accept 2
mov eax,03
mov ebx,0
mov ecx,%1
mov edx,%2
int 80h
%endmacro
section .text
global _start
_start:
dispmsg blk_bfrmsg,blk_bfrmsg_len
call dispblk_proc
menu:
dispmsg menumsg,menumsg_len
accept optionbuff,02
cmp byte [optionbuff],'1'
jne case2
dispmsg position,pos_len
accept optionbuff,02
call packnum_proc
call blkxferwo_proc
jmp exit1
case2:
cmp byte[optionbuff],'2'
jne case3
dispmsg position,pos_len
accept optionbuff,02
call packnum_proc
call blkxferw_proc
jmp exit1
case3:
cmp byte[optionbuff],'3'
je ext
dispmsg wrchmsg,wrchmsg_len
jmp menu
exit1:
dispmsg blk_afrmsg,blk_afrmsg_len
call dispblk_proc
dispmsg lfmsg,2
ext:
mov eax,01 ;Exit
mov ebx,0
int 0x80
dispblk_proc:
mov esi,srcblk
mov rcx,cnt
add rcx,[pos]
rdisp:
push rcx
mov bl,[esi] ;Read ASCII value char by char
call disp8_proc ;& Display
inc esi ;point to next char
dispmsg spacechar,1 ;Display space
pop rcx
loop rdisp ;decrement count
ret
blkxferwo_proc:
mov esi,srcblk+4
mov edi,esi
add edi,[pos]
mov ecx,cnt
blkup1:
mov al,[esi]
mov[edi],al
dec esi
dec edi
loop blkup1
ret
blkxferw_proc:
mov esi,srcblk+4
mov edi,esi
add edi,[pos]
mov ecx,cnt
std
rep movsb
ret
disp8_proc:
mov ecx,2
mov edi,dispbuff
dup1:
rol bl,4
mov al,bl
and al,0fh
cmp al,09
jbe dskip
add al,07h
dskip:
add al,30h
mov [edi],al
inc edi
loop dup1
dispmsg dispbuff,2
ret
;-------------------------------------------------
; Procedure to convert character to no.
;-------------------------------------------------
packnum_proc:
mov esi,optionbuff
mov bl,[esi]
cmp bl,39h
jbe skip1
sub bl,07h
skip1:
sub bl,30h
mov [pos],bl
ret