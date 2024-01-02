# Welcome to the Pomodoro project
 this is  Pomodoro Timer that i made using c++(cpp),i used the ncurses library.If you dont know what this is than: (ClickHERE)[https://en.wikipedia.org/wiki/Pomodoro_Technique].**I wrote the code in 3 different files** .I built a menu for the user to choose if he want the stantard Pomodoro Timer which its start from (25 min and 5 min break) or he can choose the minutes for his Pomodoro Timer. Also i added after you finish the Timer and the session completed and the worktime are saved to a file and you can see all the saved data from previous runs from the menu if you choose it.  



 

## How to compile

**FIRST** you need to download **ncurse library** 

**WINDOWS**
step1:
-Download and run the Cygwin installer from (cygwinInstall)[https://www.cygwin.com/install.html].
-during the installation, select the "libncurses-devel" package from the list of available packages.
step2:
-Install MSYS2 from (msys2Install)[https://www.msys2.org/].
-Open the MSYS2 terminal and run the following command to install ncurses:
        **pacman -S mingw-w64-x86_64-ncurses**  

**UBUNTU**
step1
-open a Terminal and run this commands
       **sudo apt update**
**sudo apt install libncurses5-dev libncursesw5-dev**

**macOS**
-open a Terminal and run this commands
step1:
**/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"**
step2:
**brew install ncurses**

after you done installing all this things, you can compile and link programs using the library. 
Remember to include the **-lncurses** flag during the compilation.


### Compile my code
to compile my code that i have written in 3 different files(Header file,source file,main file):

**-g++ main.cpp pomodoro.cpp -o Pomodoro -lncurses**



