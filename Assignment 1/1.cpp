// Program to print out large letters - Comp Sci 30 S
// Evan Bartlett

#include <iostream>
#include <conio.h>
#include <string>

using namespace std;

// function that returns the string received from the user
string getInput() {
    string str; // string to temporarily store input
    while (true) {

        getline(cin, str); // use getline on cin to prevent space char delimiting

        for (char &i: str) { // for every char in the string, accessed by reference

            i = tolower(i); // make sure every character is lowercase

        }

        break;
    }
    return str; // return the temp string
}

// Function to index the string, modifies the ascii value of each char in the string so its numeric value is the
// index to its large version in the array of large characters
// It also converts anything non-alphanumeric to just be a space, is later outputted as a few newlines
// str - string to be indexed
string indexString(string str) {
    for (char& i: str) {
        if (i >= 'a' && i <= 'z') {
            i -= 97; // if the char is a letter, subract the value of lowercase a so 'a' becomes 0 and 'z' becomes 25
        }
        else {
            if (i >= '0' && i <= '9') { // else if the char is a number, subtract ascii value of 0 so '0' becomes 26
                i -= 22;

            }
            else {
                i = ' '; // number is not alphanumeric, convert to space char
            }
        }
    }
    return str; // return the temp string
}

// uses the array of letters to print each char in the string
// if the char is a space, prints 3 newlines, otherwise uses the char value as the array index
// str - string to be printed
// letters[36] - array of large characters to use to print the string
void printLetters(const string &str, string letters[36]) {
    for (const char& i: str) {

        if (i == ' ') { // if char is a space print newlines and proceed to shift loop iteration
            cout << "\n\n\n";
            continue;
        }
        cout << letters[ i ] << "\n";
    }
}

// function to ask the user whether they want to restart
// if the input is not 'y' or 'n' it will continue to ask for input
// input - ref to be modified with teh vale of the user's input
void askRestart(char &input) {
    while (true) {
        input = tolower(_getch());
        if (input == 'y' || input == 'n') { // if input is valid exit the loop, otherwise continue
            cout << input << endl;
            break;
        }
    }
}

int main() {

    char input; // character to store whether the user wants to restart

    string letters[36] = { // array containing the large letters
            "   _,   \n"" ,&*&%; \n"" &!  |% \n"":%$&%&%!\n""!%;  ;%;\n""&;    &^\n","_______,  \n""|$&&#$$;, \n""|%:   :|).\n""||&&&$),  \n""|$:   :|);\n""#$$%$&:/' \n"," _;&$$&&-\n"",&%!   ^&\n""&:       \n""%;_     .\n"" &$__  ;$\n""  !&&$$&'\n","#%$%%;  \n""%;   '%_\n""%!    '&\n""%|    ,$\n""%!  ,:&/\n""#%%$%/  \n","#&&$$&%&\n""&;      \n""&!_____,\n""&:&$$&%&\n""&!      \n""#&%%#&%&\n","#&&$$&&;\n""$;'     \n""#&%%#&&;\n""&:^     \n""$;      \n""%!      \n"," ________ \n""/&''^^'?$;\n""$:        \n""&; ,_____,\n""&!   !&'  \n""':&&$&&/' \n","&!     !&\n""$!     !%\n""$!_____!&\n""%!&&&&&!&\n""&!     !$\n""%!     !&\n","&$&&$&##&\n""   !&!   \n""   !$!   \n""   !%!   \n""   !$!   \n""&&&$&$&&%\n","##########\n""     !#! \n""-=-   !&!\n"" $'    !#!\n""^&&&$&%/!'\n","&   ,:&&\n""& ,:&&; \n""&&<    \n""&)^!$;  \n""&)  !&;,\n""&;    !$\n","|#,     \n""|#;     \n""|#:     \n""|#:     \n""|#;____,\n""|#&&&&$;\n","_,     ,_\n""%^$, ,$^%\n""@ '$_$; @\n""&  '|'  &\n""#   ^   #\n","&&,    !&\n""&^&,   ;&\n""&; ;&; !&\n""&!  '&:!&\n""&!   ;&;&\n""&!    !&&\n","          \n"" *;&&%@:* \n"":&      &!\n""!#      ;&\n"" ;@<*&&!* \n""          \n","_&&&&*, \n""&!    ;&\n""&&$&&/! \n""&'      \n""&!      \n""&;      \n","         \n"" *;&%@:* \n"":&     &!\n""!#   \\;&\n"" ;@<*&/\\,\n""       :\\\n","#&&%&&*_ \n""&!    ,&;\n""&$&%8*&/'\n""&&!@.    \n""&   ;& , \n""&;    '$?\n"," *&%&&_,\n""$;     ^\n"" ^%&*_, \n""_,    :&\n"" ^$&7&# \n","_________\n""%$%&$&%&%\n""  '!%'   \n""   *#    \n""   ;%    \n""   &$    \n",";,     ,!\n"";&     $;\n"":&     &!\n""!#     ;&\n"" ;@<*>!* \n""         \n","&,      &\n""%!     !%\n""'&!   !&;\n""  ^&_;&; \n""   '$;  \n","*,  _,  .*\n""&! ,&&; :&\n""&!,& &; !&\n""&;&'  :&!&\n""&&:    ;&&\n""&;      !&\n","#,     ;#\n""'&$;  &%!\n""  ;&_$:  \n""  !$^$;  \n"":%$  ^%& \n""#      !%\n","&:     ;&\n"" $;   !& \n""  &._<#' \n""  '*|#!  \n""   ;$%   \n""   &!$   \n","/&&$$%@&&%*\n""       ,%;'\n""    :$%,   \n""  ;&%!     \n""/#%;       \n""*$$%&$&%&&/\n","  &&@%&$%@  \n"" &&^    ^&& \n""&&^&.    '&$\n""&!  @&;   :%\n""%:  :%&   :&\n""$@.  '&$,;&&\n"" &$;  '^$&& \n""  &%$%$@#&  \n","   %&$    \n"" $&^*&    \n""&^  $&    \n""    &#    \n""    %&    \n""    #&    \n""&%$%@$@%$#\n"," ,&%$$&.\n""&%'  '^&\n""    !&&!\n""  ,&&:  \n"".&&^.   \n""&%$@&$$&\n","  #$%^$ \n"" %^   :&\n""    $%@ \n"" &,   '$\n""  %#$&# \n","$     %\n""$     &\n""*&#&$!%\n""     '$\n""      &\n",":-><;+*\n""&      \n""$&*<*<;\n""      $\n""'&*-&' \n","*&$#&% \n""&      \n""$&*<*<)\n""&     $\n""'%*^&&^\n","&%$@&$$&%;\n""      '@; \n""  --+*&!+-\n""    ;&:'  \n""  !&;'    \n"" !%'      \n"," *;&&%@:* \n"":&      &!\n""!#      ;&\n"" ;@<*&&!* \n"":&      &!\n""!#      ;&\n"" ;@<*&&!* \n"," *;&&%@:* \n"":&      &!\n""!#      ;&\n"" ;@<*&&!+&\n""        !&\n""        ;&\n""        !&\n"
    };

    string word; // string to store the characters the user want to enlarge

    bool flag = true; // bool to control while loop


    while (flag) { // while loop to control whether the user wants to enter another word
        cout << "Welcome to Giant Letters!! Please enter the letters / words you would like to have BIGIFYIED: \n";

        word = getInput(); // get input for what user wants enlarged
        word = indexString(word); // convert ascii values to their array indexes

        cout << "\n\n"; // print a few newlines
        printLetters(word, letters); // using the chars as indexes print the large letters from the array

        cout << "\nWould you like to enter another word? (Y/N) ";
        askRestart(input); // modify input to be 'y' or 'n' depending on whether the user wants to continue

        switch (input) { // switch statement to control whether the user wants to continue

            case 'n': case 'N': { // if the user wants to quit, print a thank you message and exit the loop
                cout << "Thank you! Press any key to exit...";
                flag = false;
                _getche();
                break;
            }

            case 'y': case 'Y': { // if the user wants to continue, print a few newlines and continue the loop
                cout << "Alright!\n\n";
                break;
            }
        }

    }

    return 0;
}