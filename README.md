# CS 146 Assignment #5 (Project)
Kyle San Clemente
33685024

## TA README
  - I definitely shouldn't get full credit for this, I wasn't able to meet all the requirements, and I did kind of a bad job in my implementation. I did not set aside enough time to complete this project.
  - I have created a test script called test.sh, it depends on the script runTest.sh
  - I have created a Makefile which compiles all my code, and runs my test script
  - *Please make sure that the file structure matches what is in the zip file to run the test script/Makefile*
  - The nsh file should work fine alone, I have only implemented the following commands
    - echo
    - cd
    - pwd
    - ls
    - exit
    - cat
    - piping to cat *cat is the only command that can be piped to*

### Due dates:
 - Part 2: Friday June 9th 10:59pm

   Write a simple Unix command-line shell called "nsh". It will support, at the very least: shell scripts; the running of arbitrary commands with arguments; the “cd” command; at least one pipe; and I/O redirection (including append). Beyond that, there is considerable choice as to what you decide to implement. **The assignment is out of 30 marks, but bonus marks are possible.**

## PART 2: Executing Commands (15 or more marks, due Thu of Week 10.)
### TODO
  - [x] set up test script
  - [x] make echo work
  - [x] make cd work
  - [x] make ls work
  - [x] make pwd work
  - [x] make exit work
  - [x] implement cat
  - [x] implement piping
  - [ ] implement infile
  - [ ] implement outfile

### Details
  In Part 2 you will execute the commands using system calls. As mentioned above, the shell MUST implement shell scripting to facilitate easy testing of your shell, and your shell should be able to handle commands with at least one pipe. Handling multiple pipes (ie., more than 2 commands piped together) is worth extra marks, as described below

  **EXTENSIONS TO THE SHELL --- do not start until minimal shell is working, or you won’t get the points.** The following extensions are possible, BUT ONLY IF YOUR MINIMAL SHELL IS WORKING. If you'd like to try something not listed, talk to me. You may choose to do up to 10 marks worth of extensions, and your maximum mark will be 40---ie., you can earn up to 10 "bonus" points on this assignment.

  * **[1 mark]** Implement background execution using '&'.
  * **[1 mark]** Comments. Anything after a '#' to the end-of-line is ignored. Note that this automatically allows you to begin your nsh scripts with "#!/home/you/bin/nsh", giving automatic execution of executable nsh scripts.
  * **[1 mark]** Implement the shell escape character using "\", so "echo \|" will output a single "|".
  * **[1 mark]** Implement the “exit” command. With no arguments, it exits with the exit status of the most recently executed command, or it accepts a single integer argument which will be nsh’s exit status.
  * **[2 marks]** Implement single quoting so arguments can have spaces inside them. For 1 more mark, allow the argument to have single quotes inside, so 'now\'s the time' becomes a single argument "now's the time".
  * **[3 marks]** Handle more than one pipe. Eg., “who | grep foobar | uniq –c | sort –nr | less”
  * **[4 marks]** Implement environment variables. You don't need to distinguish between shell and environment variables (ie, no "export" command). Just use putenv(3c) and getenv(3c). Duplicate the Bourne Shell's use of them. This can be tricky, you should carefully experiment with how the Bourne Shell handles variables. Note especially what happens with
    * `$ foo='hello world' # there's a space in there`
    * `$ prargs $foo # how many arguments is that?`
    * `$ bar=$foo # does bar become 'hello' or 'hello world'?`
  * **[4 marks]** Implement back-quotes, ie. an arbitrary nsh command line can be put in back-quotes, and its output is substituted onto the current command line. Remember to parse the spaces after substitution.
  * **[4 marks]** Implement double-quotes, so variables and back-quotes can be put inside them. (Of course this only makes sense if you've implemented at least one of variables or back-quotes.) It must support allowing double-quotes inside the double quotes using "\"".
  * **[6 marks]** Use lex(1) and yacc(1) to do the parsing for you. If you do this, it may actually make some of the other stuff easier, but there's alot to learn to do it. You may use GNU's flex(1) and bison(1) instead.


## Testing
You must hand in test scripts that test and demonstrate the functionality of each of the basic and extended features you implement. Your grade will depend strongly on how well your test scripts actually test the features you claim to have implemented; the grader will not spend time testing your shell to see if it does what you say it does; you must demonstrate this yourself with your test scripts. We will, of course, run your test scripts to ensure they do what you say they do.

## Documentation
Provide a cover page that lists the extensions that you implemented, so I know what extra marks to give you. Document any known bugs you have found in your shell. If you document a bug, you may get partial marks for a feature that is partially implemented; undocumented bugs will significantly lower your mark.

## What to hand in
Hand in paper copies of the cover page, your manual page, all your source files, all your test scripts and their output, and your Makefile. Also electronically sumbit everything (except the cover page) using the submit command as in previous assignments.
