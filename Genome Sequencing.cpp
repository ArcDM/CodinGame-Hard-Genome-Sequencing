#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**This program takes an input of a set of sequences
 * and gives an output of the shortest sequence that
 * could contain each of the subsequences.
 * Overlap is a key feature and is expected.
 * 
 * This program could be optimized by recognising
 * patterns used in previus combined sequences instead
 * of calculating them each time they show up.
 *
 * This program will get slower for each input by (N!)
 */
 
string overlap_sequences(string root_sequence, string insert_sequence)
{ // This method takes two strings as input and outputs one string that has the two strings as substrings
    for(int root_index = 0; root_index < root_sequence.size(); root_index++)
    {
        bool match = true;
        
        for(int insert_index = 0; insert_index < insert_sequence.size(); insert_index++)
        { // insert_index is a step in both strings
            if(root_index + insert_index >= root_sequence.size())
            { // insert_sequence sub string matched to the end of root_sequence with remaining
                return root_sequence.substr(0, root_index) + insert_sequence;
            }
            
            if(insert_sequence[insert_index] != root_sequence[root_index + insert_index])
            { // character did not match
                match = false;
                break;
            }
        }
        
        if(match)
        { // all of insert_sequence sub string found within root_sequence
            return root_sequence;
        }
    }
    
    return root_sequence + insert_sequence; // no overlap match possible, cancatinate instead
}

vector<string> list_permutation(vector<string> &input_list, string derivitive_sequence = "")
{ // This method recursively returns a list of every possible orginization of the input_list, each modified by overlap_sequences
    vector<string> derived_lists;

    if(input_list.size() > 1)
    {
        for(string sequence: input_list)
        {
            string input_sequence;
            vector<string> return_list, argument_list (input_list.size());
            
            // argument_list is input_list exluding sequence
            argument_list.resize( distance( argument_list.begin(), 
            copy_if( input_list.begin(), input_list.end(), argument_list.begin(), 
            [sequence](string copied_string) {return !(copied_string == sequence);} )));
            // could have been shorter, but this can work with duplicate elements
        
            if(derivitive_sequence == "") // if empty
            { // first run of list_permutation
                return_list = list_permutation(argument_list, sequence);
            }
            else
            {
                return_list = list_permutation(argument_list, overlap_sequences(derivitive_sequence, sequence));
            }
            
            // add return_list to derived_lists
            derived_lists.insert(derived_lists.end(), return_list.begin(), return_list.end());
        }
    }
    else // last of derivitive_sequence
    {
        derived_lists = {overlap_sequences(derivitive_sequence, input_list[0])};
    }
            
    return derived_lists;
}

int main()
{
    vector<string> sequence_list;
    string answer = "";
    int sequence_count;
    cin >> sequence_count; cin.ignore();
    
    for(int count = 0; count < sequence_count; count++)
    {
        string input_sequence;
        
        cin >> input_sequence; cin.ignore();
        cerr << input_sequence << " "; // input print for user reference
        
        sequence_list.push_back(input_sequence);
    } cerr << endl;

    for(string sequence: list_permutation(sequence_list))
    { // for all sequence combinations found in list_permutation
        cerr << "Combined " << sequence << endl;
    
        if(answer == "" || answer.size() > sequence.size())
        { // keep the shortest of combined sequences
            answer = sequence;
        }
    }
        
    cout << answer.size() << endl;
}