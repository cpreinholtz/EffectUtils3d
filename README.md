# Example arduino library
Open source under the MIT License


Checkout https://arduino.github.io/arduino-cli/0.29/library-specification/


Using this repo:
create new repo from this repo
update library properties* important if wanting to actually publish to arduino libs
Add src files
Add tests, run tests
Add examples



Directory structure  
Root
    |-.h and .cpp (for arduino libs sources must be in root folder)
    |-VS (THIS DIRECTORY IS IGNORED in the gitignore, just used for setting up Visual Studio projects for testing and debugging)
    |-Test (constains sources specifically for testing)
    |-src
        |-.h and .cpp (for arduino libs sources must be in root folder or root/src)
    |-Examples 
        |-ExScetch (contains ExScetch.ino for arduino IDE usage)