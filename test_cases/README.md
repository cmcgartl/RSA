# CS 104: Fall 2023 Homework 4 RSA Tests

Here you will find a folder containing some tests that are being run with HW4. We are releasing these tests earlier than normal so you can fix errors and test your code. 

## What the testcases are doing 
The runner for these testcases is a bit more complex so here's what is going on (and where you can find the information to run it manually). 

### What files are where
Every testcases has two parts: encryption and decrypt. The plaintext/encrypted files are provided in the `test_input` folder. `plain#.txt` can be encrypted to `encrypted#.txt` and vise versa. The p,q and n values that were used to perform the encryption/decryption are stored at the top of the run_tests.sh file (note that the first number in the sequence is the testcase number). The output of the testcase will be stored in the `test_output` folder where `test#.encrypt` is the result of the encryption and `test#.decrypt` is the result of the decryption.

### Testing Encryption:
To test encryption, the testcase will take your rsa executable and pass in the p,q values as command line arguments (even though they do not get used). Then in will pass in the following text (where values in angle brackets are replaced accordingly):
```
    ENCRYPT test_output/test#.encrypt <N> <string in test_input/plain#.txt>
    EXIT
```
Following this, the `test_output/test#.encrypt` file that is created will be compared to the `test_input/encrypted#.txt` for similarity (ignores any trailing whitespace)

### Testing Decryption:
To test decryption, the testcase will take your rsa executable (seperate execution) and pass in the p,q values as command line arguments. Then in will pass in the following text:
```
    DECRYPT test_input/encrypted#.txt test_output/test#.decrypt
    EXIT
```
Following this, the `test_output/test#.decrypt` file that is created will be compared to the `test_input/plain#.txt` for similarity (ignores any trailing whitespace)

## Running the Tests
There is a shell script included in this directory which can be used to automatically run all of the tests. To run these tests, you will need to:

1. Copy the `hw4_tests` directory into your `hw4` folder

2. Be in a docker shell or your VM

3. Compile your program into an executable. The executable should be named `rsa` and the parent directory (`hw4` folder). 

4. Go to the hw4_tests if you are not already `cd hw4_tests`

5. Run the script with the command: `bash ./run_tests.sh` through the command line. The script will give error messages if your program ever crashes, or the output is different that expected. The script will output a diff of the program output and expected solution. The output files will be placed in the `test_output/` folder.

**Important**: It is **highly** suggested that you confirm your executable works on the first testcase before attempting to run the testing script. This will avoid many issues which may be due to your code. **When in doubt** run the testcase manually, it is very likely that your code is failing it somehow.

## Known Issues
- Be careful when modifying the input files, especially the plain#.txt files. Windows computers may automatically change the line endings to CRLF which will introduce a \r character that gets encrypted when the testcases are run.