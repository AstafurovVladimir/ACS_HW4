global CountVowels
CountVowels:
section .data							
stringAlphabet	db "aeiouy",0
section .text							
    push rbp
    mov rbp,rsp
    mov r10,rdi
    mov r11,rsi
    mov r8d,0    ; counter
    mov r9,0    ; alph counter
    lea rsi,[stringAlphabet]	; 	search argument
bigloop:
    lea rdi,[r10]   ; string
    mov rcx,r11     ; length
    lodsb
    cld
search:
    scasb
    je char_found
return:
    loop search
    inc r9
    cmp r9,6
    jne bigloop
    cvtsi2sd xmm0, r8d
    cvtsi2sd xmm1, r11
    divsd xmm0,xmm1
    jmp exit
        
char_found:
    inc r8d
    jmp return
    
global HeapSort
HeapSort:
section .data
section .text
    push rbp
    mov rbp, rsp
    mov rdi,rdi ; values, size = 8, qword
    mov rsi,rsi ; positions, size = 8, qword
    mov rdx,rdx ; length
    
    mov r8,0    ; saves index i to give to Heapify
    mov r12,0   ; saves length for Heapify
    mov rcx,rdx ; i
LoopBuildHeap:
    mov r8,rcx
    mov r12,rdx
    call Heapify    ; Heapify(rcx, rdx)
    dec rcx
    cmp rcx,0
    jge LoopBuildHeap
;   builheap ended

    mov rcx,rdx
    dec rcx
LoopUnheap:
    jmp UnheapSwap
EndUnheapSwap:
    mov r8,0
    mov r12,rcx
    call Heapify    ; Heapify(0, rcx)
    dec rcx
    cmp rcx,0
    jge LoopUnheap
    jmp exit
    

Heapify:
    mov r9,r8   ; ma = i
    mov r10,r8  ; l = 2 * i + 1
    sal r10,1
    add r10,1
    mov r11,r8  ; r = 2 * i + 2
    sal r11,1
    add r11,2
    cmp r10,r12
    jl MAtoL
EndMAtoL:
    cmp r11,r12
    jl MAtoR
EndMAtoR:
    cmp r9,r8
    jne HeapifySwap
EndHeapifySwap:
    ret
    
MAtoL:
    movsd xmm0,qword[rdi+r10*8]    ; values[l] -> xmm0
    movsd xmm1,qword[rdi+r9*8]     ; values[ma] -> xmm1
    comisd xmm1,xmm0
    jae EndMAtoL             ; dont swap if values[ma] >= values[l]
    mov r9,r10
    jmp EndMAtoL

MAtoR:
    movsd xmm0,qword[rdi+r11*8]    ; values[r]
    movsd xmm1,qword[rdi+r9*8]     ; values[ma]
    comisd xmm1,xmm0
    jae EndMAtoR
    mov r9,r11
    jmp EndMAtoR
    
HeapifySwap:
    movsd xmm0,qword[rdi+r9*8]  ; remember values[ma]
    movsd xmm1,qword[rdi+r8*8]  ; remember values[i]
    mov r14,qword[rsi+r9*8]     ; remember positions[ma]
    mov r15,qword[rsi+r8*8]     ; remember positions[i]
    movsd qword[rdi+r8*8],xmm0  ; write the pairs the other way around
    movsd qword[rdi+r9*8],xmm1
    mov qword[rsi+r8*8],r14
    mov qword[rsi+r9*8],r15
    mov r8,r9
    jmp Heapify

UnheapSwap:
    movsd xmm0,qword[rdi]       ; remember values[0]
    movsd xmm1,qword[rdi+rcx*8] ; remember values[i]
    mov r14,qword[rsi]          ; remember positions[0]
    mov r15,qword[rsi+rcx*8]    ; remember positions[i]
    movsd qword[rdi+rcx*8],xmm0 ; write the pairs the other way around
    movsd qword[rdi],xmm1
    mov qword[rsi+rcx*8],r14
    mov qword[rsi],r15
    jmp EndUnheapSwap
    
exit:
    leave
    ret
