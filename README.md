## About The Project

This project is a hobby endeavor aimed at porting the Zelda game from a Python repository to C++, with the purpose of facilitating learning and development.

Author:
- YouTube: https://www.youtube.com/watch?v=QU1pPzEGrqw
- Git Repository: https://github.com/clear-code-projects/Zelda

Features:
- CMake Build System
- Google Test
- Continuous Integration and Development with Github Workflows
- Generated Installer

### Built With

* [![SFML][SFML-icon]][SFML-url]

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Project Structure

This project is structured into two executables and a shared static library. The reason for this structure is that Google Test, a testing framework, requires the application code to be in its own separate binary. To achieve this, it is recommended to encapsulate the application logic in a common library, which can be shared between the two executables. One executable is used for running the game itself, while the other executable is dedicated to running tests using Google Test. This approach ensures a clear separation between the application and the testing components.

The main entry point of the project is the bootstrap directory, which contains minimal code necessary to invoke the functionality provided by the static library and start running the game. The purpose of the bootstrap directory is to serve as a lightweight starting point that facilitates the connection between the application's executable and the functionality encapsulated within the static library. By calling into the static library, the game is launched and can begin its execution.

Similarly, the tests directory contains the source files for testing.

## Getting Started

This project utilizes CMake with the Visual Studio 16 2019 multi-target generator. It should be possible to generate build files for other build chains and platforms with minimal adjustments, if required.

The project also includes Visual Studio Code configuration files in the `.vscode` directory, which enable setting up the Debug configuration and CMake configuration.

To get started, clone the repository to a local destination using git:

```
git clone --recursive https://github.com/twje/cpp_zelda.git
```

Ensure that you perform a --recursive clone to fetch all submodules.

Next, run the batch `scripts` from the scripts directory to configure and build the application. You may need to modify the command line arguments to fit your requirements:

Configure:
```
>> configure.bat`
```

Build:
```
>> build.bat
```

Test:
```
<TBA>
```

Install:
```
<TBA>
```

<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[SFML-icon]: https://www.sfml-dev.org/images/logo.png
[SFML-url]: https://www.sfml-dev.org/

## License

Distributed under the MIT License. See [LICENSE.txt](LICENSE.txt) for more information.

## Acknowledgments

- [clear-code-projects](https://github.com/clear-code-projects)