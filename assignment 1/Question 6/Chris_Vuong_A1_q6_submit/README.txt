File definition:

Report: this is the word documentation about the algorithm applies in the c++ File
q6.cpp : this is the c++ file that run algorithm, output a file circular_<length of word>.txt 
    execution: g++ q6.cpp -O3
               ./a <length of word> <expected size of sequence> <expected substring>
                    <length of word> : the length of the word (required)
                    <expected size of sequence> : expected the output longest sequence (required)
                    <expected substring> : the initial word pass to the algorithm (optional)
                    example : ./a 5 2971 
                                (this command will loop for all 5 character word, loop through all of them RANDOMLY and find the sequence has 2971 length)
                              ./a 5 2971 slice
                                (this command will loop for all 5 character word, loop and compair if the word start with 'slice' with expected of 2971 length)


output file: formatted circular_<length of word>.txt the output of a success execution that store the longest circular it can find
log file: formatted <length of word>_out_log<_fail>.txt the example console log that will print out the screen, with the fail output is the caught of bad_allocated termination.