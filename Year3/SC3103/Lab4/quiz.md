### run the mutex one without joint, what will happen
pthread_join serves to wait for the specified threads to complete. Without these calls, there is no guarantee that the threads will have completed before the main function exits and the program terminates. This can lead to undefined behavior, as the threads may still be running when the program exits. The actual output is unpredctable, range from no output to partial output, determined by the timing of the threads.

### serve client one and what is the two codes that create the connection (in the terminal): server you run port number and client you run server ip and port number

### show the code for serve and client side, ask what will be the output