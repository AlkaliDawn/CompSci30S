#include <iostream>
#include <conio.h>
using namespace std;

/**
 *
 * @param character
 * @return False if input is invalid
 *         True if input is valid
 */
bool validateInput(const char& character) {

    if ((character < '0' || character > '9') && (character < 'a' || character > 'z')) {
        return true;
    }

    return false;
}

/**
 *
 * @param str string for validated input to be stored in
 *
 * Repeatedly gets input from the user until a valid string is found.
 * Uses @a getline on cin
 */
void getInput(string &str) { // ascii 48 - 57, 97 - 122
    while (true) {

        getline(cin, str);

        for (char &i: str) {

            i = tolower(i);

            if (validateInput(i)) {
                str.erase(str.find(i), 1);
            }

        }

        break;
    }

}

/**
 *
 * @param str string to have its characters converted to indexes
 *
 * Receives a string "@a str" by reference and converts each character to its index in the array of large letters,
 * by subtracting a constant int based on whether each character is a letter or number
 */
void indexString(string& str) {
    for (char &i: str) {
        if (i == ' ') {
            str.erase(str.find(i), 1);
            continue;
        }
        if (i >= 'a' && i <= 'z') {
            i -= 97;
        }
        else { // 48 - 26
            i -= 22;
        }
    }
}

void printLetters(const string &str, auto letters) {
    for (const char& i: str) {
        cout << letters[ i ] << "\n";
    }
}

int main() {

    char input;

    string letters[36] = {
            "   _,   \n"" ,&*&%; \n"" &!  |% \n"":%$&%&%!\n""!%;  ;%;\n""&;    &^\n","_______,  \n""|$&&#$$;, \n""|%:   :|).\n""||&&&$),  \n""|$:   :|);\n""#$$%$&:/' \n"," _;&$$&&-\n"",&%!   ^&\n""&:       \n""%;_     .\n"" &$__  ;$\n""  !&&$$&'\n","#%$%%;  \n""%;   '%_\n""%!    '&\n""%|    ,$\n""%!  ,:&/\n""#%%$%/  \n","#&&$$&%&\n""&;      \n""&!_____,\n""&:&$$&%&\n""&!      \n""#&%%#&%&\n","#&&$$&&;\n""$;'     \n""#&%%#&&;\n""&:^     \n""$;      \n""%!      \n"," ________ \n""/&''^^'?$;\n""$:        \n""&; ,_____,\n""&!   !&'  \n""':&&$&&/' \n","&!     !&\n""$!     !%\n""$!_____!&\n""%!&&&&&!&\n""&!     !$\n""%!     !&\n","&$&&$&##&\n""   !&!   \n""   !$!   \n""   !%!   \n""   !$!   \n""&&&$&$&&%\n","##########\n""     !#! \n""-=-   !&!\n"" $'    !#!\n""^&&&$&%/!'\n","&   ,:&&\n""& ,:&&; \n""&&<    \n""&)^!$;  \n""&)  !&;,\n""&;    !$\n","|#,     \n""|#;     \n""|#:     \n""|#:     \n""|#;____,\n""|#&&&&$;\n","_,     ,_\n""%^$, ,$^%\n""@ '$_$; @\n""&  '|'  &\n""#   ^   #\n","&&,    !&\n""&^&,   ;&\n""&; ;&; !&\n""&!  '&:!&\n""&!   ;&;&\n""&!    !&&\n","          \n"" *;&&%@:* \n"":&      &!\n""!#      ;&\n"" ;@<*&&!* \n""          \n","_&&&&*, \n""&!    ;&\n""&&$&&/! \n""&'      \n""&!      \n""&;      \n","         \n"" *;&%@:* \n"":&     &!\n""!#   \\;&\n"" ;@<*&/\\,\n""       :\\\n","#&&%&&*_ \n""&!    ,&;\n""&$&%8*&/'\n""&&!@.    \n""&   ;& , \n""&;    '$?\n"," *&%&&_,\n""$;     ^\n"" ^%&*_, \n""_,    :&\n"" ^$&7&# \n","_________\n""%$%&$&%&%\n""  '!%'   \n""   *#    \n""   ;%    \n""   &$    \n",";,     ,!\n"";&     $;\n"":&     &!\n""!#     ;&\n"" ;@<*>!* \n""         \n","&,      &\n""%!     !%\n""'&!   !&;\n""  ^&_;&; \n""   '$;  \n","*,  _,  .*\n""&! ,&&; :&\n""&!,& &; !&\n""&;&'  :&!&\n""&&:    ;&&\n""&;      !&\n","#,     ;#\n""'&$;  &%!\n""  ;&_$:  \n""  !$^$;  \n"":%$  ^%& \n""#      !%\n","&:     ;&\n"" $;   !& \n""  &._<#' \n""  '*|#!  \n""   ;$%   \n""   &!$   \n","/&&$$%@&&%*\n""       ,%;'\n""    :$%,   \n""  ;&%!     \n""/#%;       \n""*$$%&$&%&&/\n","  &&@%&$%@  \n"" &&^    ^&& \n""&&^&.    '&$\n""&!  @&;   :%\n""%:  :%&   :&\n""$@.  '&$,;&&\n"" &$;  '^$&& \n""  &%$%$@#&  \n","   %&$    \n"" $&^*&    \n""&^  $&    \n""    &#    \n""    %&    \n""    #&    \n""&%$%@$@%$#\n"," ,&%$$&.\n""&%'  '^&\n""    !&&!\n""  ,&&:  \n"".&&^.   \n""&%$@&$$&\n","  #$%^$ \n"" %^   :&\n""    $%@ \n"" &,   '$\n""  %#$&# \n","$     %\n""$     &\n""*&#&$!%\n""     '$\n""      &\n",":-><;+*\n""&      \n""$&*<*<;\n""      $\n""'&*-&' \n","*&$#&% \n""&      \n""$&*<*<)\n""&     $\n""'%*^&&^\n","&%$@&$$&%;\n""      '@; \n""  --+*&!+-\n""    ;&:'  \n""  !&;'    \n"" !%'      \n"," *;&&%@:* \n"":&      &!\n""!#      ;&\n"" ;@<*&&!* \n"":&      &!\n""!#      ;&\n"" ;@<*&&!* \n"," *;&&%@:* \n"":&      &!\n""!#      ;&\n"" ;@<*&&!+&\n""        !&\n""        ;&\n""        !&\n"
    } ;
   
    string word;

    bool flag = true;
    while (flag) {
        cout << "Welcome to Giant Letters!! Please enter the letters / words you would like to have BIGIFYIED: \n";
        
        getInput(word);
    
        indexString(word);
    
        cout << "\n\n";
    
        printLetters(word, letters);
        
        cout << "\nWould you like to enter another word? (Y/N) ";

        while (true) {
            input = tolower(_getch());
            if (input == 'y' || input == 'n') {
                cout << input << endl;
                break;
            }
        }

            switch (input) {

                case 'n': case 'N': {
                        cout << "Thank you! Press any key to exit...";
                        flag = false;
                        _getche();
                        break;
                }

                case 'y': case 'Y': {
                    cout << "Alright!\n\n";
                    break;
                }
            }

    }
    
    return 0;
}