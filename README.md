# IndoorGMLParser

This is informal parser of OGC(Open Geospatial Consortium) IndoorGML in C++.
And this project is under development so please wait if you use this till releasing.

It is supported by Visual Studio Community 2015 version.
Before using this, several things need to be checked : 
- This project is built at x64 env. Please check your platform information at Properties of the project.
- set 'Runtime Library' as '/MDd' at at properties> Configuration Properties> Code Generation
- Set 'PATH=$(SolutionDir)external/xercesc/dll;' at properties> Configuration Properties> Debugging> Environment.
- Set 'XERCES_STATIC_LIBRARY;XML_LIBRARY' at properties> Configuration Properties> C/C++> Preprocessor> Preprocessor Definitions.
