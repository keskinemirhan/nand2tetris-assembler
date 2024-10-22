# Hackasm - Assembler for Hack Assembly

Made for the Hack Computer from [Nand2Tetris](https://www.nand2tetris.org).

**Note**:  This project was created solely for personal practice with the C programming language. I did not put much effort into it and tried to complete it as quickly as possible, so I'm not even sure how it will perform. I only tested it with the Rect.asm and Pong.asm files and compared the binary text output with the correct ones. 

This assembler translates Hack Assembly to Hack Machine Code like this:


```
$ ./hackasm Rect.asm out
$ cat out
1110001100001000
0100111000001101
1110110000010000
0000000000001110
1110001100001000
0110101101000101
1110110000010000
0000000001011111
1110101010000111
0000000000000000
1111110010101000
1111110000010000
0000000000000101
1110001100001000
0000000000000000
...
```

Hackasm does not produce machine code as a binary file for execution but as a text file.

## Usage

```
$ ./hackasm <asm_file> <out_file>
```



