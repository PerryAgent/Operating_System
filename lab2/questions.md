# Assignment 2 (deadline: 03-Sep 2021 23:59 hrs)

## Instructions

  1. The instructions on how to submit each answer is indicated below
     the question (in the line starting with "Ans."). Please follow
     those instructions carefully.

  2. Use code-blocks when you are pasting outputs seen on the terminal.


## Questions

1. **[1 mark]** With an example, explain the output of the `diff`  command.

    **Ans.** 
    Three files have been used to check how the ``diff`` command works. The files are as follows:
    a.txt

    ```
    cat
    dog
    goat
    cow
    ```
    
    b.txt

    ```
    catnip
    dog
    banana
    carrot
    potato
    ```

    c.txt
    ```
    cat
    dog
    goat
    cow
    ```

    ``diff a.txt b.txt``

    Output in terminal:
    ```
    1c1
    < cat
    ---
    > catnip
    3,4c3,5
    < goat
    < cow
    \ No newline at end of file
    ---
    > banana
    > carrot
    > potato
    \ No newline at end of file
    ```
    Here first difference is spotted in 1st line of both files denoted by 1c1
    `<` denotes line from file 1, `>` denotes line from file 2 that are different.
    The next difference is spotted from lines 3 to 4 in a.txt and 3 to 5 in b.txt, denoted by 3,4c3,5   

    On running `diff` with c.txt and b.txt the same output as above is received, because a.txt and c.txt have same content

    On running this command with a.txt and c.txt, no output is received implying they are same.

2. **[1 mark]** Using an example, show how one can measure the time taken to execute a command.

    **Ans.**. A C program has been used: `time.c` which has been pushed in lab2. The following command has been executed:
    ```time gcc time.c -o time```

    The following was the output for the same:
    
    ```
    real	0m0.042s
    user	0m0.028s
    sys	0m0.013s
    ```
    Here the total time taken was 42 ms, out of which 28 ms was spent in user mode, and 13 ms was the CPU time. 
    

3. **[1 mark]** What is the difference between a hard-link and a soft-link in Linux Filesystem.
   With an example, show the commands you will use to create such links.

    **Ans.**. 
    Hard links always points to the same inode as the source file, and not just its name. Therefore moving it across the same filesystem, deleting it or even changing its name does not affect the link. To create a hard link we can use the following command:

    ``ln ogfilename linkname``

    Soft links just point to the file path and has its separate inode. Soft links can be linked across various file systems but would not work if the original file is deleted or moved. To create a soft link we can use the following command:

    ``ln -s ogfilename linkname``
	 
4. **[1 mark]** How will you create named pipes in UNIX. Show an example usage of such named pipes.

    **Ans.**. We use the following command to make named pipes:

    ```
    mkfifo pipename
    ```
    Now the pipe is named *pipename* and can be used over several terminals to pipe the input/output across several processes.

    In one terminal we can stream input to *pipename*:

    ```
    echo "hello,hello,bye" > pipename
    ```

    In a second terminal we can read from this pipe:

    ```
    cut -d',' -f 3 < pipename
    ```
    This outputs `bye`
    Therefore using this makes pipes more flexible to use.
	
5. Analysis of the `syslog` file.

    a. **[2 marks]** Count the number of error messages in the `syslog` file.

    **Ans.**.
       We can use `grep` to find words matching with "error". We can print all the matching words in separate lines by using `-o`  and using `-i` accepts all case and then pipe that to `wc -l` to get number of lines.

       ```
       grep -o -i error /var/log/syslog | wc -l
       ```

       The output: `788`

    b. **[2 marks]** Count the number of lines in the log file.	    

    **Ans.**.
             We can use the following command to get number of lines in log file:

             ```
             wc -l /var/log/syslog
             ```
             The ouput was:
             `33023`

    c. **[2 marks]** Count the number of unique words in the log file.	    

    **Ans.**. 
             The following commang gives number of unique words in `syslog`

             ```
             tr ' ' '\n' < /var/log/syslog | sort | uniq | wc -l
             ```

             The output for the same: `26852`

    d. **[2 marks]** Find the latest error message

    **Ans.**. 
             The following commang gives latest error message in `syslog`

             ```
             grep -i error /var/log/syslog | tail -1
             ```

             The output for the same: 
             ```
             Sep  3 17:22:17 perry-VivoBook-ASUSLaptop-X412FJC-X412FJ gnome-shell[1801]: Received error from D-Bus search provider org.gnome.seahorse.Application.desktop during GetResultMetas: Gio.DBusError: GDBus.Error:org.freedesktop.DBus.Error.UnknownMethod: No such interface “org.gnome.Shell.SearchProvider2” on object at path /org/gnome/seahorse/Application
             ```


    e. **[2 marks]** Find the oldest error message

    **Ans.**. 
             The following commang gives oldest error message in `syslog`

             ```
             grep -i -m 1 error /var/log/syslog
             ```

             The output for the same: 
             ```
             Aug 30 09:57:19 perry-VivoBook-ASUSLaptop-X412FJC-X412FJ thermald[782]: [WARN]error: could not parse file /etc/thermald/thermal-conf.xml
             ```
	    
    f. **[2 marks]** Find the average time between the errors

    **Ans.**. 
             The script used:
             ```
             grep -i error /var/log/syslog | head -1 | cut -d ' ' -f 1-3 >oldtime
             grep -i error /var/log/syslog | tail -1 | cut -d ' ' -f 1-4 >latesttime
             grep -o -i error /var/log/syslog | wc -l >count
             d1="$oldtime"
             d2="$latesttime"
             c="$count"
             date1=$(date -d "$d1" +%s) 
             date2=$(date -d "$d2" +%s)
             diff=`expr $date1 - $date2`
             echo `expr $diff/$c`
             rm oldtime latesttime count
             ```


6. `echoes` using pipes. You should do all the following
   questions inside the folder `lab2/echoes`

    a. **[2 marks]**  Write a C program (`iecho.c`) that reads an input (using `scanf()`)
      and stores it to a variable named `num`, increments `num` by one, and prints
      the incremented value (using `printf()`). Compile this program to create
      an executable named `iecho`.

    **Ans.**. (Do this in the folder echoes. YOU SHOULD NOT COMMIT THE EXECUTABLE
      	   `iecho` INTO YOUR REPO. DOING SO WILL ATTRACT PENALTY).

    b. **[2 marks]**  Compile `driver.c` into an executable named `driver`. Pipe the output
      of `driver` as the input of `iecho`.

    **Ans.**. 
      Command used:
      ```
      ./driver | ./iecho
      ```

      Output:
      `1`

      
    c. **[8 marks]**  Uncomment the lines 9 and 10 of `driver.c`, and recompile the code
      (executable name can continue to be `driver`). Write a command or shell script
      such that `driver` gets (or reads) the incremented value (which is nothing but
      the output of `iecho`). NOTE: This requires a two-way communication where `driver`
      sends a number to `iecho`, `iecho` increments it and sends the incremented value
      back to `driver`. The `driver` then prints both the original value sent and the
      incremented value it received on `stderr`.

    **Ans.**. (PASTE the command used to achieve this, and the output seen on your
      	   terminal. Enclose the text/command/output that you are copying from
	   the terminal into this file in code blocks). 

      The shell script used:
      ```
      mkfifo pipe1 #Pipe 1
      mkfifo pipe2 #Pipe 2
      2>file3 #File to store stderr
      ./driver > pipe1 < pipe2 & #Running driver exe and redirecting output to pipe 1 and input from pipe 2
      for var in 1 2 3 4 5 #Loop to run iecho 5 time
      do 
      ./iecho < pipe1 > pipe2 & #Redirecting input from pipe 1 and output to pipe 2 
      done
      cat file3 #Finally displaying the contents of stderr
      rm pipe1 pipe2 file3  #Deleting the pipes and files created
      ```
      The script was run using `bash script.sh`

      The output seen:
      ```
      Even: sent: 0, got 1
      Even: sent: 1, got 2
      Even: sent: 2, got 3
      Even: sent: 3, got 4
      Even: sent: 4, got 5
      ```


7. **[12 marks]** The folder `lab2/dedup/inputs` has some files that contain information about the
   marks secured by some students in a few subjects. Since a lot of such files may be
   generated in future, you wish to save disk space. Write a shell script `dedup.sh`
   that takes a directory name as an input argument, finds all regular files immediately
   under this directory that are duplicates, and replaces the duplicates with soft-links.
   NOTE:
	a. The filename of the duplicates should remain same (before and after replacing them
	   with soft links).
	b. Your script should not search for duplicates recursively.
	b. The original files that is the one that is lexicographically first.
	c. If there are more than one duplicate, the duplicates should continue to link
	   to the original (lexicographically first) file only.
	d. If the script is not given any input argument, it is assume the current working
	   directory as its input.
	e. The filenames can contain special characters such as "*", spaces, "~", and
	   leading "-".
	f. Your script should ignore all non-regular files such as links, pipes, directories

    **Ans.**. (Complete this exercise in `dedup.sh` present under `lab2/dedup`)

