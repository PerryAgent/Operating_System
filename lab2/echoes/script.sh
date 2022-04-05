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