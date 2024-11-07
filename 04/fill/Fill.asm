// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, 
// the screen should be cleared.

//// Replace this comment with your code.




(ISET)

    @8192
    D=A
    @i
    M=D

(ILOOP)

    @i
    M=M-1
    D=M
    @ISET
    D;JLT

(KEYPRESSED)
    @KBD
    D=M
    @BLACK_LOOP
    D;JGT
    @WHITE_LOOP
    D;JEQ
    0;JMP


(BLACK_LOOP)

    @SCREEN
    D=A
    @i
    A=D+M
    M=-1
    @ILOOP
    0;JMP


(WHITE_LOOP)

    @SCREEN
    D=A
    @i
    A=D+M
    M=0
    @ILOOP
    0;JMP