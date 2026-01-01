# </> Corkus-CLI </>

## Pop the cork on your mods!

## ©2026 RavagerStudio > License: GPL-3.0

### FOR RED HAT LINUX FOLKS AN RPM IS AVAILABLE NOW IN CORKUS RELEASES

## Overview

> A straightforward tool for creating ModInfo.xml files for 7 Days to Die Modlets, developed in C++ & corkml.
>
> Now in version 2.0 (EARLY ACCESS), The app will create whole mod folders ready for any dev to make a modlet with
> different {xml skeletons and templates for each(TESTING PHASE)}
>
>Takes your input to name the Directories and has pre-configured skeleton options based on recent 7dtd files
>
> Verify your .cork config files with a unique stored key every time you generate
>
> The configs use an xml spinoff for the app called [corkml](#corkml), since cml is common markup language already.
>
> It is recommended you generate & fill out
> the [un.cork](https://github.com/XxRaVaGeRxX/corkus-cli/blob/master/Build-Scripts/Linux/build/un.cork) for smooth
> workflows
>
> FLOSS 7 Days To Die Modlet Structure Generator
>
> Enjoy the simplicity of a one click file generation app - Choose to set up after first run with `un.cork` - Generate
> in app
>
> Corkus will auto-detect and generate a `.cork & .keys` if you delete your original copy but at this time if you delete
`.keys` only, - you will have to regenerate both files, which corkus does automatically at runtime by simply checking
> the directory its in for the files which if they do not exist are then created and signed with a new generated KEY
>
>This makes it so a new key will be made and encrypted into a .keys file for corkus. corkml will check your inputs and
> give errors if an input value is incorrect or if the .cork file key does not match your .keys vault. `un.cork` is
> unusual, but a key helps confirm its a Corkus document. For both you and Corkus, & plain-text hash is shown during runtime.
> Straight commandline tools are not out of testing yet.
>
> Turn off Auto Generation to "save" your config.
>
> Wiki with more detailed instructions/changelog coming soon.
>
> `Time to pop the cork on your mod workflow`

## Features

> Friendly CLI interface
>
>Quick and easy file generation
>
>Cross-platform compatibility with CMake
>
>Now has an `un.cork` file for setting user defaults

## Usage

> Clone the repository
>
>Build from source with CMake for your platform, instructions below.
>
>Run the executable {NO WINDOWS EXE @ this time} and follow the terminal prompts to generate your Modlet file.
>
>Alternatively run the terminal prompts once to where it asks if you have an un.cork, that will proceed to a generation
> if you say no. Then from there corkus should read and write the files based off your custom un.cork file in the same
> directory
>
>`POP THAT MODLET WORKFLOW CORK!`

## Linux

##### CMake

> Ensure you have a recent CMake at least v3.5
>
>Clone the repo
>
>     git clone https://github.com/XxRaVaGeRxX/Corkus.git
>
> `cd` into the repo location
>
> Then `cd /Build-Scripts/Linux`
>
>Run this command in the same directory - Gives permission to execute
>
>     chmod +x build.sh
>
>Then run this command - CMake Build Script for Linux
>
>     ./build.sh
>
>Then run the program still in the repo directory and it should run in the terminal
>
>     ./build/corkus

##### Pre-Compiled Executable

> Or try the pre-compiled executable in the build folder
>
>Download linux executable in
> the [build folder](https://github.com/XxRaVaGeRxX/corkus-cli/tree/master/Build-Scripts/Linux/build)
>
>Give it permission to run with `chmod +x ./corkus` in appropriate directory
>
>Then run the executable with `./Corkus`
>
>`OR CLICK THE EXE in the path you want to create!!`

##### Linux RPM is now available
>Pre-Release
>
>More Coming Soon

## Windows

> Please Note: Windows is not officially supported yet. I do not own a Windows machine to test on.
>
> If any windows user wants to help out, please feel free to submit a pull request.
>
>Ensure you have a recent CMake
>
>Start by cloning the repo
>
>`cd` into the repo directory
>
>`cd /Build-Scripts/Windows`
>
>Run the build.bat file
>
> `cd` into the repo directory
>
> `cd /build`
>
> `corkus.exe`

## Corkml

### Current corkml structure for the generated `.cork & un.cork`

    <?corkml version="0.1" encoding="UTF-8"?>
    <CORKFILE>
      <corkml version="2.0" type="default">
        <config>
          <ModInfo>...</ModInfo>
          <XML>...</XML>
          <Corkus>...</Corkus>
        </config>
        <KEY>64_hex_characters_here</KEY>
      </corkml>
    </CORKFILE>`

## CommandLine (**WARNING: IN TEST PHASE**)

> ./corkus before all Example: ./corkus --new-cork
>
> The RPM package install will remove the need for the ./corkus command
>
> Keep in mind that the RPM is actively lowercase `corkus` for cli
>
> --install // Adds Corkus to PATH, shows a menu to choose the path location (Tested For Installation to the bashrc
> Only, Use Discretion removing automatically)
>
> --new-cork // Generate new .cork, corkus default config
>
>--new-uncork // Generate new un.cork, primary user config folder
>
>--skeleton // MENU WORKS BUT NOT LOGICALLY LINED UP YET WILL MAKE THE FILE. Creates a Single or Multiple xml by choice
> like items.xml
>
> --build // Build just a ModInfo.xml from current config
>
>--clean // Clean all config files .keys, .cork, & un.cork
>
>--validate -filehere- // Validate a corkml file/Check user errors in corkml un.cork
>
>--verify-keys // Verify keys in .keys match in the .cork and un.cork
>
>--list-skeletons // show skeletons available with identifying integer
>
> -h or -help // shows verbose help menu
>
> -v or -version // version info
