Report on Attack LAB


Goal: To understand x86-64 calling conventions, instructions, and stack organization
      Buffer overflow attacks on two programs
      Not intended to teach attacks to any system resources (that are criminal activities).

![image](https://user-images.githubusercontent.com/90389456/192702449-dddc30d5-2b85-4c5e-a5fe-09e265dc9cb6.png)



Target programs

  - It reads a string from standard input.

1 	int getbuf()
2 	{
3 		char buf[BUFFER_SIZE];
4 		Gets(buf);
5 		return 1;
6      }

  - Normal execution
    
    unix> ./ctarget
    
    Cookie: 0x1a7dd803
    
    Type string: Keep it short!
    
    No exploit. Getbuf returned 0x1
    
    Normal return
    
    

  - With a longer string

    unix> ./ctarget

    Cookie: 0x1a7dd803

    Type string: This is not a very interesting string, but it has the property ...

    Ouch!: You caused a segmentation fault!

    Better luck next time

