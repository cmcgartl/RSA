#!/bin/bash

# Arguments formated as such: Test case number, command line args 1 and 2 (p, q), n value
testcases="1,9733,9739,94789687
        2,9733,9739,94789687
        3,1901,1907,3625207
        4,4337,4339,18818243
        5,1877,1879,3526883
        6,2503,3023,7566569
        7,9733,9739,94789687
        8,1901,1907,3625207
        9,4337,4339,18818243
        10,1877,1879,3526883
        11,1901,1907,3625207
        12,9733,9739,94789687
"

# Check for file
EXECUTABLEPATH="../rsa"
if [ ! -f $EXECUTABLEPATH ]; then
    echo "Error: Could not find $EXECUTABLEPATH"
    exit 1
fi

# Create output directory
rm -r test_output
mkdir -p test_output

# Run all tests
OLDIFS=$IFS;
for n in $testcases;
do
    IFS=',';
    set -- $n;
    # Set up variables
    plainFile="test_input/plain$1.txt"
    plaintext=$(cat $plainFile)
    encryptedFile="test_input/encrypted$1.txt"
    encryptedText=$(cat $encryptedFile)
    encryptOutputFile="test_output/test$1.encrypt"
    decryptOutputFile="test_output/test$1.decrypt"
    encryptInput="ENCRYPT $encryptOutputFile $4 $plaintext"
    decryptInput="DECRYPT $encryptedFile $decryptOutputFile"
    endCommand=$'EXIT\n'
    echo "Running testcase $1 with args: $2 $3 with: $plainFile and $encryptedFile"
    echo "Encrypting..."
    # Run encrypt command
    fullInput="$encryptInput
                $endCommand"
    echo $fullInput | ./$EXECUTABLEPATH $2 $3
    if [ $? -ne 0 ]; then
        # Stop if the executable does not return 0
        echo "Error on test $n, check that the test does not crash and make sure it returns 0 from main"
        break
    else
        # Compare encrypt output
        diff --strip-trailing-cr -Z $encryptOutputFile $encryptedFile > /dev/null 2>&1
        if [ $? -ne 0 ]; then
            diff --strip-trailing-cr -Z $encryptOutputFile $encryptedFile
            echo "...Test $1 Encryption failed, check output/solution file for differences"
            break # Comment out this line to avoid stopping on failures
        else
            echo "...Test $1 Encryption passed!"
        fi
    fi
    # Run decrypt command
    echo "Decrypting..."
    fullInput="$decryptInput
                $endCommand"
    echo $fullInput | ./$EXECUTABLEPATH $2 $3
    if [ $? -ne 0 ]; then
        # Stop if the executable does not return 0
        echo "Error on test $n, check that the test does not crash and make sure it returns 0 from main"
        break
    else
        # Compare decrypt output
        diff -w $decryptOutputFile $plainFile > /dev/null 2>&1
        if [ $? -ne 0 ]; then
            diff --strip-trailing-cr -Z $decryptOutputFile $plainFile
            echo "...Test $1 Decryption failed, check output/solution file for differences"
            break # Comment out this line to avoid stopping on failures
        else
            echo "...Test $1 Decryption passed!"
        fi
    fi
done
IFS=$OLDIFS