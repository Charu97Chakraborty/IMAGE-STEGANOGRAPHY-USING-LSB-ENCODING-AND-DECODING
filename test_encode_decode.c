/*
Name            :   Charushila Chakraborty
Date            :   31-03-2023
Description     :   LSB Image Steganography
Sample Input    :   For encoding:
                    ./a.out -e <beautiful.bmp> <secret.txt>
                    For decoding:
                    ./a.out -d <stego.bmp> <decode_secret.txt>
Sample Output   :   Encoding:
                    Data will be encoded in a stego.bmp file created as ouput
                    Decoding:
                    Data will be decoded in decoded_secret.txt file
*/



#include <stdio.h>
#include <string.h>
#include "encode.h"
#include "decode.h"
#include "types.h"

int main(int argc, char *argv[])
{
    // checks if more than 1 command line arguments are passed
    if (argc > 1)
    {
        // Function check operation type is called and return is stored in integer variable operation
        int operation = check_operation_type(argv);
        // If operation is encode
        if (operation == e_encode)
        {
            // checks if atleast 4 or more command line arguments are passed
            if (argc >= 4)
            {
                printf("Selected Encoding\n");
                // Structure to store information required for encoding secret file to source Image
                EncodeInfo encInfo;
                // Reads and Validates arguments by calling read_and_validate_encode_args function
                if (read_and_validate_encode_args(argv, &encInfo) == e_success)
                {
                    printf("Read and validate function is successfully executed\n");
                    // calls do encoding function and starts encoding, checks if function executed successfully
                    if (do_encoding(&encInfo) == e_success)
                    {
                        printf("Encoding completed\n");
                        // Closing the open files
                        fclose(encInfo.fptr_src_image);
                        fclose(encInfo.fptr_secret);
                        fclose(encInfo.fptr_stego_image);
                    }
                    else
                    {
                        printf("Encoding failed\n");
                    }
                }
                else
                {
                    // prints error if read_and_validate_encode_args function failed
                    printf("Read and validate function is failure\n");
                    return -1;
                }
            }
            // else if less than 4 command line arguments are passed
            else
            {
                // Printing error with info on how to pass arguments
                printf("Please pass required command line arguments for encoding\nEg: ./a.out -e beautiful.bmp secret.txt\n");
            }
        }
        // If operation is decode
        else if (operation == e_decode)
        {
            // checks if atleast 3 or more command line arguments are passed
            if (argc >= 3)
            {
                printf("Selected Decoding\n");
                // Structure to store information required for decoding secret file from steged Image
                DecodeInfo decInfo;
                // Reads and Validates arguments by calling read_and_validate_decode_args function
                if (read_and_validate_decode_args(argv, &decInfo) == e_success)
                {
                    printf("Read and validate function is successfully executed\n");
                    // calls do decoding function and starts decoding, checks if function executed successfully
                    if (do_decoding(&decInfo) == e_success)
                    {
                        printf("Decoding completed\n");
                        // Closing the open files
                        fclose(decInfo.fptr_stego_image);
                        fclose(decInfo.fptr_output);
                    }
                    else
                    {
                        printf("Decoding failed\n");
                    }
                }
                else
                {
                    // prints error if read_and_validate_encode_args function failed
                    printf("Read and validate function is failure\n");
                    return -1;
                }
            }
            // else if less than 3 command line arguments are passed
            else
            { // Printing error with info on how to pass arguments
                printf("Please pass required command line arguments for decoding\nEg: ./a.out -d stego.bmp\n");
            }
        }

        else
        {
            // Prints error if operation is not passed correctly
            printf("Operation is Invalid.\nPlease pass -e for encoding and -d for decoding\n");
        }
    }
    // else if only 1 command line argument is passed
    else
    {
        // Prints error if arguments are not passed correctly
        printf("Please pass required command line arguments\nFor Encoding:\nEg: ./a.out -e beautiful.bmp secret.txt\nFor Decoding:\nEg: ./a.out -d stego.bmp\n");
    }

    return 0;
}

/* Check the operation type mentioned by user
 * Input: Command line arguments
 * Output: Operation to do is identified ie.., encode or decode
 * Return: e_decode or e_encode or e_unsupported, if invalid operation
 */
OperationType check_operation_type(char *argv[])
{
    // Compares command line argument given and returns operation name accordingly
    if (strcmp(argv[1], "-e") == 0)
        return e_encode;
    else if (strcmp(argv[1], "-d") == 0)
        return e_decode;
    else
        return e_unsupported;
}
