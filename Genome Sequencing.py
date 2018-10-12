import sys

"""
    This program takes an input of a set of sequences
    and gives an output of the shortest sequence that
    could contain each of the subsequences.
    Overlap is a key feature and is expected.
    
    This program could be optimized by recognising 
    patterns used in previus combined sequences instead
    of calculating them each time they show up.
    
    This program will get slower for each input by N!
"""

def overlap_sequences( root_sequence, insert_sequence ):
# This method takes two strings as input and outputs one string that has the two strings as substrings
    for root_index in range( len( root_sequence ) ):
        match = True;

        for insert_index in range( len( insert_sequence ) ): # insert_index is a step in both strings
            if root_index + insert_index >= len( root_sequence ):
            # insert_sequence sub string matched to the end of root_sequence with remaining
                return root_sequence[ :root_index ] + insert_sequence # break multiple loops

            if insert_sequence[ insert_index ] != root_sequence[ root_index + insert_index ]:
            # character did not match
                match = False
                break

        if match: # all of insert_sequence sub string found within root_sequence
            return root_sequence

    return root_sequence + insert_sequence # no overlap match possible, cancatinate instead

def list_permutation( input_list, derivitive_sequence = '' ):
# This method recursively returns a list of every possible orginization of the input_list,
# each modified by overlap_sequences
    derived_lists = []

    if len( input_list ) > 1:
        for iteration in range( len( input_list ) ):
            if derivitive_sequence: # if not None
                # sends a list exluding the element used in overlap_sequences
                derived_lists += list_permutation( input_list[ :iteration ] + input_list[ iteration + 1: ],
                                        overlap_sequences( derivitive_sequence, input_list[ iteration ] ) )
            else: # first run of list_permutation
                derived_lists += list_permutation( input_list[ :iteration ] + input_list[ iteration + 1: ],
                                                input_list[ iteration ] ) # first of derivitive_sequence

        return derived_lists
        
    else: # last of derivitive_sequence
        return [ overlap_sequences( derivitive_sequence, input_list[ 0 ] ) ]
        
sequence_list = [ input() for input_sequence in range( int( input() ) ) ]
print( sequence_list, file = sys.stderr )

combined_sequences = list_permutation( sequence_list )

answer = combined_sequences[0]
print( 'Combined', answer, file=sys.stderr )

for sequence in combined_sequences[ 1: ]: # for all of the rest
    print( 'Combined', sequence, file = sys.stderr )
    
    if len( answer ) > len( sequence ): # keep the shortest of combined_sequences
        answer = sequence
        
print( len(answer) )