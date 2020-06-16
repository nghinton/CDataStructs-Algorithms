Hello! 

Welcome to my personal data structure and sorting algorithm library. I wrote this
library summer 2020 as a way to develop my understanding of the C language while I was 
working through Learn C the Hard Way by Zed Shaw.

The library includes a pretty extensive makfile (for a basic project) that will compile and 
execute unit tests automatically, and includes the option to install the library directly, 
customize as needed. 

I didnt write everything here, I need to give credit where it is due. 
  - I wrote this library while working through Learn C the hard Way so the structure of the directory, 
    the makefile, and dbg.h is all the work of Zed Shaw https://github.com/zedshaw
  - The dgb.h, lists, hashmap and binary tree are VERY similar to his code, with dgb.h EXACTLY his code,
    I just formatted it in places to my personal coding style.
  - Minunit is used to run the unit testing and the source can be found here - http://www.jera.com/techinfo/jtns/jtn002.html
  - Bstring.c and .h are a third party library, and can be found here - http://bstring.sourceforge.net
  - Most of the algorithms were implemented while i was looking at CLRS, but a couple code bits were taken from 
    around the internet at various sites
  - The wikipedia article on Red / Black trees provided most of the code for the insert and removal
    fix up code and can be found here - https://en.wikipedia.org/wiki/Red%E2%80%93black_tree

This library is free for anyone to use or play with as covered by the license, but its still
a pretty rough implementation. While it wont break your computer, use at your own risks.

Things that need work:
  - Unit testing still needs to be fleshed out more. Particularly the dynamic arryas, circular
    dynamic arrays, stacks and queues
  - The code needs to be prettied up in some spots, and the commenting needs to be more extensive
